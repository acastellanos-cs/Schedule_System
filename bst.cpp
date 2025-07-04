/*****************************************************************************
# Author:           Aura Castellanos Calderon
# Project:          Project 3
# Name of file:     bst.cpp
# Description:      implementation of bst (balanced tree - red black tree)
#****************************************************************************/


#include "bst.h"

//Function: Default constructor
Node::Node():data(nullptr),parent(nullptr),left(nullptr),right(nullptr),color(0)
{
}

//Function:constructor with args
Node::Node(const shared_ptr<list_lll> & new_data):data(new_data), parent(nullptr),left(nullptr),right(nullptr),color(0)
{
}

//Function: return true if the names are equal 
bool Node::Comp_name(const shared_ptr<Event> & new_data)const
{
	if(data->Comp_name_newdata(new_data)){
		return true;
	}
	return false;
}

//Function:return true if the curr name is greater than the new data
bool Node::greater_than(const shared_ptr<Event> & new_data)const
{

	if(data->greater_than_newdata(new_data))
	{
		return true; 
	}
	return false;
}

//Function: get the left node of the tree
shared_ptr<Node> & Node::get_left()
{
	return left;
}

//Function: get the right node of the tree
shared_ptr<Node> & Node::get_right()
{
	return right;
}

//Function: get parent 
shared_ptr<Node> & Node::get_parent()
{
	return parent;
}

//Function: set right
void Node::set_right(shared_ptr<Node> & new_right)
{	
	right.reset(new Node);
	right = shared_ptr<Node>(new_right);
}

//Function: set left
void Node::set_left(shared_ptr<Node> & new_left)
{
	left.reset(new Node);
	left = shared_ptr<Node>(new_left);
}	

//Function: set parent
void Node::set_parent(shared_ptr<Node> & new_parent)
{
	parent.reset(new Node);
	parent = shared_ptr<Node>(new_parent);
}

//Function: set data
void Node::set_data(const shared_ptr<Event> & source)
{
	data->Insert(source); 
}

//Function: get data
shared_ptr<list_lll> & Node::get_data()
{
	return data;
}

//Function: get color
int Node::get_color()const
{
	return color;
}

//Function: set color
void Node::set_color(const int new_color)
{
	color = new_color;
}

//Function:edit data - replace the data
void Node::Edit_data(const shared_ptr<Event> & source)
{
	data->Edit_node(source); 
}

//Function:display the node 
void Node::Display()const
{
	data->Display(); 
	cout << "color: ";
	if(color == 0){
		cout <<  "black" <<  endl;
	}
	else{
		cout << "red" << endl;
	}
}


//BST CLASS ******************************************************************
//

//Function: Default constructor
BST::BST():root(nullptr)
{

}	

//Function:Destructor constructor
BST::~BST()
{
}

//Function: copy constructor
BST::BST(const BST & source)
{
	if(!source.root){
		root.reset();
	}else{
		copy(root,root, source.root); 
	}
}

//Function: helper function to copy a whole tree 
void BST::copy(shared_ptr<Node> & curr,shared_ptr <Node> & curr_parent, shared_ptr<Node> source)
{
	if(!source){
		curr.reset();
		return;
	}

	curr = make_shared<Node>(source->get_data());
	//it is not root
	if(source->get_parent()){
		curr->set_parent(curr_parent); 	
	}	
	
	copy(curr->get_left(),curr, source->get_left());
	copy(curr->get_right(),curr, source->get_right());
}


//Function:Insert new data to the tree 
void BST::Insert(const shared_ptr<Event> & source)
{
	if(this->root)
	{
		Insert_sorted(root,root, source); 
	}
	else{
		//when the tree is empty
		//add source with black color because it is the root
		//create the list_lll
		shared_ptr<list_lll>new_list(new list_lll);
		new_list->Insert(source); 
		//create the root pointed to the list_lll
		shared_ptr<Node> root ( new Node); 
		this->root = make_shared<Node>(new_list);

		int newcolor = 0;	
		root->set_color(newcolor); 
	}
}

