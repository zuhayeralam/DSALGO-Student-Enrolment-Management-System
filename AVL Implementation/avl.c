#include<stdlib.h>
#include<stdio.h>
#include "avl.h"

AVL new_avl()
{
    AVL temp;
    temp.root = NULL;
    return temp;
}

/*
 * Function: find_avl_node
 * -----------------------
 *   helper function used by find_avl
 *
 *   self: AVLNodePtr, where the finding operation begin
 *         usually a root of the tree is passed by find_avl function
 *   n: the number which will be searched for in the tree
 *
 *   returns: AVLNodePtr, the node containing n
 */
AVLNodePtr find_avl_node(AVLNodePtr self, long n)
{
    if (self == NULL || (n == self->id))
    {
        return self;
    }
    else if (n < self->id)
    {
        return find_avl_node(self->left, n);
    }
    else
    {
        return find_avl_node(self->right, n);
    }
}

/*
 * Function: find_avl
 * ------------------
 *   finds a number in the given tree which matches the given number
 *   using the helper function find_avl_node
 *
 *   self: address of the tree where the number will be searched
 *   n: the number which will be searched for in the tree
 *
 *   returns: AVLNodePtr, the node containing n
 */
AVLNodePtr find_avl(AVL* self, long n)
{
    return find_avl_node(self->root, n);
}

/*
 * Function: find_avl
 * ------------------
 *   returns height of a tree
 *
 *   self: tree node of which the height will be counted
 *
 *   returns: height of the tree
 */
int height(AVLNodePtr self)
{
    if (self == NULL)
    {
        return 0;
    }
    else
    {
        int l = height(self->left);
        int r = height(self->right);
        if (l < r)
        {
            return 1 + r;
        }
        else
        {
            return 1 + l;
        }
    }
}
/*
 * Function: find_avl
 * ------------------
 *   compares the height of two tree nodes and returns the difference
 *
 *   self: the parent tree node of two tree nodes(which will be compared)
 *
 *   returns: difference in height of two trees
 */
int height_difference(AVLNodePtr self)
{
    int diff = 0;
    if (self != NULL)
    {
        diff = height(self->left) - height(self->right);
    }
    return diff;
}

/* www.geeksforgeeks.org was consulted for the idea of this code
 * Function: left_rotate
 * ---------------------
 *   performs left rotation in the given tree node
 *
 *   self: the tree node where the rotation will occur
 *   www.geeksforgeeks.org was consulted for the idea of this code
 *   returns: current node in the position of given tree node
 */
AVLNodePtr left_rotate(AVLNodePtr self)
{
    AVLNodePtr y = self->right;
    AVLNodePtr temp = y->left;
    y->left = self;
    self->right = temp;
    return y;
}


/*
 * Function: left_rotate
 * ---------------------
 *   performs right rotation in the given tree node
 *
 *   self: the tree node where the rotation will occur
 *
 *   returns: current node in the position of given tree node
 */
AVLNodePtr right_rotate(AVLNodePtr self)
{
    AVLNodePtr y = self->left;
    AVLNodePtr temp = y->right;
    y->right = self;
    self->left = temp;
    return y;
}

/* www.geeksforgeeks.org was consulted for the idea of this code
 * Function: insert_avl_node
 * -------------------------
 *   helper function used by insert_avl function
 *
 *   self: node where the insertion operation begin
 *   n: the number which will be inserted in the node
 *  
 *   returns: self, the root node of the tree after insertion
 */
AVLNodePtr insert_avl_node(AVLNodePtr self, long n)
{   /* found where to put it*/
    int diff = 0;
    if (self == NULL)
    {
        self = malloc(sizeof * self);
        self->id = n;
        self->left = self->right = NULL;

    }
    else if (n < self->id)
    {
        self->left = insert_avl_node(self->left, n);
    }
    else if (n > self->id)
    {
        self->right = insert_avl_node(self->right, n);
    }

    diff = height_difference(self);

    if (diff > 1 && n < self->left->id)
    {
        return right_rotate(self);
    }
    else if (diff < -1 && n > self->right->id)
    {
        self->left = left_rotate(self->left);
        return right_rotate(self);
    }
    else if (diff > 1 && n > self->left->id)
    {
        return left_rotate(self);
    }
    else if (diff < -1 && n < self->right->id)
    {
        return left_rotate(self);
    }
    return self;
}

/* 
 * Function: insert_avl
 * --------------------
 *   passing the root of given tree the helper function insert_avl_node,
 *   creates a new tree node containing the given number.
 *   inserts the node in the tree
 *
 *   self: address of the tree where the node will be inserted
 *   n: the number which will be inserted in the node
 */
