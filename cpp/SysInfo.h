#ifndef __SYS_INFO_H_
#define __SYS_INFO_H_

#include "Node.h"

class SysInfo : public Node
{
public:
    /// Constructs the sys info object with a unique identifier of the calling node
    explicit SysInfo(int nodeId);

    /// Prints system info to a log file and standard output
    virtual void run() override;

private:
    /// Prints CPU usage of the program
    void printCPUStats();

    /// Executes the given command, returning its output in string format
    std::string exec(const char* cmd); 
private:
    /// Node identifier
    int m_nodeId;
};

#endif //__SYS_INFO_H_

