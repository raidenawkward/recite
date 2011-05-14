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
	// output
	static void show_warning(const string warning);
	static void show_check_result(const string result);

	// input
	static string get_user_input(const string message);
};


#endif  // RUI_H
