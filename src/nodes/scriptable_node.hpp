#ifndef SCRIPTABLE_NODE_HPP
#define SCRIPTABLE_NODE_HPP

#define SOL_CHECK_ARGUMENTS 0
#define SOL_NO_CHECK_NUMBER_PRECISION 1
#include "../sol.hpp"

#include <iostream>

#include "node_logic.h"
#include "filesystem.hpp"
namespace fs = ghc::filesystem;

namespace classes {
	inline float luma(Color col) {
		return col.r * 0.299f + col.g * 0.587f + col.b * 0.114f;
	}

	inline void init(lua_State* L) {
		sol::state_view vL(L);

		vL.new_usertype<PixelData>(
					"PixelData",
					sol::constructors<PixelData(), PixelData(int, int), PixelData(const std::string&)>(),
					"width", sol::readonly_property(&PixelData::width),
					"height", sol::readonly_property(&PixelData::height),
					"get", &PixelData::get,
					"set", &PixelData::set,
					"__call", sol::overload(&PixelData::get, &PixelData::set)
		);

		vL.new_usertype<Color>(
					"Color",
					"r", &Color::r,
					"g", &Color::g,
					"b", &Color::b,
					"a", &Color::a
		);

		vL["luma"] = &luma;
		vL["unorm"] = [](float v, int max) {
			return int((max + 0.5f) * v);
		};
	}
}

constexpr int TileSize = 32;
class ScriptableNode : public Node {
public:
	inline ScriptableNode() {
		L = luaL_newstate();
		luaL_openlibs(L);
		classes::init(L);

		sol::state_view vL(L);
		vL["param"] = [=](int i) {
			return param(i).value;
		};
	}

	inline virtual ~ScriptableNode() override {
		lua_close(L);
	}

	// TODO: Find a way to parallelize this without breaking Lua...
	inline virtual PixelData process(const PixelData& in) override {
		reset();

		PixelData out(in.width(), in.height());
		for (int k = 0; k < in.width() * in.height(); k++) {
			int x = k % in.width();
			int y = k / in.width();
			float fx = float(x) / in.width();
			float fy = float(y) / in.height();
			Color c = process(in, fx, fy);
			out.set(x, y, c.r, c.g, c.b, c.a);
		}
		return out;
	}

	inline virtual Color process(const PixelData& in, float x, float y) override {
		if (fileName.empty() || !m_ret.valid()) return color;
		if (m_process.get_type() == sol::type::function) {
			auto&& rval = m_process.call(x, y);
			Color ret = color;
			if (rval.get_type() == sol::type::table) {
				auto&& rv = rval.get<std::vector<float>>();
				if (rv.size() == 1) {
					ret.r = rv[0];
					ret.g = 0.0f;
					ret.b = 0.0f;
					ret.a = 1.0f;
				} else if (rv.size() == 2) {
					ret.r = rv[0];
					ret.g = rv[1];
					ret.b = 0.0f;
					ret.a = 1.0f;
				} else if (rv.size() == 3) {
					ret.r = rv[0];
					ret.g = rv[1];
					ret.b = rv[2];
					ret.a = 1.0f;
				} else if (rv.size() == 4) {
					ret.r = rv[0];
					ret.g = rv[1];
					ret.b = rv[2];
					ret.a = rv[3];
				}
			} else if (rval.get_type() == sol::type::number) {
				ret.r = ret.g = ret.b = rval.get<float>();
				ret.a = 1.0f;
			}
			return ret;
		}
		return color;
	}

	inline void refresh() {
		if (!fileName.empty()) {
			sol::state_view vL(L);
			try {
				std::string path = fs::absolute(fs::path(fileName)).string();
				m_ret = vL.safe_script_file(path);
				if (m_ret.valid()) {
					name = m_ret["name"].get_or<std::string>("Script");
					m_process = m_ret["process"];
					if (m_ret["inputs"].get_type() == sol::type::table) {
						m_params.clear();
						for (auto&& s : m_ret["inputs"].get<std::vector<std::string>>()) {
							addParam(s);
						}
					}
				}
			} catch (const sol::error& err) {
				std::cerr << err.what() << std::endl;
			}
		}
	}

	inline virtual void load(const Json& json) override {
		fileName = json.value("fileName", "");
		refresh();
	}

	inline virtual void save(Json& json) override {
		json["fileName"] = fileName;
	}

	inline virtual NodeType type() override { return NodeType::Script; }

	std::string fileName{}, name{"Script"};
	const Color color{ 0.0f, 0.0f, 0.0f, 1.0f };

private:
	lua_State* L;
	sol::table m_ret;
	sol::function m_process{};

	struct Tile {
		int x, y;
	};
};

#endif // SCRIPTABLE_NODE_HPP
