#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Context.h"

using namespace std;

template<class Scheduler>
class Producer
{
private:
	int _t;
	Parser _parser;
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
	Producer(string sourceFile): _t(0) , _parser(Parser(sourceFile)) {
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
			} else {
				_t++;
			}
		} while (_anyRemains());
	}
};

