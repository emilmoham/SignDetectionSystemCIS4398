#ifndef __NODE_H_
#define __NODE_H_

/**
 * @class Node
 * @brief Interface for nodes in the cluster
 */
class Node
{
public:
    // Main execution loop
    virtual void run() = 0;
};

#endif //__NODE_H_

