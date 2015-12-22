#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>


class Heap {
public:
    template <typename RandoIt, typename Comparator>
    static void heapify(RandoIt begin, RandoIt end, Comparator comp)
    {
        size_t size = end - begin;

        for (size_t i = size/2; i--; ) {
            sift_down(begin, end, i, comp);
        }
    }

    template <typename RandoIt, typename Comparator>
    static void push(RandoIt begin, RandoIt end, const typename RandoIt::value_type& val, Comparator comp)
    {        
        size_t size = end - begin;
        sift_up(begin, end, size - 1, comp);
    }

    template <typename RandoIt, typename Comparator>
    static void pop(RandoIt begin, RandoIt end, Comparator comp)
    {
        std::swap(*begin, *end);        
        sift_down(begin, end - 1, 0, comp);
    }

    template <typename RandoIt, typename Comparator>
    static typename RandoIt::value_type& top(RandoIt begin, RandoIt end)
    {
        return *begin;
    }

    template <typename RandoIt, typename Comparator>
    static void sort(RandoIt begin, RandoIt end, Comparator comp)
    {
        size_t size = end - begin;

        heapify(begin, end, comp);

        for (size_t i = size - 1; i > 0; i--) {
            std::swap(*begin, *(begin + i));
            sift_down(begin, begin + i, 0, comp);
        }
    }

private:

    template <typename RandoIt, typename Comparator>
    static void sift_up(RandoIt begin, RandoIt end, size_t pos, Comparator comp)
    {
        size_t parent = pos;

        while ((pos = parent) != 0) {
            parent = (pos - 1)/2;
            if (comp(*(begin + pos), *(begin + parent))) {
                std::swap(*(begin + pos), *(begin + parent));
            }
            else {
                return;
            }
        }
    }

    template <typename RandoIt, typename Comparator>
    static void sift_down(RandoIt begin, RandoIt end, size_t pos, Comparator comp)
    {
        size_t size = end - begin;
        size_t left, right, cur;

        while (true) {
            left  = 2*pos + 1;
            right = 2*pos + 2;

            if (left >= size) {
                return;
            }

            cur = comp(*(begin + pos), *(begin + left)) ? pos : left;

            if (right < size && comp(*(begin + right), *(begin + cur))) {
                cur = right;
            }

            if (cur == pos) {
                return;
            }

            std::swap(*(begin + pos), *(begin + cur));
            pos = cur;
        }
    }

};



int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::pair<int, int>> data;

    int x, y;
    for (size_t i = 0; i < n; i++) {
        std::cin >> x >> y;
        data.push_back(std::make_pair(x, y));
    }

    Heap::sort(data.begin(), data.end(), std::greater<std::pair<int, int>>());

    for (auto& it : data) {
        std::cout<< it.first << " " << it.second << std::endl;
    }

    return 0;
}