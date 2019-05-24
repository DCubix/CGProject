#ifndef FILTER_H
#define FILTER_H

#include <memory>

#include "image.h"

using ImagePtr = std::unique_ptr<Image>;

class Filter {
public:
	virtual void process(const PixelData& in, PixelData& out, int x, int y) = 0;
protected:
	Color convolute(const PixelData& in, const std::vector<float>& kernel, int kernelSize, int x, int y);
};

class FilterStack {
public:
	FilterStack() = default;
	~FilterStack() = default;

	PixelData apply(const PixelData& in);
	PixelData applyOne(Filter* filter, const PixelData& in);
	PixelData applyRegion(const PixelData& in, int rx, int ry, int rw, int rh);

	void add(Filter* filter);

private:
	std::vector<std::unique_ptr<Filter>> m_filters;

	PixelData apply(Filter* filter, const PixelData& in, int rx, int ry, int rw, int rh);
};

#endif // FILTER_H
