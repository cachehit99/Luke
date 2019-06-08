#pragma once
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <optional>
#include <stack>


template <class Value>
class TernarySearchTree
{
	struct Node
	{
		enum { Left, Middle, Right, NumNodes };
		char key;
		std::unique_ptr<Value> value;
		std::array<std::unique_ptr<Node>, NumNodes> children;
	};

public:
	TernarySearchTree() : root_(nullptr) {}

	void Put(const std::string& key, const Value& value)
	{
		if (key.empty())
		{
			return;
		}

		size_t depth = 0;
		std::unique_ptr<Node>* pnode = &root_;
		while (depth < key.size())
		{
			const char c = key[depth];
			if (*pnode == nullptr)
			{
				pnode->reset(new Node);
				(*pnode)->key = c;
			}

			const std::unique_ptr<Node>& node = *pnode;
			if (c < node->key)
			{
				pnode = &node->children[Node::Left];
			}
			else if (c > node->key)
			{
				pnode = &node->children[Node::Right];
			}
			else if (depth < key.size() - 1)
			{
				pnode = &node->children[Node::Middle];
				depth++;
			}
			else
			{
				if (node->value == nullptr)
				{
					num_items++;
				}
				node->value.reset(new Value(value));
				if (max_depth < depth)
				{
					max_depth = depth;
				}
				return;
			}
		}
	}
	std::optional<Value> Get(const std::string& key)
	{
		auto pnode = Get(root_, key);
		if (pnode == nullptr)
		{
			return {};
		}
		else
		{
			return *pnode->get()->value;
		}
	}
	void Remove(const std::string& key)
	{
		if (key.empty())
		{
			return;
		}

		size_t depth = 0;
		std::unique_ptr<Node>* pnode = &root_;
		std::vector<unique_ptr<Node>*> trace;
		trace.reserve(max_depth);
		while (depth < key.size())
		{
			const char c = key[depth];
			if (*pnode == nullptr)
			{
				return;
			}

			const std::unique_ptr<Node>& node = *pnode;
			trace.push_back(pnode);

			if (c < node->key)
			{
				pnode = &node->children[Node::Left];
			}
			else if (c > node->key)
			{
				pnode = &node->children[Node::Right];
			}
			else if (depth == key.size() - 1)
			{
				break;
			}
			else
			{
				pnode = &node->children[Node::Middle];
				depth++;
			}
		}

		int idx = static_cast<int>(trace.size()) - 1;
		trace[idx]->get()->value.reset();
		num_items--;
		while (idx >= 0)
		{
			auto top = trace[idx--];

			bool removed = false;
			if (top->get()->value == nullptr)
			{
				bool has_child = false;
				for (int i = 0; i < Node::NumNodes; ++i)
				{
					if (top->get()->children[i] != nullptr)
					{
						has_child = true;
						break;
					}
				}
				if (!has_child)
				{
					top->reset();
					removed = true;
				}
			}
			if (!removed)
			{
				break;
			}
		}
	}
	std::vector<std::string> Keys()
	{
		std::vector<std::string> keys;
		keys.reserve(num_items);
		Collect(root_, keys, "");
		return keys;
	}
	std::vector<std::string> KeysWithPrefix(const string& prefix)
	{
		std::vector<std::string> keys;
		auto pnode = Get(root_, prefix);
		if (pnode != nullptr)
		{
			keys.reserve(num_items);
			keys.push_back(prefix);
			Collect((*pnode)->children[Node::Middle], keys, prefix);
			keys.shrink_to_fit();
		}
		return keys;
	}
	inline size_t Size() { return num_items; }

private:
	void Collect(const std::unique_ptr<Node>& node, std::vector<std::string>& keys, std::string prefix)
	{
		if (node == nullptr)
		{
			return;
		}

		Collect(node->children[Node::Left], keys, prefix);
		if (node->value != nullptr)
		{
			keys.push_back(prefix + node->key);
		}
		Collect(node->children[Node::Middle], keys, prefix + node->key);
		Collect(node->children[Node::Right], keys, prefix);
	}
	std::unique_ptr<Node>* Get(std::unique_ptr<Node>& node, const string& key)
	{
		if (key.empty())
		{
			return nullptr;
		}

		size_t depth = 0;
		std::unique_ptr<Node>* pnode = &node;
		while (depth < key.size())
		{
			const char c = key[depth];
			if (*pnode == nullptr)
			{
				return nullptr;
			}

			const std::unique_ptr<Node>& node = *pnode;
			if (c < node->key)
			{
				pnode = &node->children[Node::Left];
			}
			else if (c > node->key)
			{
				pnode = &node->children[Node::Right];
			}
			else if (depth == key.size() - 1)
			{
				return pnode;
			}
			else
			{
				pnode = &node->children[Node::Middle];
				depth++;
			}
		}
		return nullptr;
	}

	size_t max_depth = 0U;
	size_t num_items = 0U;
	std::unique_ptr<Node> root_;
};
