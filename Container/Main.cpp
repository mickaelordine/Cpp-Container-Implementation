
#include <iostream>
#include <list>
#include <map>
#include <ostream>

#include "List.h"
#include "Map.h"

namespace ListTest
    {
        // ===== FUNZIONI DI TEST =====
        void test_basic_operations()
        {
            std::cout << "\n========== TEST: Basic Operations ==========\n";
            MyStl::List<int> list;
            
            std::cout << "Empty list: " << (list.empty() ? "YES" : "NO") << std::endl;
            std::cout << "Size: " << list.size() << std::endl;
            
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
            list.print();
            
            list.push_front(5);
            list.push_front(1);
            list.print();
            list.print_reverse();
            
            std::cout << "Front: " << list.front() << std::endl;
            std::cout << "Back: " << list.back() << std::endl;
            std::cout << "Size: " << list.size() << std::endl;
            std::cout << "Empty: " << (list.empty() ? "YES" : "NO") << std::endl;
        }

        void test_pop_operations()
        {
            std::cout << "\n========== TEST: Pop Operations ==========\n";
            MyStl::List<int> list;
            
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
            list.push_back(40);
            list.print();
            
            list.pop_front();
            std::cout << "After pop_front: ";
            list.print();
            
            list.pop_back();
            std::cout << "After pop_back: ";
            list.print();
            
            list.pop_front();
            list.pop_back();
            std::cout << "After popping all: ";
            list.print();
            std::cout << "Empty: " << (list.empty() ? "YES" : "NO") << std::endl;
        }

        void test_copy_constructor()
        {
            std::cout << "\n========== TEST: Copy Constructor ==========\n";
            MyStl::List<int> list1;
            list1.push_back(1);
            list1.push_back(2);
            list1.push_back(3);
            
            std::cout << "Original list: ";
            list1.print();
            
            MyStl::List<int> list2 = list1;
            std::cout << "Copied list: ";
            list2.print();
            
            list1.push_back(999);
            std::cout << "After modifying original: ";
            list1.print();
            std::cout << "Copy unchanged: ";
            list2.print();
        }

        void test_move_constructor()
        {
            std::cout << "\n========== TEST: Move Constructor ==========\n";
            MyStl::List<int> list1;
            list1.push_back(10);
            list1.push_back(20);
            list1.push_back(30);
            
            std::cout << "Original list: ";
            list1.print();
            
            MyStl::List<int> list2 = std::move(list1);
            std::cout << "Moved list: ";
            list2.print();
            std::cout << "Original after move (should be empty): ";
            list1.print();
        }

        void test_assignment_operators()
        {
            std::cout << "\n========== TEST: Assignment Operators ==========\n";
            MyStl::List<int> list1;
            list1.push_back(1);
            list1.push_back(2);
            
            MyStl::List<int> list2;
            list2.push_back(99);
            
            std::cout << "Before assignment:\n";
            std::cout << "List1: ";
            list1.print();
            std::cout << "List2: ";
            list2.print();
            
            list2 = list1;  // Copy assignment
            std::cout << "\nAfter copy assignment:\n";
            std::cout << "List1: ";
            list1.print();
            std::cout << "List2: ";
            list2.print();
            
            MyStl::List<int> list3;
            list3 = std::move(list1);  // Move assignment
            std::cout << "\nAfter move assignment:\n";
            std::cout << "List3: ";
            list3.print();
            std::cout << "List1 (should be empty): ";
            list1.print();
        }

        void test_clear()
        {
            std::cout << "\n========== TEST: Clear ==========\n";
            MyStl::List<int> list;
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
            
            std::cout << "Before clear: ";
            list.print();
            
            list.clear();
            std::cout << "After clear: ";
            list.print();
            std::cout << "Size: " << list.size() << std::endl;
            std::cout << "Empty: " << (list.empty() ? "YES" : "NO") << std::endl;
            
            // Test che possiamo ancora usare la lista dopo clear
            list.push_back(100);
            std::cout << "After adding element: ";
            list.print();
        }

        void test_exceptions()
        {
            std::cout << "\n========== TEST: Exceptions ==========\n";
            MyStl::List<int> list;
            
            try {
                list.front();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty front(): " << e.what() << std::endl;
            }
            
            try {
                list.back();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty back(): " << e.what() << std::endl;
            }
            
            try {
                list.pop_front();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty pop_front(): " << e.what() << std::endl;
            }
            
            try {
                list.pop_back();
            } catch (const std::out_of_range& e) {
                std::cout << "✓ Caught exception on empty pop_back(): " << e.what() << std::endl;
            }
        }

        void test_with_strings()
        {
            std::cout << "\n========== TEST: With Strings ==========\n";
            MyStl::List<std::string> list;
            
            list.push_back("Hello");
            list.push_back("World");
            list.push_front("C++");
            list.push_back("!");
            
            list.print();
            list.print_reverse();
        }

        void full_test()
        {
            ListTest::test_basic_operations();
            std::cout << "\n===================\n";
            ListTest::test_pop_operations();
            std::cout << "\n===================\n";
            ListTest::test_copy_constructor();
            std::cout << "\n===================\n";
            ListTest::test_move_constructor();
            std::cout << "\n===================\n";
            ListTest::test_assignment_operators();
            std::cout << "\n===================\n";
            ListTest::test_clear();
            std::cout << "\n===================\n";
            ListTest::test_exceptions();
            std::cout << "\n===================\n";
            ListTest::test_with_strings();
            std::cout << "\n===================\n";
        }
    }

int main(int argc, char* argv[])
{
    ListTest::full_test();
    MyStl::Map<const int, std::string> map;
    std::pair<const int, std::string> pair(1,"hello");
    map.insert(pair);
    
    return 0;
}
