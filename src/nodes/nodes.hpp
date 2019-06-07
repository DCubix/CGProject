#ifndef NODES_HPP
#define NODES_HPP

#include <algorithm>
#include <array>

#include "node_logic.h"
#include "filesystem.hpp"

namespace fs = ghc::filesystem;

inline static float luma(Color col) {
	return col.r * 0.299f + col.g * 0.587f + col.b * 0.114f;
}

class ColorNode : public Node {
public:
	inline virtual Color process(const PixelData& in, float x, float y) override {
		return color;
	}

	// inline virtual PixelData gpuProcess(const PixelData& in, bool half) override {
	// 	const size_t sz = in.width() * in.height();
	// 	cl::Buffer result(m_system->context(), CL_MEM_WRITE_ONLY, sz);
	// 	cl::Kernel k = cl::Kernel(m_system->program(), "ColorNode");

	// 	float col[] = { color.r, color.g, color.b, color.a };
	// 	k.setArg(0, sizeof(float) * 4, col);
	// 	k.setArg(1, result);
	// 	m_system->queue().enqueueNDRangeKernel(k, cl::NullRange, cl::NDRange(sz), cl::NullRange);
	// 	m_system->queue().finish();

	// 	PixelData out(in.width(), in.height());
	// 	m_system->queue().enqueueReadBuffer(result, CL_TRUE, 0, out.data().size(), &out.data()[0]);
	// 	return out;
	// }

	inline virtual NodeType type() override { return NodeType::Color; }

	virtual void load(const Json& json) override {
		auto col = json.value("color", Json::array({ 0.0f, 0.0f, 0.0f, 1.0f }));
		color.r = col[0];
		color.g = col[1];
		color.b = col[2];
		color.a = col[3];
	}

	virtual void save(Json& json) override {
		json["color"] = { color.r, color.g, color.b, color.a };
	}

	Color color{ 0.0f, 0.0f, 0.0f, 1.0f };
};

class ImageNode : public Node {
public:
	inline virtual Color process(const PixelData& in, float x, float y) override {
		int ix = int((image.width()+0.5f) * x);
		int iy = int((image.height()+0.5f) * y);
		Color col = image.get(ix, iy);
		return col;
	}

	inline virtual NodeType type() override { return NodeType::Image; }

	virtual void load(const Json& json) override {
		fileName = json["fileName"];
		image = PixelData(fs::absolute(fs::path(fileName)).string());
	}

	virtual void save(Json& json) override {
		json["fileName"] = fileName;
	}

	PixelData image{};
	std::string fileName{};
};

class MultiplyNode : public Node {
public:
	inline MultiplyNode() {
		addParam("A");
		addParam("B");
		addParam("Fat.");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		auto&& pb = param(1).value;
		auto&& fac = param(2).value;

		int xa = int((pa.width() + 0.5f) * x);
		int ya = int((pa.height() + 0.5f) * y);
		int xb = int((pb.width() + 0.5f) * x);
		int yb = int((pb.height() + 0.5f) * y);
		int xf = int((fac.width() + 0.5f) * x);
		int yf = int((fac.height() + 0.5f) * y);

		Color na = pa.get(xa, ya);
		Color nb = pb.get(xb, yb);
		float fc = param(2).connected ? luma(fac.get(xf, yf)) : factor;
		return Color{ na.r * nb.r * fc, na.g * nb.g * fc, na.b * nb.b * fc, na.a };
	}

	inline virtual NodeType type() override { return NodeType::Multiply; }

	virtual void load(const Json& json) override {
		factor = json.value("factor", 1.0f);
	}

	virtual void save(Json& json) override {
		json["factor"] = factor;
	}

	float factor{ 1.0f };
};

