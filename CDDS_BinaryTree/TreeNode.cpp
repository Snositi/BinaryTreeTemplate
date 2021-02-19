#include "TreeNode.h"
#include <iostream>
#include "raylib.h"

TreeNode::TreeNode(int value)
{
	m_value = value;
}

void TreeNode::draw(int x, int y, bool selected)
{
	//creates an array to store the int value
	static char buffer[10];

	//convert the int value into a static "char buffer"
	sprintf(buffer, "%d", m_value);

	//Draw the "outline" of a circle
	DrawCircle(x, y, 30, YELLOW);

	//Circle is green if the circle is selected
	if (selected)
		DrawCircle(x, y, 28, GREEN);

	else //circle is black if it is not selected
		DrawCircle(x, y, 28, BLACK);

	//Text is drawn on the circle
	DrawText(buffer, x - 12, y - 12, 12, WHITE);
}