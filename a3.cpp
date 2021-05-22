// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Riya Dhariwal
// St.# : 301363373
// Email: riya_dhariwal@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

// Inforation about Smart_bot:
// My smart bot is a Software Systems chatbot that can provide answers to simple questions regarding the SoSy program.
// It can find minimum gpa requirements, what SoSy is as a program, where SoSy classes are, potential job offers in the future,
// how much tutition is, the difference between comp sci and sosy, and it can also pick a random first year course for you just for fun.
// To run it, put in a string paramater containing your question (ex. Smart_bot s("chooose a course for me");). get_reply() finds the answer
//so when you run it with converse, the question will cout. When the constructor is called, it will automatically cout the name of the smartbot
//and the status of the question (whether you passed one in or not).
//ALL credit goes to   http://www.sfu.ca/computing.html  for the answers to the questions


#include "cmpt_error.h"    // These are the only permitted includes!
#include "Chatbot.h"       //
#include <iostream>        // Don't include anything else.
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <cassert>

using namespace std;

class Mirror_bot : public Chatbot{
private:
	string mirror_name;
	string mirror_phrase;

public:
	//default constructor 
	Mirror_bot ()
	: mirror_name(""), mirror_phrase("first reply")
	{}

	//contructor - no phrase string passed in
	Mirror_bot (string name)
	: mirror_name (name), mirror_phrase ("first reply")
	{}

	//constructor 
	Mirror_bot (string name, string phrase)
	: mirror_name (name), mirror_phrase (phrase)
	{} 

	//give string to chatbot
	void tell(const string& s){
		mirror_phrase = s;
	}

	//unique chatbot name returned by name function 
	string name() const{
		return mirror_name;
	}

	//get phrase
	string get_reply(){
		return mirror_phrase;
	}

};//class Mirror_bot


class Random_bot : public Chatbot{
private:
	string random_name;
	vector<string> random_list; 
	string random_phrase;

public:
	//default constructor
	Random_bot ()
	:random_name(""), random_phrase("")
	{
		srand(time(0));
	}

	//constructor
	Random_bot (string name, vector<string> phrases)
	:random_name(name), random_list(phrases)
	{
		//seeds it in the constructor so it is only called once
		srand(time(NULL)); 

		//error check if vector passed in is empty
		if (random_list.size() == 0) {
			cmpt::error ("empty vector");
		}
	}
	string name() const{
		return random_name;
	}

	void tell (const string& s){
		random_phrase = s;
	}

	string get_reply(){ 
		//gets a random number to choose from te list of vector
		int randomIndex = rand() % random_list.size();
		random_phrase = random_list[randomIndex];

		return random_phrase;  
	} 

};//class Random_bot


class User_bot : public Chatbot{
private:
	string user_name;
	string user_phrase;

public:
	//default constructor
	User_bot()
	: user_name(""), user_phrase ("")
	{}

	//constructor 
	User_bot(string name)
	: user_name(name), user_phrase ("")
	{}

	string name() const {
		return user_name;
	}

	void tell(const string& s){
		user_phrase = s;
	}

  	string get_reply(){
  		string user_input;
  		getline(cin,user_input);

  		user_phrase = user_input;

  		return user_phrase;
  	}

}; //class User_bot


class Datetime_bot : public Chatbot{
private:
	string dt_name;
	string dt_phrase;
	vector<string> dt_list;

 public:

 	//default constructor
 	Datetime_bot()
 	: dt_name(""), dt_phrase("")
	{srand(time(NULL));}

	//constructor
	Datetime_bot(string name, vector<string> phrases)
	:dt_name(name), dt_list(phrases)
	{
		srand(time(NULL));

		if (dt_list.size() == 0) {
			cmpt::error ("empty vector");
		}

	}

	string name() const {
		return dt_name;
	}

	void tell(const string& s) {
		dt_phrase = s;
	}

	string get_reply() {
		//transforms the phrase all into lowercase to make comparison easy
		transform(dt_phrase.begin(), dt_phrase.end(), dt_phrase.begin(), ::tolower);
		//finds whether date or time is in the phrase
		if (dt_phrase.find("date") != std::string::npos || dt_phrase.find("time") != std::string::npos){

   			auto end = std::chrono::system_clock::now();

			std::time_t end_time = std::chrono::system_clock::to_time_t(end);
			return dt_phrase = std::ctime(&end_time);
		}
		else{
			int dtIndex = rand() % dt_list.size();
			dt_phrase = dt_list[dtIndex];
	
			return dt_phrase;
		}
	}

}; //class Datetime_bot 


