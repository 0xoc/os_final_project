#include "Consumer.h"

Consumer::Consumer(Buffer* buffer, bool* shouldStop): _buffer(buffer), _shouldStop(shouldStop)
{
}

void Consumer::consume()
{
	bool run = true;

	while (run) {
		if (*_shouldStop)
			run = false;

		_buffer->full.wait("consumer full");
		Context c = _buffer->currentContext;
		_buffer->empty.signal("consumer empty");

		// if pid of currect context exists in time sheet,
		// try to append to the last time range

		cout << c.getPid() << " : " << c.getLastShareStartTime() << " - " << c.getLastShare() << endl;


		if (_timeSheet.find(c.getPid()) != _timeSheet.end()) {
			vector< pair<int, int> >& v = _timeSheet[c.getPid()];

			if (v.size() != 0) {
				pair<int, int>& last = v.back();

				if (last.second == c.getLastShareStartTime()) {
					last.second = c.getLastShare();
				}
			}
		}
		else {
			// add it to the time sheet
			_timeSheet[c.getPid()].push_back(
				make_pair(c.getLastShareStartTime(), c.getLastShare())
			);
		}
	}
}
