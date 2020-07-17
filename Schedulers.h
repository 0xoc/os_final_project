#pragma once
#include "Context.h"

class RoundRobin {
public:
	int operator()(const Context* c1, const Context* c2) {
		int c1_a = c1->getLastShare();
		int c2_a = c2->getLastShare();
		if (c1_a == c2_a)
			return c1->getPid() > c2->getPid();
		return c1_a > c2_a;
	}

	static int getTimeQ(Context* c) {
		int q = 100;

		if (c->getRemainingTime() > q)
			return q;
		else
			return c->getRemainingTime();

	}
};

class SJF {
public:
	int operator()(const Context* c1, const Context* c2) {
		int c1_a = c1->getBurstTime();
		int c2_a = c2->getBurstTime();
		if (c1_a == c2_a)
			return c1->getPid() > c2->getPid();
		return c1_a > c2_a;
	}

	static int getTimeQ(Context* c) {
		return c->getRemainingTime();
	}
};

class SRT {
public:
	int operator()(const Context* c1, const Context* c2) {
		int c1_a = c1->getRemainingTime();
		int c2_a = c2->getRemainingTime();
		if (c1_a == c2_a)
			return c1->getPid() > c2->getPid();
		return c1_a > c2_a;
	}

	static int getTimeQ(Context* c) {
		return 1;
	}
};
