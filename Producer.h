#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Context.h"
#include "Semaphore.h"
#include <thread>

using namespace std;

extern Semaphore _mutex;

template<class Scheduler>
class Producer
{
private:
	int _t;
	Parser _parser;
	Buffer* _buffer;
	bool* _shouldStop;
	priority_queue<Context*, vector<Context*>, Scheduler> _readyQueue;

private:
	void _clearReadyQ() {
		priority_queue<Context*, vector<Context*>, Scheduler> empy;
		swap(_readyQueue, empy);
	}

private:
	void _updateActiveProcesses() {
		_clearReadyQ();
		for (int i = 0; i < _parser.getContexts().size(); i++) {
			Context* c = &_parser.getContexts()[i];
			if (c->isActive(_t)) {
				_readyQueue.push(c);
			}
		}
	}

	bool _anyRemains() {
		for (int i = 0; i < _parser.getContexts().size(); i++) {
			Context c = _parser.getContexts()[i];
			if (!c.ended())
				return true;
		}

		return false;
	}

public:
	Producer(string sourceFile, Buffer* buffer, bool* shouldStop): 
		_t(0) , 
		_parser(Parser(sourceFile)),
		_shouldStop(shouldStop),
		_buffer(buffer) {}

	void tick() {
		do {
			_updateActiveProcesses();
			if (!_readyQueue.empty()) {
				// produce
				Context* c = _readyQueue.top();
				int q = Scheduler::getTimeQ(c);

				c->run(q, _t);
				_t += q;

				_buffer->empty.wait("producer empty");
				_buffer->currentContext = *c;
				_buffer->full.signal("producer full");
			} else {
				_t++;
			}
		} while (_anyRemains());

		_mutex.wait("producer should stop");
		*_shouldStop = true;
		_mutex.signal("producer shoudl stop ");

	}

};