//Function: Search the right spot for the new data and insert
//sorting by name 
void BST::Insert_sorted(shared_ptr<Node> & curr, shared_ptr<Node> & curr_parent,  const shared_ptr<Event> & source)
{
	if(!curr){
		shared_ptr<list_lll>a_list(new list_lll);
		a_list->Insert(source); 
		curr = make_shared<Node>(a_list);

		curr->set_parent(curr_parent); 
		if(curr_parent->get_right() == curr){
			//cout << "right" << endl;
		}
		if(curr_parent->get_left() == curr){
			//cout << "left" << endl;
		}

		int newcolor = 1;
                curr->set_color(newcolor);
		Check_bst(curr); 
		return; 
	}
	if(curr->Comp_name(source)){
		curr->set_data(source); 	
		return;
	}

	if(curr->greater_than(source)){
		Insert_sorted(curr->get_left(),curr, source);	
	}
	else{
		Insert_sorted(curr->get_right(), curr, source); 
	}
}

//Check the red-black tree follow the rules 

//Function:Helper check red-black tree function
void BST::Check_bst(shared_ptr<Node> & curr) 
{
	int color_black = 0;
	int color_red = 1; 
	if(!curr){
		return;
	}
	if((curr == this->root)){
		return;
	}

	//check parent color
	shared_ptr<Node> temp_parent(new Node);
	temp_parent = shared_ptr<Node>(curr->get_parent()); 
        //if temp_parent doesn't exist - curr is the root
       	
    if((temp_parent->get_color() == 1) && (temp_parent != this->root)){

	//if parent is black nothing happens
	//parent is red we have to fix 
	
		//get grandparent node 
		shared_ptr<Node> temp_grandparent(new Node);
		temp_grandparent = shared_ptr<Node>(temp_parent->get_parent());

		//find the uncle
		shared_ptr<Node> temp_uncle(new Node);
		//temp to see if curr is false- left  true- right
		bool temp_parent_pos = false; 

		if(temp_parent == temp_grandparent->get_right()){
			temp_uncle = shared_ptr<Node>(temp_grandparent->get_left());
			temp_parent_pos = true; 
		}
		else{
			temp_uncle = shared_ptr<Node>(temp_grandparent->get_right());
			temp_parent_pos = false;  
		}
		shared_ptr<Node> temp(new Node);

		//3.1P is red and Uncle is red
		if((temp_uncle) && (temp_uncle->get_color() == 1)){
			//flip color of p & u = red ---> black
			//grandparent = black ---> red
			if(temp_grandparent != this->root){
				temp_grandparent->set_color(color_red);
				temp = shared_ptr<Node>(temp_grandparent); 
			}
			temp_uncle->set_color(color_black);
			temp_parent->set_color(color_black);
		}
	
		//3.2 uncle is black or null
		else if((!temp_uncle) || (temp_uncle->get_color() == 0)){

			//3.2.1
                        //if Parent is right
                        if(temp_parent_pos){
                                //curr is right
                                if(temp_parent->get_right() == curr){
                                        //curr- the children is on the right side
                                        //left-rotation
					temp_grandparent->set_color(color_red);
                                        temp_parent->set_color(color_black);
                                        Left_rotation(temp_grandparent);
                                	temp = shared_ptr<Node>(curr);
				}
				//3.2.2.curr is left 
                                else{
                                        //curr-the children is on the left side
                                        //right -rotation
                                        temp = shared_ptr<Node>(temp_parent);
					Right_rotation(temp_grandparent);
                                	//do 3.2.1 curr is on the right side
					 temp_grandparent->set_color(color_red);
                                        temp_parent->set_color(color_black);
                                        Left_rotation(temp_grandparent);
					
				}
                        }//if parent is left
                        else{
                                //3.2.4 curr is right
                                if(temp_parent->get_right() == curr){
                                        //curr- the children is on the right side
                                        //left-rotation
					temp = shared_ptr<Node>(temp_parent); 
                                        Left_rotation(temp_grandparent);
					temp_grandparent->set_color(color_red);
                                        temp_parent->set_color(color_black);
                                        Right_rotation(temp_grandparent);
                                }
                                else{
                                        //3.2.3 curr-the children is on the left side
                                        //right -rotation
                                        temp_grandparent->set_color(color_red);
                                        temp_parent->set_color(color_black);
					Right_rotation(temp_grandparent);
					temp = shared_ptr<Node>(curr);
                                }
			}
		}
			Check_bst(temp_grandparent); 
	}
}

//Function: edit a node 
void BST::Edit_node()
{
	cout << "Insert the node you want to edit" << endl;

         shared_ptr<Event>temp (new Event);
	 temp->Insert();
		
	 shared_ptr<Node> temp_node (new Node);
	 temp_node = shared_ptr(Find_node(this->root, temp));

	 temp_node->Edit_data(temp); 
}

