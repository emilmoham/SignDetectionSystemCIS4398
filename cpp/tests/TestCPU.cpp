#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <array>
#include <chrono>
#include <thread>
#include <atomic>

#include <unistd.h>

std::atomic_bool IsBusy;

/// Executes the given command, returning its output in string format
std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;

    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
        throw std::runtime_error("popen() failed!");

    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }

    return result;
}

/// Prints CPU usage of the program
void printCPUStats()
{
    pid_t procId = getpid();
    std::stringstream ss;
    ss << "ps -p " << procId << " -o %cpu";
    try
    {
        std::cout << "CPU Usage: " << exec(ss.str().c_str()) << std::endl;
    }
    catch (std::runtime_error &e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
}

/// Recursively calculates the first n fibonacci numbers in order to use CPU resources
int calculateFib(int n)
{
    if (n == 0)
        return 0;
    else if (n < 3)
        return 1;
    
    return calculateFib(n - 1) + calculateFib(n - 2);
}

/// Uses CPU resources, called in order to check if printCPUStats() is working properly
void useUpCPU()
{
    int fibN = calculateFib(40000);
    std::cout << "\nThe 40,000th number in the fibonacci sequence is " << fibN << std::endl;
    IsBusy.store(false);
}

int main(int argc, char **argv)
{
    IsBusy.store(true);
    std::thread t1(useUpCPU);
    while (IsBusy.load())
    {
        printCPUStats();
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    t1.join();
    return 0;
}
