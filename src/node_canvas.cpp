#include "node_canvas.h"

constexpr int NodeWidth = 80;
constexpr int textPad = 3;
constexpr int GridSize = 8;

#include "nodes/nodes.hpp"

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
		renderer.line(b.x, y, b.x + b.width, y, 196, 212, 209, 50);
	}
	for (int x = b.x; x < b.x + b.width; x += GridSize) {
		renderer.line(x, b.y, x, b.y + b.height, 196, 212, 209, 50);
	}
	renderer.rect(b.x, b.y, b.width, b.height, 196, 212, 209, 50);
	//

	renderer.rect(b.x, b.y, b.width, b.height, 0, 0, 0, 80, true);

	auto nodes = m_system->nodes();
	std::sort(nodes.begin(), nodes.end(), [&](int a, int b) {
		return m_gnodes[a].selected < m_gnodes[b].selected;
	});

	m_gnodes[0].x = b.width - 12;
	m_gnodes[0].y = b.height / 2 - m_gnodes[0].height / 2;

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

		if (conn->src != conn->dest) {
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
			renderer.roundRect(mx - 3, my - 3, 6, 6, 6, 196, 212, 209);
		} else {
			const int rad = 10;
			const int w = rad * 3;
			const int nw = std::abs(connDestX - connSrcX) + w - 1;
			renderer.roundRect(
				connDestX - w / 2, connDestY,
				nw, dest.height - 16, rad,
				196, 212, 209
			);
			int mx = (connDestX + connSrcX) / 2;
			int my = connDestY + dest.height - 16;
			renderer.roundRect(mx - 3, my - 3, 6, 6, 6, 196, 212, 209);
		}
	}

	for (int nid : nodes) {
		GNode& gnode = m_gnodes[nid];
		Node* node = m_system->get<Node>(nid);
		int nx = gnode.x + b.x;
		int ny = gnode.y + b.y;

		int ngx = ::floor(gnode.x / GridSize) * GridSize + b.x;
		int ngy = ::floor(gnode.y / GridSize) * GridSize + b.y;

		if (node->type() != NodeType::Output) {
			if (gnode.selected && m_state == Moving) {
				renderer.rect(ngx, ngy, NodeWidth, gnode.height, 255, 255, 255, 50, true);
			}
			renderer.flatPanel(nx, ny, NodeWidth, gnode.height, 0, 3, 0.8f);
			renderer.pushClipping(nx + 1, ny + 1, NodeWidth - 2, gnode.height - 2);
			renderer.rect(nx + 1, ny + 1, NodeWidth - 2, 16, 0, 0, 0, 80, true);
			if (node->type() == NodeType::Color) {
				ColorNode* n = (ColorNode*) node;
				renderer.rect(nx + 4, ny + 20, 16, 12,
							  n->color.r * 255.0f,
							  n->color.g * 255.0f,
							  n->color.b * 255.0f,
							  255, true);
			}

			std::string txt = "";
			switch (node->type()) {
				default: break;
				case NodeType::Add: txt = "Soma"; break;
				case NodeType::Multiply: txt = "Mult"; break;
				case NodeType::Color: txt = "Cor"; break;
				case NodeType::Erode: txt = "Erodir"; break;
				case NodeType::Dilate: txt = "Dilatar"; break;
				case NodeType::Median: txt = "Mediano"; break;
				case NodeType::Convolute: txt = "Convoluir"; break;
				case NodeType::Threshold: txt = "Limiar"; break;
				case NodeType::Image: txt = "Imagem"; break;
				case NodeType::BrightnessContrast: txt = "Brlh./Ctr."; break;
				case NodeType::WebCam: txt = "WebCam"; break;
				case NodeType::Mirror: txt = "Espelhar"; break;
				case NodeType::FishEye: txt = "O. Peixe"; break;
				case NodeType::Mix: txt = "Mesclar"; break;
				case NodeType::Invert: txt = "Inverter"; break;
			}
			renderer.text(nx + 5, ny + 5, txt, 0, 0, 0, 128);
			renderer.text(nx + 4, ny + 4, txt, 255, 255, 255, 180);

			for (int i = 0; i < node->paramCount(); i++) {
				int py = inY(i) + ny;
				renderer.textSmall(nx + textPad, py + textPad, "\x9", 0, 0, 0, 200);
				renderer.textSmall(nx + textPad + 8, py + textPad, node->paramName(i), 0, 0, 0, 200);
			}

			renderer.popClipping();

			int py = inY(0) + ny;
			renderer.textSmall(nx + NodeWidth - (textPad + 8), py + textPad, "\x9", 0, 0, 0, 200);

			if (gnode.selected) {
				renderer.rect(nx + 2, ny + 2, NodeWidth - 4, gnode.height - 4, 255, 255, 255, 50, true);
			}

			//renderer.textSmall(nx + 4, py + 4, std::to_string(node->level()), 255, 0, 0, 255);
		} else {
			renderer.flatPanel(nx, ny, NodeWidth, gnode.height, 0, 2, 0.2f);
			int py = inY(0) + ny;
			renderer.textSmall(nx + textPad, py + textPad, "\x9", 0, 0, 0, 200);
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
