/*****************************************************************************
# Author:           Aura Castellanos Calderon
# Project:          Project 3
# Name of file:     bst.h
# Description:      header of bst.h (balanced  search tree - red black tree)
****************************************************************************/
#pragma once
#ifndef BST_H
#define BST_H
#include <iostream>
#include <memory>
#include <string>
#include "schedule.h"

using namespace std;



class Node_lll
{

                public:
                        Node_lll();
                        Node_lll(const Node_lll & source);
                        Node_lll(const shared_ptr<Event> & source);
                        Node_lll & operator=(const Node_lll & source);
                        void set_next(shared_ptr<Node_lll> & new_next);
                        void set_data(const shared_ptr<Event> & new_data);
                        shared_ptr<Node_lll> & get_next();
                        shared_ptr<Event> & get_data();
                        bool greater_than(const shared_ptr<Event> & new_data)const;
                        bool Comp_name(const shared_ptr<Event> & new_data)const;
                        bool Comp_days(int day)const;

			bool equal(const shared_ptr<Event> & new_data)const;
			bool not_equal(const shared_ptr<Event> & new_data)const;


                        void Display();

                private:
                        shared_ptr<Event> data_lll;
                        shared_ptr<Node_lll> next;
};

class list_lll
{
                public:
                        list_lll();
                        list_lll(const list_lll & new_list);
                        list_lll & operator =(const list_lll & source);
                        void Insert(const shared_ptr<Event> & new_event);
                        void Display();
                        void Remove(shared_ptr<Event> & new_event);
                        void Find(int day);
                        void Edit_node(const shared_ptr<Event> & new_event);
                        shared_ptr<Event>& get_head();
                        bool greater_than_newdata(const shared_ptr<Event> & new_data)const;
                        bool Comp_name_newdata(const shared_ptr<Event> & new_data)const;

                private:
                        shared_ptr<Node_lll> head;
                        void insertend(shared_ptr<Node_lll> & a_head, shared_ptr<Node_lll> & newnode);
                        void printnode(shared_ptr<Node_lll> & curr);
                        void copy(shared_ptr<Node_lll> & dest, const shared_ptr<Node_lll> & sour);
                        void display_list(shared_ptr<Node_lll> & curr);
                        bool remove_node(shared_ptr<Node_lll> & curr, shared_ptr<Event> & new_event);
                        int find_node(shared_ptr<Node_lll> & curr, int day);
                        bool edit_one_node(shared_ptr<Node_lll> & curr, const shared_ptr<Event> & new_event);


};



class Node
{
        public:
                Node();
                Node(const shared_ptr<list_lll>& new_data);
                shared_ptr<Node> & get_left();
                shared_ptr<Node> & get_right();
		shared_ptr<Node> & get_parent(); 
		void set_right(shared_ptr<Node> & new_right);
		void set_left(shared_ptr<Node> & new_left); 
		void set_data(const shared_ptr<Event> & source); 
		void set_parent(shared_ptr<Node> & new_aprent); 
		shared_ptr<list_lll> &get_data();
                int get_color()const;
                void set_color(const int new_color);
                void Edit_data(const shared_ptr<Event> & source);
	       	void Display()const;
		bool Comp_name(const shared_ptr<Event> & new_data)const;
		bool greater_than(const shared_ptr<Event> & new_data)const; 
		
        private:
                shared_ptr <list_lll> data;
                shared_ptr <Node> parent;
                shared_ptr <Node> left;
                shared_ptr <Node> right;
                int color; // 0 - black 1-red

};

class BST
{
        public:
		BST();	
		~BST();	
		BST(const BST & source);
		void Insert(const shared_ptr<Event> & source);
		void Display()const;
		void Edit_node();
        private:
                shared_ptr<Node> root;

		void Insert_sorted(shared_ptr<Node> & curr,shared_ptr<Node> & curr_parent, const shared_ptr<Event> & source);
		void Check_bst(shared_ptr<Node> & curr);
		void Display_tree(const shared_ptr<Node> & root)const;
		void Left_rotation(shared_ptr<Node> & curr);
		void Right_rotation(shared_ptr<Node> & curr);
		void copy(shared_ptr<Node> & curr, shared_ptr<Node> & curr_parent, shared_ptr<Node> source);
		shared_ptr<Node> & Find_node(shared_ptr<Node> & curr, shared_ptr<Event> source); 
		shared_ptr<Node> & maximun(shared_ptr<Node> & curr);
		shared_ptr<Node> & minimun(shared_ptr<Node> & curr);
		shared_ptr<Node> & predecessor(shared_ptr<Node> & curr);
		shared_ptr<Node> & predecessor_option(shared_ptr<Node> & curr, shared_ptr<Node> & temp);
		shared_ptr<Node> & successor(shared_ptr<Node> & curr);
                shared_ptr<Node> & successor_option(shared_ptr<Node> & curr, shared_ptr<Node> & temp);
};

#endif

