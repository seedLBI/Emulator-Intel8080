#ifndef RINGBUFFER_H
#define RINGBUFFER_H


#include <memory>
#include <vector>
#include <string>
#include <stdexcept>



template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity)
        : _capacity(capacity), buffer(capacity), head(0), tail(0), _size(0) {}

    explicit RingBuffer()
        : _capacity(0), buffer(0), head(0), tail(0), _size(0) {}


    void push_front(const T& value) {
        head = (head == 0) ? _capacity - 1 : head - 1;
        buffer[head] = value;
        if (_size < _capacity) {
            ++_size;
        }
        else {
            tail = (tail == 0) ? _capacity - 1 : tail - 1;
        }
    }

    void pop_front() {
        if (_size == 0) {
            throw std::out_of_range("RingBuffer is empty");
        }
        head = (head + 1) % _capacity;
        --_size;
    }

    const T& front() const {
        if (_size == 0) {
            throw std::out_of_range("RingBuffer is empty");
        }
        return buffer[head];
    }

    void clear() {
        head = 0;
        tail = 0;
        _size = 0;
    }

    size_t size() const { return _size; }

    size_t capacity() const { return _capacity; }

    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return buffer[(head + index) % _capacity];
    }

    void resize(size_t new_capacity) {
        if (new_capacity == _capacity) {
            return; // Никаких изменений не требуется
        }

        std::vector<T> new_buffer(new_capacity);

        // Сохраняем элементы, если новая емкость больше или равна текущему размеру
        size_t num_elements_to_copy = _size < new_capacity ? _size: new_capacity;

        for (size_t i = 0; i < num_elements_to_copy; ++i) {
            new_buffer[i] = buffer[(head + i) % _capacity];
        }

        buffer = std::move(new_buffer);
        _capacity = new_capacity;
        head = 0;
        tail = num_elements_to_copy % new_capacity;
        _size = num_elements_to_copy;
    }

private:
    size_t _capacity;
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t _size;
};


#endif // !RINGBUFFER_H

