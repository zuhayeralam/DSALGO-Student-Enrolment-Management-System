#pragma once
#define MIN_ID 0
#define MAX_ID 999999

typedef struct avlNode {
	long id;
	struct avlNode* left;
	struct avlNode* right;
} *AVLNodePtr;

typedef struct avl {
	AVLNodePtr root;
} AVL;

AVL new_avl();
AVLNodePtr find_avl(AVL* self, long n);
int height(AVLNodePtr self);
void insert_avl(AVL* self, long n);
void delete_avl(AVL* self, long n);
void print_in_order_avl(AVL* self);
int count_avl(AVL* self);
void destroy_avl(AVL* self);