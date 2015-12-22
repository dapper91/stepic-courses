#include <iostream>
#include <iterator>
#include <vector>


template <typename Comparator>
size_t upper_bound(std::vector<int> data, size_t from, size_t to, Comparator comp)
{
    size_t pivot;
    int result = to;

    while (from != to) {
        pivot = from + (to - from)/2;

        if (comp(data[pivot])) {
            from = pivot + 1;
        }
        else {
            result = pivot;
            to = pivot;
        }
    }

    return result;
}


template <typename Comparator>
void insertion_sort(std::vector<int>& data, Comparator comp)
{
    size_t bound = 0, index = 0;
    size_t size = data.size();
    int val;

    while (bound != size) {
        val = data[bound];
        index = upper_bound(data, 0, bound, std::bind2nd(comp, val));

        for (size_t i = bound; i > index; i--) {
            data[i] = data[i-1];
        }
        data[index] = val;
        bound++;       
    }    
}

int main()
{
    std::vector<int> data(std::istream_iterator<int>(std::cin),
                          std::istream_iterator<int>());   

    insertion_sort(data, std::less<int>());

    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}