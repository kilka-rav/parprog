#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <iterator>
#include <algorithm>
#include <functional>


#define ERROR(message) std::cout << "FILE = " << __FILE__ << " LINE = " << __LINE__ << " ERROR = " << message << std::endl;

void check_argc(int arg);
int check_atoi(int num);

template <typename T>
void print_list(std::list<T>& lst);

template <typename It, typename Order>
void merge_sort(It begin, It end, Order order);

template <typename It>
void merge_sort(It begin, It end);

template <typename T>
void merge_sort(std::list<T>& lst);

