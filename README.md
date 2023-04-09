# Assignment-5-142
Introduction
This code uses pthreads and a linked list to demonstrate parallel programming techniques. The program creates three threads: one for inserting values into the linked list, one for looking up values in the linked list, and one for removing values from the linked list.

Dependencies
The code requires the pthread library and a custom list library "list.h". Make sure that the pthread library is installed on your system.

Usage
Compile the code using the following command: gcc main.c list.c -o main -lpthread
Run the executable by typing ./main in the terminal.
The program will create three threads that perform the following operations:
Insert values into the linked list
Look up values in the linked list
Remove values from the linked list
After the threads have finished, the program will display the final contents of the linked list.
The program will then destroy the linked list and exit.
