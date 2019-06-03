#include <iostream>
#include <memory>

#include "widgets/list.h"
#include "widgets/check.h"
#include "widgets/label.h"
#include "widgets/imageview.h"
#include "widgets/button.h"
#include "widgets/spinner.h"
#include "widgets/colorpicker.h"

#include "stb_image_write.h"

#include "osdialog/OsDialog.hpp"

#include "image.h"
#include "application.h"
#include "nodes/node_logic.h"
#include "nodes/nodes.hpp"
#include "nodes/scriptable_node.hpp"
#include "node_canvas.h"

#include "filesystem.hpp"

namespace fs = ghc::filesystem;

class App : public Application {
public:
	void onBuild(GUI* gui) override {
		gui->load(
			#include "ui.h"
		);

		Panel* pnlParams = gui->get<Panel>("pnlParams");

		cnv = gui->create<NodeCanvas>();
		cnv->configure(0, 0);

		Button* btnOpen = gui->get<Button>("btnOpen");
		Button* btnSave = gui->get<Button>("btnSave");
		Button* btnSaveAs = gui->get<Button>("btnSaveAs");
		Button* btnSaveImg = gui->get<Button>("btnSaveImg");
		Button* btnAdd = gui->get<Button>("btnAdd");
		Button* btnDel = gui->get<Button>("btnDel");
		List* lstNodes = gui->get<List>("lstNodes");

		spnWidth = gui->get<Spinner>("spnWidth");
		spnHeight = gui->get<Spinner>("spnHeight");

		imgResult = gui->get<ImageView>("imgResult");

		gui->get<Panel>("pnlView")->add(cnv);

		NodeSystem* sys = cnv->system();

		auto onChange = [=](){ saved = false; };

		spnWidth->onChange([=](float v) {
			int w = int(v);
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h);
		});

		spnHeight->onChange([=](float v) {
			int w = int(spnWidth->value());
			int h = int(v);
			process(imgResult, gui, w, h);
		});