class Smart_bot : public Chatbot{
private:
	string smart_question;
	string smart_answer;
	string smart_name = "SoFy the SoSy robot";
	vector<string> good_things = {"You'll be well-prepared to secure employment with one of many high-tech companies located locally, and internationally.",
								  "Gain valuable work experience (usually 8 month terms), and earn competitive wages in our co-operative education program.",
								  "Study at SFU's Surrey campus, located in a major technology center that is home to local and international companies in software development, telecommunications, gaming, finance, bioinformatics and more.",
								  "Graduate with an industry recognized degree (Bachelor of Science) from one of Canada’s most prestigious computer science schools.",
								  "Be well prepared to continue with graduate studies (M.Sc., PhD) thanks to our school’s strong research focus."};
	vector<string> course_list = {"MATH 150/151", "MACM 101", "CMPT 130", "CMPT 105W", "CMPT 106", "MSE 110"};

public:
	Smart_bot()
	:smart_question(""), smart_answer("")
	{
		srand(time(NULL));
		cout << "Hello my name is SoFy the SoSy robot and I'm here to answer basic questions about the SoSy program."
			 << "\n"
			 << "Please enter a question. " << "\n";
	}
	Smart_bot(string question)
	:smart_question(question), smart_answer("")
	{
		srand(time(NULL));
		cout << "Hello my name is SoFy the SoSy robot and I'm here to answer basic questions about the SoSy program."
			 << "\n"
			 << "you have entered this question: " << smart_question << "\n";
	}

	void tester(){
		cout << "q is " << smart_question << "\n";
	}

	string name() const {
		return smart_name;
	}

	void tell(const string& s) {
		smart_question = s;
	}
	  
	string get_reply(){

		transform(smart_question.begin(), smart_question.end(), smart_question.begin(), ::tolower);

		if ((smart_question.find("gpa") != std::string::npos) && (smart_question.find("low") != std::string::npos || smart_question.find("minimum") != std::string::npos || smart_question.find("lowest") != std::string::npos)){
			
			smart_answer = "The minimum gpa required is 2.40 CGPA during the program. For internal transfers, a CRGPA of 2.67 and a CGPA of 2.4 ! \n I hope this answered your question !";
			
			return smart_answer;
		}

		else if ((smart_question.find("good") != std::string::npos || smart_question.find("benefit") != std::string::npos || smart_question.find("advantages") != std::string::npos || smart_question.find("benefits") != std::string::npos || smart_question.find("advantage") != std::string::npos)){
			
			int goodIndex = rand() % good_things.size();
			smart_answer = good_things[goodIndex];

			return smart_answer;
		}

		else if (smart_question.find("what") != std::string::npos && smart_question.find("sosy")!= std::string::npos){
			smart_answer = "Software Systems (SoSy) is is an applied area of computer science that focuses on the development of high-quality software for public and private industry. \n This is a practical, hands-on program delivered through a combination of lectures, case studies, and individual and team projects.";

			return smart_answer;
		}

		else if (smart_question.find("where") != std::string::npos && (smart_question.find("sosy") != std::string::npos || smart_question.find("classes") != std::string::npos)){
			smart_answer = "SoSy is offered at the Surrey campus. ";

			return smart_answer;
		}

		else if ((smart_question.find("job") != std::string::npos) || (smart_question.find("work") != std::string::npos) ){
			smart_answer = "SoSy graduates work for companies like TELUS, Business Objects, Electronic Arts Canada, IBM, Microsoft, BC Cancer Research Agency, HSBC, Nokia and many other private and public sector organizations. ";

			return smart_answer;
		}

		else if ((smart_question.find("cost") != std::string::npos) || (smart_question.find("tuition") != std::string::npos) ){
			smart_answer = "The average cost for domestic students is $7,676 / term. For international students it is $12,927 / term.";

			return smart_answer;
		}

		else if ((smart_question.find("more") != std::string::npos) && (smart_question.find("information") != std::string::npos) ){
			smart_answer = "Contact our prospective student advisor at fasreach@sfu.ca.";

			return smart_answer;
		}

		else if ( (smart_question.find("difference") != std::string::npos  || smart_question.find("differences") != std::string::npos)  &&  (smart_question.find("sosy")!= std::string::npos || smart_question.find("burnaby") != std::string::npos || smart_question.find("program") != std::string::npos || smart_question.find("programs") != std::string::npos)){
			smart_answer = "Computing science has a theoretical approach, but you will also learn practical skills to solve problems using computers in a variety of areas. \n Software systems specializes in producing high-quality software developers. Software systems students gain practical experience working in teams and gain more in-depth software engineering skills.";
			
			return smart_answer;
		}

		else if ((smart_question.find("find") != std::string::npos || smart_question.find("choose") != std::string::npos || smart_question.find("pick") != std::string::npos) && (smart_question.find("course") != std::string::npos || smart_question.find("class") != std::string::npos)){
			int courseIndex = rand() % course_list.size();
			smart_answer = course_list[courseIndex];

			return smart_answer;
		}

		else{
			
			smart_answer = "Sorry I didn't understand your question. Can you ask it again differently? Or maybe a different question?";
			
			return smart_answer;
		}

		return smart_answer;
	}
}; //class Smart_bot


void converse(Chatbot* a, Chatbot* b, int max_turns) {
		
	for(int turn = 1; turn <= max_turns; turn++) {
		string a_msg = a->get_reply();
		cout << "(" << turn << ") " << a->name() << ": " << a_msg << "\n";

		turn++;
		if (turn > max_turns) return;

		b->tell(a_msg);
		string b_msg = b->get_reply();

		cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
		a->tell(b_msg);
	} // for
}