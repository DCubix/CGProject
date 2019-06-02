function vlen(v)
	return math.sqrt(v[1] * v[1] + v[2] * v[2] + v[3] * v[3])
end

function vnorm(v)
	local ln = vlen(v)
	return { v[1] / ln, v[2] / ln, v[3] / ln }
end

function vcross(a, b)
	return {
		a[2] * b[3] - a[3] * b[2],
		a[3] * b[1] - a[1] * b[3],
		a[1] * b[2] - a[2] * b[1]
	}
end

function _process(x, y)
	local pa = param(0)
	local ix = unorm(x, pa.width)
	local iy = unorm(y, pa.height)
	local s11 = luma(pa:get(ix, iy))
	local s01 = luma(pa:get(ix - 1, iy))
	local s21 = luma(pa:get(ix + 1, iy))
	local s10 = luma(pa:get(ix, iy - 1))
	local s12 = luma(pa:get(ix, iy + 1))
	local va = vnorm({ 1.0, 0.0, s21 - s01 })
	local vb = vnorm({ 0.0, 1.0, s12 - s10 })
	local vc = vcross(va, vb)
	return { vc[1] * 0.5 + 0.5, vc[2] * 0.5 + 0.5, vc[3] * 0.5 + 0.5 }
end

return {
	name = "N. Map",
	inputs = { "A" },
	process = _process
}