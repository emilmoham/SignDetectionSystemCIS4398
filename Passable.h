#ifndef __PASSABLE_H_
#define __PASSABLE_H_

/**
 * @class Passable
 * @brief Interface for objects that are passed between nodes via MPI
 */
class Passable
{
public:
    // Serializes and sends the object to the given recipient
    virtual void send(int recipient) = 0;

    // Receives and deserializes the object from a sender
    virtual void receive(int sender) = 0;
};

#endif //__PASSABLE_H_