//Function:Left_rotation 
void BST::Left_rotation(shared_ptr<Node> & curr)
{
	//curr = grandparent
	//parent = parent
	shared_ptr<Node> temp_parent( new Node);
	temp_parent = shared_ptr(curr->get_right()); 
	curr->set_right(temp_parent->get_left());

	//if temp_parent has a left subtree 
	//assign curr as the parent of left subtree of temp_child
	if(temp_parent->get_left()){
		shared_ptr<Node>temp_child_left(new Node);
		temp_child_left = shared_ptr(temp_parent->get_left()); 
		temp_child_left->set_parent(curr); 
	}
	//assign parent of curr to a parent of parent 
	temp_parent->set_parent(curr->get_parent()); 

	//if the parent of parent  is null, make parent as the root
	if(!temp_parent->get_parent()){
		this->root = shared_ptr<Node>(temp_parent); 
	}
	else{
		//check which subtree is parent 
		shared_ptr<Node>temp_grandp (new Node);
		temp_grandp = shared_ptr(curr->get_parent());

		//if parent is a child left
		if(temp_grandp->get_left() == curr){
			temp_grandp->set_left(temp_parent);
		}
		else{
			temp_grandp->set_right(temp_parent);
		}
	}
 	temp_parent->set_left(curr); 
	curr->set_parent(temp_parent);
}

//Function:Right_rotation
void BST::Right_rotation(shared_ptr<Node> & curr)
{
	//curr = grandparent
        shared_ptr<Node> temp_parent(new Node); 
	temp_parent = shared_ptr(curr->get_left());
	curr->set_left(temp_parent->get_right()); 

	//if temp_parent has a right subtree 
        //assign curr as the parent of right subtree of temp_child
        if(temp_parent->get_right()){
                shared_ptr<Node>temp_child_right(new Node);
                temp_child_right = shared_ptr(temp_parent->get_right());
                temp_child_right->set_parent(curr);
        }

        //assign parent of curr to a parent of parent 
        temp_parent->set_parent(curr->get_parent());

        //if the parent of parent  is null, make parent as the root
        if(!temp_parent->get_parent()){
                this->root = shared_ptr<Node>(temp_parent);
        }
        else{
                //check which subtree is parent 
                shared_ptr<Node>temp_grandp (new Node);
                temp_grandp = shared_ptr(curr->get_parent());

                //if parent is a child left
                if(temp_grandp->get_left() == curr){
                        temp_grandp->set_left(temp_parent);
                }
                else{
                        temp_grandp->set_right(temp_parent);
                }
        }

        temp_parent->set_right(curr);
        curr->set_parent(temp_parent);
}


//Function:Find the node with the same name
shared_ptr<Node>  &  BST::Find_node(shared_ptr<Node> & curr, shared_ptr<Event>  source)
{
	//base case
	if(!curr){
		return curr;
	}
	//find the node 
	if(curr->Comp_name(source)){
		return curr; 
	}
	//search
	if(curr->greater_than(source)){
		return Find_node(curr->get_left(), source);
	}
	else{
		return Find_node(curr->get_right(), source); 
	}
	return curr;
}

//Function: find the maximun of a tree
shared_ptr <Node> & BST::maximun(shared_ptr<Node> & curr){

	if(curr->get_right()){
		return maximun(curr->get_right());
	}
	return curr; 
}

//Function:find the minimun of a tree
shared_ptr <Node> & BST::minimun(shared_ptr<Node> & curr){
	if(curr->get_left()){
		return minimun(curr->get_left());
	}
	return curr;
} 

//inorder predecessor largest element on the left 
shared_ptr <Node> & BST::predecessor(shared_ptr<Node> & curr)
{
	if(curr->get_left()){
		return maximun(curr->get_left());
	}

	return predecessor_option(curr, curr->get_parent());
}

//Function: find the predecessor when there is not left side
shared_ptr <Node> & BST::predecessor_option(shared_ptr<Node> & curr, shared_ptr<Node> & temp)
{
	if((temp) && (temp->get_left() == curr)){
               	return successor_option(temp, temp->get_parent());
        }
	return temp; 
}


//Function: find inorder successor smallest of the right 
shared_ptr <Node> & BST::successor(shared_ptr<Node> & curr)
{
	if(curr->get_right()){
		return minimun(curr->get_right());
	}
        return successor_option(curr, curr->get_parent());  
}

