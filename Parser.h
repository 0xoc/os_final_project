#pragma once
#include <iostream>
#include <vector>
#include "Context.h"

using namespace std;

class Parser
{
private:
	string _fileName;
	vector<Context> _contexts;
public:
	Parser(string fileName);
	vector<Context>& getContexts();

public:
	static string readFile(string fileName);
};

