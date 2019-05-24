#include "filter.h"

#include <chrono>
#include <iostream>
#define BEGIN_BENCH std::chrono::high_resolution_clock::now()
#define END_BENCH(clk, name) std::cout << "RUN-TIME OF " << name << ": " << \
	std::chrono::duration_cast<std::chrono::milliseconds>( \
			std::chrono::high_resolution_clock::now() - clk \
	).count() << " ms " << std::endl;

Color Filter::convolute(const PixelData& in, const std::vector<float>& kernel, int kernelSize, int x, int y) {
	const int w = kernelSize;
	const int mean = w / 2;

	Color sum = { 0.0f, 0.0f, 0.0f, 1.0f };
	for (int n = -mean; n <= mean; n++) {
		for (int m = -mean; m <= mean; m++) {
			auto col = in.get(x + n, y + m);
			if (col.has_value()) {
				Color color = col.value();
				float kv = kernel[(n + mean) + (m + mean) * w];
				sum.r += color.r * kv;
				sum.g += color.g * kv;
				sum.b += color.b * kv;
				sum.a = color.a;
			}
		}
	}
	return sum;
}

PixelData FilterStack::apply(const PixelData& in) {
	PixelData out(in.width(), in.height());

	auto clk = BEGIN_BENCH;
	for (int y = 0; y < in.height(); y++) {
		for (int x = 0; x < in.width(); x++) {
			Color col = in.get(x, y).value();
			out.set(x, y, col.r, col.g, col.b, col.a);
		}
	}
	for (auto& filter : m_filters) {
		out = apply(filter.get(), out, 0, 0, in.width(), in.height());
	}
	END_BENCH(clk, "Filter Processing")

			return out;
}

PixelData FilterStack::applyOne(Filter* filter, const PixelData& in) {
	return apply(filter, in, 0, 0, in.width(), in.height());
}

PixelData FilterStack::applyRegion(const PixelData& in, int rx, int ry, int rw, int rh) {
	PixelData out(in.width(), in.height());
	for (int y = 0; y < in.height(); y++) {
		for (int x = 0; x < in.width(); x++) {
			Color col = in.get(x, y).value();
			out.set(x, y, col.r, col.g, col.b, col.a);
		}
	}
	for (auto& filter : m_filters) {
		out = apply(filter.get(), out, rx, ry, rw, rh);
	}
	return out;
}

void FilterStack::add(Filter* filter) {
	m_filters.push_back(std::unique_ptr<Filter>(filter));
}

PixelData FilterStack::apply(Filter* filter, const PixelData& in, int rx, int ry, int rw, int rh) {
	PixelData out(in.width(), in.height());

	#pragma omp parallel for schedule(dynamic)
	for (int y = 0; y < in.height(); y++) {
		for (int x = 0; x < in.width(); x++) {
			if (x > rx && x < rx + rw && y > ry && y < ry + rh) {
				filter->process(in, out, x, y);
			} else {
				const Color def = { 0.0f, 0.0f, 0.0f, 1.0f };
				auto col = in.get(x, y).value_or(def);
				out.set(x, y, col.r, col.g, col.b, col.a);
			}
		}
	}
	return out;
}
