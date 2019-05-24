#ifndef FILTERS_HPP
#define FILTERS_HPP

#include "filter.h"
#include <algorithm>

#include "kernels.hpp"

namespace filters {
	inline float luma(Color col) {
		return col.r * 0.299f + col.g * 0.587f + col.b * 0.114f;
	}

	class DilationFilter : public Filter {
	public:
		inline virtual void process(const PixelData& in, PixelData& out, int x, int y) override {
			const float lm = luma(in.get(x, y).value());
			if (lm >= 0.99f) {
				out.set(x, y, 1.0f, 1.0f, 1.0f, 1.0f);
				out.set(x - 1, y, 1.0f, 1.0f, 1.0f, 1.0f);
				out.set(x + 1, y, 1.0f, 1.0f, 1.0f, 1.0f);
				out.set(x, y - 1, 1.0f, 1.0f, 1.0f, 1.0f);
				out.set(x, y + 1, 1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	};

	class EdgeDetectionFilter : public Filter {
	public:
		inline virtual void process(const PixelData& in, PixelData& out, int x, int y) override {
			Color hc = convolute(in, kernels::sobelKernel(kernels::Orientation::Horizontal), 3, x, y);
			Color vc = convolute(in, kernels::sobelKernel(kernels::Orientation::Vertical), 3, x, y);
			Color ccol = {
				::sqrt(hc.r * hc.r + vc.r * vc.r),
				::sqrt(hc.g * hc.g + vc.g * vc.g),
				::sqrt(hc.b * hc.b + vc.b * vc.b),
				1.0f
			};
			out.set(x, y, ccol.r, ccol.g, ccol.b, ccol.a);
		}
	};

	class ErosionFilter : public Filter {
	public:
		inline virtual void process(const PixelData& in, PixelData& out, int x, int y) override {
			const Color def = { 0.0f, 0.0f, 0.0f, 1.0f };
			const float sum
					= luma(in.get(x - 1, y).value_or(def))
					+ luma(in.get(x + 1, y).value_or(def))
					+ luma(in.get(x, y - 1).value_or(def))
					+ luma(in.get(x, y + 1).value_or(def));
			if (luma(in.get(x, y).value()) >= 0.99f && sum < 4.0f) {
				out.set(x, y, 0.0f, 0.0f, 0.0f, 1.0f);
			}
		}
	};

	class MedianFilter : public Filter {
	public:
		inline virtual void process(const PixelData& in, PixelData& out, int x, int y) override {
			std::vector<Color> v;
			const int m = m_size / 2;

			v.reserve(m*m);

			for (int ky = -m; ky <= m; ky++) {
				for (int kx = -m; kx <= m; kx++) {
					auto col = in.get(kx + x, ky + y);
					if (col.has_value()) v.push_back(col.value());
				}
			}

			std::sort(v.begin(), v.end(), [](const Color& a, const Color& b) {
				float la = luma(a);
				float lb = luma(b);
				return la > lb;
			});

			Color med = v[m_size];
			out.set(x, y, med.r, med.g, med.b, med.a);
		}

		inline int& size() { return m_size; }
		inline void size(int s) { m_size = s; }

	private:
		int m_size{ 5 };
	};

	class ThresholdFilter : public Filter {
	public:
		inline virtual void process(const PixelData& in, PixelData& out, int x, int y) override {
			float lm = luma(in.get(x, y).value());
			if (!m_locallyAdaptive) {
				float g = lm >= m_threshold ? 1.0f : 0.0f;
				out.set(x, y, g, g, g, 1.0f);
			} else {
				const int m = m_regionSize / 2;
				float sum = 0.0f;
				for (int ky = -m; ky <= m; ky++) {
					for (int kx = -m; kx <= m; kx++) {
						auto col = in.get(kx + x, ky + y);
						if (col.has_value()) {
							sum += luma(col.value());
						}
					}
				}
				sum /= (m_regionSize * m_regionSize);

				float g = lm >= (sum * m_threshold) ? 1.0f : 0.0f;
				out.set(x, y, g, g, g, 1.0f);
			}
		}

		float threshold() const { return m_threshold; }
		void threshold(float v) { m_threshold = v; }

		int regionSize() const { return m_regionSize; }
		void regionSize(int v) { m_regionSize = v; }

		int locallyAdaptive() const { return m_locallyAdaptive; }
		void locallyAdaptive(bool v) { m_locallyAdaptive = v; }

	private:
		float m_threshold{ 0.5f };
		int m_regionSize{ 3 };
		bool m_locallyAdaptive{ false };
	};

	class BlurFilter : public Filter {
	public:
		BlurFilter() {
			update();
		}

		inline virtual void process(const PixelData& in, PixelData& out, int x, int y) override {
			Color ccol = convolute(in, m_kernel, int(m_kernelSize), x, y);
			out.set(x, y, ccol.r, ccol.g, ccol.b, ccol.a);
		}

		kernels::KernelSize kernelSize() const { return m_kernelSize; }
		void kernelSize(kernels::KernelSize v) {
			m_kernelSize = v;
			update();
		}

		bool gaussian() const { return m_gaussian; }
		void gaussian(bool v) {
			m_gaussian = v;
			update();
		}

	private:
		inline void update() {
			if (m_gaussian) {
				m_kernel = kernels::gaussianBlur(m_kernelSize, 1.2f);
			} else {
				m_kernel = kernels::boxBlur(m_kernelSize);
			}
		}

		kernels::Kernel m_kernel;
		kernels::KernelSize m_kernelSize{ kernels::KernelSize::K3x3 };
		bool m_gaussian{ false };
	};
}

#endif // FILTERS_HPP
