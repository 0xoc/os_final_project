#pragma once
#include <iostream>
#include <string>
using namespace std;

class Context
{
private:
	int _pid;			// Proccess ID
	int _arrivalTime;	// Arrival Time
	int _burstTime;		// burst time

public:
	Context(): _pid(0), _arrivalTime(0), _burstTime(0) {}
	Context(int pid, int arrivalTime, int burstTime) : 
		_pid(pid), _arrivalTime(arrivalTime), _burstTime(burstTime) {}
	Context(string pid, string arrivalTime, string burstTime) {
		_pid = stoi(pid);
		_arrivalTime = stoi(arrivalTime);
		_burstTime = stoi(burstTime);
	}
	int getPid();
	int getArrivalTime();
	int getBurstTime();

	void setPid(int pid);
	void setArrivalTile(int arrivalTime);
	void setBurstTime(int burstTime);

	void print() {
		cout << _pid << ";" << _arrivalTime << ';' << _burstTime << endl;
	}

};