void insert_avl(AVL* self, long n)
{
    self->root = insert_avl_node(self->root, n);
}

/*
 * Function: min_node
 * ------------------
 *   returns the child of a given AVL tree node which contains
 *   the lowest value
 *
 *   self: address of the node where the desired node will be searched for
 *
 *   returns: AVLNodePtr, the node containing lowest balue
 */
AVLNodePtr min_node(AVLNodePtr self)
{
    AVLNodePtr current = self;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

/* www.geeksforgeeks.org was consulted for the idea of this code
 * Function: delete_avl_node
 * -------------------------
 *   helper function used by delete_avl function
 *
 *   self: AVLNodePtr, where the deletion operation begin
 *   n: the number which will be deleted in the node
 *
 *   returns: self, the root node of the tree after deletion
 */
AVLNodePtr delete_avl_node(AVLNodePtr self, long n)
{
    int diff = 0;
    if (self != NULL)
    {
        if (n == self->id) // found item
        {
            if (self->left != NULL && self->right != NULL)   // two child case 
            {
                AVLNodePtr successor = min_node(self->right);
                self->id = successor->id;
                self->right = delete_avl_node(self->right, self->id);
            }
            else        // one or zero child case 
            {
                AVLNodePtr to_free = self;
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
            self->left = delete_avl_node(self->left, n);
        }
        else
        {
            self->right = delete_avl_node(self->right, n);
        }
    }

    diff = height_difference(self);

    if (diff > 1 && height_difference(self->left) >= 0)
    {
        return right_rotate(self);
    }
    else if (diff > 1 && height_difference(self->left) < 0)
    {
        self->left = left_rotate(self->left);
        return right_rotate(self);
    }
    else if (diff < -1 && height_difference(self->right) <= 0)
    {
        return left_rotate(self);
    }
    else if (diff < -1 && height_difference(self->right) > 0)
    {
        return left_rotate(self);
    }
    return self;
}

/*
 * Function: delete_avl
 * --------------------
 *   passing the root of given tree to the helper function delete_avl_node,
 *   removes the tree node containing the given number.
 *   updates the current tree
 *
 *   self: address of the tree where the node will be removed
 *   n: the number which will be deleted in the node
 */
void delete_avl(AVL* self, long n)
{
    self->root = delete_avl_node(self->root, n);
}

/*
 * Function: print_in_order_avl_node
 * ---------------------------------
 *   helper function of print_in_order_avl
 *
 *   self: AVLNodePtr, node where the printiong operation start
 */
void print_in_order_avl_node(AVLNodePtr self)
{
    if (self != NULL)
    {
        print_in_order_avl_node(self->left);
        if (self->id >= MIN_ID && self->id <= MAX_ID) {
            printf("%d\n", self->id);
        }
        print_in_order_avl_node(self->right);
    }
}

/*
 * Function: print_in_order_avl
 * ----------------------------
 *   passes the root of given tree to the helper function print_in_order_avl_node.
 *   which prints element of every tree node in order.
 *
 *   self: address of the tree which will be printed
 */
void print_in_order_avl(AVL* self)
{
    print_in_order_avl_node(self->root);
}

/*
 * Function: count_avl_node
 * ------------------------
 *   helper function of count_avl
 *
 *   return: count, total number of child nodes of a given node
 */
int count_avl_node(AVLNodePtr self)
{
    int count = 1;
    if (self->left != NULL)
    {
        count += count_avl_node(self->left);
    }
    if (self->right != NULL)
    {
        count += count_avl_node(self->right);
    }
    return count;
}

/*
 * Function: count_avl
 * -------------------
 *   returns the total number of node of a tree
 *   uses the helper function count_avl_node
 *
 *   return: count, total number of nodes in a tree
 */
int count_avl(AVL* self)
{
    int count = 0;
    if (self->root != NULL) {
        count = count_avl_node(self->root);
    }
    return count;
}

/*
 * Function: destroy_avl_node
 * --------------------------
 *   frees memory of children nodes given a node
 *
 *   self: address of the node to be destroyed
 */
void destroy_avl_node(AVLNodePtr self)
{
    if (self != NULL) {
        destroy_avl_node(self->right);
        destroy_avl_node(self->left);
        free(self);
    }
}

/*
 * Function: destroy_avl
 * ---------------------
 *   frees memory of a AVL using
 *   the helper function destroy_avl_node
 *
 *   self: address of the tree which will be destroyed
 */
void destroy_avl(AVL* self)
{
    destroy_avl_node(self->root);
}