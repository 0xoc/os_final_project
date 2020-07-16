#include <iostream>
#include <thread>         // std::thread
#include "Context.h"
#include "Parser.h"
#include "Producer.h"
#include "Schedulers.h"
#include "Semaphore.h"

Buffer* buffer = new Buffer();		// main buffer that producer and consumer will use

int main() {
	Producer<RoundRobin> producer("data/producer.ctx", buffer);

	producer.tick();

	delete buffer;
	return 0;
}