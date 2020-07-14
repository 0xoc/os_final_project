#include <iostream>
#include <thread>         // std::thread
#include "Context.h"
#include "Parser.h"

using namespace std;

void producer(Context* buffer) {
	while(1)
	cout << "from producer" << endl;
}

void consumer(Context* buffer) {
	while(1)
	cout << "from consumer" << endl;
}



int main() {
	
	cout << Parser::readFile("data/producer.ctx") << endl;
	return 0;
	Context* buffer = new Context();

	thread _producer(producer, buffer);
	thread _consumer(consumer, buffer);
	
	cout << "Os project started" << endl;
	
	_producer.join();
	_consumer.join();

	delete buffer;

	return 0;
}