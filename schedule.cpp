/*****************************************************************************
# Author:           Aura Castellanos Calderon
# Project:          Project 3
# Name of file:     schedule.cpp
# Description:      implementation of schedule.h ( hierarchy)
#****************************************************************************/

#include "schedule.h"


//Base class Event 
Event::Event():name(), duration(0), start_hour(0), start_min(0), end_hour(0),end_min(0), days(0)	 
{
}

//constructor with arguments 
Event::Event(std::string a_name, int a_duration, int a_start,int a_start_min, int a_end, int a_end_min, int a_days): name(a_name),duration(a_duration), start_hour(a_start), start_min(a_start_min), end_hour(a_end), end_min(a_end_min), days(a_days)
{
}

//function:virtual destructor
Event::~Event()
{
}

//function:assignment operator
Event & Event::operator=(const Event & source)
{
	if(this == &source){
		return *this;
	}
	
	name.assign(source.name);
	duration = source.duration;
	start_hour = source.start_hour;
	start_min = source.start_min;
	end_hour = source.end_hour;
	end_min = source.end_min;
	days = source.days;
	return *this;
}

bool Event::Compare_name(const Event & new_event)const
{
	if(name.compare(new_event.name)== 0){ 
 		 return true; 
        }   
        return false;
}


bool Event::Compare_day(int day)const
{
	if(days == day){
		return true;
	}
	return false;
}

//function : use operator overloading to compare the events 
bool Event::operator ==(const Event & new_event) const
{
	if(((name.compare(new_event.name))== 0) && (duration == new_event.duration) && (start_hour == new_event.start_hour) && (start_min == new_event.start_min) && (end_hour == new_event.end_hour) && (end_min == new_event.end_min) && (days == new_event.days)){
		return true; 
	}
	return false;
}

//function: use operator overloading, return bool if they are not equal
bool Event::operator != (const Event & new_event)const
{
	if(((name.compare(new_event.name))== 0) && (duration == new_event.duration) && (start_hour == new_event.start_hour) && (start_min == new_event.start_min) && (end_hour == new_event.end_hour) && (end_min == new_event.end_min) && (days == new_event.days)){
                return false;
        }
        return true;
}


bool Event::operator <(const Event & new_event)const
{
	if((name.compare(new_event.name))< 0){
		return true;
	}
	return false;
}


bool Event::operator >(const Event & new_event)const
{
	if((name.compare(new_event.name))> 0){
                return true;
        }
        return false;
}


bool Event::Insert()
{
	int optionUser; 
	int MAXCHAR = 30;
	char temp_name[MAXCHAR];
	char c; 
	bool temp_ret =  false; 

	cout << "Insert participant name: " << endl;
	cin.getline(temp_name, MAXCHAR, '\n'); 
	char * temp_newname = new char[strlen(temp_name) + 1];
	strcpy(temp_newname, temp_name);
	std::string temp_str( temp_newname, strlen(temp_name) + 1);
	temp_ret = Edit_name(temp_str); 
	
        cout << "Enter start time (24hours - time): " << endl;
 	cin >> start_hour >> c >> start_min; 	
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout << "Enter end time (24 hours -time): " << endl;
	cin >> end_hour >> c >> end_min;
	cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	temp_ret = Calculate_duration(); 
		
	if(!temp_ret){
		throw temp_ret;
	}
	cout << "no throw was executed in calculate_duration" << endl;


        cout << "Enter day for the meeting: " << endl;
	cout << "1 - Monday " << endl;
        cout << "2 - Tuesday " << endl;
        cout << "3 - Wednesday " << endl;
        cout << "4 - Thursday" << endl;
        cout << "5 - Friday " << endl;
        cout << "6 - Saturday " << endl;
        cout << "7 - Sunday " << endl;
	cin >> optionUser;
        while((optionUser != 1) && (optionUser != 2) && (optionUser != 3) && (optionUser != 4) && (optionUser != 5)  && (optionUser != 6) && (optionUser != 7))
        {
                cout << "Option error. Please try again!!"  << endl;
                cout << "Enter option: " << endl;
                cin >> optionUser;
        }
	days = optionUser;
	delete [] temp_newname; 
	return temp_ret; 

}

//function edit the event class 
void Event::Edit()
{
        int MAXCHAR = 30;
        char temp_name[MAXCHAR];

        cout << "Insert participant name: " << endl;
        cin.getline(temp_name, MAXCHAR, '\n');
        char * temp_newname = new char[strlen(temp_name) + 1];
        strcpy(temp_newname, temp_name);
        std::string temp_str( temp_newname, strlen(temp_name) + 1);
        bool temp_ret = Edit_name(temp_str);
	
	if(temp_ret){
		cout << "name edited " << endl;
	}

}

bool Event::Edit_name(const std::string temp_str)
{
	name.assign(temp_str); 
	if(name.compare(temp_str) == 0){
		return true;
	}
	return false;
}