class AddNode : public Node {
public:
	inline AddNode() {
		addParam("A");
		addParam("B");
		addParam("Fat.");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		auto&& pb = param(1).value;
		auto&& fac = param(2).value;

		int xa = int((pa.width() + 0.5f) * x);
		int ya = int((pa.height() + 0.5f) * y);
		int xb = int((pb.width() + 0.5f) * x);
		int yb = int((pb.height() + 0.5f) * y);
		int xf = int((fac.width() + 0.5f) * x);
		int yf = int((fac.height() + 0.5f) * y);

		Color na = pa.get(xa, ya);
		Color nb = pb.get(xb, yb);
		float fc = param(2).connected ? luma(fac.get(xf, yf)) : factor;
		return Color{ na.r + nb.r * fc, na.g + nb.g * fc, na.b + nb.b * fc, na.a };
	}

	inline virtual NodeType type() override { return NodeType::Add; }

	virtual void load(const Json& json) override {
		factor = json.value("factor", 1.0f);
	}

	virtual void save(Json& json) override {
		json["factor"] = factor;
	}

	float factor{ 1.0f };
};

class MixNode : public Node {
public:
	inline MixNode() {
		addParam("A");
		addParam("B");
		addParam("Fat.");
	}

	inline float lerp(float a, float b, float t) {
		return (1.0f - t) * a + b * t;
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		auto&& pb = param(1).value;
		auto&& fac = param(2).value;

		int xa = int((pa.width() + 0.5f) * x);
		int ya = int((pa.height() + 0.5f) * y);
		int xb = int((pb.width() + 0.5f) * x);
		int yb = int((pb.height() + 0.5f) * y);
		int xf = int((fac.width() + 0.5f) * x);
		int yf = int((fac.height() + 0.5f) * y);

		Color na = pa.get(xa, ya);
		Color nb = pb.get(xb, yb);
		float fc = param(2).connected ? luma(fac.get(xf, yf)) : factor;
		return Color{
			lerp(na.r, nb.r, fc),
			lerp(na.g, nb.g, fc),
			lerp(na.b, nb.b, fc),
			lerp(na.a, nb.a, fc)
		};
	}

	inline virtual NodeType type() override { return NodeType::Mix; }

	virtual void load(const Json& json) override {
		factor = json.value("factor", 1.0f);
	}

	virtual void save(Json& json) override {
		json["factor"] = factor;
	}

	float factor{ 1.0f };
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

	virtual void load(const Json& json) override {
		threshold = json.value("threshold", 1.0f);
	}

	virtual void save(Json& json) override {
		json["threshold"] = threshold;
	}

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

		Color cmax = { 0.0f, 0.0f, 0.0f, 1.0f };
		float maxLuma = 0.0f;
		const int m = int(size) / 2;
		for (int i = -m; i <= m; i++) {
			for (int j = -m; j <= m; j++) {
				Color tmp = pa.get(ix + i, iy + j);
				float l = luma(tmp);
				if (l > maxLuma) {
					cmax = tmp;
					maxLuma = l;
				}
			}
		}
		return cmax;
	}

	inline virtual NodeType type() override { return NodeType::Dilate; }

	virtual void load(const Json& json) override {
		size = json.value("size", 3.0f);
	}

	virtual void save(Json& json) override {
		json["size"] = size;
	}

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

		Color cmin = { 1.0f, 1.0f, 1.0f, 1.0f };
		float minLuma = 1.0f;
		const int m = int(size) / 2;

		for (int i = -m; i <= m; i++) {
			for (int j = -m; j <= m; j++) {
				Color tmp = pa.get(ix + i, iy + j);
				float l = luma(tmp);
				if (l < minLuma) {
					cmin = tmp;
					minLuma = l;
				}
			}
		}
		return cmin;
	}

	inline virtual NodeType type() override { return NodeType::Erode; }

	virtual void load(const Json& json) override {
		size = json.value("size", 3.0f);
	}

	virtual void save(Json& json) override {
		json["size"] = size;
	}

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

	virtual void load(const Json& json) override {
		filter = Filter(json.value("filter", 1));
	}

	virtual void save(Json& json) override {
		json["filter"] = int(filter);
	}

	Filter filter{ Filter::GaussianBlur };

};

