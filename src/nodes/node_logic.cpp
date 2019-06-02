#include "node_logic.h"

#include <iostream>
#include <numeric>

#include "nodes.hpp"

void Node::addParam(const std::string& name) {
	m_paramNames.push_back(name);
	m_params.push_back(Param{});
}

Node::Param& Node::param(unsigned int id) {
	return m_params[id];
}

std::string Node::paramName(unsigned int id) {
	return m_paramNames[id];
}

PixelData Node::process(const PixelData& in) {
	reset();

	PixelData out(in.width(), in.height());
	#pragma omp parallel for schedule(dynamic)
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

NodeSystem::NodeSystem() {
	create<OutputNode>();
}

NodeSystem::~NodeSystem() {
	if (m_ctx) {
		m_timerThread.~thread();
		Cap_releaseContext(m_ctx);
	}
}

void NodeSystem::startCapture() {
	// Initialize WebCam if available
	m_ctx = Cap_createContext();
	if (m_ctx) {
		int dID = 0;
		int fID = 0;
		for(int device = 0; device < Cap_getDeviceCount(m_ctx); device++) {
			std::string deviceName = Cap_getDeviceName(m_ctx, device);
			std::cout << device << ") " << deviceName << std::endl;
			for(int format = 0; format < Cap_getNumFormats(m_ctx, device); format++) {
				CapFormatInfo finfo;
				Cap_getFormatInfo(m_ctx, device, format, &finfo);

				std::string fourcc{};
				for(uint32_t i = 0; i < 4; i++) {
					fourcc += (char)(finfo.fourcc & 0xFF);
					finfo.fourcc >>= 8;
				}

				std::cout << "\t" << finfo.width << "x" << finfo.height << " " << fourcc << " " << finfo.fps << "fps" << std::endl;

				if (finfo.width == 320 && finfo.height == 240) {
					dID = device;
					fID = format;
				}
			}
		}

		m_streamID = Cap_openStream(m_ctx, dID, fID);
		if (m_streamID != -1) {
			Cap_getFormatInfo(m_ctx, dID, fID, &m_capInfo);
			m_lastCamFrame = PixelData(m_capInfo.width, m_capInfo.height);

			// Start capturing frames
			m_timerThread = std::thread([](CapContext ctx, int stream, NodeSystem* sys) {
				while (true) {
					if (Cap_hasNewFrame(ctx, stream) == 1) {
						std::vector<unsigned char> pixels;
						pixels.resize(sys->cameraFrame().width() * sys->cameraFrame().height() * 3);
						Cap_captureFrame(ctx, stream, &pixels[0], pixels.size());

						for (int k = 0; k < pixels.size() / 3; k++) {
							int x = k % sys->cameraFrame().width();
							int y = k / sys->cameraFrame().width();
							int j = k * 3;
							sys->cameraFrame().set(
								x, y,
								float(pixels[j + 0]) / 255.0f,
								float(pixels[j + 1]) / 255.0f,
								float(pixels[j + 2]) / 255.0f,
								1.0f
							);
						}
						sys->hasFrame(true);
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 10));
				}
			}, m_ctx, m_streamID, this);
			m_timerThread.detach();
			m_capturing = true;
		}
	}
}

void NodeSystem::stopCapture() {
	if (m_ctx) {
		m_timerThread.~thread();
		Cap_releaseContext(m_ctx);
		m_capturing = false;
	}
}

void NodeSystem::destroy(unsigned int id) {
	auto pos = std::find(m_usedNodes.begin(), m_usedNodes.end(), id);
	if (pos == m_usedNodes.end()) return;
	for (unsigned int cid : getAllConnections(id)) {
		disconnect(cid);
	}

	m_lock.lock();
	m_usedNodes.erase(pos);
	m_nodes[id].reset();
	m_lock.unlock();

	int cnt = 0;
	for (auto nid : m_usedNodes) {
		if (get<Node>(nid)->type() == NodeType::WebCam) {
			cnt++;
		}
	}

	if (cnt == 0) {
		stopCapture();
	}
}

void NodeSystem::clear() {
	m_lock.lock();
	m_usedNodes.clear();
	m_usedConnections.clear();

	for (auto&& ptr : m_nodes) if (ptr) ptr.reset();
	for (auto&& ptr : m_connections) if (ptr) ptr.reset();
	m_lock.unlock();
	create<OutputNode>();
}

unsigned int NodeSystem::connect(unsigned int src, unsigned int dest, unsigned int param) {
	// is it full?
	if (m_usedConnections.size() == MaxConnections-1) return UINT32_MAX;

	auto poss = std::find(m_usedNodes.begin(), m_usedNodes.end(), src);
	if (poss == m_usedNodes.end()) return UINT32_MAX;

	auto posd = std::find(m_usedNodes.begin(), m_usedNodes.end(), dest);
	if (posd == m_usedNodes.end()) return UINT32_MAX;

	if (getConnection(src, dest, param) != UINT32_MAX) {
		return UINT32_MAX;
	}

	m_lock.lock();
	// find a free spot
	unsigned int spot = 0;
	for (spot = 0; spot < MaxConnections; spot++)
		if (!m_connections[spot]) break;
	m_usedConnections.push_back(spot);

	Connection* conn = new Connection();
	conn->src = src;
	conn->dest = dest;
	conn->destParam = param;
	m_connections[spot] = std::unique_ptr<Connection>(conn);

	m_nodes[dest]->param(param).connected = true;

	m_lock.unlock();

	return spot;
}

