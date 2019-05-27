#ifndef NODES_HPP
#define NODES_HPP

#include "node_logic.h"

inline static float luma(Color col) {
	return col.r * 0.299f + col.g * 0.587f + col.b * 0.114f;
}

class ColorNode : public Node {
public:
	inline virtual Color process(const PixelData& in, float x, float y) override {
		return color;
	}

	inline virtual NodeType type() override { return NodeType::Color; }

	Color color{ 0.0f, 0.0f, 0.0f, 1.0f };
};

class ImageNode : public Node {
public:
	inline virtual Color process(const PixelData& in, float x, float y) override {
		int ix = int((image.width()+0.5f) * x);
		int iy = int((image.height()+0.5f) * y);
		return image.get(ix, iy);
	}

	inline virtual NodeType type() override { return NodeType::Image; }

	PixelData image{ };
};

class MultiplyNode : public Node {
public:
	inline MultiplyNode() {
		addParam("A");
		addParam("B");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		auto&& pb = param(1).value;

		int xa = int((pa.width() + 0.5f) * x);
		int ya = int((pa.height() + 0.5f) * y);
		int xb = int((pb.width() + 0.5f) * x);
		int yb = int((pb.height() + 0.5f) * y);

		Color na = pa.get(xa, ya);
		Color nb = pb.get(xb, yb);
		return Color{ na.r * nb.r, na.g * nb.g, na.b * nb.b, na.a * nb.a };
	}

	inline virtual NodeType type() override { return NodeType::Multiply; }
};

class AddNode : public Node {
public:
	inline AddNode() {
		addParam("A");
		addParam("B");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		auto&& pb = param(1).value;

		int xa = int((pa.width() + 0.5f) * x);
		int ya = int((pa.height() + 0.5f) * y);
		int xb = int((pb.width() + 0.5f) * x);
		int yb = int((pb.height() + 0.5f) * y);

		Color na = pa.get(xa, ya);
		Color nb = pb.get(xb, yb);
		return Color{ na.r + nb.r, na.g + nb.g, na.b + nb.b, na.a + nb.a };
	}

	inline virtual NodeType type() override { return NodeType::Add; }
};

class ThresholdNode : public Node {
public:
	inline ThresholdNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);

		float lm = luma(pa.get(ix, iy));
		if (!locallyAdaptive) {
			float g = lm >= threshold ? 1.0f : 0.0f;
			return Color{ g, g, g, 1.0f };
		} else {
			const int m = int(regionSize) / 2;
			float sum = lm;
			for (int ky = -m; ky <= m; ky++) {
				for (int kx = -m; kx <= m; kx++) {
					if (kx == 0 && ky == 0) continue;
					Color col = in.get(kx + ix, ky + iy);
					sum += luma(col);
				}
			}
			sum /= ((regionSize * regionSize) + 1);

			float g = lm >= (sum * threshold) ? 1.0f : 0.0f;
			return Color{ g, g, g, 1.0f };
		}
	}

	inline virtual NodeType type() override { return NodeType::Threshold; }

	float threshold{ 0.5f };
	float regionSize{ 3 };
	bool locallyAdaptive{ false };
};

class DilateNode : public Node {
public:
	inline DilateNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);

		std::vector<Color> v;
		const int m = int(size) / 2;
		for (int i = -m; i <= m; i++) {
			for (int j = -m; j <= m; j++) {
				Color tmp = pa.get(ix + i, iy + j);
				v.push_back(tmp);
			}
		}

		return *std::min_element(v.begin(), v.end(), [](const Color& a, const Color& b) {
			return luma(a) > luma(b);
		});
	}

	inline virtual NodeType type() override { return NodeType::Dilate; }

	float size{ 3 };
};

class ErodeNode : public Node {
public:
	inline ErodeNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);
		
		std::vector<Color> v;
		const int m = int(size) / 2;
		for (int i = -m; i <= m; i++) {
			for (int j = -m; j <= m; j++) {
				Color tmp = pa.get(ix + i, iy + j);
				v.push_back(tmp);
			}
		}

		return *std::max_element(v.begin(), v.end(), [](const Color& a, const Color& b) {
			return luma(a) > luma(b);
		});
	}

	inline virtual NodeType type() override { return NodeType::Erode; }

	float size{ 3 };
};

