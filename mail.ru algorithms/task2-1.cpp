#include <iostream>
#include <algorithm>



template <typename T>
class Deque {
public:
    Deque() :
        _capacity(1),
        _size(0),
        _begin(0),
        _data(nullptr)
    {
        _alloc(0);
    }

    size_t size()
    {
        return _size;
    }

    size_t empty()
    {
        return _size == 0;
    }

    T& front()
    {
        return _data[_begin];
    }

    T& back()
    {
        return _data[_prev(_end())];
    }

    void push_front(const T& value)
    {
        if (_size == _capacity-1) {
            _alloc_ahead(_size+1);
        }
        _begin = _prev(_begin);
        _data[_begin] = value;
        _size++;
    }

    void push_back(const T& value)
    {
        if (_size == _capacity-1) {
            _alloc_ahead(_size+1);
        }
        _data[_end()] = value;
        _size++;
    }

    void pop_front()
    {
        _size--;
        _begin = _next(_begin);
        if (_size < _capacity * DECREASE_FACTOR) {
            _alloc_ahead(_size+1);
        }
    }

    void pop_back()
    {
        _size--;
        if (_size < _capacity * DECREASE_FACTOR) {
            _alloc_ahead(_size+1);
        }
    }

private:
    T* _data;
    size_t _size;
    size_t _capacity;
    size_t _begin;

    const float INCREASE_FACTOR = 1.5;
    const float DECREASE_FACTOR = 0.5;

    size_t _end()
    {
        return (_begin + _size)%_capacity;
    }

    size_t _next(size_t index)
    {
        return (index + 1)%_capacity;
    }

    size_t _prev(size_t index)
    {
        return (index == 0) ? _capacity-1 : index-1;
    }

    void _alloc(size_t n)
    {
        _size = std::min(_size, n);     

        T* tmp = new T [n+1];
        for (size_t i = _begin, j = 0; i != _end(); i = _next(i), j++) {            
            tmp[j] = _data[i];
        }
        std::swap(tmp, _data);
        _capacity = n+1;
        _begin = 0;     

        delete[] tmp;
    }

    void _alloc_ahead(size_t n)
    {
        _alloc(n * INCREASE_FACTOR);
    }
};

int main()
{
    int n, op, val, res;   

    std::cin >> n;
    Deque<int> deq;

    for (int i = 0; i < n; i++) {
        std::cin >> op;
        std::cin >> val;

        switch (op) {
            case 1:
                deq.push_front(val);                
                break;
            case 3:
                deq.push_back(val);
                break;
            case 2:
                if (deq.empty()) {
                    res = -1;
                }
                else {
                    res = deq.front();
                    deq.pop_front();
                }
                if (val != res) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
            case 4:
                if (deq.empty()) {
                    res = -1;
                }
                else {
                    res = deq.back();
                    deq.pop_back();
                }
                if (val != res) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }
                break;
        }
    }

    std::cout << "YES" << std::endl;

    return 0;
}