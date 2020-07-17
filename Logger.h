#pragma once
#include <iostream>
#include <string>

using namespace std;

class Logger {
public:
	static void log(string msg, int level = 0) {
		// level 0: log
		// level 1: warning
		// level 2: error

		string _level;

		switch (level)
		{
		case 0:
			_level = "INFO";
			break;
		case 1:
			_level = "WARNING";
			break;
		case 2:
			_level = "ERROR";
			break;
		default:
			_level = "SYSTEM";
			break;
		}

		cout << "[" << _level << "] " << msg << endl;
	}
};