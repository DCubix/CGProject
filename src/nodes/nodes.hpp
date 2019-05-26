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
		int ix = int(image.width() * x);
		int iy = int(image.height() * y);
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
		Color na = color(0);
		Color nb = color(1);
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
		Color na = color(0);
		Color nb = color(1);
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
		int ix = int(in.width() * x);
		int iy = int(in.height() * y);
		float lm = luma(color(0));
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
		int ix = int(in.width() * x);
		int iy = int(in.height() * y);
		Color maxValue;
		const int m = int(size) / 2;
		for (int i = -m; i <= m; i++) {
			for (int j = -m; j <= m; j++) {
				Color tmp = in.get(ix + i, iy + j);
				maxValue.r = std::max(tmp.r, maxValue.r);
				maxValue.g = std::max(tmp.g, maxValue.g);
				maxValue.b = std::max(tmp.b, maxValue.b);
				maxValue.a = tmp.a;
			}
		}
		return maxValue;
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
		int ix = int(in.width() * x);
		int iy = int(in.height() * y);
		Color minValue;
		const int m = int(size) / 2;
		for (int i = -m; i <= m; i++) {
			for (int j = -m; j <= m; j++) {
				Color tmp = in.get(ix + i, iy + j);
				minValue.r = std::min(tmp.r, minValue.r);
				minValue.g = std::min(tmp.g, minValue.g);
				minValue.b = std::min(tmp.b, minValue.b);
				minValue.a = tmp.a;
			}
		}
		return minValue;
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
		int ix = int(in.width() * x);
		int iy = int(in.height() * y);
		const int w = 3;
		const int mean = w / 2;

		Color sum = color(0);
		for (int n = -mean; n <= mean; n++) {
			for (int m = -mean; m <= mean; m++) {
				if (n == 0 && m == 0) continue;
				Color col = in.get(ix + n, iy + m);
				float kv = KERNEL[int(filter)][(n + mean) + (m + mean) * w];
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
		int ix = int(in.width() * x);
		int iy = int(in.height() * y);

		std::vector<Color> v;
		const int m = int(size) / 2;

		v.reserve(m * m);

		for (int ky = -m; ky <= m; ky++) {
			for (int kx = -m; kx <= m; kx++) {
				int ox = kx + ix;
				int oy = ky + iy;
				v.push_back(in.get(ox, oy));
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

#endif // NODES_HPP