static const float KERNEL[][9] = {
	{ 0.0625f, 0.125f, 0.0625f, 0.125f, 0.25f, 0.125f, 0.0625f, 0.125f, 0.0625f },
	{ 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f, 0.111111f },
	{ 0.0f, -1.0f, 0.0f, -1.0f, 5.0f, -1.0f, 0.0f, -1.0f, 0.0f },
	{ -0.0943852f, -0.155615f, -0.0943852f, -0.155615f, 1.0f, -0.155615f, -0.0943852f, -0.155615f, -0.0943852f },
	{ 0.0f, -1.0f, 0.0f, -1.0f, 4.0f, -1.0f, 0.0f, -1.0f, 0.0f },
	{ -2.0f, -1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f },
	{ 5.0f, -3.0f, -3.0f, 5.0f, 0.0f, -3.0f, 5.0f, -3.0f, -3.0f }
};

class ConvoluteNode : public Node {
public:
	enum Filter {
		GaussianBlur = 1,
		BoxBlur,
		Sharpen,
		EdgeGauss,
		EdgeLaplace,
		Emboss,
		EdgeEmboss
	};

	inline ConvoluteNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);
		
		const int w = 3;
		const int mean = w / 2;

		Color sum = { 0.0f, 0.0f, 0.0f, 1.0f };
		for (int n = -mean; n <= mean; n++) {
			for (int m = -mean; m <= mean; m++) {
				Color col = pa.get(ix + n, iy + m);
				float kv = KERNEL[int(filter) - 1][(n + mean) + (m + mean) * w];
				sum.r += col.r * kv;
				sum.g += col.g * kv;
				sum.b += col.b * kv;
				sum.a  = col.a;
			}
		}
		return sum;
	}

	inline virtual NodeType type() override { return NodeType::Convolute; }

	Filter filter{ Filter::GaussianBlur };
};

class MedianNode : public Node {
public:
	inline MedianNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);

		std::vector<Color> v;
		const int m = int(size) / 2;

		v.reserve(m * m);

		for (int ky = -m; ky <= m; ky++) {
			for (int kx = -m; kx <= m; kx++) {
				int ox = kx + ix;
				int oy = ky + iy;
				v.push_back(pa.get(ox, oy));
			}
		}

		std::sort(v.begin(), v.end(), [](const Color& a, const Color& b) {
			return luma(a) > luma(b);
		});

		return v[v.size() / 2];
	}

	inline virtual NodeType type() override { return NodeType::Median; }

	float size{ 3 };
};

class BrightnessContrastNode : public Node {
public:
	inline BrightnessContrastNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);

		Color na = pa.get(ix, iy);
		return {
			std::clamp(na.r * contrast + brightness, 0.0f, 1.0f),
			std::clamp(na.g * contrast + brightness, 0.0f, 1.0f),
			std::clamp(na.b * contrast + brightness, 0.0f, 1.0f),
			na.a
		};
	}

	inline virtual NodeType type() override { return NodeType::BrightnessContrast; }

	float brightness{ 0.0f }, contrast{ 1.0f };
};

class WebCamNode : public Node {
public:
	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = m_system->cameraFrame();
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);
		return pa.get(ix, iy);
	}

	inline virtual NodeType type() override { return NodeType::WebCam; }
};

class MirrorNode : public Node {
public:
	inline MirrorNode() {
		addParam("A");
	}

	inline float cyclef(float f) {
		auto m2 = std::fmod(f, 2.0f);
		return m2 < 1.0 ? m2 : 2 - m2;
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		float mx = cyclef(x * 2.0f) * 0.5f;
		float my = y;
		if (vertical) {
			my = cyclef(y * 2.0f) * 0.5f;
		}
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * mx);
		int iy = int((pa.height()+0.5f) * my);
		return pa.get(ix, iy);
	}

	inline virtual NodeType type() override { return NodeType::Mirror; }

	bool vertical{ false };
};

class FishEyeNode : public Node {
public:
	inline FishEyeNode() {
		addParam("A");
	}

	inline std::tuple<float, float> distort(float px, float py) {
		float theta  = std::atan2(py, px);
		float radius = std::sqrt(px * px + py * py);
		radius = std::pow(radius, quant);
		px = radius * std::cos(theta);
		py = radius * std::sin(theta);
		return { 0.5f * (px + 1.0f), 0.5f * (py + 1.0f) };
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;

		float fx = x * 2.0f - 1.0f;
		float fy = y * 2.0f - 1.0f;

		auto uv = std::make_tuple(0.0f, 0.0f);
		float d = std::sqrt(fx * fx + fy * fy);
		if (d < 1.0f) {
			uv = distort(fx, fy);
		} else {
			uv = std::make_tuple(x, y);
		}

		int ix = int((pa.width()+0.5f) * std::get<0>(uv));
		int iy = int((pa.height()+0.5f) * std::get<1>(uv));
		return pa.get(ix, iy);
	}

	inline virtual NodeType type() override { return NodeType::FishEye; }

	float quant{ 1.0f };

};

#endif // NODES_HPP
