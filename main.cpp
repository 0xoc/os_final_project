#include <iostream>
#include <thread>         // std::thread
#include "Context.h"
#include "Parser.h"
#include "Producer.h"
#include "Schedulers.h"
#include "Semaphore.h"
#include "Consumer.h"
#include "Logger.h"

Buffer* buffer = new Buffer();		// main buffer that producer and consumer will use
bool* shouldStop = new bool();		// indicates whether all proccesses are done or not
Semaphore _mutex(1);

void runProducer();
void runConsumer();

int main() {

	*shouldStop = false;
	thread pt = thread(runProducer);
	thread ct = thread(runConsumer);

	pt.join();
	ct.join();

	delete buffer;
	delete shouldStop;

	return 0;
}

void runProducer() {
	Producer<RoundRobin> producer("data/producer.ctx", buffer, shouldStop);
	producer.tick();

	Logger::log("Producer Finished");
}

void runConsumer() {
	Consumer consumer(buffer, shouldStop);
	consumer.consume();

	Logger::log("Consumer Finished");
}