#ifndef RUI_H
#define RUI_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include "define.h"
using namespace std;

class RUI
{
public:
	RUI();
	// output
	void show_warning(const string warning);
	void show_check_result(const string result);
	void show_check_result_spliter();

	void set_spliter(const string spliter, int length);
	// input
	string get_user_input(const string message);


private:
	string _spliter;
	int _spliterLength;
};


#endif  // RUI_H
