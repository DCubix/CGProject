#include <iostream>
#include <filesystem>

#include "widgets/check.h"
#include "widgets/label.h"
#include "widgets/imageview.h"
#include "widgets/button.h"
#include "widgets/spinner.h"

#include "stb_image_write.h"
#include "filters.hpp"

#include "osdialog/OsDialog.hpp"

#include "application.h"

namespace fs = std::filesystem;

class App : public Application {
public:
	void onBuild(GUI* gui) override {
		gui->load(
					#include "ui.h"
		);

		median = std::unique_ptr<Filter>(new filters::MedianFilter());
		dilation = std::unique_ptr<Filter>(new filters::DilationFilter());
		erosion = std::unique_ptr<Filter>(new filters::ErosionFilter());
		threshold = std::unique_ptr<Filter>(new filters::ThresholdFilter());
		edge = std::unique_ptr<Filter>(new filters::EdgeDetectionFilter());
		blur = std::unique_ptr<Filter>(new filters::BlurFilter());

		Button* btnOpen = gui->get<Button>("btnOpen");
		Button* btnSave = gui->get<Button>("btnSave");
		Button* btnDilation = gui->get<Button>("btnDilation");
		Button* btnErosion = gui->get<Button>("btnErosion");
		Button* btnEdge = gui->get<Button>("btnEdge");
		Button* btnMedian = gui->get<Button>("btnMedian");
		Button* btnBox = gui->get<Button>("btnBox");
		Button* btnThreshold = gui->get<Button>("btnThreshold");
		Button* btnApply = gui->get<Button>("btnApply");
		Button* btnSwap = gui->get<Button>("btnSwap");
		ImageView* A = gui->get<ImageView>("A");
		ImageView* B = gui->get<ImageView>("B");
		Label* lblFilter = gui->get<Label>("lblFilter");
		Panel* pnlParams = gui->get<Panel>("pnlParams");

		btnOpen->onClick([=](int btn, int x, int y) {
			auto ret = osd::Dialog::file(
						osd::DialogAction::OpenFile,
						".",
						osd::Filters("Imagens:jpg,png,bmp,tga,psd,hdr,gif,pic,pgm,ppm")
			);

			if (ret.has_value() && fs::exists(fs::path(ret.value()))) {
				if (!imgA) {
					imgA = std::make_unique<Image>();
				}
				if (imgB) {
					imgB.reset();
				}
				dataA = PixelData(ret.value());

				imgA->load(gui->renderer(), dataA);
				A->image(imgA.get());

				btnDilation->enabled(true);
				btnDilation->onExit();
				btnErosion->enabled(true);
				btnErosion->onExit();
				btnEdge->enabled(true);
				btnEdge->onExit();
				btnMedian->enabled(true);
				btnMedian->onExit();
				btnThreshold->enabled(true);
				btnThreshold->onExit();
				btnBox->enabled(true);
				btnBox->onExit();
				btnApply->enabled(true);
				btnApply->onExit();

				btnSave->enabled(false);
				btnSave->onExit();
				btnSwap->enabled(false);
				btnSwap->onExit();
			}
		});

		btnApply->onClick([=](int btn, int x, int y) {
			if (selected == nullptr) {
				if (!imgB) {
					imgB = std::make_unique<Image>();
				}
				dataB = PixelData(dataA.width(), dataA.height());
				for (int y = 0; y < dataB.height(); y++) {
					for (int x = 0; x < dataB.width(); x++) {
						Color c = dataA.get(x, y).value();
						dataB.set(x, y, c.r, c.g, c.b, c.a);
					}
				}
				imgB->load(gui->renderer(), dataB);
				B->image(imgB.get());
			} else {
				FilterStack fs{};
				dataB = fs.applyOne(selected, dataA);

				if (!imgB) {
					imgB = std::make_unique<Image>();
				}
				imgB->load(gui->renderer(), dataB);
				B->image(imgB.get());
			}
			btnSave->enabled(true);
			btnSave->onExit();
			btnSwap->enabled(true);
			btnSwap->onExit();
		});

		btnSwap->onClick([=](int btn, int x, int y) {
			if (imgB) {
				dataA = PixelData(dataB.width(), dataB.height());
				for (int y = 0; y < dataA.height(); y++) {
					for (int x = 0; x < dataA.width(); x++) {
						Color c = dataB.get(x, y).value();
						dataA.set(x, y, c.r, c.g, c.b, c.a);
					}
				}
				imgA->load(gui->renderer(), dataA);
			}
		});

		btnDilation->onClick([=](int btn, int x, int y) {
			selected = median.get();
			lblFilter->text("Dilatacao");
			pnlParams->removeAll();
		});

		btnErosion->onClick([=](int btn, int x, int y) {
			selected = erosion.get();
			lblFilter->text("Erosao");
			pnlParams->removeAll();
		});

		btnMedian->onClick([=](int btn, int x, int y) {
			selected = median.get();
			lblFilter->text("Mediano");

			pnlParams->removeAll();
			Spinner* spn = gui->create<Spinner>();
			spn->suffix(" Area");
			spn->minimum(3.0f);
			spn->maximum(13.0f);
			spn->step(1.0f);
			spn->value(((filters::MedianFilter*) median.get())->size());
			spn->configure(0, 0, 2);
			spn->onChange([&](float v) {
				((filters::MedianFilter*) median.get())->size(int(v));
			});
			pnlParams->add(spn);
		});

		btnThreshold->onClick([=](int btn, int x, int y) {
			selected = threshold.get();
			lblFilter->text("Limiar");

			auto th = ((filters::ThresholdFilter*) threshold.get());

			pnlParams->removeAll();
			Spinner* spnT = gui->create<Spinner>();
			spnT->suffix(" Limiar");
			spnT->minimum(0.0f);
			spnT->maximum(1.0f);
			spnT->step(0.01f);
			spnT->value(th->threshold());
			spnT->configure(0, 0, 2);
			spnT->onChange([=](float v) {
				th->threshold(v);
			});
			pnlParams->add(spnT);

			Spinner* spnA = gui->create<Spinner>();
			spnA->suffix(" Area");
			spnA->minimum(3.0f);
			spnA->maximum(9.0f);
			spnA->step(1.0f);
			spnA->value(th->regionSize());
			spnA->configure(0, 2, 2);
			spnA->onChange([=](float v) {
				th->regionSize(int(v));
			});
			pnlParams->add(spnA);

			Check* chkLA = gui->create<Check>();
			chkLA->text("Adaptativo");
			chkLA->configure(1, 0, 4);
			chkLA->checked(th->locallyAdaptive());
			chkLA->onChecked([=](bool v) {
				th->locallyAdaptive(v);
			});
			pnlParams->add(chkLA);
		});

		btnEdge->onClick([=](int btn, int x, int y) {
			selected = edge.get();
			lblFilter->text("Bordas");
			pnlParams->removeAll();
		});

		btnBox->onClick([=](int btn, int x, int y) {
			selected = blur.get();
			lblFilter->text("Borrar");
			pnlParams->removeAll();

			auto bf = ((filters::BlurFilter*) blur.get());

			Button* btnK3 = gui->create<Button>();
			btnK3->text("3x3");
			btnK3->configure(0, 0);
			btnK3->onClick([=](int b, int x, int y) { bf->kernelSize(kernels::KernelSize::K3x3); });
			pnlParams->add(btnK3);

			Button* btnK5 = gui->create<Button>();
			btnK5->text("5x5");
			btnK5->configure(0, 1);
			btnK5->onClick([=](int b, int x, int y) { bf->kernelSize(kernels::KernelSize::K5x5); });
			pnlParams->add(btnK5);

			Button* btnK9 = gui->create<Button>();
			btnK9->text("9x9");
			btnK9->configure(0, 2);
			btnK9->onClick([=](int b, int x, int y) { bf->kernelSize(kernels::KernelSize::K9x9); });
			pnlParams->add(btnK9);

			Button* btnK13 = gui->create<Button>();
			btnK13->text("13x13");
			btnK13->configure(0, 3);
			btnK13->onClick([=](int b, int x, int y) { bf->kernelSize(kernels::KernelSize::K13x13); });
			pnlParams->add(btnK13);

			Check* chkLA = gui->create<Check>();
			chkLA->text("Gaussiano");
			chkLA->configure(1, 0, 4);
			chkLA->checked(bf->gaussian());
			chkLA->onChecked([=](bool v) {
				bf->gaussian(v);
			});
			pnlParams->add(chkLA);
		});

		btnSave->onClick([=](int btn, int x, int y) {
			auto ret = osd::Dialog::file(
						osd::DialogAction::OpenFile,
						".",
						osd::Filters("Imagem PNG:png")
			);

			if (ret.has_value()) {
				stbi_write_png(ret.value().c_str(), dataB.width(), dataB.height(), 4, dataB.data().data(), 4 * dataB.width());
			}
		});
	}

	std::unique_ptr<Filter> median, dilation, erosion, threshold, edge, box, blur;

	PixelData dataA, dataB;
	ImagePtr imgA, imgB;
	Filter* selected{ nullptr };
};

int main(int argc, char** argv) {

	return App().run("Image Studio");
}
