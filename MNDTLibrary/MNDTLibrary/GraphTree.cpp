#include "GraphTree.h"

GraphTree::GraphTree(C_UINT32 nodeSize)
{
	_nodeSize = nodeSize;
	_graphNodes = new GraphNode[nodeSize];

	for (UINT32 index = 0; index < nodeSize; index++)
	{
		GraphNode* graphNode = &_graphNodes[index];
		graphNode->next = index;
		graphNode->rank = 0;
		graphNode->size = 1;
	}
}

UINT32 GraphTree::Find(C_UINT32 index)
{
	UINT32 next = index;

	while (next != _graphNodes[next].next)
	{
		next = _graphNodes[next].next;
	}

	_graphNodes[index].next = next;

	return next;
}

void GraphTree::Merge(C_UINT32 index1, C_UINT32 index2)
{
	GraphNode& graphNode1 = _graphNodes[index1];
	GraphNode& graphNode2 = _graphNodes[index2];

	if (graphNode1.rank > graphNode2.rank)
	{
		graphNode2.next = index1;
		graphNode1.size += graphNode2.size;
	}
	else
	{
		graphNode1.next = index2;
		graphNode2.size += graphNode1.size;

		if (graphNode1.rank == graphNode2.rank)
		{
			graphNode2.rank++;
		}
	}
	_nodeSize--;
}


GraphTree::~GraphTree()
{
	delete[] _graphNodes;
}