		cnv->onConnect([=]() {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h);
			onChange();
		});

		cnv->onSelect([=](Node* node) {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());

			#define Proc(v) ((Widget*)v)->onRelease(processImage)
			auto&& processImage = [=](int b, int x, int y) {
				int w = int(spnWidth->value());
				int h = int(spnHeight->value());
				process(imgResult, gui, w, h);
			};

			pnlParams->removeAll();
			if (node) {
				btnDel->enabled(true);
				btnDel->onExit();

				switch (node->type()) {
					case NodeType::Color: {
						ColorNode* n = (ColorNode*) node;

						ColorPicker* cp = gui->create<ColorPicker>();
						cp->color(n->color);

						((Widget*) cp)->onPress([=](int b, int x, int y) {
							n->color = cp->color();
						});
						((Widget*) cp)->onMove([=](int x, int y) {
							n->color = cp->color();
						});

						((Widget*) cp)->onRelease([=](int b, int x, int y) {
							n->color = cp->color();
							processImage(b, x, y);
						});
						pnlParams->add(cp);

						Spinner* sv = gui->spinner(
							&cp->value(),
							0.0f, 1.0f, LL(" Value"), true, [=](){ n->color = cp->color(); onChange(); }, 0.01f
						);
						Proc(sv);
						sv->bounds().height = 20;
						pnlParams->add(sv);
					} break;
					case NodeType::Image: {
						ImageNode* n = (ImageNode*) node;

						Label* lblInfo = gui->create<Label>();
						lblInfo->text(LL("File") + ": " + (n->fileName.empty() ? LL("<empty>") : n->fileName));
						lblInfo->bounds().height = 80;
						lblInfo->wordWrap(true);

						Button* loadImg = gui->create<Button>();
						loadImg->text(LL("Open") + "...");
						loadImg->bounds().height = 20;
						loadImg->onClick([=](int b, int x, int y) {
							auto ret = osd::Dialog::file(
										osd::DialogAction::OpenFile,
										".",
										osd::Filters("Images:jpg,png,bmp,tga,psd,hdr,gif,pic,pgm,ppm")
							);

							if (ret.has_value() && fs::exists(fs::path(ret.value()))) {
								n->image = PixelData(ret.value());
								spnWidth->value(n->image.width());
								spnHeight->value(n->image.height());
								process(imgResult, gui, int(spnWidth->value()), int(spnHeight->value()));
								onChange();

								fs::path rel = fs::relative(fs::path(ret.value()));
								n->fileName = rel.string();
								lblInfo->text(LL("File") + ": " + (n->fileName.empty() ? LL("<empty>") : n->fileName));
							}
						});
						pnlParams->add(loadImg);
						pnlParams->add(lblInfo);

					} break;
					case NodeType::Threshold: {
						ThresholdNode* n = (ThresholdNode*) node;
						Spinner* th = gui->spinner(
							&n->threshold,
							0.0f, 1.0f, LL(" Threshold"), true, onChange, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Dilate: {
						DilateNode* n = (DilateNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							3.0f, 9.0f, LL(" Size"), true, onChange, 1
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::Erode: {
						ErodeNode* n = (ErodeNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							3.0f, 9.0f, LL(" Size"), true, onChange, 1
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::Convolute: {
						ConvoluteNode* n = (ConvoluteNode*) node;
						List* rs = gui->create<List>();
						rs->list({
									 LL("Blur (Gaussian)"),
									 LL("Blur (Box)"),
									 LL("Sharpen"),
									 LL("Edges (Gauss)"),
									 LL("Edges (Laplace)"),
									 LL("Emboss"),
									 LL("Emboss (Edges)")
						});
						rs->selected(int(n->filter) - 1);
						rs->onSelected([=](int s) {
							n->filter = ConvoluteNode::Filter(s + 1);
							process(imgResult, gui, w, h);
						});
						pnlParams->add(rs);
					} break;
					case NodeType::Median: {
						MedianNode* n = (MedianNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							3.0f, 9.0f, LL(" Size"), true, onChange, 1
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::BrightnessContrast: {
						BrightnessContrastNode* n = (BrightnessContrastNode*) node;
						Spinner* bs = gui->spinner(
							&n->brightness,
							-1.0f, 5.0f, LL(" Brightness"), true, onChange, 0.01f
						);
						Proc(bs);
						bs->bounds().height = 20;
						pnlParams->add(bs);

						Spinner* cs = gui->spinner(
							&n->contrast,
							0.0f, 5.0f, LL(" Contrast"), true, onChange, 0.1f
						);
						Proc(cs);
						cs->bounds().height = 20;
						pnlParams->add(cs);
					} break;
					case NodeType::Mirror: {
						MirrorNode* n = (MirrorNode*) node;
						Check* rs = gui->create<Check>();
						rs->text("Vertical");
						rs->checked(n->vertical);
						rs->onChecked([=](bool v) {
							n->vertical = v;
							process(imgResult, gui, w, h);
						});
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::FishEye: {
						FishEyeNode* n = (FishEyeNode*) node;
						Spinner* rs = gui->spinner(
							&n->quant,
							0.0f, 4.0f, LL(" Size"), true, onChange, 0.01f
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::Add: {
						AddNode* n = (AddNode*) node;
						Spinner* th = gui->spinner(
							&n->factor,
							0.0f, 1.0f, LL(" Factor"), true, onChange, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Multiply: {
						MultiplyNode* n = (MultiplyNode*) node;
						Spinner* th = gui->spinner(
							&n->factor,
							0.0f, 1.0f, LL(" Factor"), true, onChange, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Mix: {
						MixNode* n = (MixNode*) node;
						Spinner* th = gui->spinner(
							&n->factor,
							0.0f, 1.0f, LL(" Factor"), true, onChange, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Distort: {
						DistortNode* n = (DistortNode*) node;
						Spinner* th = gui->spinner(
							&n->strenght,
							0.0f, 1.0f, LL(" Factor"), true, onChange, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					// case NodeType::Script: {
					// 	ScriptableNode* n = (ScriptableNode*) node;

					// 	Label* lblInfo = gui->create<Label>();
					// 	lblInfo->text(LL("File") + ": " + (n->fileName.empty() ? LL("<empty>") : n->fileName));
					// 	lblInfo->bounds().height = 80;
					// 	lblInfo->wordWrap(true);

					// 	Button* loadScp = gui->create<Button>();
					// 	loadScp->text(LL("Open") + "...");
					// 	loadScp->bounds().height = 20;

					// 	Button* reloadScp = gui->create<Button>();
					// 	reloadScp->text(LL("Reload"));
					// 	reloadScp->bounds().height = 20;

					// 	reloadScp->onClick([=](int b, int x, int y) {
					// 		if (!n->fileName.empty()) {
					// 			n->refresh();
					// 			process(imgResult, gui, int(spnWidth->value()), int(spnHeight->value()));
					// 			onChange();
					// 		}
					// 	});

					// 	loadScp->onClick([=](int b, int x, int y) {
					// 		if (!cnv->system()->getAllConnections(n->id()).empty()) {
					// 			osd::Dialog::message(
					// 						osd::MessageLevel::Error,
					// 						osd::MessageButtons::Ok,
					// 						LL("Error"),
					// 						LL("Please remove all the connections before reloading the script.")
					// 			);
					// 		} else {
					// 			auto ret = osd::Dialog::file(
					// 						osd::DialogAction::OpenFile,
					// 						".",
					// 						osd::Filters("Lua Script:lua")
					// 			);

					// 			if (ret.has_value() && fs::exists(fs::path(ret.value()))) {
					// 				fs::path rel = fs::relative(fs::path(ret.value()));
					// 				n->fileName = rel.string();
					// 				n->refresh();

					// 				lblInfo->text(LL("File") + ": " + (n->fileName.empty() ? LL("<empty>") : n->fileName));

					// 				process(imgResult, gui, int(spnWidth->value()), int(spnHeight->value()));
					// 				onChange();
					// 			}
					// 		}
					// 	});
					// 	pnlParams->add(loadScp);
					// 	pnlParams->add(reloadScp);
					// 	pnlParams->add(lblInfo);

					// } break;
					case NodeType::NormalMap: {
						NormalMapNode* n = (NormalMapNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							0.1f, 2.0f, LL(" Size"), true, onChange, 0.1f
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					default: break;
				}
			} else {
				btnDel->enabled(false);
				btnDel->onExit();
			}
		});

		btnAdd->onClick([=](int btn, int x, int y) {
			int selected = lstNodes->selected();
			switch (selected) {
				case 0: cnv->create<AddNode>(); break;
				case 1: cnv->create<MultiplyNode>(); break;
				case 2: cnv->create<ColorNode>(); break;
				case 3: cnv->create<ImageNode>(); break;
				case 4: cnv->create<ErodeNode>(); break;
				case 5: cnv->create<DilateNode>(); break;
				case 6: cnv->create<MedianNode>(); break;
				case 7: cnv->create<ConvoluteNode>(); break;
				case 8: cnv->create<ThresholdNode>(); break;
				case 9: cnv->create<BrightnessContrastNode>(); break;
				case 10: cnv->create<WebCamNode>(); break;
				case 11: cnv->create<MirrorNode>(); break;
				case 12: cnv->create<FishEyeNode>(); break;
				case 13: cnv->create<MixNode>(); break;
				case 14: cnv->create<InvertNode>(); break;
				case 15: cnv->create<DistortNode>(); break;
//				case 16: cnv->create<ScriptableNode>(); break;
				case 16: cnv->create<NormalMapNode>(); break;
				default: break;
			}
			onChange();
		});

		btnDel->onClick([=](int btn, int x, int y) {
			if (!cnv->selected().empty()) {
				for (auto id : cnv->selected()) sys->destroy(id);
				btnDel->enabled(false);
				btnDel->onExit();
				pnlParams->removeAll();
				onChange();
			}
		});

		auto fileOpen = [=]() {
			auto ret = osd::Dialog::file(
						osd::DialogAction::OpenFile,
						".",
						osd::Filters("Image Studio Project:isp")
			);
			if (ret.has_value() && fs::exists(fs::path(ret.value()))) {
				std::ifstream fp(ret.value());
				Json json; fp >> json;
				cnv->load(json);
				fp.close();
				saved = true;
				currentFileName = ret.value();

				int w = int(spnWidth->value());
				int h = int(spnHeight->value());
				process(imgResult, gui, w, h);
			}
		};

		auto fileSaveAs = [=](const std::string& fileName) {
			std::ofstream fp(fileName);
			Json json; cnv->save(json);
			fp << json;
			fp.close();
			saved = true;
			currentFileName = fileName;
		};

		auto fileSaveDialog = [=]() {
			auto ret = osd::Dialog::file(
						osd::DialogAction::SaveFile,
						".",
						osd::Filters("Image Studio Project:isp")
			);

			if (ret.has_value()) {
				fileSaveAs(ret.value());
			}
		};

		btnOpen->onClick([=](int btn, int x, int y) {
			if (!saved) {
				auto res = osd::Dialog::message(
							osd::MessageLevel::Warning,
							osd::MessageButtons::YesNo,
							LL("Warning"),
							LL("Your current project has not been saved, continue?")
				);
				if (res == osd::Dialog::ReturnType::Yes) {
					fileOpen();
				}
			} else {
				fileOpen();
			}
		});

		btnSave->onClick([=](int btn, int x, int y) {
			if (currentFileName.empty()) {
				fileSaveDialog();
			} else {
				fileSaveAs(currentFileName);
			}
		});

		btnSaveAs->onClick([=](int btn, int x, int y) {
			fileSaveDialog();
		});

		btnSaveImg->onClick([=](int btn, int x, int y) {
			auto ret = osd::Dialog::file(
						osd::DialogAction::SaveFile,
						".",
						osd::Filters("PNG Image:png")
			);

			if (ret.has_value()) {
				fs::path fp(ret.value());
				fp.replace_extension(".png");

				int w = int(spnWidth->value());
				int h = int(spnHeight->value());
				PixelData img = cnv->system()->process(PixelData(w, h));
				stbi_write_png(fp.string().c_str(), w, h, 4, img.dataCopy().data(), img.width() * 4);
			}
		});

	}

	inline void process(ImageView* res, GUI* gui, int w, int h) {
		PixelData img = cnv->system()->process(PixelData(w, h));
		if (result) {
			result.reset();
		}
		result = std::make_unique<Image>();
		result->load(gui->renderer(), img);
		res->image(result.get());
	}

	inline virtual void onTick(GUI* gui, float dt) override {
		if (cnv->system()->capturing() && cnv->system()->hasFrame()) {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h);
		}
	}

	NodeCanvas* cnv;
	std::unique_ptr<Image> result;
	float utime{ 0.0f };

	ImageView* imgResult;
	Spinner* spnWidth;
	Spinner* spnHeight;

	std::string currentFileName;
	bool saved{ false };
};

int main(int argc, char** argv) {
	return App().run("Image Studio", 800, 600);
	//return 0;
}
