/*****************************************************************************
# Author:           Aura Castellanos Calderon
# Project:          Project 3
# Name of file:     main.cpp
# Description:      file with the implementation of main.h where it contains 
                    the menu-based user interface to allow the user to use 
                    the all functions on the menu 
#****************************************************************************/

#include "bst.h"
#include "schedule.h"
#include <iostream>
#include <string>
#include <cstring>
#include <memory>


using namespace std;

int menu(); 


int main()
{
	
	cout << "Schedule program" << endl; 
<<<<<<< HEAD
	BST mytree;
	int result = menu(); 
	
=======


	BST mytree;

	int result = menu(); 

>>>>>>> c1ce0b27cb7d60cbd348a950a09c1a9648744760
	while((result == 1) || (result == 2)){
	
	   cout << endl;
	   if(result == 1){
    		int option = 0;
                cout << "Select number of type event: " << endl;
                cout << "1. Demo" << endl;
                cout << "2. Full day" << endl;
                cout << "3. Meeting" << endl;
                cin >> option;
		cin.ignore(30, '\n');
                while((option != 1)&& (option != 2) && (option != 3)){
			cout << "Invalid input! " << endl;
                        cout << "insert again: " << endl;
                        cin >> option;
                }
		cout << endl;
		shared_ptr<Event> my_new_node(new Event);
                if(option == 1){
                        shared_ptr<Demo> my_new(new Demo); 
                        my_new->Insert();
                        my_new_node = shared_ptr(my_new);
                	mytree.Insert(my_new_node); 
		}
                else if(option == 2){
                        shared_ptr<Fullday> my_new(new Fullday);
                        my_new->Insert();
                        my_new_node = shared_ptr(my_new);
			mytree.Insert(my_new_node);
                }
                else{
                        shared_ptr<Meeting> my_new(new Meeting); 
                        my_new->Insert();
                        my_new_node = shared_ptr(my_new);
                        mytree.Insert(my_new_node);
		}
           }
           else{
                mytree.Display();
           }
           result  = menu();
        }
<<<<<<< HEAD
	cout << "Thanks for using the scheduling system" << endl;
=======
	cout << "Now let's practice RTTI" << endl; 
		
		cin.ignore(30, '\n');
		cout << "Insert the new meeting" << endl; 
		Event * temp_node; 
		Meeting  mymeet; 
		mymeet.Insert(); 
		temp_node = &mymeet; 
		Event * temp2; 
		temp2 = dynamic_cast<Event*>(temp_node);
		if(temp2){
			cout << "my new node is an event" << endl;
		}
		cout << endl;

		cout << "Insert a demo " << endl;
		Demo mydemo; 
		mymeet.Insert(); 
		Event * mytemp3 = &mydemo;
		Demo * temp_node_demo; 
	
		temp_node_demo = dynamic_cast<Demo*>(mytemp3);
		if(temp_node_demo){
			cout << "my new node is a demo" << endl;
		}
		cout << endl;

		cout << "Insert a fullday" << endl;
		Fullday myfullday;
		myfullday.Insert(); 
		Event * temp4 = &myfullday; 
		Fullday * temp_node_fullday; 
		temp_node_fullday = dynamic_cast<Fullday*>(temp4);
		if(temp_node_fullday){
                        cout << "my new node is a fullday" << endl;
                }
		


>>>>>>> c1ce0b27cb7d60cbd348a950a09c1a9648744760
	return 0; 
}


int menu(){
	
	int result;
	cout << "Insert the number of the following options: " << endl;
        cout << "1.Insert event" << endl;
        cout << "2.Display event" << endl;
        cout << "3.Exit" << endl;
		      
      	cin >> result;
        while((result != 1) && (result != 2) &&  (result != 3)){
                cout << " try again!! " << endl;
                cin >> result;
        }
	return result;
}

