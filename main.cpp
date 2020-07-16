#include <iostream>
#include <thread>         // std::thread
#include "Context.h"
#include "Parser.h"
#include "Producer.h"

using namespace std;

Context buffer[1];		// main buffer that producer and consumer will use
int T = 0;				// system time, consumer will increment T as time goes on

class RoundRobin{
public:
	int operator()(const Context& c1, const Context& c2) {
		int c1_a = c1.getArrivalTime();
		int c2_a = c2.getArrivalTime();

		return c1_a > c2_a;

	}
};

int SJF (Context& c1, Context& c2) {
	return 0;
};

int main() {
	Producer<RoundRobin> producer("");
	Context c1(3, 5, 0);
	Context c2(1, 0, 0);
	Context c3(2, 2, 0);

	producer._readyQueue.push(c1);
	producer._readyQueue.push(c2);
	producer._readyQueue.push(c3);

	for (int i = 0; i < 3; i++) {
		cout << producer._readyQueue.top().getPid() << endl;
		producer._readyQueue.pop();
	}

	return 0;
}