bool Event::Calculate_duration()
{
	int temp_hour;
	int temp_min; 
	int maxmin = 60; 
	if(end_hour > start_hour){
		if(end_min >= start_min){
			temp_min = end_min - start_min; 
			temp_hour = end_hour - start_hour; 
		}
		else{
			temp_min = maxmin - start_min + end_min; 
			temp_hour = end_hour - start_hour - 1;
		}
		duration = (temp_hour * maxmin) + temp_min;

		return true;
	}
	if(end_hour == start_hour){
		if(end_min > start_min){
			temp_hour = end_hour - start_hour;
			temp_min = end_min - start_min;
			duration = (temp_hour * maxmin) + temp_min;
			return true;
		}
	}
	return false; 
}

void Event::Display_day(int type_day)const
{
        switch(type_day)
        {
                case 1:
                        cout << "Monday" << endl;
                        break;
                case 2:
                        cout << "Tuesday " << endl;
                        break;
                case 3:
                        cout << "Wednesday " << endl;
                        break;
                case 4:
                        cout << "Thursday" << endl;
                        break;
                case 5:
                        cout << "Friday " << endl;
                        break;
                case 6:
                        cout << "Saturday " << endl;
                        break;
                case 7:
                        cout << "Sunday " << endl;
                        break;
        }
}

//Function: display duration in hh:mm
void Event::Display_duration(int a_duration)const
{
	int MAXMIN = 60; 
	int temp_min = 0;
	int temp_hour = 0; 
	if(duration > MAXMIN){
		temp_hour = duration / MAXMIN; 
		temp_min = duration % MAXMIN; 
	}
	else{
		temp_hour = 0;
		temp_min = a_duration; 
	}
	cout << temp_hour << ":" << temp_min << endl;
}

void Event::Display() const
{
	cout << "Participant name: " << name << endl;
	cout << "Day:";
	Display_day(days); 
	cout << "Start time: " << start_hour << ":" << start_min << endl;
	cout << "End time: " << end_hour << ":" << end_min << endl;
	cout << "Duration: ";
	Display_duration(duration); 
}




//***************************************************************
Meeting::Meeting():Event(),subject(),type_pers()
{
}

Meeting::Meeting(std::string a_name, int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days, std::string a_subject, std::string a_type_part):Event(a_name, a_duration, a_start, a_start_min, a_end, a_end_min, a_days), subject(a_subject), type_pers(a_type_part)
{
}

bool Meeting::operator==(const std::string & new_subject)const
{
	if((subject.compare(new_subject)) == 0){
		return true;
	}
	return false;	
}

bool Meeting::operator !=(const std::string & new_subject)const
{
	if(subject.compare(new_subject) != 0){
		return true;
	}
	return false;
}



bool Meeting::Insert()
{
	int MAXCHAR = 30; 
	int MAXCHARSUB = 60; 
	char temp_subject[MAXCHARSUB];
	char temp_type[MAXCHAR]; 

	//insert data for the event class
	Event::Insert(); 
	
	cin.ignore(MAXCHAR, '\n'); 
	
	cout << "Insert role of the participant: " << endl;
	cin.getline(temp_type, MAXCHAR, '\n');
	char * temp_newtype = new char [strlen(temp_type) + 1];
	strcpy(temp_newtype, temp_type); 
	std::string temp_type_str(temp_newtype, strlen(temp_type) + 1); 
	
	if(Edit_type_per(temp_type_str)){
		cout << "role saved " << endl;
	}

	cout << "Insert subject: " << endl;
	cin.getline(temp_subject,MAXCHARSUB, '\n');
	char * temp_newsubject = new char[strlen(temp_subject) + 1];
	strcpy(temp_newsubject, temp_subject);
	std::string temp_sub( temp_newsubject, strlen(temp_subject) + 1);

	if(Edit_subject(temp_sub)){
		cout << "subject saved " << endl;
	}
	delete [] temp_newtype;
	delete [] temp_newsubject;
	
	return true; 
}

//function: edit the meeting (derived class) 
void Meeting::Edit()
{
	Event::Edit(); 

	int MAXCHAR =30; 
	char temp_sub[MAXCHAR];
	char temp_type[MAXCHAR];

	cout << "Enter the subject: " << endl;
	cin.getline(temp_sub, MAXCHAR, '\n');
	char * temp_char_sub = new char [strlen(temp_sub) + 1];
	strcpy(temp_char_sub, temp_sub);
	std::string temp_str_sub(temp_char_sub); 
	Edit_subject(temp_str_sub); 

	cout << "Enter the role of participant" << endl;
	cin.getline(temp_type, MAXCHAR, '\n');
	char * temp_char_type = new char [strlen(temp_type) + 1];
	strcpy(temp_char_type, temp_type);
	std::string temp_str_type(temp_char_type);
	Edit_type_per(temp_str_type); 

}

bool Meeting::Edit_type_per(std::string a_type)
{
        type_pers.assign(a_type);
        if(type_pers.compare(a_type) == 0){
                return true;
        }
        return false;
}

bool Meeting::Edit_subject(std::string a_subj)
{
	subject.assign(a_subj);
	if(subject.compare(a_subj) == 0){
		return true;
	}
	return false;
}

void Meeting::Display()const
{
	Event::Display();
	cout << "Role: " << type_pers << endl;
	cout << "Subject: " << subject << endl;
}

