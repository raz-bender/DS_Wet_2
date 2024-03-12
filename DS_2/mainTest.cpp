//
// Created by raz29 on 10/02/2024.
//
#include <string>
#include <iostream>
#include "../AvlTree.h"

#include <cstdlib> 
#include <string>
#include <cassert>  
#include <vector>
#include <mutex>
#include <random>
using namespace std;

using std::cout;

void TestRankTree()
{
	AvlTree<int, int> tree = AvlTree<int, int>();
	for (int i = 1; i < 10; i++)
	{
		tree.insert(i, i);
	}
	assert(tree.getNodeRank(tree.find(7)) == 7);
	for (int i = 1; i < 10; i++)
	{
		tree.insert(i, i + 1, true);
	}
	tree.printBinaryTree(5);
	tree.remove(4,4);
	tree.remove(4,5);
	tree.remove(5,5);
	tree.remove(5,6);
	assert(tree.getNodeRank(tree.find(9, 9)) == 13);

	AvlTree<int, int> tree2 = AvlTree<int, int>();
	for (int i = 1; i <= 1000; i++)
	{
		tree2.insert(i, i);
	}
	assert(tree2.getNodeRank(tree2.find(7)) == 7);
	assert(tree2.getNodeRank(tree2.find(456, 456)) == 456);
	int a = tree2.getNodeRank(tree2.find(999));
	for (int i = 1; i <= 20; i++)
	{
		tree2.remove(50*i);
	}
	int b = tree2.getNodeRank(tree2.find(999));
	assert(tree2.getNodeRank(tree2.find(999)) == 980);

	printf("Rank tree test passed\n");
}

void TestOtherTree()
{
	AvlTree<int, int> tree = AvlTree<int, int>();
	for (int i = 1; i <= 14; i++)
	{
		tree.insert(i, i);
	}
	for (int i = 1; i <= 4; i++)
	{
		tree.insert(i, i);
	}
	assert(tree.getSize() == 14);
	for (int i = 1; i <= 4; i++)
	{
		tree.insert(i, i, true);
	}

	assert(tree.getSize() == 18);
	tree.setValueToNodes(tree.find(12), tree.find(4), 5);
	tree.setValueToNodes(tree.find(13), tree.find(5), 10);
	assert(tree.getNodeCalculatedValue(tree.find(7)) == 15);
	assert(tree.getNodeCalculatedValue(tree.find(13)) == 10);
	assert(tree.getNodeCalculatedValue(tree.find(14)) == 0);
	assert(tree.getNodeCalculatedValue(tree.find(4)) == 5);
	assert(tree.getNodeCalculatedValue(tree.find(3)) == 0);


	for (int i = 1; i <= 4; i++)
	{
		tree.insert(4, 4, true);
	}
	tree.insert(5,6,true);
	tree.printBinaryTree(5);
	printf("Other tree test passed\n");
}


int main() {
	TestOtherTree();
	TestRankTree();
}