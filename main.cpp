#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

//chrono_literals include suffix like 's' , 'min' e.g. std::this_thread::sleep_for(1s) = This thread sleeps for 1 second.
using namespace std::chrono_literals;


struct Data {
    int number = 0;
    std::mutex mutex;
};

void print_time_slept(Data &data1) {

    for (int i = 0; i < 10; ++i) {

        std::this_thread::sleep_for(1s);

        data1.mutex.lock();

        data1.number++;
        std::cout << "This thread has slept for " << i << " seconds\n";
        std::cout << "The number is now " << data1.number << std::endl;

        data1.mutex.unlock();

    }
}

int factorial_calc(int num_to_calc) {
    if(num_to_calc == 0) {
        return 1;
    }
    return num_to_calc * factorial_calc(num_to_calc-1);
}

//Default thread
int main() {

    Data data1;

    std::thread thread1(print_time_slept, std::ref(data1));
    float decimal_seconds = 0;

    for (int i = 0; i < 20; ++i) {

        std::this_thread::sleep_for(0.5s);

        data1.mutex.lock();

        if(i > 10)
            data1.number = data1.number +100;

        decimal_seconds = (float)i / 2;
        std::cout << "Main thread has been waiting for " << decimal_seconds << " seconds\n";

        data1.mutex.unlock();

    }
    int number = 5;

    std::cout << "Factorial of " << number << " = " << factorial_calc(number) << std::endl;




    //Blocks main until thread1 is finished
    thread1.join();



    return 0;
}
