#ifndef NODE_H
#define NODE_H

#include <array>
#include <stack>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <algorithm>
#include <optional>
#include <utility>

#include "image.h"

constexpr unsigned int MaxNodes = 128;
constexpr unsigned int MaxConnections = MaxNodes * 2;

enum class NodeType {
	None = 0,
	Color,
	Image,
	Output,
	Multiply,
	Add,
	Threshold,
	Dilate,
	Erode,
	Convolute,
	Median
};

class NodeSystem;
class Node {
	friend class NodeSystem;
public:
	struct Param {
		Color value;
		bool connected{ false };
	};

	Node() = default;
	virtual ~Node() = default;

	virtual NodeType type() { return NodeType::None; }
	virtual Color process(const PixelData& in, float x, float y) { return { }; }

	unsigned int id() const { return m_id; }

	void addParam(const std::string& name);
	Param& param(unsigned int id);
	Color color(unsigned int id) { return param(id).value; }
	std::string paramName(unsigned int id);

	unsigned int paramCount() const { return m_params.size(); }

protected:
	const Color def = { 0.0f, 0.0f, 0.0f, 1.0f };

	unsigned int m_id{ 0 };
	bool m_solved{ false };

	std::vector<Param> m_params;
	std::vector<std::string> m_paramNames;

	Color m_lastSample{ 0.0f, 0.0f, 0.0f, 1.0f };
};
using NodePtr = std::unique_ptr<Node>;

class OutputNode : public Node {
public:
	OutputNode();
	virtual NodeType type() override { return NodeType::Output; }
	virtual Color process(const PixelData& in, float x, float y) override { return color(0); }
};

class NodeSystem {
public:
	struct Connection {
		unsigned int src, dest, destParam;

		Connection() = default;
		~Connection() = default;
	};

	NodeSystem();
	~NodeSystem() = default;

	template <class T, typename... Args>
	unsigned int create(Args&&... args) {
		// is it full?
		if (m_usedNodes.size() == MaxNodes-1) return UINT32_MAX;

		m_lock.lock();
		// find a free spot
		unsigned int spot = 0;
		for (spot = 0; spot < MaxNodes; spot++)
			if (!m_nodes[spot]) break;
		m_usedNodes.push_back(spot);

		// create node
		T* node = new T(std::forward<Args>(args)...);
		node->m_id = spot;
		m_nodes[spot] = std::unique_ptr<T>(node);

		m_lock.unlock();
		return spot;
	}

	void destroy(unsigned int id);
	void clear(int width, int height);

	template <class T>
	T* get(unsigned int id) {
		auto pos = std::find(m_usedNodes.begin(), m_usedNodes.end(), id);
		if (pos == m_usedNodes.end()) return nullptr;
		return dynamic_cast<T*>(m_nodes[id].get());
	}

	unsigned int connect(unsigned int src, unsigned int dest, unsigned int param);
	void disconnect(unsigned int connection);
	unsigned int getConnection(unsigned int dest, unsigned int param);
	std::vector<unsigned int> getConnections(unsigned int dest, unsigned int param);
	unsigned int getConnection(unsigned int src, unsigned int dest, unsigned int param);
	unsigned int getNodeConnection(unsigned int src, unsigned int dest);
	std::vector<unsigned int> getAllConnections(unsigned int node);

	std::vector<unsigned int> nodes() { return m_usedNodes; }
	std::vector<unsigned int> connections() { return m_usedConnections; }

	Connection* getConnection(unsigned int id) { return m_connections[id].get(); }

	PixelData process(const PixelData& in);

private:
	std::vector<unsigned int> getConnectionsLastToFirst(unsigned int start);

	std::array<std::unique_ptr<Connection>, MaxConnections> m_connections;
	std::vector<unsigned int> m_usedConnections;

	std::array<NodePtr, MaxNodes> m_nodes;
	std::vector<unsigned int> m_usedNodes;

	std::mutex m_lock;

	void process(const PixelData& in, PixelData& out, float x, float y, const std::vector<unsigned int>& conns);
};

#endif // NODE_H
