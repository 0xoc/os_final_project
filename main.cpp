#include <iostream>
#include <thread>
#include "Context.h"
#include "Parser.h"
#include "Producer.h"
#include "Schedulers.h"
#include "Semaphore.h"
#include "Consumer.h"
#include "Logger.h"

Buffer* buffer = new Buffer();		// main buffer that producer and consumer will use
Semaphore _mutex(1);				// controls changes to shouldStop variable

void runProducer();						// producer thread function
void runConsumer(Consumer* consumer);	// consumer thread funciton

int main() {

	Consumer consumer(buffer);

	thread pt = thread(runProducer);
	thread ct = thread(runConsumer, &consumer);

	pt.join();
	ct.join();

	Logger::log("Consumer Finished");
	
	consumer.printStats();

	delete buffer;

	return 0;
}

void runProducer() {
	Producer<RoundRobin> producer("data/producer.ctx", buffer);
	producer.tick();

	Logger::log("Producer Finished");
}

void runConsumer(Consumer* consumer) {
	consumer->consume();
}