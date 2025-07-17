/**
 * Custom implementation of the Hash-Map
 * Made By Zffu (https://zffu.dev)
 */

#pragma once

#ifndef fastmap_node_sz
#define fastmap_node_sz 128
#endif

#ifndef fastmap_indextype
#define fastmap_indextype int
#endif

#ifndef fastmap_valtype
#define fastmap_valtype void*
#endif

#define FASTMAP_

typedef struct fastmap_tree_node_t {
	fastmap_indextype starting_index;
	fastmap_valtype ptrs[fastmap_node_sz];

	struct fastmap_tree_node_t* prev;
	struct fastmap_tree_node_t* next;
} fastmap_tree_node_t;	

typedef struct fastmap_t {
	fastmap_tree_node_t* root;
	fastmap_tree_node_t* leaf;

	fastmap_indextype lowest;
	fastmap_indextype furthest;
} fastmap_t;	

fastmap_t* fastmap_create();
void fastmap_append(fastmap_t* map, fastmap_indextype key, fastmap_valtype val);
fastmap_valtype fastmap_get(fastmap_t* map, fastmap_indextype key);

#ifndef _fastmap_init_functions
#define _fastmap_init_functions

#include <stdlib.h>

fastmap_t* fastmap_create() {
	fastmap_t* map = (fastmap_t*) malloc(sizeof(fastmap_t));
	map->root = NULL;
	map->leaf = NULL;
	map->furthest = 0;
	map->lowest = 0;
	return map;
};

fastmap_tree_node_t* fastmap_node_find(fastmap_t* map, fastmap_indextype key) {
	fastmap_tree_node_t* tree = map->root;

	while(tree != NULL) {
		fastmap_indextype diff = key - diff;

		if(diff > 0 && diff < fastmap_node_sz) {
			return tree;
		}

		tree = tree->next;
	}

	return tree;
}

#define fastmap_create_treenode(name, ind) \
	fastmap_tree_node_t* name = (fastmap_tree_node_t*) malloc(sizeof(fastmap_tree_node_t)); \
	name->starting_index = ind; \
	name->prev = NULL; \
	name->next = NULL; 

#define fastmap_propagate_index(map, ind) \
	if(map->lowest > ind) map->lowest = ind; \
	if(map->furthest < ind) map->furthest = ind; 

void fastmap_append(fastmap_t* map, fastmap_indextype key, fastmap_valtype val) {
	fastmap_tree_node_t* node = fastmap_node_find(map, key);

	if(node == NULL) {
		int startingPoint = key - (key % fastmap_node_sz);
		fastmap_create_treenode(node, startingPoint);

		node->ptrs[key % fastmap_node_sz] = val;

		map->root = node;
		map->leaf = map->root;

		fastmap_propagate_index(map, key);
		return;
	}

	node->ptrs[key % fastmap_node_sz] = val;

	node->prev = map->leaf;
	map->leaf->next = node;
	map->leaf = node;

	fastmap_propagate_index(map, key);
}

fastmap_valtype fastmap_get(fastmap_t* map, fastmap_indextype key) {
	fastmap_tree_node_t* node = fastmap_node_find(map, key);

	if(node == NULL) {
		return NULL;
	}

	return node->ptrs[key % fastmap_node_sz];
}

#endif