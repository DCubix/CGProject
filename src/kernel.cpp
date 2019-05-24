#include "kernel.h"

#include <algorithm>

Kernel::Kernel(KernelSize size) {
	m_size = size_t(size);
	m_matrix.resize(size_t(size) * size_t(size));
	std::fill(m_matrix.begin(), m_matrix.end(), 0);
	m_matrix[size_t(size)] = 1.0f;
}

Kernel::Kernel(const std::vector<float>& m, Kernel::KernelSize size) : Kernel(size) {
	for (size_t i = 0; i < m_matrix.size(); i++)
		m_matrix[i] = m[i];
}

void Kernel::set(int row, int col, float value) {
	m_matrix[col + row * m_size] = value;
}

float Kernel::get(int row, int col) {
	return m_matrix[col + row * m_size];
}
