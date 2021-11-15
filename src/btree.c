#include "../include/btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct tree_node *Insert(int x, struct tree_node *t)
{
  // new tree_node can always be placed as a leaf (at the end)

  // 1) We check if tree (entire or sub-tree) is empty. If it is empty
  // we simply return a newly created node.

  if (Empty(t))
  {
    struct tree_node *n = malloc(sizeof(struct tree_node));
    n->right = NULL;
    n->left = NULL;
    n->item = x;
    return n;
  }

  // 2) If our target, x, is smaller than whatever value we are at - we call this function on the left sub-tree.
  // Also if multiple of the same elements are gonna be present, we deal with it here. That is why x <= t->item.
  // We always go left in this case.
  else if (x <= t->item) // duplicates will be placed as a left child
    t->left = Insert(x, t->left);

  // 3) If our target, x, is larger than whatever value we are at, it is dealt with here by calling
  // insert on the right subtree.

  else
    t->right = Insert(x, t->right);

  // 4) Return entire tree
  return t;
}

struct tree_node *Remove(int x, struct tree_node *t)
{

  // 1) We check if x is present anywhere in the tree, subtrees and all.
  // Obviously x is not present if the original tree is null either, in which case
  // we do nothing.
  if (Empty(t))
    return t;

  // 2) If target x is smaller than present node, try again with left subtree.
  if (x < t->item)
    t->left = Remove(x, t->left);

  // 3) If target x is larger than present node, try again with right subtree.
  if (x > t->item)
    t->right = Remove(x, t->right);

  // 4) If we have found the target to be removed. We do something.
  if (x == t->item)
  {

    // 4a) If the tree has no children
    if (!(t->right) && !(t->left))
    {
      free(t);
      // return null for previous subtree. There is nothing to swap around
      return NULL;
    }

    // 4b) The tree has 2 children
    else if (t->right && t->left)
    {
      // we know that whatever was to the right originally is larger than anything present on the left.
      // meaning that we can find the largest value on the left subtree and push the value up instead of deleting
      // whatever node

      // we have a pointer i point to left subtree.
      struct tree_node *i = t->left;
      while (i->right) // we go all the way to the right
        i = i->right;

      // We update value here.
      t->item = i->item;

      // then we call the function to remove whatever value we copied from the subtree.
      // we already handled removing leaf nodes after all.
      // We know the node is in left subtree.
      t->left = Remove(t->item, t->left);
    }
    // 4c) 1 child
    else
    {
      struct tree_node *child;
      // have child point to whichever subtree that exists
      (t->left) ? (child = t->left) : (child = t->right);

      // kill the current subtree
      free(t);

      // instead we have it branch to the only child
      return child;
    }
  }

  // 5) Return entire tree.
  return t;
}

int Contains(int x, struct tree_node *t)
{
  // 1) Check if empty. If empty(t) evaluates to 1 we know x is not in the tree or any subtree. False/0.
  if (Empty(t))
    return 0;

  // 2) If x is in tree return 1/true.
  if (t->item == x)
    return 1;

  // 3) if x is smaller than present node, try again in left subtree.
  if (x < t->item)
    return Contains(x, t->left);

  // 4) if x is larger than present node, try again in right subtree.
  if (x > t->item)
    return Contains(x, t->right);
}

// changing signature to **t be able to change the original tree not just a local copy t.
// In the assignment it states calling initialize(t) standalone should leave the original tree empty.
// this is not possible without changing the signature. Sure you can have this always return null and
// do something like root = initialize(t) but that's no different than just calling root = NULL
// without any logic and it isn't standalone.

struct tree_node *Initialize(struct tree_node **t)
{
  // If t is NULL we can't dereference it, so we just do nothing.
  if (!t)
    return NULL;
  return (*t = NULL);
}

int Empty(struct tree_node *t)
{
  return !t;
}

int Full(struct tree_node *t)
{
  /*
  It is never full as implemented in the tests.
  This is not the common definition of a full binary tree.
  Normally a binary tree is full when all leaves have 0 or 2 children.
  But oh well.
  */
  return 0;
}
