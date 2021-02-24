#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
	while (m_root)
		remove(m_root->getData());
}

void BinaryTree::insert(int value)
{
	//If the tree is empty, set the root to be a new node with the given value.
	if (!m_root)
	{
		m_root = new TreeNode(value);
		return;
	}
	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	TreeNode* pointer = m_root;
	//Create a TreeNode pointer that will act as an iterator pointing to the parent
	//of the current node and set it to the root.
	TreeNode* parentPointer = m_root;

	//Loop until the the current node iterator reaches a nullptr.
	while (pointer)
	{
		//Check if the value we want to add to the tree is less than the value at the current node.
		if (pointer->getData() > value)
		{
			//Set the parent node to be the current node before the current node moves positions.
			parentPointer = pointer;
			//Change the current node to be the child to its left and continue.
			pointer = pointer->getLeft();
		}//Check if the value we want to add to the tree is greater than the value at the current node.
		else if (pointer->getData() < value)
		{
			//Set the parent node to be the current node before the current node moves positions.
			parentPointer = pointer;
			//Change the current node to be the child to its right and continue.
			pointer = pointer->getRight();
		} //If the value is the same as a value already in the list return 
		else if (pointer->getData() == value)
			return;
		//end loop
	}
	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	if (value < parentPointer->getData())
	{
		TreeNode* newData = new TreeNode(value);
		parentPointer->setLeft(newData);
		newData->setLeft(pointer);
	}//Otherwise, insert the value to the right.
	else if (value > parentPointer->getData())
	{
		TreeNode* newData = new TreeNode(value);
		parentPointer->setRight(newData);
		newData->setRight(pointer);
	}
}

void BinaryTree::remove(int value)
{
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	TreeNode* nodeToRemove = m_root;
	//and another to hold a reference to its parent.
	TreeNode* nodeToRemoveParent = m_root;
	//Try to find the node that matches the value given and its parent in the tree.
	if (!findNode(value, nodeToRemove, nodeToRemoveParent))
	{
		//If the node cannot be found return.
		return;
	}
	//Check to see if the node has a right
	if (nodeToRemove->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		TreeNode* firstIterator = m_root;
		TreeNode* secondIterator = m_root;
		//Set the first iterator to point to the right child of the node we want to remove.
		findNode(nodeToRemove->getRight()->getData(), firstIterator, secondIterator);
		//Loop while the first iterator has a value to its left
		while (firstIterator->hasLeft())
		{
			//Set the second iterator to be the value of the first iterator.
			secondIterator = firstIterator;
			//Set the first iterator to be the value to the left of it
			firstIterator = firstIterator->getLeft();
			//end loop
		}
		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		nodeToRemove->setData(firstIterator->getData());
		//Check if the second iterator has a left child.
		if (secondIterator->hasLeft())
		{
			//Check if the left child stores the same data as the node we wanted to remove.
			if (secondIterator->getLeft()->getData() == nodeToRemove->getData())
			{
				//Set the second iterators left child to be the first iterators right child.
				secondIterator->setLeft(firstIterator->getRight());
			}
		}
		//Check if the second iterator has a right child.
		if (secondIterator->hasRight())
		{
			//Check if the right child contains the same data as the node we want to remove.
			if (secondIterator->getRight()->getData() == nodeToRemove->getData())
			{
				//Set the right child of the second iterator to be the right child of the first iterator.
				secondIterator->setRight(firstIterator->getRight());
			}
		}
		//Delete the first iterator
		delete firstIterator;
	} //Otherwise, if the node doesn't have a right child
	else
	{
		//check if the parent of the node to remove has a left child.
		if (nodeToRemoveParent->hasLeft())
		{
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (nodeToRemoveParent->getLeft()->getData() == nodeToRemove->getData())
			{
				//Set the left child of the parent node to be the left child of the node to remove.
				nodeToRemoveParent->setLeft(nodeToRemove->getLeft());
			}
		}
		//Check if the parent of the node to remove has a right child.
		if (nodeToRemoveParent->hasRight())
		{
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (nodeToRemoveParent->getRight()->getData() == nodeToRemove->getData())
			{
				//Set the right child of the parent node to be the left child of the node to remove.
				nodeToRemoveParent->setRight(nodeToRemove->getLeft());
			}
		}
		//Check if the node we want to remove is the root.
		if (nodeToRemove == m_root)
		{
			//Set the root to be its left child.
			m_root = m_root->getLeft();

			//Delete the pointer that points to the node to remove.
			delete nodeToRemove;
		}
	}	
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* iterator = m_root;

	//Loop through the tree while the iterator isn't nullptr.
	while (iterator)
	{
		//Check if the node has the data we want
		if (iterator->getData() == value)
		{
			//Return the iterator
			return iterator;
		}//If the node doesn't have the data we want, check to see if it's higher in value.
		else if (iterator->getData() < value)
		{
			//Set the iterator to be its current right child.
			iterator = iterator->getRight();
		}//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (iterator->getData() > value)
		{
			//Set the iterator to be its current left child.
			iterator = iterator->getLeft();
		}
		//end loop
	}
	//Return nullptr
	return nullptr;
}

void BinaryTree::draw(TreeNode* selected)
{
	if(m_root)
		draw(m_root, 400, 40, 400, selected);	
}

bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	//Create two iterators: one that will point to the current node to compare the search value to,
	TreeNode* currentNode = nodeFound;
	//and the other to hold a reference to the parent.
	TreeNode* parentReference = nodeParent;

	//Loop while the current node iterator isn't nullptr/
	while (currentNode)
	{
		//Check if the search value is the same as the current nodes data.
		if (searchValue == currentNode->getData())
		{
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			nodeFound = currentNode;
			nodeParent = parentReference;
			//Return true.
			return true;
		}
		//Check if the search value is greater than the value at the current node.
		if (searchValue > currentNode->getData())
		{
			//Set the parent node to be the current node.
			parentReference = currentNode;
			//Set the current node to be the child to the right of the current node.
			currentNode = currentNode->getRight();
		} //Check if the search value is less than the value at the current node.
		else if (searchValue < currentNode->getData())
		{
				//Set the parent node to be the current node.
			parentReference = currentNode;
				//Set the current node to be its left child.
			currentNode = currentNode->getLeft();
		}
	//end loop
	}
	//Return false.
	return false;
}

void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	horizontalSpacing /= 2;
	//checks if the current node is null
	if (currentNode)
	{
		//Draws the left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line inbetween the left child and current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
	}
	//Draws the current node
	currentNode->draw(x, y, (selected == currentNode));
}
