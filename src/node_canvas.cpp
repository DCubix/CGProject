#include "node_canvas.h"

constexpr int NodeWidth = 80;
constexpr int textPad = 3;
constexpr int GridSize = 8;

#include "nodes/nodes.hpp"
#include "nodes/scriptable_node.hpp"
#include "localization.h"

static bool hitsR(int x, int y, int bx, int by, int bw, int bh) {
	return x > bx &&
		x < bx + bw &&
		y > by &&
		y < by + bh;
}

NodeCanvas::NodeCanvas() {
	m_system = std::make_unique<NodeSystem>();
	m_gnodes[0].x = 0;
	m_gnodes[0].y = 0;
	m_gnodes[0].node = 0;
}

static int inY(int index) {
	return (10 * index) + 17;
}

void NodeCanvas::onDraw(Renderer& renderer) {
	auto b = realBounds();
	renderer.panel(b.x, b.y, b.width, b.height);
	renderer.pushClipping(b.x + 1, b.y + 1, b.width - 2, b.height - 2);
	
	// Grid
	for (int y = b.y; y < b.y + b.height; y += GridSize) {
		renderer.line(b.x, y, b.x + b.width, y, 100, 100, 100);
	}
	for (int x = b.x; x < b.x + b.width; x += GridSize) {
		renderer.line(x, b.y, x, b.y + b.height, 100, 100, 100);
	}
	renderer.rect(b.x, b.y, b.width, b.height, 255, 255, 255, 60);
	//

	renderer.rect(b.x, b.y, b.width, b.height, 0, 0, 0, 60, true);

	auto nodes = m_system->nodes();
	std::sort(nodes.begin(), nodes.end(), [&](int a, int b) {
		return m_gnodes[a].selected < m_gnodes[b].selected;
	});

	m_gnodes[0].x = b.width - 40;
	m_gnodes[0].y = 20;

	for (int nid : nodes) {
		GNode& gnode = m_gnodes[nid];
		Node* node = m_system->get<Node>(nid);
		int count = node->paramCount() == 0 ? 1 : node->paramCount();
		gnode.height = 20 + (count * 10);
	}

	// Draw connections
	for (int cid : m_system->connections()) {
		auto conn = m_system->getConnection(cid);
		GNode src = m_gnodes[conn->src];
		GNode dest = m_gnodes[conn->dest];

		int connSrcX = (src.x + b.x) + NodeWidth - (textPad + 4);
		int connSrcY = (src.y + b.y) + inY(0) + textPad + 6;

		int connDestX = (dest.x + b.x) + textPad + 4;
		int connDestY = (dest.y + b.y) + inY(conn->destParam) + textPad + 6;

		connSrcY -= 2;
		connDestY -= 2;

		if (connSrcX > connDestX) {
			int mid = (connDestY - connSrcY) / 2;
			renderer.curve(
				connSrcX, connSrcY,
				connSrcX + 50, connSrcY + mid,
				connDestX - 50, connDestY - mid,
				connDestX, connDestY,
				196, 212, 209
			);
		} else {
			int mid = (connDestX - connSrcX) / 2;
			renderer.curve(
				connSrcX, connSrcY,
				connSrcX + mid, connSrcY,
				connSrcX + mid, connDestY,
				connDestX, connDestY,
				196, 212, 209
			);
		}

		int mx = (connDestX + connSrcX) / 2;
		int my = (connDestY + connSrcY) / 2;
		renderer.roundRect(mx - 3, my - 3, 6, 6, 6, 196, 212, 209, 255, true);
	}

	for (int nid : nodes) {
		GNode& gnode = m_gnodes[nid];
		Node* node = m_system->get<Node>(nid);
		int nx = gnode.x + b.x;
		int ny = gnode.y + b.y;

		int ngx = std::floor(gnode.x / GridSize) * GridSize + b.x;
		int ngy = std::floor(gnode.y / GridSize) * GridSize + b.y;

		if (node->type() != NodeType::Output) {
			if (gnode.selected && m_state == Moving) {
				renderer.rect(ngx, ngy, NodeWidth, gnode.height, 255, 255, 255, 50, true);
			}
			renderer.flatPanel(nx, ny, NodeWidth, gnode.height, 0, 3, 0.5f);
			renderer.pushClipping(nx + 1, ny + 1, NodeWidth - 2, gnode.height - 2);
			renderer.rect(nx + 1, ny + 1, NodeWidth - 2, 16, 0, 0, 0, 80, true);
			if (node->type() == NodeType::Color) {
				ColorNode* n = (ColorNode*) node;
				for (int i = 0; i < 8; i++) {
					renderer.textSmall(nx + 4 + i, ny + 20, "\x7",
									   n->color.r * 255.0f,
									   n->color.g * 255.0f,
									   n->color.b * 255.0f,
									   255
					);
				}
			}

			std::string txt = "";
			switch (node->type()) {
				default: break;
				case NodeType::Add: txt = LL("Add"); break;
				case NodeType::Multiply: txt = "Mult."; break;
				case NodeType::Color: txt = LL("Color"); break;
				case NodeType::Erode: txt = LL("Erode"); break;
				case NodeType::Dilate: txt = LL("Dilate"); break;
				case NodeType::Median: txt = LL("Median"); break;
				case NodeType::Convolute: txt = LL("Convolute"); break;
				case NodeType::Threshold: txt = LL("Threshold"); break;
				case NodeType::Image: txt = LL("Image"); break;
				case NodeType::BrightnessContrast: txt = "B/C"; break;
				case NodeType::WebCam: txt = "WebCam"; break;
				case NodeType::Mirror: txt = LL("Mirror"); break;
				case NodeType::FishEye: txt = LL("F. Eye"); break;
				case NodeType::Mix: txt = LL("Mix"); break;
				case NodeType::Invert: txt = LL("Invert"); break;
				case NodeType::Distort: txt = LL("Distort"); break;
				case NodeType::NormalMap: txt = LL("N. Map"); break;
				case NodeType::Grayscale: txt = LL("G. Scale"); break;
				// case NodeType::Script: txt = LL(((ScriptableNode*) node)->name); break;
			}
			renderer.text(nx + 5, ny + 5, txt, 0, 0, 0, 128);
			renderer.text(nx + 4, ny + 4, txt, 255, 255, 255, 180);

			for (int i = 0; i < node->paramCount(); i++) {
				int py = inY(i) + ny;
				renderer.textSmall(nx + textPad, py + textPad, "\x9", 0, 0, 0, 200);
				renderer.textSmall(nx + textPad + 8, py + textPad, LL(node->paramName(i)), 0, 0, 0, 200);
			}

			renderer.popClipping();

			int py = inY(0) + ny;
			renderer.textSmall(nx + NodeWidth - (textPad + 8), py + textPad, "\x9", 0, 0, 0, 200);

			if (gnode.selected) {
				renderer.rect(nx + 2, ny + 2, NodeWidth - 4, gnode.height - 4, 255, 255, 255, 50, true);
			}
		} else {
			renderer.flatPanel(nx, ny, NodeWidth, gnode.height, 0, 2, 0.5f);
			int py = inY(0) + ny;
			renderer.textSmall(nx + textPad, py + textPad, "\x9", 0, 0, 0, 200);
			renderer.textSmall(nx + textPad + 8, py + textPad, LL("Out"), 0, 0, 0, 200);

		}
	}

	// Draw dots
	for (int cid : m_system->connections()) {
		auto conn = m_system->getConnection(cid);
		GNode src = m_gnodes[conn->src];
		GNode dest = m_gnodes[conn->dest];

		int connSrcX = (src.x + b.x) + NodeWidth - (textPad + 4);
		int connSrcY = (src.y + b.y) + inY(0) + textPad + 6;

		int connDestX = (dest.x + b.x) + textPad + 4;
		int connDestY = (dest.y + b.y) + inY(conn->destParam) + textPad + 6;

		renderer.textSmall(connSrcX - 4, connSrcY - 6, "\x7", 196, 212, 209);
		renderer.textSmall(connDestX - 4, connDestY - 6, "\x7", 196, 212, 209);
	}

	if (m_state == Linking) {
		GNode gnode = m_gnodes[m_link.src];
		int nx = gnode.x + b.x;
		int ny = gnode.y + b.y;
		
		int connSrcX = nx + NodeWidth - (textPad + 4);
		int connSrcY = ny + inY(0) + textPad + 4;
		int mid = ((m_px + b.x) + connSrcX) / 2;

		renderer.textSmall(connSrcX - 4, connSrcY - 4, "\x7", 196, 212, 209);
		renderer.curve(
			connSrcX, connSrcY,
			mid, connSrcY,
			mid, m_py + b.y,
			m_px + b.x, m_py + b.y,
			196, 212, 209
		);
	}

	renderer.popClipping();
	m_time += 0.01f;
}