//Function: find the successor when there is not right side
shared_ptr <Node> & BST::successor_option(shared_ptr<Node> & curr, shared_ptr<Node> & temp)
{
        if((temp) && (temp->get_right() == curr)){
		return successor_option(temp, temp->get_parent()); 
        }   
        return temp; 
}

//Function:Display content of tree
void BST::Display()const
{
	if(root){
		cout << "Display Calendar ..." << endl;
		Display_tree(root);	
	}
	else{
		cout << "Calendar doesn't exist" << endl; 
	}
}

//function:Helper function to display content
void BST::Display_tree(const shared_ptr<Node> & root)const
{
	if(!root){
		return;
	}
	else{
		Display_tree(root->get_left());
		//cout << "my address ";
		//cout << root << endl;
		shared_ptr<Node>temp(new Node);
		temp = shared_ptr(root->get_parent());
		
		if(temp  && (temp->get_right() == root)){
			//cout << "right" << endl;
		}
		if(temp  && (temp->get_left() == root)){
			//cout << "left" << endl;
		}
		
		root->Display();
		//cout << root.use_count() << endl;
		cout << endl;
		Display_tree(root->get_right());
	}
}

//
//Node_location class  *********************************************************

//Function: Default constructor
Node_lll::Node_lll():data_lll(nullptr), next(nullptr)
{
}

//Function: copy constructor
Node_lll::Node_lll(const Node_lll & source):data_lll(source.data_lll), next(source.next)
{
}

//Function: constructor
Node_lll::Node_lll(const shared_ptr<Event> & source):data_lll(source), next(nullptr)
{
}

//Function: asisgnment operator
 Node_lll & Node_lll::operator=(const Node_lll & source)
{
	if(!source.data_lll){
		return *this; 
	}
	data_lll = shared_ptr<Event>(source.data_lll);
	next = shared_ptr<Node_lll>(source.next);
	return *this;
}

//Function:set next 
void Node_lll::set_next(shared_ptr<Node_lll> & new_next)
{
	next.reset();
        next = shared_ptr<Node_lll>(new_next);
}

//Function:set data
void Node_lll::set_data(const shared_ptr<Event> & new_data)
{
	data_lll.reset();
	data_lll = shared_ptr<Event>(new_data); 
}

//Function: get data 
shared_ptr<Event> & Node_lll::get_data()
{
	return data_lll;
}

//Function: get next
shared_ptr<Node_lll> &  Node_lll::get_next()
{
	return next;
}

//Function:return true if this is greater than the newdata
bool Node_lll::greater_than(const shared_ptr<Event> & new_data)const
{
	if(*this->data_lll > *new_data)
        {
                return true;
        }
        return false;
}

//Function: return true if the names are equal
bool Node_lll::Comp_name(const shared_ptr<Event> & new_data)const
{
        if(data_lll->Compare_name(*new_data)){
                return true;
        }
        return false;
}

//Function: return true if the days are equal
bool Node_lll::Comp_days(int day)const
{
        if(this->data_lll->Compare_day(day)){
                return true;
        }   
        return false;
}

//Function:Displat node
void Node_lll::Display()
{
	data_lll->Display(); 
}


//list__lll *********************************************************************

//Function: Default constructor
list_lll::list_lll():head(nullptr)
{
}	

//Function: copy constructor
list_lll::list_lll(const list_lll & new_list)
{
	copy(this->head, new_list.head);
}	

//Function:assignemnt operator
list_lll & list_lll::operator=(const list_lll & source)
{
	if(!source.head){
		return *this;
	}
	copy(this->head,source.head); 
	return *this; 
}

//Function:insert a new event
void list_lll::Insert( const shared_ptr<Event> & new_event)
{
	shared_ptr<Node_lll> obj(new Node_lll); 
	obj->set_data(new_event); 

	if(!this->head){
		this->head = obj; 
	}
	else{
		insertend(this->head, obj); 
	}
}

//Function:helper function to insert a newnode in the end
void list_lll::insertend(shared_ptr<Node_lll> & a_head, shared_ptr<Node_lll> & newnode)
{
	if(!a_head){
		a_head = shared_ptr(newnode); 
	}
	else{
		insertend(a_head->get_next(), newnode); 
	}
}

