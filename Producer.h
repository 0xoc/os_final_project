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

public:
	Producer(string sourceFile, Buffer* buffer) :
		_t(0),
		_parser(Parser(sourceFile)),
		_buffer(buffer) {}

	void putOnBuffer(Context c) {
		_buffer->empty.wait("producer empty");
		_buffer->currentContext = c;
		_buffer->count++;
		_buffer->full.signal("producer full");
	}

	void tick() {
		do {
			_updateActiveProcesses();
			if (!_readyQueue.empty()) {
				// produce
				Context* c = _readyQueue.top();
				int q = Scheduler::getTimeQ(c);

				c->run(q, _t);
				_t += q;

				putOnBuffer(*c);

			}
			else {
				_t++;

			}
		} while (_anyRemains());

		putOnBuffer(Context(-1, 0, 0));
	}

private:
	int _t;
	Parser _parser;
	Buffer* _buffer;
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

};

