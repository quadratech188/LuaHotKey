#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <unordered_map>

template <typename T> class AttributeTree {
private:
	struct AttributeNode {
		std::unique_ptr<AttributeNode> defaultNode;
		std::unordered_map<int, AttributeNode> nodes;
		std::optional<T> value;
	};

	AttributeNode root;

	bool callIncludingDefault(std::span<int> indexArray, std::function<void(T)> func, int currentIndex, AttributeNode& currentNode) {
		if (indexArray.size() == currentIndex) {
			if (currentNode.value.has_value()) {
				func(currentNode.value.value());
			}
			return true;
		}

		bool found = false;

		auto it = currentNode.nodes.find(indexArray[currentIndex]);
		if (it != currentNode.nodes.end()) {
			found |= callIncludingDefault(indexArray, func, currentIndex + 1, it->second);
		}
		if (currentNode.defaultNode != nullptr) {
			found |= callIncludingDefault(indexArray, func, currentIndex + 1, *currentNode.defaultNode);
		}
		return found;
	}
public:
	bool callIncludingDefault(std::span<int> indexArray, std::function<void(T)> func) {
		return callIncludingDefault(indexArray, func, 0, root);
	}

	T& operator[](std::span<std::optional<int>> indexArray) {
		AttributeNode* node = &root;
		for (const auto& it: indexArray) {
			if (it.has_value()) {
				node = &node->nodes[it.value()];
			}
			else {
				if (node->defaultNode == nullptr) {
					node->defaultNode = std::make_unique<AttributeNode>();
				}
				// Workaround
				node = node->defaultNode.get();
			}
		}
		if (!node->value.has_value()) {
			node->value.emplace();
		}
		return node->value.value();
	}
};
