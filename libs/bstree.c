#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bstree* bstree_create(char* key, int value)
{
    struct bstree* node;

    node = malloc(sizeof(*node));

    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

struct bstree* bstree_add(struct bstree* tree, char* key, int value)
{
    if (!tree) return bstree_create(key, value);

    if (strcmp(key, tree->key) < 0) {
        tree->left = bstree_add(tree->left, key, value);
    } else if (strcmp(key, tree->key) > 0) {
        tree->right = bstree_add(tree->right, key, value);
    }

    return tree;
}

struct bstree* bstree_lookup(struct bstree* tree, char* key)
{
    if (tree == NULL)
        return NULL;
    if (strcmp(key, tree->key) == 0) {
        return tree;
    } else if ((strcmp(key, tree->key) < 0)) {
        return bstree_lookup(tree->left, key);
    } else if ((strcmp(key, tree->key) > 0)) {
        return bstree_lookup(tree->right, key);
    }
    return NULL;
}

void delete_tree(struct bstree* tree)
{
    if (tree == NULL)
        return;
    delete_tree(tree->right);
    delete_tree(tree->left);
    free(tree);
}

struct bstree* delete_node(struct bstree* nodeTree, char* key) {
    if (nodeTree == NULL)
        return nodeTree;
    if (key < nodeTree->key)
        nodeTree->left = delete_node(nodeTree->left, key);
    else if (key > nodeTree->key)
        nodeTree->right = delete_node(nodeTree->right, key);
    else {
        if (nodeTree->left == NULL) {
            struct bstree* temp = nodeTree->right;
            free(nodeTree);
            return temp;
        }
        else if (nodeTree->right == NULL) {
            struct bstree* temp = nodeTree->left;
            free(nodeTree);
            return temp;
        }

        struct bstree* temp = bstree_min(nodeTree->right);

        nodeTree->key = temp->key;

        nodeTree->right = delete_node(nodeTree->right, temp->key);
    }
    return nodeTree;
}

struct bstree *bstree_min(struct bstree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    struct bstree *current = tree;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

struct bstree *bstree_max(struct bstree *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    struct bstree *current = tree;

    while (current->right != NULL)
    {
        current = current->right;
    }

    return current;
}