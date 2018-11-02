#include <iostream>
#include "Tree.hpp"

using namespace std;

int main()
{
	Tree<char> tree;
	
	tree.createTree('@');
	tree.preOrder();
	tree.midOrder();
	tree.postOrder();
	tree.levelOrder();
	
	tree.delLeft('L');
	tree.delRight('C');
	tree.delLeft('C');
	
	return 0;
}
