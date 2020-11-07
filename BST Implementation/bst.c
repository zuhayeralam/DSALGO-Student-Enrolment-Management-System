#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

BST new_bst()
{
    BST temp;
    temp.root = NULL;
    return temp;
}

/*
 * Function: find_bst_node
 * -----------------------
 *   helper function used by find_bst
 *
 *   self: BSTNodePtr, where the finding operation begin
 *         usually a root of the tree is passed by find_bst function
 *   n: the number which will be searched for in the tree
 *
 *   returns: BSTNodePtr, the node containing n
 */
BSTNodePtr find_bst_node(BSTNodePtr self, long n)
{
    if (self == NULL || (n == self->id)) 
    {
        return self;
    }
    else if (n < self->id) 
    {
        return find_bst_node(self->left, n);
    }
    else 
    {
        return find_bst_node(self->right, n);
    }
}
/*
 * Function: find_bst
 * ------------------
 *   finds a number in the given tree which matches the given number
 *   using the helper function find_bst_node
 *
 *   self: address of the tree where the number will be searched
 *   n: the number which will be searched for in the tree
 *
 *   returns: BSTNodePtr, the node containing n
 */
BSTNodePtr find_bst(BST* self, long n)
{
    return find_bst_node(self->root, n);
}

/*
 * Function: insert_bst_node
 * ----------------------------
 *   helper function used by insert_bst function
 *
 *   self: node where the insertion operation begin
 *   n: the number which will be inserted in the node
 *
 *   returns: self, the root node of the tree after insertion
 */
BSTNodePtr insert_bst_node(BSTNodePtr self, long n)
{   /* found where to put it*/
    if (self == NULL)
    {
        self = malloc(sizeof * self);
        self->id = n;
        self->left = self->right = NULL;

    }
    else if (n < self->id) 
    {
        self->left = insert_bst_node(self->left, n);
    }
    else if (n > self->id) 
    {
        self->right = insert_bst_node(self->right, n);
    }
    return self;
}

/*
 * Function: insert_bst
 * ----------------------------   
 *   passing the root of given tree the helper function insert_bst_node,
 *   creates a new tree node containing the given number.
 *   inserts the node in the tree
 *
 *   self: address of the tree where the node will be inserted
 *   n: the number which will be inserted in the node
 */
void insert_bst(BST* self, long n)
{
    self->root = insert_bst_node(self->root, n);
}


/*
 * Function: min_node
 * ----------------------------
 *   returns the child of a given BST tree node which contains
 *   the lowest value
 *
 *   self: address of the node where the desired node will be searched for
 *
 *   returns: BSTNodePtr, the node containing lowest balue
 */
BSTNodePtr min_node(BSTNodePtr self)
{
    BSTNodePtr current = self;
    while (current->left != NULL) 
    {
        current = current->left;
    }
    return current;
}

/*
 * Function: delete_bst_node
 * ----------------------------
 *   helper function used by delete_bst function
 *
 *   self: BSTNodePtr, where the deletion operation begin
 *   n: the number which will be deleted in the node
 *
 *   returns: self, the root node of the tree after deletion
 */
BSTNodePtr delete_bst_node(BSTNodePtr self, long n)
{
    if (self != NULL) 
    {
        if (n == self->id) // found item
        {  
            if (self->left != NULL && self->right != NULL)   // two child case 
            {
                BSTNodePtr successor = min_node(self->right);
                self->id = successor->id;
                self->right = delete_bst_node(self->right, self->id);
            }
            else        // one or zero child case 
            {
                BSTNodePtr to_free = self;
                if (self->left) 
                {
                    self = self->left;
                }
                else 
                {
                    self = self->right;
                }
                free(to_free);
            }
        }
        else if (n < self->id) 
        {
            self->left = delete_bst_node(self->left, n);
        }
        else 
        {
            self->right = delete_bst_node(self->right, n);
        }
    }
    return self;
}

/*
 * Function: delete_bst
 * ----------------------------
 *   passing the root of given tree to the helper function delete_bst_node,
 *   removes the tree node containing the given number.
 *   updates the current tree
 *
 *   self: address of the tree where the node will be removed
 *   n: the number which will be deleted in the node
 */
void delete_bst(BST* self, long n)
{
    self->root = delete_bst_node(self->root, n);
}

/*
 * Function: print_in_order_bst_node
 * ---------------------------------
 *   helper function of print_in_order_bst
 *
 *   self: BSTNodePtr, node where the printiong operation start
 */
void print_in_order_bst_node(BSTNodePtr self)
{
    if (self != NULL) 
    {
        print_in_order_bst_node(self->left);
        if (self->id >= MIN_ID && self->id <= MAX_ID) {
            printf("%d\n", self->id);
        }
        print_in_order_bst_node(self->right);
    }
}

/*
 * Function: print_in_order_bst
 * ----------------------------
 *   passes the root of given tree to the helper function print_in_order_bst_node.
 *   which prints element of every tree node in order.
 *
 *   self: address of the tree which will be printed
 */
void print_in_order_bst(BST* self)
{
    print_in_order_bst_node(self->root);
}

/*
 * Function: count_bst_node
 * ------------------------
 *   helper function of count_bst
 *
 *   return: count, total number of child nodes of a given node
 */
int count_bst_node(BSTNodePtr self)
{
    int count = 1;
    if (self->left != NULL) 
    {
        count += count_bst_node(self->left);
    }
    if (self->right != NULL) 
    {
        count += count_bst_node(self->right);
    }
    return count;
}

/*
 * Function: count_bst
 * -------------------
 *   returns the total number of node of a tree
 *   uses the helper function count_bst_node
 *   
 *   return: count, total number of nodes in a tree
 */
int count_bst(BST* self)
{
    int count = 0;
    if (self->root != NULL) {
        count = count_bst_node(self->root);
    }
    return count;
}

/*
 * Function: destroy_bst_node
 * --------------------------
 *   frees memory of children nodes given a node
 *
 *   self: address of the node to be destroyed
 */
void destroy_bst_node(BSTNodePtr self)
{
    if (self != NULL) {
        destroy_bst_node(self->right);
        destroy_bst_node(self->left);
        free(self);
    }
}

/*
 * Function: destroy_bst
 * ---------------------
 *   frees memory of a BST using
 *   the helper function destroy_bst_node
 *
 *   self: address of the tree which will be destroyed
 */
void destroy_bst(BST* self)
{
        destroy_bst_node(self->root);
}
