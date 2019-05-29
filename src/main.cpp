#include <iostream>
#include <filesystem>
#include <memory>

#include "widgets/list.h"
#include "widgets/check.h"
#include "widgets/label.h"
#include "widgets/imageview.h"
#include "widgets/button.h"
#include "widgets/spinner.h"

#include "stb_image_write.h"

#include "osdialog/OsDialog.hpp"

#include "image.h"
#include "application.h"
#include "nodes/node_logic.h"
#include "nodes/nodes.hpp"
#include "node_canvas.h"

namespace fs = std::filesystem;

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
		Button* btnAdd = gui->get<Button>("btnAdd");
		Button* btnDel = gui->get<Button>("btnDel");
		Button* btnProc = gui->get<Button>("btnProc");
		List* lstNodes = gui->get<List>("lstNodes");

		chkHalf = gui->get<Check>("chkHalf");
		spnWidth = gui->get<Spinner>("spnWidth");
		spnHeight = gui->get<Spinner>("spnHeight");

		imgResult = gui->get<ImageView>("imgResult");

		gui->get<Panel>("pnlView")->add(cnv);

		NodeSystem* sys = cnv->system();

		chkHalf->onChecked([=](bool v) {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h, v);
		});

		cnv->onConnect([=]() {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h, chkHalf->checked());
		});

		cnv->onSelect([=](Node* node) {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());

			#define Proc(v) ((Widget*)v)->onRelease(processImage)
			auto&& processImage = [=](int b, int x, int y) {
				int w = int(spnWidth->value());
				int h = int(spnHeight->value());
				process(imgResult, gui, w, h, chkHalf->checked());
			};

			pnlParams->removeAll();
			if (node) {
				btnDel->enabled(true);
				btnDel->onExit();

				switch (node->type()) {
					case NodeType::Color: {
						ColorNode* n = (ColorNode*) node;
						Spinner* sr = gui->spinner(
							&n->color.r,
							0.0f, 1.0f, " R", true, nullptr, 0.01f
						);
						sr->bounds().height = 20;
						Proc(sr);
						pnlParams->add(sr);

						Spinner* sg = gui->spinner(
							&n->color.g,
							0.0f, 1.0f, " G", true, nullptr, 0.01f
						);
						Proc(sg);
						sg->bounds().height = 20;
						pnlParams->add(sg);

						Spinner* sb = gui->spinner(
							&n->color.b,
							0.0f, 1.0f, " B", true, nullptr, 0.01f
						);
						Proc(sb);
						sb->bounds().height = 20;
						pnlParams->add(sb);

						Spinner* sa = gui->spinner(
							&n->color.a,
							0.0f, 1.0f, " A", true, nullptr, 0.01f
						);
						Proc(sa);
						sa->bounds().height = 20;
						pnlParams->add(sa);
					} break;
					case NodeType::Image: {
						ImageNode* n = (ImageNode*) node;
						Button* loadImg = gui->create<Button>();
						loadImg->text("Abrir...");
						loadImg->bounds().height = 20;
						loadImg->onClick([=](int b, int x, int y) {
							auto ret = osd::Dialog::file(
										osd::DialogAction::OpenFile,
										".",
										osd::Filters("Imagens:jpg,png,bmp,tga,psd,hdr,gif,pic,pgm,ppm")
							);

							if (ret.has_value() && fs::exists(fs::path(ret.value()))) {
								n->image = PixelData(ret.value());
								spnWidth->value(n->image.width());
								spnHeight->value(n->image.height());
								process(imgResult, gui, w, h, chkHalf->checked());
							}
						});
						pnlParams->add(loadImg);
					} break;
					case NodeType::Threshold: {
						ThresholdNode* n = (ThresholdNode*) node;
						Spinner* th = gui->spinner(
							&n->threshold,
							0.0f, 1.0f, " Limiar", true, nullptr, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Dilate: {
						DilateNode* n = (DilateNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							3.0f, 9.0f, " Tamanho", true, nullptr, 1
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::Erode: {
						ErodeNode* n = (ErodeNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							3.0f, 9.0f, " Tamanho", true, nullptr, 1
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::Convolute: {
						ConvoluteNode* n = (ConvoluteNode*) node;
						List* rs = gui->create<List>();
						rs->list({
									 "Borrar (Gaussiano)",
									 "Borrar (Caixa)",
									 "Agucar",
									 "Bordas (Gauss)",
									 "Bordas (Laplace)",
									 "Relevo",
									 "Relevo (Bordas)",
						});
						rs->selected(int(n->filter) - 1);
						rs->onSelected([=](int s) {
							n->filter = ConvoluteNode::Filter(s + 1);
							process(imgResult, gui, w, h, chkHalf->checked());
						});
						pnlParams->add(rs);
					} break;
					case NodeType::Median: {
						MedianNode* n = (MedianNode*) node;
						Spinner* rs = gui->spinner(
							&n->size,
							3.0f, 13.0f, " Tamanho", true, nullptr, 1
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::BrightnessContrast: {
						BrightnessContrastNode* n = (BrightnessContrastNode*) node;
						Spinner* bs = gui->spinner(
							&n->brightness,
							-1.0f, 5.0f, " Brilho", true, nullptr, 0.01f
						);
						Proc(bs);
						bs->bounds().height = 20;
						pnlParams->add(bs);

						Spinner* cs = gui->spinner(
							&n->contrast,
							0.0f, 5.0f, " Contraste", true, nullptr, 0.1f
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
							process(imgResult, gui, w, h, chkHalf->checked());
						});
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::FishEye: {
						FishEyeNode* n = (FishEyeNode*) node;
						Spinner* rs = gui->spinner(
							&n->quant,
							0.0f, 4.0f, " Tamanho", true, nullptr, 0.01f
						);
						Proc(rs);
						rs->bounds().height = 20;
						pnlParams->add(rs);
					} break;
					case NodeType::Add: {
						AddNode* n = (AddNode*) node;
						Spinner* th = gui->spinner(
							&n->factor,
							0.0f, 1.0f, " Fator", true, nullptr, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Multiply: {
						MultiplyNode* n = (MultiplyNode*) node;
						Spinner* th = gui->spinner(
							&n->factor,
							0.0f, 1.0f, " Fator", true, nullptr, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Mix: {
						MixNode* n = (MixNode*) node;
						Spinner* th = gui->spinner(
							&n->factor,
							0.0f, 1.0f, " Fator", true, nullptr, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
					} break;
					case NodeType::Distort: {
						DistortNode* n = (DistortNode*) node;
						Spinner* th = gui->spinner(
							&n->strenght,
							0.0f, 1.0f, " Fator", true, nullptr, 0.01f
						);
						Proc(th);
						th->bounds().height = 20;
						pnlParams->add(th);
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
				default: break;
			}
		});

		btnDel->onClick([=](int btn, int x, int y) {
			if (!cnv->selected().empty()) {
				for (auto id : cnv->selected()) sys->destroy(id);
				btnDel->enabled(false);
				btnDel->onExit();
				pnlParams->removeAll();
			}
		});

		btnOpen->onClick([=](int btn, int x, int y) {
//			auto ret = osd::Dialog::file(
//						osd::DialogAction::OpenFile,
//						".",
//						osd::Filters("Imagens:jpg,png,bmp,tga,psd,hdr,gif,pic,pgm,ppm")
//			);

//			if (ret.has_value() && fs::exists(fs::path(ret.value()))) {

//			}
		});

		btnSave->onClick([=](int btn, int x, int y) {
//			auto ret = osd::Dialog::file(
//						osd::DialogAction::SaveFile,
//						".",
//						osd::Filters("Imagem PNG:png")
//			);

//			if (ret.has_value()) {
//				stbi_write_png(ret.value().c_str(), dataB.width(), dataB.height(), 4, dataB.data().data(), 4 * dataB.width());
//			}
		});

		btnProc->onClick([=](int btn, int x, int y) {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h, chkHalf->checked());
		});

	}

	inline void process(ImageView* res, GUI* gui, int w, int h, bool half) {
		PixelData img = cnv->system()->process(PixelData(w, h), half);
		if (!result || (result && result->width() != img.width() || result->height() != img.height())) {
			result.reset();
			result = std::make_unique<Image>();
		}
		result->load(gui->renderer(), img);
		res->image(result.get());
	}

	inline virtual void onTick(GUI* gui, float dt) override {
		if (cnv->system()->capturing() && cnv->system()->hasFrame()) {
			int w = int(spnWidth->value());
			int h = int(spnHeight->value());
			process(imgResult, gui, w, h, chkHalf->checked());
		}
	}

	NodeCanvas* cnv;
	std::unique_ptr<Image> result;
	float utime{ 0.0f };

	ImageView* imgResult;
	Check* chkHalf;
	Spinner* spnWidth;
	Spinner* spnHeight;
};

int main(int argc, char** argv) {
	return App().run("Image Studio");
	//return 0;
}
