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

	int _elapesdTime;	// time that this proccess has run
	int _lastShare;		// the last time this process ran

public:
	Context(): _pid(0), _arrivalTime(0), _burstTime(0), _elapesdTime(0), _lastShare(0) {}
	Context(int pid, int arrivalTime, int burstTime) : 
		_pid(pid), _arrivalTime(arrivalTime), _burstTime(burstTime),
		_elapesdTime(0), _lastShare(0) {}
	Context(string pid, string arrivalTime, string burstTime):
		_elapesdTime(0), _lastShare(0) {
		_pid = stoi(pid);
		_arrivalTime = stoi(arrivalTime);
		_burstTime = stoi(burstTime);
	}
	
	int getPid() const;
	int getArrivalTime() const;
	int getBurstTime() const;
	int getElapsedTime() const;
	int getLastShare() const;
	
	bool started(int systemTime) const;
	bool ended() const;
	bool isActive(int systemTime) const;

	void setPid(int pid);
	void setArrivalTile(int arrivalTime);
	void setBurstTime(int burstTime);
	void run(int timeQ, int systemTime);

	void print() {
		cout << _pid << ";" << _arrivalTime << ';' << _burstTime << endl;
	}

};

