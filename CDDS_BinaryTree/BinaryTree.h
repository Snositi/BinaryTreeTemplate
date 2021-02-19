#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once

class TreeNode;

class BinaryTree
{
public:

	BinaryTree() { m_root = nullptr; };
	~BinaryTree();

	bool isEmpty() const { return m_root == nullptr; };
	void insert(int value);
	void remove(int value);
	TreeNode* find(int value);

	void draw(TreeNode* selected = nullptr);

private:
	bool findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent);

	void draw(TreeNode*, int x, int y, int horizontalSpacing, TreeNode* selected = nullptr);

	TreeNode* m_root = nullptr;
};

#endif