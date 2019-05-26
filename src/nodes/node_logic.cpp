#include "node_logic.h"

#include <numeric>

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

NodeSystem::NodeSystem() {
	create<OutputNode>();
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
}

void NodeSystem::clear(int width, int height) {
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
	PixelData out(in.width(), in.height());

	//#pragma omp parallel for schedule(dynamic)
	for (int y = 0; y < in.height(); y++) {
		for (int x = 0; x < in.width(); x++) {
			process(in, out, x, y);
		}
	}
	return out;
}

void NodeSystem::process(const PixelData& in, PixelData& out, int x, int y) {
	// Reset
	for (auto&& nid : m_usedNodes) {
		auto& node = m_nodes[nid];
		node->m_solved = false;
	}

	int i = 0;
	std::vector<int> toRemove;
	for (auto&& cid : m_usedConnections) {
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

		if (!src->m_solved) {
			src->m_lastSample = src->process(in, x, y);
			src->m_solved = true;
		}
		dest->param(conn->destParam).value = src->m_lastSample;

		if (dest->type() == NodeType::Output && !dest->m_solved) {
			Color col = dest->process(in, x, y);
			out.set(x, y, col.r, col.g, col.b, col.a);
			dest->m_solved = true;
		}
	}

	// Cleanup
	if (!toRemove.empty()) {
		std::sort(toRemove.begin(), toRemove.end());
		std::reverse(toRemove.begin(), toRemove.end());
		for (int idx : toRemove) {
			auto pos = std::find(m_usedConnections.begin(), m_usedConnections.end(), idx);
			if (pos == m_usedConnections.end()) return;

			m_lock.lock();
			m_usedConnections.erase(pos);
			m_connections[idx].reset();
			m_lock.unlock();
		}
	}
}

OutputNode::OutputNode() {
	addParam("In");
}
