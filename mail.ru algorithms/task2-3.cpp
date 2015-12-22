#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template <typename Countainer, typename Compare = std::greater<typename Countainer::value_type> >
class Heap {
public:
    typedef typename Countainer::value_type value_type;

    void push_back(const value_type& val)
    {
        cont.push_back(val);
    }

    void reserve(size_t n)
    {
        cont.reserve(n);
    }

    value_type& at(size_t n) 
    {
        return cont[n];
    }

    size_t size() const
    {
        return cont.size();
    }

    bool empty() const
    {
        return cont.empty();
    }

    void heapify()
    {
        for (size_t i = size()/2; i--; ) {
            sift_down(i);
        }
    }

    void push(const value_type& val)
    {
        push_back(val);
        sift_up(size()-1);
    }

    void pop()
    {
        std::swap(cont[0], cont[size()-1]);
        cont.pop_back();
        sift_down(0);
    }

    value_type& top()
    {
        return cont[0];
    }

private:
    Countainer cont;
    Compare comp;

    void sift_up(size_t n)
    {
        size_t parent = n;

        while ((n = parent) != 0) {
            parent = (n-1)/2;
            if (comp(cont[n], cont[parent])) {
                std::swap(cont[n], cont[parent]);
            }
            else {
                return;
            }            
        }
    }

    void sift_down(size_t n)
    {
        size_t left, right, cur;

        while (true) {
            left  = 2*n + 1;
            right = 2*n + 2;

            if (left >= size()) {
                return;
            }

            cur = comp(cont[n], cont[left]) ? n : left;

            if (right < size() && comp(cont[right], cont[cur])) {
                cur = right;
            }
            
            if (cur == n) {
                return;
            }

            std::swap(cont[n], cont[cur]);
            n = cur;
        }
    }

};

int main()
{
    int n, weight, sum, carrying, counter = 0;
    std::vector<int> vec;
    Heap<std::vector<int> > heap;

    std::cin >> n;

    heap.reserve(n);
    for (int i = 0; i < n; i++) {
        std::cin >> weight;
        heap.push_back(weight);
    }

    heap.heapify();

    std::cin >> carrying;

    while (!heap.empty()) {
        counter++;
        sum = 0;

        while (!heap.empty() && (sum += heap.top()) <= carrying) {
            vec.push_back(heap.top());
            heap.pop();
        }
        
        for (int item : vec) {
            if (item > 1) {
                heap.push(item/2);
            }            
        }
        vec.clear();
    }

    std::cout << counter << std::endl;

    return 0;
}