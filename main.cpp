#include <stddef.h>
#include <string>
#include <iostream>
#include <sstream>

template <typename T>
class CircularBuffer
{
    using value_type = T;
    using size = size_t;

private:
    value_type *m_buffer;
    size m_capacity;
    size m_head;
    size m_tail;

public:
    CircularBuffer(size capacity);

    void enqueue(value_type element);

    value_type dequeue();

    bool isFull();

    bool isEmpty();

    std::string toString();

    ~CircularBuffer();
};

template <typename T>
CircularBuffer<T>::CircularBuffer(size capacity) : m_capacity(capacity),
                                                   m_buffer(new value_type[capacity]),
                                                   m_head(0),
                                                   m_tail(0){};

template <typename T>
void CircularBuffer<T>::enqueue(value_type element)
{
    if (isFull())
        throw std::runtime_error("buffer is full");

    m_head = (m_head + 1) % m_capacity;
    m_buffer[m_head] = element;
}

template <typename T>
T CircularBuffer<T>::dequeue()
{

    T element = m_buffer[m_tail];
    m_tail = (m_tail + 1) % m_capacity;

    return element;
}

template <typename T>
bool CircularBuffer<T>::isFull()
{
    return m_tail == (m_head - 1) % m_capacity;
}

template <typename T>
bool CircularBuffer<T>::isEmpty()
{
    return m_head == m_tail;
}

template <typename T>
CircularBuffer<T>::~CircularBuffer()
{
    delete[] m_buffer;
    m_capacity = 0;
    m_head = -1;
    m_tail = 0;
}

template <>
std::string CircularBuffer<char>::toString() {

    std::stringstream stream;

    stream << "capacity: " << m_capacity << std::endl;
    stream << "head: " << m_head << std::endl;
    stream << "tail: " << m_tail << std::endl;

    for (size_t i = 0; i < m_capacity; i++)
    {
        stream << "[" << m_buffer[i] << "] ";
    }

    stream << std::endl;
    return stream.str();
}


int main()
{

    CircularBuffer<char> buffer = CircularBuffer<char>(4);
    buffer.enqueue('A');
    buffer.enqueue('B');
    buffer.enqueue('C');
    buffer.enqueue('D');

    std::cout << buffer.toString() << std::endl;

    // char c1 = buffer.dequeue();
    // std::cout << "-> [" << c1 << "] <-" << std::endl;
    // std::cout << buffer.toString() << std::endl;

    // char c2 = buffer.dequeue();
    // std::cout << "-> [" << c2 << "] <-" << std::endl;
    // std::cout << buffer.toString() << std::endl;

    return 0;
}