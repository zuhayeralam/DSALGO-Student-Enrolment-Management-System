#pragma once
#define MIN_ID 0
#define MAX_ID 999999

typedef struct bstNode {
	long id;
	struct bstNode* left;
	struct bstNode* right;
} *BSTNodePtr;

typedef struct bst {
	BSTNodePtr root;
} BST;

BST new_bst();
BSTNodePtr find_bst(BST* self, long n);
void insert_bst(BST* self, long n);
void delete_bst(BST* self, long n);
void print_in_order_bst(BST* self);
int count_bst(BST* self);
void destroy_bst(BST* self);