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
#include <chrono>
#include <thread>
#include <functional>

#include "image.h"

#include "../json.hpp"
using Json = nlohmann::json;

extern "C" {
	#include "../openpnp-capture/include/openpnp-capture.h"
}

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
	Median,
	BrightnessContrast,
	WebCam,
	Mirror,
	FishEye,
	Mix,
	Invert,
	Distort,
	NormalMap,
	Grayscale
};

class NodeSystem;
class Node {
	friend class NodeSystem;
public:
	struct Param {
		PixelData value;
		bool connected{ false };
	};

	virtual void load(const Json& json) {}
	virtual void save(Json& json) {}

	Node() = default;
	virtual ~Node() = default;

	virtual NodeType type() { return NodeType::None; }

	virtual Color process(const PixelData& in, float x, float y) { return def; }

	unsigned int id() const { return m_id; }

	void addParam(const std::string& name);
	Param& param(unsigned int id);
	std::string paramName(unsigned int id);

	unsigned int paramCount() const { return m_params.size(); }

	virtual PixelData process(const PixelData& in);
	virtual void reset() {}

protected:
	const Color def = { 0.0f, 0.0f, 0.0f, 1.0f };

	unsigned int m_id{ 0 };
	bool m_solved{ false };

	std::vector<Param> m_params;
	std::vector<std::string> m_paramNames;

	NodeSystem* m_system;
};
using NodePtr = std::unique_ptr<Node>;

class OutputNode : public Node {
public:
	OutputNode();
	virtual NodeType type() override { return NodeType::Output; }
};

class NodeSystem {
public:
	struct Connection {
		unsigned int src, dest, destParam;

		Connection() = default;
		~Connection() = default;
	};

	NodeSystem();
	~NodeSystem();

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
		node->m_system = this;
		m_nodes[spot] = std::unique_ptr<T>(node);

		if (node->type() == NodeType::WebCam) {
			startCapture();
		}

		m_lock.unlock();
		return spot;
	}

	void destroy(unsigned int id);
	void clear();

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

	PixelData& cameraFrame() { return m_lastCamFrame; }
	bool capturing() const { return m_capturing; }
	bool hasFrame() const { return m_hasNewFrame; }
	void hasFrame(bool v) { m_hasNewFrame = v; }

private:
	std::vector<unsigned int> getConnectionsLastToFirst(unsigned int start);

	void startCapture();
	void stopCapture();

	std::array<std::unique_ptr<Connection>, MaxConnections> m_connections;
	std::vector<unsigned int> m_usedConnections;

	std::array<NodePtr, MaxNodes> m_nodes;
	std::vector<unsigned int> m_usedNodes;

	std::mutex m_lock;
	PixelData* m_imgIn;

	// WebCam Capture
	CapContext m_ctx{ nullptr };
	CapFormatInfo m_capInfo;
	int m_streamID;
	PixelData m_lastCamFrame;
	std::thread m_timerThread;
	bool m_capturing{ false }, m_hasNewFrame{ false };
};

#endif // NODE_H
