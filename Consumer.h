#pragma once
#include "Context.h"
#include <map>
#include <vector>

using namespace std;

class Consumer
{
private:
	Buffer* _buffer;
	bool* _shouldStop;
	map<int, vector<pair<int, int > > > _timeSheet;
public:
	Consumer(Buffer* buffer, bool* shouldStop);
	void printTimeSheet();
	void consume();
};

