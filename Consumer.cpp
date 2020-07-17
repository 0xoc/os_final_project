#include "Consumer.h"
# include <fstream>

Consumer::Consumer(Buffer* buffer, bool* shouldStop): _buffer(buffer), _shouldStop(shouldStop)
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
		consumerFile << "P" << it->first << endl;// string (key) 

		auto v = it->second;

		for (int i = 0; i < v.size(); i++) {
			consumerFile << "\t" << v[i].first << " - " << v[i].second << endl;
		}
	}
	consumerFile << "end <----------";
	consumerFile.close();

}

void Consumer::consume()
{
	bool run = true;

	while (run) {

		_mutex.wait("");
		if (*_shouldStop)
			run = false;
		_mutex.signal("");

		_buffer->full.wait("consumer full");
		Context c = _buffer->currentContext;
		_buffer->empty.signal("consumer empty");

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
