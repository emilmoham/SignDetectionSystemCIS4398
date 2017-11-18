#include "LogHelper.h"
#include "SysInfo.h"

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

SysInfo::SysInfo(int nodeId) :
    m_nodeId(nodeId)
{
}

void SysInfo::run()
{
    while (true)
    {
        printCPUStats();
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}

void SysInfo::printCPUStats()
{
    pid_t procId = getpid();
    std::stringstream ss;
    ss << "ps -p " << procId << " -o %cpu";
    try
    {
        std::string output = exec(ss.str().c_str());
        auto newLinePos = output.find('\n');
        if (newLinePos != std::string::npos)
            output = output.substr(newLinePos + 1);
        LOG_DEBUG("SysInfo", "[Node ", m_nodeId, "]: CPU Usage: ", output);
    }
    catch (std::runtime_error &e)
    {
        LOG_ERROR("SysInfo", "Runtime error: ", e.what());
    }
}

std::string SysInfo::exec(char *cmd)
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

