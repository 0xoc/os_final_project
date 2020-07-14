#pragma once
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

	int getPid();
	int getArrivalTime();
	int getBurstTime();

	void setPid(int pid);
	void setArrivalTile(int arrivalTime);
	void setBurstTime(int burstTime);

};

