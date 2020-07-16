#include <iostream>
#include <thread>         // std::thread
#include "Context.h"
#include "Parser.h"
#include "Producer.h"

using namespace std;

Context buffer[1];		// main buffer that producer and consumer will use
int T = 0;				// system time, consumer will increment T as time goes on

class RoundRobin {
public:
	int operator()(const Context* c1, const Context* c2) {
		int c1_a = c1->getLastShare() ;
		int c2_a = c2->getLastShare() ;
		if (c1_a == c2_a)
			c1->getPid() > c2->getPid();
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

int SJF (Context& c1, Context& c2) {
	return 0;
};

int main() {
	Producer<RoundRobin> producer("data/producer.ctx");

	producer.tick();
	return 0;
}