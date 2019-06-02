function _process(x, y)
	return { math.abs(math.sin(x * 25.0)), math.abs(math.cos(y * 25.0)), 0.0, 1.0 }
end

return {
	name = "Sine",
	process = _process
}