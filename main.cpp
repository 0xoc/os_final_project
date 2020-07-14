#include <iostream>
#include <thread>         // std::thread

using namespace std;

void producer() {
	while(1)
	cout << "from producer" << endl;
}

void consumer() {
	while(1)
	cout << "from consumer" << endl;
}

int main() {
	thread _producer(producer);
	thread _consumer(consumer);


	cout << "Os project started" << endl;
	
	_producer.join();
	_consumer.join();

	return 0;
}