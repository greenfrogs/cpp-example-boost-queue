#include <boost/lockfree/queue.hpp>
#include <iostream>
#include <thread>

#define QUEUE_SIZE 5

using namespace boost;

bool isPrime(int n) {
    for (int i = 2; i <= n / i; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

unsigned generatePrime() {
    unsigned p;
    do {
        p = rand();
    } while (!isPrime(p));

    return p;
}

[[noreturn]] void fillQueueWithPrimes(boost::lockfree::queue<unsigned, boost::lockfree::capacity<QUEUE_SIZE>> *queue) {
    srand(time(nullptr));
    while (true) {
        unsigned prime = generatePrime();
        while (queue->push(prime) == 0);
        std::cout << "Pushed prime: " << prime << std::endl;
    }
}

unsigned requestPrime(boost::lockfree::queue<unsigned, boost::lockfree::capacity<QUEUE_SIZE>> *queue) {
    unsigned int prime;
    while (!queue->pop(prime));
    return prime;
}

int main() {
    auto queue = new boost::lockfree::queue<unsigned, boost::lockfree::capacity<QUEUE_SIZE>>();
    std::thread t1(fillQueueWithPrimes, queue);
    t1.detach();
    
    for (int i = 0; i < 150; i++) {
        unsigned prime = requestPrime(queue);
        std::cout << "Popped prime: " << prime << std::endl;
    }

    return 0;
}