static std::vector<float> histogram(const PixelData& pa) {
	int res[256] = { 0 };
	for (size_t hx = 0; hx < pa.width(); hx++) {
		for (size_t hy = 0; hy < pa.height(); hy++) {
			uint8_t g = uint8_t(luma(pa.get(hx, hy)) * 255.0f);
			res[g]++;
		}
	}

	std::vector<float> ret;
	ret.resize(256);
	for (size_t i = 0; i < ret.size(); i++) ret[i] = float(res[i]) / 255.0f;
	return ret;
}

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

		v.reserve(int(size) * int(size));

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

	virtual void load(const Json& json) override {
		size = json.value("size", 3.0f);
	}

	virtual void save(Json& json) override {
		json["size"] = size;
	}

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

	virtual void load(const Json& json) override {
		brightness = json.value("brightness", 1.0f);
		contrast = json.value("contrast", 1.0f);
	}

	virtual void save(Json& json) override {
		json["brightness"] = brightness;
		json["contrast"] = contrast;
	}

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

	virtual void load(const Json& json) override {
		vertical = json.value("vertical", false);
	}

	virtual void save(Json& json) override {
		json["vertical"] = vertical;
	}

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

	virtual void load(const Json& json) override {
		quant = json.value("quant", 1.0f);
	}

	virtual void save(Json& json) override {
		json["quant"] = quant;
	}

	float quant{ 1.0f };

};

class InvertNode : public Node {
public:
	inline InvertNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);
		Color col = pa.get(ix, iy);
		col.r = 1.0f - col.r;
		col.g = 1.0f - col.g;
		col.b = 1.0f - col.b;
		return col;
	}

	inline virtual NodeType type() override { return NodeType::Invert; }
};

class DistortNode : public Node {
public:
	inline DistortNode() {
		addParam("A");
		addParam("DuDv");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		auto&& dudv = param(1).value;
		int dx = int((dudv.width()+0.5f) * x);
		int dy = int((dudv.height()+0.5f) * y);
		
		Color uv = dudv.get(dx, dy);
		float fx = x + (uv.r * 2.0f - 1.0f) * strenght;
		float fy = y + (uv.g * 2.0f - 1.0f) * strenght;
		int ix = int((pa.width()+0.5f) * fx);
		int iy = int((pa.height()+0.5f) * fy);
		return pa.get(ix, iy);
	}

	inline virtual NodeType type() override { return NodeType::Distort; }

	virtual void load(const Json& json) override {
		strenght = json.value("strenght", 0.02f);
	}

	virtual void save(Json& json) override {
		json["strenght"] = strenght;
	}

	float strenght{ 0.02f };
};

class NormalMapNode : public Node {
	using vec3 = std::array<float, 3>;
public:
	inline NormalMapNode() {
		addParam("A");
	}

	inline float vlen(const vec3& v) {
		return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	}

	inline vec3 vnorm(const vec3& v) {
		float ln = vlen(v);
		return { v[0] / ln, v[1] / ln, v[2] / ln };
	}

	inline vec3 vcross(const vec3& a, const vec3& b) {
		return {
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
		};
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);

		float s01 = luma(pa.get(ix - 1, iy));
		float s21 = luma(pa.get(ix + 1, iy));
		float s10 = luma(pa.get(ix, iy - 1));
		float s12 = luma(pa.get(ix, iy + 1));

		vec3 va = vnorm({ size, 0.0, s21 - s01 });
		vec3 vb = vnorm({ 0.0, size, s12 - s10 });
		vec3 vc = vcross(va, vb);
		Color col;
		col.r = vc[0] * 0.5f + 0.5f;
		col.g = vc[1] * 0.5f + 0.5f;
		col.b = vc[2] * 0.5f + 0.5f;
		col.a = 1.0f;
		return col;
	}

	inline virtual NodeType type() override { return NodeType::NormalMap; }

	float size{ 2.0f };
};

class GrayscaleNode : public Node {
public:
	inline GrayscaleNode() {
		addParam("A");
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		auto&& pa = param(0).value;
		int ix = int((pa.width()+0.5f) * x);
		int iy = int((pa.height()+0.5f) * y);
		float lm = luma(pa.get(ix, iy));
		return { lm, lm, lm, 1.0f };
	}

	inline virtual NodeType type() override { return NodeType::Grayscale; }
};

#endif // NODES_HPP
