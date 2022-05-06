#include "sort.hpp"

void check_argc(int arg) {
        if ( arg != 3 ) {
                ERROR("ERROR IN INPUT");
                exit(1);
        }
}

int check_atoi(int num) {
        if ( num == 0 ) {
                ERROR("ERROR IN Atoi");
                exit(1);
        }
        return num;
}

template <typename T>
void print_list(std::list<T>& lst) {
        std::for_each(lst.cbegin(), lst.cend(), [](auto& elem) { std::cout << elem << " "; });
        std::cout << std::endl;
}

template void print_list<int>(std::list<int>&);


template <typename It, typename Order>
void merge_sort(It begin, It end, Order order) {
        auto size = std::distance(begin, end);  
        if ( size > 1 ) {
                It middle = std::next(begin, size / 2);
                merge_sort(begin, middle, order);
                merge_sort(middle, end, order);
                std::inplace_merge(begin, middle, end, order);
        }
        return;
}


template <typename It>
void merge_sort(It begin, It end) {
        merge_sort(begin, end, std::less<typename std::iterator_traits<It>::value_type>());
}

template void merge_sort<std::list<int>::iterator>(std::list<int>::iterator, std::list<int>::iterator);

template <typename T>
void merge_sort(std::list<T>& lst) {
	merge_sort(lst.begin(), lst.end());
}

template void merge_sort<int>(std::list<int>&);
