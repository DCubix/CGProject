#ifndef KERNEL_H
#define KERNEL_H

#include <vector>

class Kernel {
public:
	enum KernelSize {
		K3x3 = 3,
		K5x5 = 5,
		K7x7 = 7,
		K9x9 = 9,
		K11x11 = 11,
		K13x13 = 13
	};

	Kernel(KernelSize size = KernelSize::K3x3);
	Kernel(const std::vector<float>& m, KernelSize size = KernelSize::K3x3);

	float& operator [](size_t i) { return m_matrix[i]; }
	const float& operator [](size_t i) const { return m_matrix[i]; }

	void set(int row, int col, float value);
	float get(int row, int col);

	size_t size() const { return m_size; }
	std::vector<float>& matrix() { return m_matrix; }

private:
	size_t m_size;
	std::vector<float> m_matrix;
};

#endif // KERNEL_H
