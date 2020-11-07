#pragma once
#include "bst.h"

typedef char* String;
typedef struct listNode {
    String course;
    BST students;
    struct listNode* next;
} *CourseNodePtr;

typedef struct list {
    CourseNodePtr head;
} CourseList;

CourseList new_list();
CourseNodePtr search_course_node(CourseList* self, String course);
void insert_in_order(CourseList* self, String course);
void delete_list(CourseList* self, String course);
void destroy_list(CourseList* self);