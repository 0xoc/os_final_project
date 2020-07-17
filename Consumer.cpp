#include "Consumer.h"
# include <fstream>

Consumer::Consumer(Buffer* buffer): _buffer(buffer), _lastShareTime(0)
{
}

extern Semaphore _mutex;

void Consumer::printTimeSheet()
{ 
	ofstream consumerFile;
	consumerFile.open("data/consumer.txt");

	consumerFile << "start ---------->" << endl;

	for (auto it = _timeSheet.begin(); it != _timeSheet.end(); it++)
	{
		consumerFile << "P (" << it->first << ")"<< endl;// string (key) 

		auto v = it->second;

		for (int i = 0; i < v.size(); i++) {
			consumerFile << "\t" << v[i].first << " - " << v[i].second << endl;
		}
	}
	consumerFile << "end <----------";
	consumerFile.close();

}

void Consumer::printStats()
{
	ofstream statsFile;
	statsFile.open("data/stats.txt");

	// generate stats
	float atat = 0;
	float awt = 0;
	float art = 0;
	float cpuUtilization = 0;
	float throughput = 0;

	for (auto it = _history.begin(); it != _history.end(); it++) {

		// ignore the idle context
		if (it->first == -2)
			continue;

		Stats _p = getStatsOf(it->first);
		atat += _p.tat;
		awt += _p.wt;
		art += _p.rt;
	}

	// avg
	int l = _history.size();
	atat /= l; 
	awt /= l;
	art /= l;


	// idle stats
	Stats idle = getStatsOf(-2);

	cpuUtilization = (_lastShareTime - idle.elapesdTime) / _lastShareTime;
	throughput = numberOfConsumedProc() / (_lastShareTime * 0.001);

	statsFile << "ATAT: " << atat << endl;
	statsFile << "AWT: " << awt << endl;
	statsFile << "ART: " << art << endl;
	statsFile << "CPU UTILIZATION: " << cpuUtilization << endl;
	statsFile << "THROUGHPUT: " << throughput << endl;

	statsFile.close();

}

Stats Consumer::getStatsOf(int pid)
{
	Stats s;

	if (_history.find(pid) == _history.end())
		return s;

	Context& lastContext = _history[pid];
	s.tat = lastContext.getLastShare() - lastContext.getArrivalTime();
	s.wt = s.tat - lastContext.getBurstTime();
	s.rt = _timeSheet[pid][0].second - lastContext.getArrivalTime();
	s.elapesdTime = lastContext.getElapsedTime();

	return s;
}

void Consumer::consume()
{

	while (true) {

		_buffer->full.wait("consumer full");
		Context c = _buffer->currentContext;
		_buffer->count--;
		_buffer->empty.signal("consumer empty");

		// if pid is -1, producer has finished all proccesses
		if (c.getPid() == -1)
			break;

		// add it to history
		_history[c.getPid()] = c;

		// update last share
		_lastShareTime = c.getLastShare();

		// if pid of currect context exists in time sheet,
		// try to append to the last time range

		bool writtenToTimeSheet = false;

		if (_timeSheet.find(c.getPid()) != _timeSheet.end()) {
			vector< pair<int, int> >& v = _timeSheet[c.getPid()];

			if (v.size() != 0) {
				pair<int, int>& last = v.back();

				if (last.second == c.getLastShareStartTime()) {
					last.second = c.getLastShare();
					writtenToTimeSheet = true;
				}
			}
		}

		if (!writtenToTimeSheet) {
			// add it to the time sheet
			_timeSheet[c.getPid()].push_back(
				make_pair(c.getLastShareStartTime(), c.getLastShare())
			);
		}

		printTimeSheet();
	}
}

int Consumer::numberOfConsumedProc()
{
	if (_history.find(-2) == _history.end())
		return _history.size();
	return _history.size() - 1;
}
