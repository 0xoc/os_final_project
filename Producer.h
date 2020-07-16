#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Context.h"

using namespace std;

template<class Scheduler>
class Producer
{
public:
	string _sourceFile;
	priority_queue<Context, vector<Context>, Scheduler> _readyQueue;

public:
	Producer(string sourceFile) {}
};

