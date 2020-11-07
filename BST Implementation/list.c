#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "list.h"

CourseList new_list()
{
    CourseList temp;
    temp.head = NULL;
    return temp;
}

/*
 * Function: search_course_node
 * ----------------------------
 *   searches nodes of given list for given string
 *
 *   self: address of the list to be searched
 *   course: the name of the course to be searched for
 *
 *   returns: CourseNodePtr, the node of the list containing the coursename
 */
CourseNodePtr search_course_node(CourseList* self, String course)
{
    CourseNodePtr current = self->head;
    while (current != NULL)
    {
        if (strcmp(current->course, course) == 0)
        {
            return current;
        }
        current = current->next;
    }
}

/*
 * Function: inser_in_order
 * ------------------------
 *   creates a node(CourseNodePtr) with the given course name
 *   inserts the node into the given list maintaining alphabetic order
 *
 *   self: address of the list where the new node will be inserted
 *   course: the name of the course which will be inserted
 */
void insert_in_order(CourseList* self, String course)
{
    CourseNodePtr current = self->head;
    CourseNodePtr prev = NULL;
    CourseNodePtr new_node = malloc(sizeof *new_node);
    new_node->course = malloc((strlen(course) + 1));
    strcpy_s(new_node->course, strlen(course) + 1, course);
    new_node->next = NULL;
    new_node->students = new_bst();
    
    while (current != NULL && strcmp(current->course, course) < 0)
    {
        prev = current;
        current = current->next;
    }

    if (current == self->head) // at front 
    {
        new_node->next = current;
        self->head = new_node;
    }
    else                     // middle 
    {
        new_node->next = current;
        prev->next = new_node;
    }
}

/*
 * Function: delete_list
 * ---------------------
 *   deletes a node(CourseNodePtr) with the given course name
 *   from the given list
 *
 *   self: address of the list from where the node will be deleted
 *   course: the name of the course which will be removed
 */
void delete_list(CourseList* self, String course)
{
    CourseNodePtr current = self->head;
    CourseNodePtr prev = NULL;

    while (current != NULL) 
    {
        if (strcmp(current->course, course) == 0) 
        {
            if (prev == NULL)   // front of CourseList 
            {
                self->head = current->next;
                free(current);
                current = self->head;
            }
            else                // middle of CourseList 
            {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        }
        else 
        {
            prev = current;
            current = current->next;
        }
    }
}

/*
 * Function: destroy_list
 * ----------------------
 *   traverses through a given list
 *   frees memory of every list node inside the list and
 *   frees memory of the list itself
 *
 *   self: address of the list which will be destroyed
 */
void destroy_list(CourseList* self)
{
    CourseNodePtr current = self->head;
    while (current != NULL)
    {
        CourseNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }
    self->head = NULL;
}