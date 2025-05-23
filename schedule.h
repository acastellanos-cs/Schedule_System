/*****************************************************************************
# Author:           Aura Castellanos Calderon
# Project:          Project 3
# Name of file:     schedule.h
# Description:      hierarchy for the program 
#****************************************************************************/
#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <iostream>
#include <string>
#include <limits> 
#include <cstring>

using namespace std;

class Event
{
	public:
		Event();
		Event(std::string a_name, int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days); 
		~Event(); 
		Event & operator=(const Event & source); 
		virtual bool Insert();
		virtual void Edit(); 
		bool Edit_name(const std::string temp_str);	 
		bool Compare_name(const Event & new_event)const;
		bool Compare_day(int day)const;
		bool Calculate_duration(); 
		void Display_day(int type_day)const;
		void Display_duration(int a_duration)const;
		virtual void Display() const;
		bool operator ==(const Event & new_event) const; 
		bool operator != (const Event & new_event)const;
		bool operator <(const Event & new_event)const;
		bool operator >(const Event & new_event)const;
	private:
		std::string name; //participante name 
		int duration; 
		int start_hour;
		int start_min; 
		int end_hour; 
		int end_min; 
		int days; 

};

//derived from event
class Meeting: public Event
{
	public:
		Meeting();
		Meeting(std::string a_name,int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days, std::string a_subject, std::string a_type); 
		bool operator==(const std::string & new_subject)const; 
		bool operator !=(const std::string & new_subject)const;
		bool Insert(); 
		void Edit(); 
		bool Edit_type_per(std::string a_type);
		bool Edit_subject(std::string a_subj); 
		void Display()const;

	private:
		std::string subject; //subject of the meeting
	        std::string type_pers; //student, faculty
};

//derived from event
class Demo: public Event
{

     	public:	
		Demo();
                Demo(std::string a_name, int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days, std::string a_course, int a_num_demo);
		bool Insert();
                void Edit();
		bool Edit_name_course(std::string a_course);
                void Edit_num_proficiency(int num_proficiency);
                void Display()const;


        private:
		std::string name_course; 
		int num_proficiency; //proficiency demo#1 or #2 

};


//derived from event
class Fullday: public Event
{
	public:
		Fullday();
                Fullday(std::string a_name, int a_duration, int a_start, int a_start_min, int a_end, int a_end_min, int a_days, std::string a_place, std::string a_type_event);             
		bool Insert();
                void Edit();
		bool Edit_place(std::string new_place);
                bool Edit_type_event(std::string new_event);
                void Display()const;		
		

	private: 
		std::string place;
		std::string type_event;//work - vacation - sick - personal 

};
#endif