void NodeSystem::disconnect(unsigned int connection) {
	auto pos = std::find(m_usedConnections.begin(), m_usedConnections.end(), connection);
	if (pos == m_usedConnections.end()) return;
	m_lock.lock();

	Connection* conn = m_connections[connection].get();
	m_nodes[conn->dest]->param(conn->destParam).connected = false;

	m_usedConnections.erase(pos);
	m_connections[connection].reset();
	m_lock.unlock();
}

unsigned int NodeSystem::getConnection(unsigned int dest, unsigned int param) {
	for (unsigned int cid : m_usedConnections) {
		Connection* conn = m_connections[cid].get();
		if (conn->dest == dest && conn->destParam == param) {
			return cid;
		}
	}
	return UINT32_MAX;
}

std::vector<unsigned int> NodeSystem::getConnections(unsigned int dest, unsigned int param) {
	std::vector<unsigned int> res;
	for (unsigned int cid : m_usedConnections) {
		Connection* conn = m_connections[cid].get();
		if (conn->dest == dest && conn->destParam == param) {
			res.push_back(cid);
		}
	}
	return res;
}

unsigned int NodeSystem::getConnection(unsigned int src, unsigned int dest, unsigned int param) {
	for (unsigned int cid : m_usedConnections) {
		Connection* conn = m_connections[cid].get();
		if (conn->src == src && conn->dest == dest && conn->destParam == param) {
			return cid;
		}
	}
	return UINT32_MAX;
}

unsigned int NodeSystem::getNodeConnection(unsigned int src, unsigned int dest) {
	for (unsigned int cid : m_usedConnections) {
		Connection* conn = m_connections[cid].get();
		if (conn->src == src && conn->dest == dest) {
			return cid;
		}
	}
	return UINT32_MAX;
}

std::vector<unsigned int> NodeSystem::getAllConnections(unsigned int node) {
	std::vector<unsigned int> res;
	for (unsigned int cid : m_usedConnections) {
		Connection* conn = m_connections[cid].get();
		if (conn->dest == node || conn->src == node) {
			res.push_back(cid);
		}
	}
	return res;
}

PixelData NodeSystem::process(const PixelData& in) {
	PixelData out{};

	auto conns = getConnectionsLastToFirst(0);
	std::reverse(conns.begin(), conns.end());
	m_imgIn = nullptr;

	// Reset
	for (auto&& nid : m_usedNodes) {
		auto& node = m_nodes[nid];
		node->m_solved = false;
	}

	int i = 0;
	std::vector<int> toRemove;
	for (auto&& cid : conns) {
		auto& conn = m_connections[cid];
		// Cleanup
		Node* src = get<Node>(conn->src);
		Node* dest = get<Node>(conn->dest);
		if (src == nullptr || dest == nullptr) {
			toRemove.push_back(i);
			continue;
		}
		i++;
		//

		if (src->type() == NodeType::Image) {
			m_imgIn = &((ImageNode*) src)->image;
		} else if (src->type() == NodeType::WebCam) {
			m_imgIn = &m_lastCamFrame;
		}
		dest->param(conn->destParam).value = src->process(/*m_imgIn == nullptr ? in : *m_imgIn*/in);

		if (dest->type() == NodeType::Output) {
			out = ((OutputNode*) dest)->param(0).value;
		}
	}

	// Cleanup
	if (!toRemove.empty()) {
		std::sort(toRemove.begin(), toRemove.end());
		std::reverse(toRemove.begin(), toRemove.end());
		for (int idx : toRemove) {
			auto pos = std::find(m_usedConnections.begin(), m_usedConnections.end(), idx);
			if (pos != m_usedConnections.end()) {
				m_lock.lock();
				m_usedConnections.erase(pos);
				m_connections[idx].reset();
				m_lock.unlock();
			}
		}
	}

	m_hasNewFrame = false;

	return out;
}

std::vector<unsigned int> NodeSystem::getConnectionsLastToFirst(unsigned int start) {
	std::vector<unsigned int> conns;
	for (int i = 0; i < get<Node>(start)->paramCount(); i++) {
		auto cs = getConnections(start, i);
		conns.insert(conns.end(), cs.begin(), cs.end());
		for (unsigned int cid : cs) {
			auto conn = getConnection(cid);
			auto rt = getConnectionsLastToFirst(conn->src);
			conns.insert(conns.end(), rt.begin(), rt.end());
		}
	}
	return conns;
}

OutputNode::OutputNode() {
	addParam("In");
}