void NodeCanvas::onClick(int button, int x, int y) {

}

void NodeCanvas::onMove(int x, int y) {
	switch (m_state) {
		case None: break;
		case Moving: {
			int dx = x - m_px;
			int dy = y - m_py;

			for (auto&& nid : m_selected) {
				GNode& gn = m_gnodes[nid];
				gn.x += dx;
				gn.y += dy;
			}

			if (m_onChange) m_onChange();

			m_px = x;
			m_py = y;
		} break;
		case Selecting: break;
		case Linking: {
			m_px = x;
			m_py = y;
		} break;
	}
}

void NodeCanvas::onPress(int button, int x, int y) {
	auto b = bounds();
	if (button == SDL_BUTTON_LEFT) {
		bool clickConnector = false;
		bool hitSomething = false;
		int hit = UINT32_MAX;

		for (int nid : m_system->nodes()) {
			GNode& gnode = m_gnodes[nid];
			Node* node = m_system->get<Node>(nid);
			int nx = gnode.x;
			int ny = gnode.y;
			int py = inY(0) + ny;
			int px = nx + NodeWidth - (textPad + 8);

			if (hitsR(x, y, px, py, 8, 12)) {
				m_link.src = nid;
				m_link.active = true;
				clickConnector = true;
				break;
			} else if (hitsR(x, y, nx, ny, NodeWidth, gnode.height)) {
				if (!m_multiSelect) {
					for (auto&& nid : m_selected) {
						m_gnodes[nid].selected = false;
					}
					m_selected.clear();
				}
				auto it = std::find(m_selected.begin(), m_selected.end(), nid);
				if (it == m_selected.end()) {
					gnode.selected = true;
					m_selected.push_back(nid);
					if (m_onSelect) m_onSelect(node);
				}
				hit = nid;
				hitSomething = true;
			}
		}

		if (!clickConnector) {
			if (!hitSomething) {
				deselect();
				m_state = None;

				// Handle disconnections
				for (int cid : m_system->connections()) {
					auto conn = m_system->getConnection(cid);
					GNode src = m_gnodes[conn->src];
					GNode dest = m_gnodes[conn->dest];

					int connSrcX = src.x + NodeWidth - (textPad + 4);
					int connSrcY = src.y + inY(0) + textPad + 6;

					int connDestX = dest.x + textPad + 4;
					int connDestY = dest.y + inY(conn->destParam) + textPad + 6;

					connSrcY -= 2;
					connDestY -= 2;

					int mx = 0, my = 0;
					if (conn->src != conn->dest) {
						mx = (connDestX + connSrcX) / 2;
						my = (connDestY + connSrcY) / 2;
					} else {
						mx = (connDestX + connSrcX) / 2;
						my = connDestY + src.height - 16;
					}

					if (hitsR(x, y, mx - 5, my - 5, 10, 10)) {
						m_system->disconnect(cid);
						if (m_onConnect) m_onConnect();
						break;
					}
				}
			} else {
				m_state = Moving;
			}
		} else {
			m_state = Linking;
		}
		m_px = x;
		m_py = y;
	}

	Widget::onPress(button, x, y);
}

