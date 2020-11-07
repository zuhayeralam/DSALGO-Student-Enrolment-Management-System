/*
 *  KIT 205 Assignment 2 PART-A
 *  Software to manage student enrolments
 *  BST Implentation
 *
 *  Author: Zuhayer Alam
 *  Date: 8 April 2020
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "list.h"
#include"bst.h"

 /*
  * Function: prompt_string
  * -----------------------
  *  Prompts the user and returns user input (string)
  *
  *  returns: user input (string)
  */
String prompt_string()
{
    char buffer[100];
    scanf_s("%s", buffer, 100);
    String string = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy_s(string, sizeof(char)* (strlen(buffer) + 1), buffer);
    return string;
}

/*
 * Function: prompt_int
 * --------------------
 *  Prompts the user and returns user input (integer)
 *
 *  returns: user input (integer)
 */
long prompt_int()
{
    long num;
    scanf_s("%d", &num);
    return num;
}

/*
 * Function: option_destroy_quit
 * -----------------------------
 *   frees memory of every BST node and BST inside the given list
 *   and then, frees the memory of every list node and the given list
 *
 *   my_list: address of the list which will be destroyed
 */
void option_destroy_quit(CourseList* my_list) 
{
    CourseNodePtr current = my_list->head;
    while (current != NULL)
   {
       destroy_bst(&(current->students));
       current = current->next;
   }
    destroy_list(my_list);
}

/*
 * Function: option_insert_course
 * ------------------------------
 *   insert a listnode to the given list in alphabetical order
 *   which contains the course name entered by user
 *
 *   my_list: address of the list which will store the listnode
 */
void option_insert_course(CourseList* my_list)
{
    printf("Enter course name: ");
    insert_in_order(my_list, prompt_string());
}

/*
 * Function: option_delete_course
 * ------------------------------
 *   delete a listnode from the given list
 *   which contains the course name entered by user
 *
 *   my_list: address of the list from which the listnode will be deleted
 */
void option_delete_course(CourseList* my_list)
{
    printf("Enter course name which you want to remove: ");
    delete_list(my_list, prompt_string());
}

/*
 * Function: option_enrol_student
 * ------------------------------
 *   stores student ID entered by user in a new BST node
 *   in the BST tree of the listnode
 *   which contains the course name entered by the user
 *
 *   my_list: address of the list which cointains the listnode
              where the student will be enrolled
 */
void option_enrol_student(CourseList* my_list)
{
    CourseNodePtr targeted_course;
    printf("Enter course name for enrollment: ");
    targeted_course = search_course_node(my_list, prompt_string());
    printf("Enter Student ID: ");
    insert_bst(&targeted_course->students, prompt_int());
}

/*
 * Function: option_unenrol_student
 * --------------------------------
 *   deletes the BST node where the student ID entered by user was stored
 *   from the BST tree of the listnode
 *   which contains the course name entered by the user
 *
 *   my_list: address of the list which cointains the listnode
              from where the student will be unenrolled
 */
void option_unenrol_student(CourseList* my_list)
{
    CourseNodePtr targeted_course;
    printf("Enter course name for unenrollment: ");
    targeted_course = search_course_node(my_list, prompt_string());
    printf("Enter Student ID: ");
    delete_bst(&targeted_course, prompt_int());
}

/*
 * Function: print_ordered_summary
 * -------------------------------
 *   traverses through the given list and for every listnode,
 *   prints the course name
 *   along with the total student numbers for each course after
 *   counting every BST node in the BST tree of the listnode
 *
 *   my_list: address of the list from which the summary
 *            will be produced and printed
 */
void print_ordered_summary(CourseList* my_list)
{
    CourseNodePtr current = my_list->head;
    while (current != NULL) 
    {
        printf("%s ", current->course);
        printf("%d\n", count_bst(&(current->students)));
        current = current->next;
    }
    printf("\n");
}

/*
 * Function: print_student_list
 * ----------------------------
 *   searches the listnode which contains the course name entered by user
 *   prints the student ID(s) in the BST nodes inside the BST tree of that course
 *   in ascending order
 *
 *   my_list: address of the list which will be searched for the course name
 *            received from user input.
 */
void print_student_list(CourseList* my_list)
{
    CourseNodePtr targeted_course;
    printf("Enter course name for ordered student list: ");
    targeted_course = search_course_node(my_list, prompt_string());
    print_in_order_bst(&(targeted_course->students));
}

/*
 * Function: print_course_list
 * ---------------------------
 *   traverses the given list and for every listnode,
 *   searches for the BST node containing student ID received from user input,
 *   in the BST tree. If the student exists in that tree
 *   then prints the course name
 *
 *   my_list: address of the list which will be searched for the course name
 *            received from user input.
 */
void print_course_list(CourseList* my_list)
{
    printf("Enter Student ID: ");
    long id = prompt_int();
    CourseNodePtr current = my_list->head;
    while (current != NULL) 
    {
        if (find_bst(&(current->students), id) != NULL) 
        {
            printf("%s \n", current->course);
        }
        current = current->next;
    }
}

int main(int argc, char* argv[]) {
    CourseList courses = new_list();
    int quit = 0;
    while (!quit)
    {
        int option = 0;
        printf("\n(0 = quit, 1 = Add Course, 2 = Remove Course, 3 = Enrol Student, 4 = Un-enrol student\n");
        printf("5 = Print summary, 6 = print list of students, 7 = print list of courses of a student)\n");
        printf("Enter option: ");
        scanf_s("%d", &option);
        switch (option)
        {
        case 0:
            quit = 1;
            break;
        case 1:
            option_insert_course(&courses);
            break;
        case 2:
            option_delete_course(&courses);
            break;
        case 3:
            option_enrol_student(&courses);
            break;
        case 4:
            option_unenrol_student(&courses);
            break;
        case 5:
            print_ordered_summary(&courses);
            break;
        case 6:
            print_student_list(&courses);
            break;
        case 7:
            print_course_list(&courses);
            break;
        }
    }
    option_destroy_quit(&courses);
}