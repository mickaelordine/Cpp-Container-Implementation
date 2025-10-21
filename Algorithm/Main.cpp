#include <chrono>
#include <iostream>
#include <vector>

#include "../Container/Deque.h"
#include "Sorting/Algorithm.h"

#define amount 10

namespace bubble_test
{
    void test()
    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::vector<int> v;
        for (int i = 0; i < amount; ++i)
        {
            v.push_back(amount - i);
        }
    
        start =  std::chrono::system_clock::now();
        MyStl::bubble_sort(v.begin(), v.end());
        end =  std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "bubble Sort elapsed time: " << elapsed_seconds.count() << "s\n";
        std::cout << "\n";
        v.clear();
    }
}

namespace quicksort_test
{
    void test()
    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        MyStl::Deque<int> dq;
        std::vector<int> v;
        for (int i = 0; i < amount; ++i)
        {
            v.push_back(amount - i);
        }
    
        start =  std::chrono::system_clock::now();
        MyStl::quick_sort(v.begin(), v.end());
        end =  std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Quick Sort elapsed time: " << elapsed_seconds.count() << "s\n";
        std::cout << "\n";
        v.clear();
    }
}

namespace insertion_test
{
    void test()
    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        MyStl::Deque<int> dq;
        std::vector<int> v;
        for (int i = 0; i < amount; ++i)
        {
            v.push_back(amount - i);
        }
    
        start =  std::chrono::system_clock::now();
        MyStl::insertion_sort(  v.begin(), v.end());
        end =  std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "insertion Sort elapsed time: " << elapsed_seconds.count() << "s\n";
        std::cout << "\n";

        for (auto elem : v)
        {
            std::cout << elem << " ";
        }
        std::cout << "\n";
        v.clear();
    }
}

namespace selection_test
{
    void test()
    {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        MyStl::Deque<int> dq;
        std::vector<int> v;
        for (int i = 0; i < amount; ++i)
        {
            v.push_back(amount - i);
        }
    
        start =  std::chrono::system_clock::now();
        MyStl::selection_sort(  v.begin(), v.end());
        end =  std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "selection Sort elapsed time: " << elapsed_seconds.count() << "s\n";
        std::cout << "\n";
        for (auto elem : v)
        {
            std::cout << elem << " ";
        }
        std::cout << "\n";
        v.clear();
    }
}


int main()
{
    // bubble_test::test();
    // quicksort_test::test();
    // insertion_test::test();
    // selection_test::test();
    
    return 0;
}
