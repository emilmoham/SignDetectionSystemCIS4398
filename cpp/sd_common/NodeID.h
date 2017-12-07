#ifndef __NODE_ID_H_
#define __NODE_ID_H_

// List of nodes in the cluster and their identifiers
enum NodeID
{
    MASTER_ID       = 0,
    PREPROCESSOR_ID = 1,
    ANALYZER_A      = 2, 
    ANALYZER_B      = 3,
    RENDERER_ID     = 4
};

#endif //__NODE_ID_H_

