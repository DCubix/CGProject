#include <iostream>
#include <filesystem>
#include <memory>

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
//		auto img = sys->process(imo->image);
//		stbi_write_png("tst.png", img.width(), img.height(), 4, img.data().data(), 4 * img.width());

		gui->load(
					#include "ui.h"
		);

		cnv = gui->create<NodeCanvas>();
		cnv->configure(0, 0);

		Button* btnOpen = gui->get<Button>("btnOpen");
		Button* btnSave = gui->get<Button>("btnSave");

		gui->get<Panel>("pnlView")->add(cnv);

		NodeSystem* sys = cnv->system();

		btnOpen->onClick([=](int btn, int x, int y) {
			auto ret = osd::Dialog::file(
						osd::DialogAction::OpenFile,
						".",
						osd::Filters("Imagens:jpg,png,bmp,tga,psd,hdr,gif,pic,pgm,ppm")
			);

			if (ret.has_value() && fs::exists(fs::path(ret.value()))) {

				btnSave->enabled(false);
				btnSave->onExit();
			}
		});

		btnSave->onClick([=](int btn, int x, int y) {
			auto ret = osd::Dialog::file(
						osd::DialogAction::SaveFile,
						".",
						osd::Filters("Imagem PNG:png")
			);

			if (ret.has_value()) {
				stbi_write_png(ret.value().c_str(), dataB.width(), dataB.height(), 4, dataB.data().data(), 4 * dataB.width());
			}
		});
	}

	NodeCanvas* cnv;

	PixelData dataA, dataB;
};

int main(int argc, char** argv) {
	return App().run("Image Studio");
	//return 0;
}
