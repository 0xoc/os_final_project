#pragma once
#include <iostream>
#include <string>
#include "Semaphore.h"

using namespace std;

class Context
{
public:
	Context() { _zeroInitialize(); }
	Context(int pid, int arrivalTime, int burstTime) {
		_setupInitialize(pid, arrivalTime, burstTime);
	}
	Context(string pid, string arrivalTime, string burstTime) {
		_setupInitialize(stoi(pid), stoi(arrivalTime), stoi(burstTime));
	}

	int getPid() const;
	int getArrivalTime() const;
	int getBurstTime() const;

	int getElapsedTime() const;
	int getLastShare() const;
	int getRemainingTime() const;

	int getLastShareStartTime() const;
	int getLastShareTimeQuantom() const;

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

private:
	int _pid;						// Proccess ID
	int _arrivalTime;				// Arrival Time
	int _burstTime;					// burst time

	int _elapesdTime;				// time that this proccess has run
	int _lastShareStartTime;		// the last time this process ran
	int _lastShareTimeQuantom;		// duration of the last share
	int _lastShare;					// _lastShareStartTime + _lastShareTimeQuantom

private:
	void _zeroInitialize() {
		_pid = 0; _arrivalTime = 0; _burstTime = 0;
		_elapesdTime = 0; _lastShareStartTime = 0;
		_lastShareTimeQuantom = 0; _lastShare = 0;
	}
	void _setupInitialize(int pid, int arrivalTime, int burstTime) {
		
		_zeroInitialize();

		_pid = pid; _arrivalTime = arrivalTime;
		_burstTime = burstTime;
	}
};


struct Buffer {
	Context currentContext;
	Semaphore full;
	Semaphore empty;

	int count;

	Buffer() : full(0), empty(1), count(0) {}
};