//Function:remove the node
void list_lll::Remove(shared_ptr<Event> & new_event)
{
	if(!this->head){
		cout << "List is empty" << endl;
	}else{
		if(head->Comp_name(new_event)){
				shared_ptr<Node_lll> temp (new Node_lll);
				temp = shared_ptr<Node_lll>(head->get_next());
				this->head.reset();
				this->head = shared_ptr<Node_lll>(temp); 
				cout << "Node removed!" << endl;
		}
		else if(remove_node(this->head, new_event)){
			cout << "Node removed!" << endl;
		}
		else{
			cout <<"Node wasn't removed" << endl;
		}
	}
	
}

//Function: helper function to remove the specific node
bool list_lll::remove_node(shared_ptr<Node_lll> & curr, shared_ptr<Event> & new_event)
{
	if(!curr){
		return false;
	}

	shared_ptr<Node_lll> temp (new Node_lll);
	temp = shared_ptr<Node_lll>(curr->get_next());
	if(temp->Comp_name(new_event)){
		curr->set_next(temp->get_next());
	        temp.reset();
		return true; 	
	}

	return remove_node(temp, new_event); 
}

//Function:find the data when the days match
void list_lll::Find(int day)
{
	if(!this->head){
		cout << "List is empty" << endl;
	}
	else{
		int num = find_node(this->head,day);
		cout << num << " values match!!" << endl; 
	}
}

//Function:helper function to find the node
int list_lll::find_node(shared_ptr<Node_lll> & curr, int day)
{
	if(!curr){
		return 0;
	}
	int counter = find_node(curr->get_next(), day);

	if(curr->Comp_days(day)){
		printnode(curr); 
		++counter;
	}
	return counter; 
}

//Function:edit a node with a new event
void list_lll::Edit_node(const shared_ptr<Event> & new_event)
{
	if(!this->head){
		return; 
	}
	if(edit_one_node(this->head, new_event)){
		cout << "Node edited!!"<< endl;
	}
}

//Function:helper function to edit the node 
bool list_lll::edit_one_node(shared_ptr<Node_lll> & curr,const shared_ptr<Event> & new_event)
{
	if(!curr){
		return false;
	}
	if(curr->get_data() == new_event){
		int option = 0;
		cout << "Select number of type event: " << endl;
		cout << "1. Demo" << endl;
		cout << "2. Full day" << endl;
		cout << "3. Meeting" << endl;
		cin >> option; 
		while((option != 1) ||(option != 2) ||(option != 3)){
			cout << "Invalid input! " << endl;
			cout << "insert again: " << endl;
			cin >> option; 
		}
		
		if(option == 1){
			shared_ptr<Demo> my_new; 
			my_new->Insert(); 
			shared_ptr<Event> my_new_node(new Event); 
			my_new_node = shared_ptr(my_new); 
			curr->set_data(my_new_node); 
			return true;
		}
		else if(option == 2){
                        shared_ptr<Fullday> my_new;
                        my_new->Insert();
			return true;
		}
		else{
			shared_ptr<Meeting> my_new;
                        my_new->Insert();
			return true;
		}
		return false;
	}
	return edit_one_node(curr->get_next(), new_event); 
}

//Function:get the head of the lll
shared_ptr<Event>&  list_lll::get_head()
{ 
	return head->get_data();	 
}

//Function:return true if the name is greater than the new_data
bool list_lll::greater_than_newdata(const shared_ptr<Event> & new_data)const
{
	if(head->greater_than(new_data)){
		return true;
	}
	return false;
}

//Function:return true if the name are equal
bool list_lll::Comp_name_newdata(const shared_ptr<Event> & new_data)const
{
        if(head->Comp_name(new_data)){
                return true;
        }
        return false;
}

//Function:print node - the lll
void list_lll::printnode(shared_ptr<Node_lll> & curr)
{
	curr->Display(); 
}

//Function:helper function to copy the lll
void list_lll::copy(shared_ptr<Node_lll> & dest, const shared_ptr<Node_lll> & sour)
{
	if(sour){
		dest = shared_ptr<Node_lll>(sour);
		copy(dest->get_next(), sour->get_next());
	}
}

//Function:display the lll
void list_lll::display_list(shared_ptr<Node_lll> & curr)
{
	if(curr){
		curr->Display();
		display_list(curr->get_next());
	}
}

//Function:helper function to display the  lll
void list_lll::Display()
{
	cout << "Linked list: " << endl;
	if(this->head){
		display_list(this->head);
	}
}