//***************************************************************

Demo::Demo():Event(), name_course(), num_proficiency() 
{
}

Demo::Demo(std::string a_name, int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days, std::string a_course, int a_num_demo):Event(a_name, a_duration, a_start, a_start_min, a_end, a_end_min, a_days), name_course(a_course), num_proficiency(a_num_demo)
{
}

bool Demo::Insert()
{
	int MAXCHAR = 30; 
	char temp_course[MAXCHAR]; 

	Event::Insert();
	cin.ignore();
	cout << "Insert course name: " << endl;
	cin.getline(temp_course, MAXCHAR, '\n');
	char * temp_ch_course = new char[strlen(temp_course) + 1];
	strcpy(temp_ch_course, temp_course);
	std::string temp_str(temp_ch_course, strlen(temp_course) + 1); 
	
	if(Edit_name_course(temp_str)){
		cout << "Course name saved" << endl;
	}

	cout << "Insert number of proficiency: " << endl;

	cin >> num_proficiency;
	return true;
}

void Demo::Edit()
{
	int MAXCHAR = 30;
        char temp_course[MAXCHAR];

	Event::Edit();
	cin.ignore();

        cout << "Insert course name: " << endl;
        cin.getline(temp_course, MAXCHAR, '\n');
        char * temp_ch_course = new char[strlen(temp_course) + 1]; 
        strcpy(temp_ch_course, temp_course);
        std::string temp_str(temp_ch_course, strlen(temp_course) + 1); 
    
        if(Edit_name_course(temp_str)){
                cout << "Course name saved" << endl;
        }   

        cout << "Insert number of proficiency: " << endl;
	int temp_proficiency;
        cin >> temp_proficiency;
	Edit_num_proficiency(temp_proficiency);
}



bool Demo::Edit_name_course(std::string a_course)
{
	name_course.assign(a_course);
        if(name_course.compare(a_course) == 0){ 
                return true;
        }   
        return false;
}

void Demo::Edit_num_proficiency(int a_proficiency)
{
	num_proficiency = a_proficiency; 
}

void Demo::Display()const
{
	Event::Display();

	cout << "Course name: " << name_course << endl;
	cout << "Num proficiency: " << num_proficiency << endl;
}

//***************************************************************


Fullday::Fullday():Event(),place(), type_event()
{
}
        
Fullday::Fullday(std::string a_name, int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days, std::string a_place, std::string a_type_event):Event(a_name, a_duration, a_start, a_start_min, a_end, a_end_min, a_days), place(a_place), type_event(a_type_event)
{
}
         
bool Fullday::Insert()
{
	int MAXCHAR = 30;
	char temp_place[MAXCHAR];
	char temp_type[MAXCHAR];

	Event::Insert();
	cin.ignore();

	cout << "Insert location for the event: " << endl;
	cin.getline(temp_place, MAXCHAR, '\n');
	char * temp_ch_place = new char[strlen(temp_place) + 1]; 
	strcpy(temp_ch_place, temp_place);
	std::string temp_str_place(temp_ch_place, strlen(temp_place) + 1);

	if(Edit_place(temp_str_place)){
		cout << "Location saved " << endl;
	}

	cout << "Insert type of event (work - vacation - sick): " << endl;
	cin.getline(temp_type, MAXCHAR, '\n');
	char * temp_ch_type = new char [strlen(temp_type) + 1];
	strcpy(temp_ch_type, temp_type);
	std::string temp_str_type(temp_ch_type, strlen(temp_type));

	if(Edit_type_event(temp_str_type)){
		cout << "Type of event saved" << endl;
	}
	return true;
}	

void Fullday::Edit()
{
	int MAXCHAR = 30;
        char temp_place[MAXCHAR];
        char temp_type[MAXCHAR];

        Event::Edit();
        

        cout << "Insert location for the event: " << endl;
        cin.getline(temp_place, MAXCHAR, '\n');
        char * temp_ch_place = new char[strlen(temp_place) + 1];
        strcpy(temp_ch_place, temp_place);
        std::string temp_str_place(temp_ch_place, strlen(temp_place) + 1);

        if(Edit_place(temp_str_place)){
                cout << "Location saved " << endl;
        }

        cout << "Insert type of event (work - vacation - sick): " << endl;
        cin.getline(temp_type, MAXCHAR, '\n');
        char * temp_ch_type = new char [strlen(temp_type) + 1];
        strcpy(temp_ch_type, temp_type);
        std::string temp_str_type(temp_ch_type, strlen(temp_type));
	
	if(Edit_type_event(temp_str_type)){
                cout << "Type of event saved" << endl;
        }

}



bool Fullday::Edit_place(std::string new_place)
{
	place.assign(new_place);
        if(place.compare(new_place) == 0){ 
                return true;
        }   
        return false;
}

bool Fullday::Edit_type_event(std::string new_event)
{
	type_event.assign(new_event);
        if(type_event.compare(new_event) == 0){ 
                return true;
        }   
        return false;
}

void Fullday::Display()const
{
	Event::Display();
	cout << "Place: " << place << endl;
	cout << "Type of event: " << type_event << endl; 
}
