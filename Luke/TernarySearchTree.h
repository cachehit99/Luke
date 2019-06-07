#pragma once
#include <string>
#include <memory>
#include <array>
#include <optional>


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
		unique_ptr<Node>* pnode = &root_;
		while (depth < key.size())
		{
			const char c = key[depth];
			if (*pnode == nullptr)
			{
				pnode->reset(new Node);
				(*pnode)->key = c;
			}

			unique_ptr<Node>& node = *pnode;
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
				node->value.reset(new Value(value));
				return;
			}
		}
	}
	std::optional<Value> Get(const std::string& key)
	{
		if (key.empty())
		{
			return {};
		}

		size_t depth = 0;
		Node* node = root_.get();
		while (depth < key.size())
		{
			const char c = key[depth];
			if (node == nullptr)
			{
				return {};
			}

			if (c < node->key)
			{
				node = node->children[Node::Left].get();
			}
			else if (c > node->key)
			{
				node = node->children[Node::Right].get();
			}
			else if (depth == key.size() - 1)
			{
				return *node->value;
			}
			else
			{
				node = node->children[Node::Middle].get();
				depth++;
			}
		}
		return {};
	}

private:
	std::unique_ptr<Node> root_;
};
