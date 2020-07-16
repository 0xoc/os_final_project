#include "Consumer.h"

Consumer::Consumer(Buffer* buffer, bool* shouldStop): _buffer(buffer), _shouldStop(shouldStop)
{
}

void Consumer::consume()
{
	while (!_shouldStop) {
		_buffer->full.wait();
		Context c = _buffer->currentContext;
		_buffer->empty.signal();

		// if pid of currect context exists in time sheet,
		// try to append to the last time range

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
