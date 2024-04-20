#include <stdio.h>
#include <stdlib.h>
#pragma once

struct bstree {
  char *key;
  int value;
  struct bstree *left;
  struct bstree *right;
};

struct bstree *bstree_create(char *key, int value);
struct bstree *bstree_add(struct bstree *tree, char *key, int value);
struct bstree *bstree_lookup(struct bstree *tree, char *key);
struct bstree *bstree_min(struct bstree *tree);
struct bstree *bstree_max(struct bstree *tree);
struct bstree *delete_node(struct bstree *nodeTree, char *key);
void delete_tree(struct bstree *tree);