#ifndef KERNELS_HPP
#define KERNELS_HPP

#include <algorithm>
#include <cmath>
#include <vector>

namespace kernels {

	enum Orientation {
		Horizontal = 0,
		Vertical
	};

	enum KernelSize {
		K3x3 = 3,
		K5x5 = 5,
		K7x7 = 7,
		K9x9 = 9,
		K11x11 = 11,
		K13x13 = 13
	};

	using Kernel = std::vector<float>;

	inline Kernel boxBlur(KernelSize size) {
		Kernel bb;
		bb.resize(size_t(size) * size_t(size));
		std::fill(bb.begin(), bb.end(), 1.0f / float(bb.size()));
		return bb;
	}

	inline Kernel gaussianBlur(KernelSize size, float sigma = 1.0f) {
		Kernel gb;

		const int w = int(size);
		const int mean = w / 2;
		const float s = 2.0f * sigma * sigma;
		float sum = 0.0f;

		gb.resize(w * w);

		for (int x = -mean; x <= mean; x++) {
			for (int y = -mean; y <= mean; y++) {
				float r = float(::sqrt(x * x + y * y));
				int i = (x + mean) + (y + mean) * w;
				gb[i] = float((::exp(-(r * r) / s)) / (float(M_PI) * s));
				sum += gb[i];
			}
		}

		// Normalize
		for (size_t i = 0; i < w * w; i++) {
			gb[i] /= sum;
		}

		return gb;
	}

	inline Kernel sharpenKernel() {
		return {
			0, -1, 0,
			-1, 5, -1,
			0, -1, 0
		};
	}

	inline Kernel sobelKernel(Orientation orientation) {
		switch (orientation) {
			case Horizontal: return {
					-1, -2, -1,
					 0,  0,  0,
					 1,  2,  1
			};
			case Vertical: return {
					-1, 0, 1,
					-2, 0, 2,
					-1, 0, 1
			};
		}
	}

	inline Kernel edgeDetectKernel() {
		return {
			-1, -1, -1,
			-1,  8, -1,
			-1, -1, -1
		};
	}

}

#endif // KERNELS_HPP