void NodeCanvas::onRelease(int button, int x, int y) {
	for (auto&& nid : m_selected) {
		GNode& gn = m_gnodes[nid];
		gn.x = ::floor(gn.x / GridSize) * GridSize;
		gn.y = ::floor(gn.y / GridSize) * GridSize;
	}

	for (int nid : m_system->nodes()) {
		GNode& gnode = m_gnodes[nid];
		Node* node = m_system->get<Node>(nid);
		int nx = gnode.x;
		int ny = gnode.y;

		for (int i = 0; i < node->paramCount(); i++) {
			int py = inY(i) + ny;
			if (hitsR(x, y, nx + textPad, py + textPad, 8, 6) && m_link.active && m_link.src != nid) {
				if (m_system->connect(m_link.src, nid, i) != UINT32_MAX) {
					m_link.src = 0;
					m_link.active = false;
					if (m_onConnect) m_onConnect();
				}
				break;
			}
		}
	}

	m_state = None;
	m_sw = 0;
	m_sh = 0;
}

void NodeCanvas::onKeyPress(int key, int mod) {
	if (key == SDLK_LCTRL || key == SDLK_RCTRL) m_multiSelect = true;
}

void NodeCanvas::onKeyRelease(int key, int mod) {
	if (key == SDLK_LCTRL || key == SDLK_RCTRL) m_multiSelect = false;
}

void NodeCanvas::deselect() {
	for (auto&& nid : m_selected) {
		m_gnodes[nid].selected = false;
	}
	m_selected.clear();
	if (m_onSelect) m_onSelect(nullptr);
}

struct TypeMapEntry { std::string n; NodeType t; };

