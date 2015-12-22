#include <iostream>
#include <vector>


template <typename RandomIt, typename Comparator>
void merge_sort(RandomIt begin, RandomIt end, Comparator comp)
{
    typedef typename RandomIt::value_type value_type;

    size_t size = end - begin;
    RandomIt pivot = begin + size / 2;    

    if (size > 1) {
        value_type* tmp = new value_type[size];

        merge_sort(begin, pivot, comp);
        merge_sort(pivot, end, comp);
        merge(begin, pivot, pivot, end, tmp, comp);

        std::copy(tmp, tmp + size, begin);

        delete[] tmp;
    }
}

template <typename RandomIt, typename OutIt, typename Comparator>
void merge(RandomIt begin1, RandomIt end1, 
           RandomIt begin2, RandomIt end2, 
           OutIt output, Comparator comp)
{
    while (begin1 != end1 && begin2 != end2) {
        if (comp(*begin1, *begin2)) {
            *output = *begin1;
            output++;
            begin1++;
        }
        else {
            *output = *begin2;
            output++;
            begin2++;
        }
    }

    while (begin1 != end1) {
        *output++ = *begin1++;
    }

    while (begin2 != end2) {
        *output++ = *begin2++;
    }
}

enum type {
    BEGIN,
    END
};


int main ()
{
    std::vector<std::pair<int, type>> data;
    size_t n;
    int begin, end;

    std::cin >> n;

    for (size_t i = 0; i < n; i++) {
        std::cin >> begin >> end;
        data.push_back(std::make_pair(begin, BEGIN));
        data.push_back(std::make_pair(end,   END));
    }

    merge_sort(data.begin(), data.end(), std::less<std::pair<int, type>>());   

    size_t segments = 0, length = 0;
    int prev = 0;
    for (auto& it : data) {
        if (segments == 1) {
            length += it.first - prev;
        }
        if (it.second == BEGIN) {
            segments++;
        }
        else {
            segments--;
        }  
        prev = it.first;      
    }

    std::cout << length << std::endl;

    return 0;
}