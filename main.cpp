#include <iostream>
#include <thread>         // std::thread
#include "Context.h"
#include "Parser.h"
#include "Producer.h"
#include "Schedulers.h"
#include "Semaphore.h"
#include "Consumer.h"

Buffer* buffer = new Buffer();		// main buffer that producer and consumer will use
bool* shouldStop = new bool();		// indicates whether all proccesses are done or not

int main() {
	*shouldStop = false;
	Producer<RoundRobin> producer("data/producer.ctx", buffer, shouldStop);
	Consumer consumer(buffer, shouldStop);

	producer.tick();

	delete buffer;
	delete shouldStop;
	return 0;
}