#define TM(t) { #t, NodeType::t }
static const TypeMapEntry TypeMap[] = {
	TM(Add),
	TM(Multiply),
	TM(Mix),
	TM(None),
	TM(Color),
	TM(Erode),
	TM(Image),
	TM(Dilate),
	TM(Invert),
	TM(Median),
	TM(Mirror),
	TM(Output),
	TM(WebCam),
	TM(Distort),
	TM(FishEye),
	TM(Convolute),
	TM(Threshold),
	TM(BrightnessContrast),
	TM(Script),
	TM(NormalMap),
	TM(Grayscale)
};

void NodeCanvas::load(const Json& json) {
	m_system->clear();

	Json nodes = json["nodes"];
	Json conns = json["conns"];

	for (size_t i = 0; i < nodes.size(); i++) {
		Json nd = nodes[i];
		int node = -1;
		auto tp = std::find_if(std::begin(TypeMap), std::end(TypeMap), [nd](const TypeMapEntry& e){
			return e.n == nd["type"];
		});
		if (tp != std::end(TypeMap)) {
			NodeType type = tp->t;
			switch (type) {
				default: break;
				case NodeType::Add: node = create<AddNode>(); break;
				case NodeType::Multiply: node = create<MultiplyNode>(); break;
				case NodeType::Mix: node = create<MixNode>(); break;
				case NodeType::Color: node = create<ColorNode>(); break;
				case NodeType::Erode: node = create<ErodeNode>(); break;
				case NodeType::Image: node = create<ImageNode>(); break;
				case NodeType::Dilate: node = create<DilateNode>(); break;
				case NodeType::Invert: node = create<InvertNode>(); break;
				case NodeType::Median: node = create<MedianNode>(); break;
				case NodeType::Mirror: node = create<MirrorNode>(); break;
				case NodeType::WebCam: node = create<WebCamNode>(); break;
				case NodeType::Distort: node = create<DistortNode>(); break;
				case NodeType::FishEye: node = create<FishEyeNode>(); break;
				case NodeType::Convolute: node = create<ConvoluteNode>(); break;
				case NodeType::Threshold: node = create<ThresholdNode>(); break;
				case NodeType::BrightnessContrast: node = create<BrightnessContrastNode>(); break;
				// case NodeType::Script: node = create<ScriptableNode>(); break;
				case NodeType::NormalMap: node = create<NormalMapNode>(); break;
				case NodeType::Grayscale: node = create<GrayscaleNode>(); break;
			}

			if (node != -1) {
				m_gnodes[node].x = nd["x"];
				m_gnodes[node].y = nd["y"];
				m_system->get<Node>(node)->load(nd);
			}
		}
	}

	for (size_t i = 0; i < conns.size(); i++) {
		Json cn = conns[i];
		m_system->connect(cn["src"], cn["dest"], cn["destParam"]);
	}
}

void NodeCanvas::save(Json& json) {
	Json nodes = Json::array();
	for (unsigned int nid : m_system->nodes()) {
		Node* node = m_system->get<Node>(nid);
		GNode& nd = m_gnodes[nid];
		Json jnd; node->save(jnd);
		jnd["x"] = nd.x;
		jnd["y"] = nd.y;
		std::string type = "ERROR";
		switch (node->type()) {
			default: continue;
			case NodeType::Add: type = "Add"; break;
			case NodeType::Multiply: type = "Multiply"; break;
			case NodeType::Mix: type = "Mix"; break;
			case NodeType::Color: type = "Color"; break;
			case NodeType::Erode: type = "Erode"; break;
			case NodeType::Image: type = "Image"; break;
			case NodeType::Dilate: type = "Dilate"; break;
			case NodeType::Invert: type = "Invert"; break;
			case NodeType::Median: type = "Median"; break;
			case NodeType::Mirror: type = "Mirror"; break;
			case NodeType::WebCam: type = "WebCam"; break;
			case NodeType::Distort: type = "Distort"; break;
			case NodeType::FishEye: type = "FishEye"; break;
			case NodeType::Convolute: type = "Convolute"; break;
			case NodeType::Threshold: type = "Threshold"; break;
			case NodeType::BrightnessContrast: type = "BrightnessContrast"; break;
			case NodeType::Script: type = "Script"; break;
			case NodeType::NormalMap: type = "NormalMap"; break;
			case NodeType::Grayscale: type = "Grayscale"; break;
		}
		jnd["type"] = type;
		nodes.push_back(jnd);
	}

	Json conns = Json::array();
	for (unsigned int cid : m_system->connections()) {
		auto conn = m_system->getConnection(cid);
		Json con;
		con["src"] = conn->src;
		con["dest"] = conn->dest;
		con["destParam"] = conn->destParam;
		conns.push_back(con);
	}

	json["nodes"] = nodes;
	json["conns"] = conns;
}
