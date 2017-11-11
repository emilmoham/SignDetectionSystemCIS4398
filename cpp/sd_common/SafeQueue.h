#ifndef __SAFE_QUEUE_H_
#define __SAFE_QUEUE_H_

#include <deque>
#include <mutex>
#include <thread>
#include <utility>

/**
 * @class SafeQueue
 * @brief Thread-safe queue
 */
template <class T>
class SafeQueue
{
public:
    /// Default constructor
    SafeQueue() = default;

    /// Returns a const_reference to the first element in the queue
    typename std::deque<T>::const_reference front() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.front();
    }
    
    /// Returns a const_reference to the element at the given position in the queue
    typename std::deque<T>::const_reference at(typename std::deque<T>::size_type pos) const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.at(pos);
    }

    /// Returns true if the queue contains the given item, false if else
    bool contains(const T &item) const noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto it = m_queue.cbegin(); it != m_queue.cend(); ++it)
        {
            if (*it == item)
                return true;
        }
        return false;
    }
    
    /// Erases the item from the queue, if it is in the queue
    void erase(const T &item)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto it = m_queue.cbegin(); it != m_queue.cend(); ++it)
        {
            if (*it == item)
            {
                m_queue.erase(it);
                return;
            }
        }

    }   

    /// Appends a copy of the given element to the back of the queue
    void enqueue(const T &item)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push_back(item);
    }

    /// Removes and returns the item at the front of the queue
    T dequeue()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        T item = std::move(m_queue.front());
        m_queue.pop_front();
        return item;
    }

    /// Returns true if the queue is empty, false if else
    bool empty() const noexcept
    {
        return m_queue.empty();
    }

    /// Returns the number of elements in the queue
    typename std::deque<T>::size_type size() const noexcept
    {
        return m_queue.size();
    }

private:
    /// The actual queue structure
    std::deque<T> m_queue;

    /// Mutex
    std::mutex m_mutex;
};

#endif //__SAFE_QUEUE_H_

