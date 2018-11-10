#pragma once
#ifndef GRAPH_TREE_H
#define GRAPH_TREE_H
#include "general.h"

typedef struct {
	UINT32 rank;
	UINT32 next;
	UINT32 size;
} GraphNode;

class GraphTree
{
public:
	GraphTree(C_UINT32 nodeSize);

	~GraphTree();

	UINT32 Find(C_UINT32 index);

	void Merge(C_UINT32 index1, C_UINT32 index2);

	UINT32 NumSets() const { return _nodeSize; };

	UINT32 GetSize(C_UINT32 index) const { return _graphNodes[index].size; };
private:
	UINT32 _nodeSize;
	GraphNode* _graphNodes;
};

#endif
