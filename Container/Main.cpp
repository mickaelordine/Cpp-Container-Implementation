
#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include <cassert>

#include "Deque.h"
#include "List.h"
#include "Map.h"
#include "Set.h"

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

namespace MapTest
{
    // Utility per stampare separatori
    void printSeparator(const std::string& title = "")
    {
        std::cout << "\n" << std::string(60, '=') << "\n";
        if (!title.empty())
            std::cout << "  " << title << "\n" << std::string(60, '=') << "\n";
    }

    void printSubSection(const std::string& title)
    {
        std::cout << "\n--- " << title << " ---\n";
    }

    // Helper per stampare una mappa (in-order traversal visivo)
    template<typename K, typename T>
    void printMap(MyStl::Map<K, T>& map, const std::string& name)
    {
        std::cout << "📦 Map [" << name << "] - Size: " << map.size() << "\n";
        std::cout << "   Content: { ";
        // Qui dovresti iterare sulla mappa, per ora stampiamo manualmente
        std::cout << "... }\n";
    }

    // Test 1: Default Constructor
    void testDefaultConstructor()
    {
        printSeparator("TEST 1: Default Constructor");
        
        MyStl::Map<int, std::string> map;
        std::cout << "  Created empty map\n";
        std::cout << "  Size: " << map.size() << " (expected: 0)\n";
        std::cout << "  Empty: " << (map.empty() ? "Yes" : "No") << "\n";
    }

    // Test 2: Insert e accesso con operator[]
    void testInsertAndAccess()
    {
        printSeparator("TEST 2: Insert & Operator[]");
        
        MyStl::Map<int, std::string> map;
        
        printSubSection("Inserting elements");
        std::pair<const int, std::string> p1(10, "Dieci");
        std::pair<const int, std::string> p2(5, "Cinque");
        std::pair<const int, std::string> p3(15, "Quindici");
        std::pair<const int, std::string> p4(3, "Tre");
        std::pair<const int, std::string> p5(7, "Sette");
        
        map.insert(p1);
        std::cout << "  [1] Inserted (10, \"Dieci\") - Size: " << map.size() << "\n";
        
        map.insert(p2);
        std::cout << "  [2] Inserted (5, \"Cinque\") - Size: " << map.size() << "\n";
        
        map.insert(p3);
        std::cout << "  [3] Inserted (15, \"Quindici\") - Size: " << map.size() << "\n";
        
        map.insert(p4);
        std::cout << "  [4] Inserted (3, \"Tre\") - Size: " << map.size() << "\n";
        
        map.insert(p5);
        std::cout << "  [5] Inserted (7, \"Sette\") - Size: " << map.size() << "\n";

        std::cout << "\n  Tree Structure (conceptual):\n";
        std::cout << "           10(Dieci)\n";
        std::cout << "          /          \\\n";
        std::cout << "      5(Cinque)    15(Quindici)\n";
        std::cout << "      /      \\\n";
        std::cout << "   3(Tre)  7(Sette)\n";

        printSubSection("Accessing with operator[]");
        std::cout << "  map[10] = \"" << map[10] << "\"\n";
        std::cout << "  map[5]  = \"" << map[5] << "\"\n";
        std::cout << "  map[15] = \"" << map[15] << "\"\n";
        std::cout << "  map[3]  = \"" << map[3] << "\"\n";
        std::cout << "  map[7]  = \"" << map[7] << "\"\n";

        printSubSection("Creating new element with operator[]");
        std::cout << "  Before: Size = " << map.size() << "\n";
        std::string val = map[20]; // Dovrebbe creare elemento
        std::cout << "  map[20] = \"" << val << "\" (default string)\n";
        std::cout << "  After: Size = " << map.size() << "\n";
    }

    // Test 3: Find
    void testFind()
    {
        printSeparator("TEST 3: Find");
        
        MyStl::Map<int, std::string> map;
        map.insert(std::make_pair(100, "Cento"));
        map.insert(std::make_pair(50, "Cinquanta"));
        map.insert(std::make_pair(150, "Centocinquanta"));
        
        printSubSection("Finding existing keys");
        auto result1 = map.find(100);
        std::cout << "  find(100): {" << result1.first << ", \"" << result1.second << "\"}\n";
        
        auto result2 = map.find(50);
        std::cout << "  find(50):  {" << result2.first << ", \"" << result2.second << "\"}\n";

        printSubSection("Finding non-existing key");
        auto result3 = map.find(999);
        std::cout << "  find(999): Should print error message above\n";
    }

    // Test 4: At (con eccezioni)
    void testAt()
    {
        printSeparator("TEST 4: At (with exceptions)");
        
        MyStl::Map<int, std::string> map;
        map.insert(std::make_pair(1, "Uno"));
        map.insert(std::make_pair(2, "Due"));
        
        printSubSection("Accessing existing keys");
        try {
            std::cout << "  map.at(1) = \"" << map.at(1) << "\"\n";
            std::cout << "  map.at(2) = \"" << map.at(2) << "\"\n";
        } catch(const std::exception& e) {
            std::cout << "  ❌ Unexpected exception: " << e.what() << "\n";
        }

        printSubSection("Accessing non-existing key");
        try {
            std::cout << "  Trying map.at(999)...\n";
            std::string val = map.at(999);
            std::cout << "  ❌ Should have thrown exception!\n";
        } catch(const std::exception& e) {
            std::cout <<  e.what() << "  ✓ Exception caught correctly\n";
        }
    }

    // Test 5: Copy Constructor
    void testCopyConstructor()
    {
        printSeparator("TEST 5: Copy Constructor");
        
        MyStl::Map<int, std::string> original;
        original.insert(std::make_pair(1, "Alpha"));
        original.insert(std::make_pair(2, "Beta"));
        original.insert(std::make_pair(3, "Gamma"));
        
        std::cout << "Original map created with 3 elements\n";
        std::cout << "  Size: " << original.size() << "\n";

        printSubSection("Creating copy");
        MyStl::Map<int, std::string> copy(original);
        std::cout << "  Copy size: " << copy.size() << "\n";
        
        printSubSection("Verifying copy content");
        std::cout << "  copy[1] = \"" << copy[1] << "\"\n";
        std::cout << "  copy[2] = \"" << copy[2] << "\"\n";
        std::cout << "  copy[3] = \"" << copy[3] << "\"\n";

        printSubSection("Modifying copy (should not affect original)");
        copy.insert(std::make_pair(4, "Delta"));
        std::cout << "  Inserted (4, \"Delta\") in copy\n";
        std::cout << "  Original size: " << original.size() << " (should be 3)\n";
        std::cout << "  Copy size: " << copy.size() << " (should be 4)\n";
    }

    // Test 6: Copy Assignment
    void testCopyAssignment()
    {
        printSeparator("TEST 6: Copy Assignment");
        
        MyStl::Map<int, std::string> map1;
        map1.insert(std::make_pair(10, "Ten"));
        map1.insert(std::make_pair(20, "Twenty"));
        
        MyStl::Map<int, std::string> map2;
        map2.insert(std::make_pair(99, "NinetyNine"));
        
        std::cout << "Map1 size: " << map1.size() << "\n";
        std::cout << "Map2 size: " << map2.size() << "\n";

        printSubSection("Assignment: map2 = map1");
        map2 = map1;
        
        std::cout << "  Map2 size after assignment: " << map2.size() << " (should be 2)\n";
        std::cout << "  map2[10] = \"" << map2[10] << "\"\n";
        std::cout << "  map2[20] = \"" << map2[20] << "\"\n";

        printSubSection("Self-assignment test");
        map1 = map1;
        std::cout << "  Map1 size after self-assignment: " << map1.size() << " (should be 2)\n";
    }

    // Test 7: Move Constructor
    void testMoveConstructor()
    {
        printSeparator("TEST 7: Move Constructor");
        
        MyStl::Map<int, std::string> original;
        original.insert(std::make_pair(5, "Five"));
        original.insert(std::make_pair(10, "Ten"));
        
        std::cout << "Original map size: " << original.size() << "\n";

        printSubSection("Moving to new map");
        MyStl::Map<int, std::string> moved(std::move(original));
        
        std::cout << "  Moved map size: " << moved.size() << " (should be 2)\n";
        std::cout << "  Original map size: " << original.size() << " (should be 0)\n";
        std::cout << "  moved[5] = \"" << moved[5] << "\"\n";
    }

    // Test 8: Move Assignment
    void testMoveAssignment()
    {
        printSeparator("TEST 8: Move Assignment");
        
        MyStl::Map<int, std::string> map1;
        map1.insert(std::make_pair(100, "Hundred"));
        
        MyStl::Map<int, std::string> map2;
        map2.insert(std::make_pair(200, "TwoHundred"));
        map2.insert(std::make_pair(300, "ThreeHundred"));
        
        std::cout << "Map1 size: " << map1.size() << "\n";
        std::cout << "Map2 size: " << map2.size() << "\n";

        printSubSection("Move assignment: map1 = std::move(map2)");
        map1 = std::move(map2);
        
        std::cout << "  Map1 size: " << map1.size() << " (should be 2)\n";
        std::cout << "  Map2 size: " << map2.size() << " (should be 0)\n";
        std::cout << "  map1[200] = \"" << map1[200] << "\"\n";
    }

    // Test 9: Clear
    void testClear()
    {
        printSeparator("TEST 9: Clear");
        
        MyStl::Map<int, std::string> map;
        map.insert(std::make_pair(1, "One"));
        map.insert(std::make_pair(2, "Two"));
        map.insert(std::make_pair(3, "Three"));
        map.insert(std::make_pair(4, "Four"));
        map.insert(std::make_pair(5, "Five"));
        
        std::cout << "Map size before clear: " << map.size() << "\n";
        
        printSubSection("Clearing map");
        map.clear();
        
        std::cout << "  Map size after clear: " << map.size() << " (should be 0)\n";
        std::cout << "  Empty: " << (map.empty() ? "Yes" : "No") << "\n";

        printSubSection("Inserting after clear");
        map.insert(std::make_pair(99, "NinetyNine"));
        std::cout << "  Map size: " << map.size() << " (should be 1)\n";
        std::cout << "  map[99] = \"" << map[99] << "\"\n";
    }

    // Test 10: Stress Test
    void testStress()
    {
        printSeparator("TEST 10: Stress Test");
        
        MyStl::Map<int, int> map;
        const int N = 1000;
        
        printSubSection("Inserting 1000 elements");
        for (int i = 0; i < N; ++i) {
            map.insert(std::make_pair(i, i * 10));
        }
        std::cout << "  ✓ Inserted " << N << " elements\n";
        std::cout << "  Final size: " << map.size() << "\n";

        printSubSection("Accessing random elements");
        std::cout << "  map[0] = " << map[0] << "\n";
        std::cout << "  map[500] = " << map[500] << "\n";
        std::cout << "  map[999] = " << map[999] << "\n";

        printSubSection("Clearing large map");
        map.clear();
        std::cout << "  ✓ Cleared map\n";
        std::cout << "  Size after clear: " << map.size() << "\n";
    }
    
    // Test 11: Erase
    void testErase()
    {
        MyStl::Map<int, std::string> map;
    
        // Costruisci albero
        map.insert({10, "Ten"});
        map.insert({5, "Five"});
        map.insert({15, "Fifteen"});
        map.insert({3, "Three"});
        map.insert({7, "Seven"});
        map.insert({12, "Twelve"});
        map.insert({20, "Twenty"});
    
        std::cout << "Initial size: " << map.size() << "\n\n";
    
        // Caso 1: Foglia
        std::cout << "=== Test 1: Erase leaf (3) ===\n";
        map.erase(3);
        std::cout << "Size: " << map.size() << "\n\n";
    
        // Caso 2: Un figlio
        std::cout << "=== Test 2: Erase node with one child (5) ===\n";
        map.erase(5);
        std::cout << "Size: " << map.size() << "\n\n";
    
        // Caso 3: Due figli
        std::cout << "=== Test 3: Erase node with two children (15) ===\n";
        map.erase(15);
        std::cout << "Size: " << map.size() << "\n\n";
    
        // Verifica contenuto
        std::cout << "=== Remaining elements ===\n";
        std::cout << "map[10] = " << map[10] << "\n";
        std::cout << "map[7] = " << map[7] << "\n";
        std::cout << "map[20] = " << map[20] << "\n";
    }

    // Test 12: Iterator
    void testIterator()
    {
        MyStl::Map<int, std::string> map;
        map.insert({10, "Ten"});
        map.insert({5, "Five"});
        map.insert({15, "Fifteen"});
        map.insert({3, "Three"});
        map.insert({7, "Seven"});
    
        std::cout << "=== Iterating with range-based for ===\n";
        for (auto& pair : map)
        {
            std::cout << pair.first << " -> " << pair.second << "\n";
        }
    
        std::cout << "\n=== Iterating with explicit iterator ===\n";
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            std::cout << it->first << " -> " << it->second << "\n";
        }
    
        std::cout << "\n=== Modifying values through iterator ===\n";
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            it->second += "!";  // Modifica il valore
        }
    
        for (auto& pair : map)
        {
            std::cout << pair.first << " -> " << pair.second << "\n";
        }
    }
    
    // Funzione principale per eseguire tutti i test
    void runAllTests()
    {
        std::cout << "\n";
        std::cout << "//////////////////////////////////////////////////////////////\n";
        std::cout << "/           MyStl::Map - COMPREHENSIVE TEST SUITE            /\n";
        std::cout << "//////////////////////////////////////////////////////////////\n";

        try {
            testDefaultConstructor();
            testInsertAndAccess();
            testFind();
            testAt();
            testCopyConstructor();
            testCopyAssignment();
            testMoveConstructor();
            testMoveAssignment();
            testClear();
            testStress();
            testErase();
            testIterator();

            printSeparator("SUMMARY");
            std::cout << "✓ All tests completed!\n";
            std::cout << "  Check output above for any issues.\n\n";

        } catch (const std::exception& e) {
            std::cout << "\n❌ FATAL ERROR: " << e.what() << "\n\n";
        }
    }
}

namespace DequeTest
{
    // Utility functions
    void printSeparator(const std::string& title = "")
    {
        std::cout << "\n" << std::string(70, '=') << "\n";
        if (!title.empty())
            std::cout << "  " << title << "\n" << std::string(70, '=') << "\n";
    }

    void printSubSection(const std::string& title)
    {
        std::cout << "\n--- " << title << " ---\n";
    }

    template<typename T>
    void printDeque(MyStl::Deque<T>& dq, const std::string& name)
    {
        std::cout << "📦 Deque [" << name << "] - Size: " << dq.size() << "\n";
        std::cout << "   Elements: [";
        for (size_t i = 0; i < dq.size(); ++i)
        {
            std::cout << dq[i];
            if (i < dq.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    // TEST 1: Default Constructor
    void testDefaultConstructor()
    {
        printSeparator("TEST 1: Default Constructor");
        
        MyStl::Deque<int> dq;
        
        std::cout << "✓ Created empty deque\n";
        std::cout << "  Size: " << dq.size() << " (expected: 0)\n";
        std::cout << "  Empty: " << (dq.empty() ? "Yes" : "No") << "\n";
        
        assert(dq.size() == 0);
        assert(dq.empty());
        
        std::cout << "✓ Test PASSED!\n";
    }

    // TEST 2: Push Back
    void testPushBack()
    {
        printSeparator("TEST 2: Push Back");
        
        MyStl::Deque<int> dq;
        
        printSubSection("Pushing elements to back");
        for (int i = 1; i <= 5; ++i)
        {
            dq.push_back(i * 10);
            std::cout << "  [" << i << "] Pushed " << (i * 10) 
                      << " - Size: " << dq.size() << "\n";
        }
        
        printDeque(dq, "after push_back");
        
        assert(dq.size() == 5);
        assert(dq.front() == 10);
        assert(dq.back() == 50);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 3: Push Front
    void testPushFront()
    {
        printSeparator("TEST 3: Push Front");
        
        MyStl::Deque<int> dq;
        
        printSubSection("Pushing elements to front");
        for (int i = 1; i <= 5; ++i)
        {
            dq.push_front(i * 10);
            std::cout << "  [" << i << "] Pushed " << (i * 10) 
                      << " - Size: " << dq.size() << "\n";
        }
        
        printDeque(dq, "after push_front");
        
        std::cout << "\n  Expected order: [50, 40, 30, 20, 10]\n";
        
        assert(dq.size() == 5);
        assert(dq.front() == 50);
        assert(dq.back() == 10);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 4: Mixed Push Front and Back
    void testMixedPush()
    {
        printSeparator("TEST 4: Mixed Push Front & Back");
        
        MyStl::Deque<std::string> dq;
        
        printSubSection("Alternating push operations");
        dq.push_back("C");
        std::cout << "  push_back(C): "; printDeque(dq, "dq");
        
        dq.push_front("B");
        std::cout << "  push_front(B): "; printDeque(dq, "dq");
        
        dq.push_back("D");
        std::cout << "  push_back(D): "; printDeque(dq, "dq");
        
        dq.push_front("A");
        std::cout << "  push_front(A): "; printDeque(dq, "dq");
        
        dq.push_back("E");
        std::cout << "  push_back(E): "; printDeque(dq, "dq");
        
        std::cout << "\n  Expected: [A, B, C, D, E]\n";
        
        assert(dq.size() == 5);
        assert(dq[0] == "A");
        assert(dq[2] == "C");
        assert(dq[4] == "E");
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 5: Operator[] and at()
    void testElementAccess()
    {
        printSeparator("TEST 5: Element Access (operator[] and at())");
        
        MyStl::Deque<int> dq;
        for (int i = 0; i < 10; ++i)
            dq.push_back(i * 5);
        
        printDeque(dq, "test deque");
        
        printSubSection("Using operator[]");
        std::cout << "  dq[0] = " << dq[0] << " (expected: 0)\n";
        std::cout << "  dq[5] = " << dq[5] << " (expected: 25)\n";
        std::cout << "  dq[9] = " << dq[9] << " (expected: 45)\n";
        
        printSubSection("Modifying through operator[]");
        dq[5] = 999;
        std::cout << "  dq[5] = 999\n";
        std::cout << "  dq[5] = " << dq[5] << " (expected: 999)\n";
        
        printSubSection("Using at() with bounds checking");
        try {
            std::cout << "  dq.at(3) = " << dq.at(3) << "\n";
            std::cout << "  Trying dq.at(100)...\n";
            int val = dq.at(100);
            std::cout << "  ❌ Should have thrown exception!\n";
            assert(false);
        } catch (const std::out_of_range& e) {
            std::cout << "  ✓ Exception caught: " << e.what() << "\n";
        }
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 6: Front and Back
    void testFrontBack()
    {
        printSeparator("TEST 6: Front & Back Access");
        
        MyStl::Deque<int> dq;
        dq.push_back(100);
        dq.push_back(200);
        dq.push_back(300);
        
        printDeque(dq, "test deque");
        
        std::cout << "\n  front() = " << dq.front() << " (expected: 100)\n";
        std::cout << "  back() = " << dq.back() << " (expected: 300)\n";
        
        printSubSection("Modifying through front() and back()");
        dq.front() = 111;
        dq.back() = 333;
        
        printDeque(dq, "after modification");
        
        assert(dq.front() == 111);
        assert(dq.back() == 333);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 7: Pop Back
    void testPopBack()
    {
        printSeparator("TEST 7: Pop Back");
        
        MyStl::Deque<int> dq;
        for (int i = 1; i <= 5; ++i)
            dq.push_back(i * 10);
        
        printDeque(dq, "initial");
        
        printSubSection("Popping from back");
        while (!dq.empty())
        {
            std::cout << "  Popping " << dq.back() << " - ";
            dq.pop_back();
            std::cout << "Size: " << dq.size() << "\n";
        }
        
        std::cout << "\n  Final size: " << dq.size() << " (expected: 0)\n";
        assert(dq.empty());
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 8: Pop Front
    void testPopFront()
    {
        printSeparator("TEST 8: Pop Front");
        
        MyStl::Deque<int> dq;
        for (int i = 1; i <= 5; ++i)
            dq.push_back(i * 10);
        
        printDeque(dq, "initial");
        
        printSubSection("Popping from front");
        while (!dq.empty())
        {
            std::cout << "  Popping " << dq.front() << " - ";
            dq.pop_front();
            std::cout << "Size: " << dq.size() << "\n";
        }
        
        std::cout << "\n  Final size: " << dq.size() << " (expected: 0)\n";
        assert(dq.empty());
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 9: Mixed Pop Operations
    void testMixedPop()
    {
        printSeparator("TEST 9: Mixed Pop Operations");
        
        MyStl::Deque<int> dq;
        for (int i = 1; i <= 10; ++i)
            dq.push_back(i);
        
        printDeque(dq, "initial");
        
        printSubSection("Alternating pop operations");
        
        dq.pop_front();
        std::cout << "  After pop_front(): "; printDeque(dq, "dq");
        
        dq.pop_back();
        std::cout << "  After pop_back(): "; printDeque(dq, "dq");
        
        dq.pop_front();
        std::cout << "  After pop_front(): "; printDeque(dq, "dq");
        
        dq.pop_back();
        std::cout << "  After pop_back(): "; printDeque(dq, "dq");
        
        std::cout << "\n  Expected: [3, 4, 5, 6, 7, 8]\n";
        
        assert(dq.size() == 6);
        assert(dq.front() == 3);
        std::cout << "  dq.back() = " << dq.back() << "\n";
        assert(dq.back() == 8);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 10: Clear
    void testClear()
    {
        printSeparator("TEST 10: Clear");
        
        MyStl::Deque<int> dq;
        for (int i = 0; i < 20; ++i)
            dq.push_back(i);
        
        std::cout << "Size before clear: " << dq.size() << "\n";
        
        dq.clear();
        
        std::cout << "Size after clear: " << dq.size() << " (expected: 0)\n";
        std::cout << "Empty: " << (dq.empty() ? "Yes" : "No") << "\n";
        
        printSubSection("Pushing after clear");
        dq.push_back(999);
        dq.push_front(111);
        
        printDeque(dq, "after clear and push");
        
        assert(dq.size() == 2);
        assert(dq.front() == 111);
        assert(dq.back() == 999);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 11: Copy Constructor
    void testCopyConstructor()
    {
        printSeparator("TEST 11: Copy Constructor");
        
        MyStl::Deque<int> original;
        for (int i = 1; i <= 5; ++i)
            original.push_back(i * 10);
        
        printDeque(original, "original");
        
        printSubSection("Creating copy");
        MyStl::Deque<int> copy(original);
        
        printDeque(copy, "copy");
        
        printSubSection("Verifying independence");
        copy[2] = 999;
        original.push_back(60);
        
        std::cout << "  Modified copy[2] = 999 and pushed 60 to original\n";
        printDeque(original, "original");
        printDeque(copy, "copy");
        
        assert(original.size() == 6);
        assert(copy.size() == 5);
        assert(original[2] == 30);
        assert(copy[2] == 999);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 12: Copy Assignment
    void testCopyAssignment()
    {
        printSeparator("TEST 12: Copy Assignment");
        
        MyStl::Deque<int> dq1;
        for (int i = 1; i <= 5; ++i)
            dq1.push_back(i);
        
        MyStl::Deque<int> dq2;
        dq2.push_back(99);
        dq2.push_back(88);
        
        std::cout << "Before assignment:\n";
        printDeque(dq1, "dq1");
        printDeque(dq2, "dq2");
        
        printSubSection("Assignment: dq2 = dq1");
        dq2 = dq1;
        
        printDeque(dq2, "dq2 after assignment");
        
        printSubSection("Self-assignment test");
        dq1 = dq1;
        printDeque(dq1, "dq1 after self-assignment");
        
        assert(dq2.size() == 5);
        assert(dq1.size() == 5);
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 13: Stress Test - Many Push/Pop
    void testStress()
    {
        printSeparator("TEST 13: Stress Test");
        
        MyStl::Deque<int> dq;
        const int N = 1000;
        
        printSubSection("Pushing 1000 elements from back");
        for (int i = 0; i < N; ++i)
            dq.push_back(i);
        
        std::cout << "  Size: " << dq.size() << " (expected: 1000)\n";
        std::cout << "  dq[0] = " << dq[0] << " (expected: 0)\n";
        std::cout << "  dq[500] = " << dq[500] << " (expected: 500)\n";
        std::cout << "  dq[999] = " << dq[999] << " (expected: 999)\n";
        
        printSubSection("Pushing 1000 elements from front");
        for (int i = 0; i < N; ++i)
            dq.push_front(i + 10000);
        
        std::cout << "  Size: " << dq.size() << " (expected: 2000)\n";
        std::cout << "  dq[0] = " << dq[0] << " (expected: 10999)\n";
        std::cout << "  dq[999] = " << dq[999] << " (expected: 10000)\n";
        std::cout << "  dq[1999] = " << dq[1999] << " (expected: 999)\n";
        
        printSubSection("Popping all elements");
        while (!dq.empty())
            dq.pop_back();
        
        std::cout << "  Size after popping all: " << dq.size() << "\n";
        
        assert(dq.empty());
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 14: Chunk Boundary Test
    void testChunkBoundaries()
    {
        printSeparator("TEST 14: Chunk Boundary Crossing");
        
        MyStl::Deque<int> dq;
        
        // Assuming DEFAULT_CHUNK_SIZE = 16
        const int CHUNK_SIZE = 16;
        
        printSubSection("Filling across multiple chunks");
        for (int i = 0; i < CHUNK_SIZE * 3; ++i)
        {
            dq.push_back(i);
        }
        
        std::cout << "  Pushed " << (CHUNK_SIZE * 3) << " elements\n";
        std::cout << "  Size: " << dq.size() << "\n";
        
        printSubSection("Verifying elements across chunks");
        std::cout << "  dq[0] = " << dq[0] << "\n";
        std::cout << "  dq[15] = " << dq[15] << " (chunk boundary)\n";
        std::cout << "  dq[16] = " << dq[16] << " (next chunk)\n";
        std::cout << "  dq[31] = " << dq[31] << " (chunk boundary)\n";
        std::cout << "  dq[32] = " << dq[32] << " (next chunk)\n";
        
        for (size_t i = 0; i < dq.size(); ++i)
        {
            std::cout << dq[i] << " ";
            assert(dq[i] == static_cast<int>(i));
        }
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // TEST 15: Exception Safety
    void testExceptions()
    {
        printSeparator("TEST 15: Exception Safety");
        
        MyStl::Deque<int> dq;
        
        printSubSection("pop_back on empty deque");
        try {
            dq.pop_back();
            std::cout << "  ❌ Should have thrown exception!\n";
            assert(false);
        } catch (const std::out_of_range& e) {
            std::cout << "  ✓ Exception caught: " << e.what() << "\n";
        }
        
        printSubSection("pop_front on empty deque");
        try {
            dq.pop_front();
            std::cout << "  ❌ Should have thrown exception!\n";
            assert(false);
        } catch (const std::out_of_range& e) {
            std::cout << "  ✓ Exception caught: " << e.what() << "\n";
        }
        
        printSubSection("at() out of bounds");
        dq.push_back(1);
        try {
            int val = dq.at(10);
            std::cout << "  ❌ Should have thrown exception!\n";
            assert(false);
        } catch (const std::out_of_range& e) {
            std::cout << "  ✓ Exception caught: " << e.what() << "\n";
        }
        
        std::cout << "\n✓ Test PASSED!\n";
    }

    // Main test runner
    void runAllTests()
    {
        std::cout << "\n";
        std::cout << "//////////////////////////////////////////////////////////////////////\n";
        std::cout << "/          MyStl::Deque - COMPREHENSIVE TEST SUITE                   /\n";
        std::cout << "//////////////////////////////////////////////////////////////////////\n";

        int passed = 0;
        int total = 15;

        try {
            testDefaultConstructor(); ++passed;
            testPushBack(); ++passed;
            testPushFront(); ++passed;
            testMixedPush(); ++passed;
            testElementAccess(); ++passed;
            testFrontBack(); ++passed;
            testPopBack(); ++passed;
            testPopFront(); ++passed;
            testMixedPop(); ++passed;
            testClear(); ++passed;
            testCopyConstructor(); ++passed;
            testCopyAssignment(); ++passed;
            testStress(); ++passed;
            testChunkBoundaries(); ++passed;
            testExceptions(); ++passed;

            printSeparator("SUMMARY");
            std::cout << "✓ ALL TESTS PASSED! (" << passed << "/" << total << ")\n";
            std::cout << " Your Deque implementation is working correctly!\n\n";

        } catch (const std::exception& e) {
            std::cout << "\n FATAL ERROR: " << e.what() << "\n";
            std::cout << "Tests passed: " << passed << "/" << total << "\n\n";
        }
    }
}

namespace SetTest
{
   using namespace MyStl;

   // Helper function to print test results
   void print_test(const std::string& test_name, bool passed)
   {
      std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << test_name << std::endl;
   }

   // Test 1: Default constructor and empty set
   void test_default_constructor()
   {
      Set<int> s;
      bool passed = s.empty() && s.size() == 0;
      print_test("Default Constructor", passed);
   }

   // Test 2: Insert single element
   void test_insert_single()
   {
      Set<int> s;
      s.insert(10);
      bool passed = s.size() == 1 && !s.empty() && s.contains(10);
      print_test("Insert Single Element", passed);
   }

   // Test 3: Insert multiple elements
   void test_insert_multiple()
   {
      Set<int> s;
      s.insert(10);
      s.insert(5);
      s.insert(15);
      s.insert(3);
      s.insert(7);
      
      bool passed = s.size() == 5 && 
                    s.contains(10) && s.contains(5) && 
                    s.contains(15) && s.contains(3) && s.contains(7);
      print_test("Insert Multiple Elements", passed);
   }

   // Test 4: Insert duplicate (should not increase size)
   void test_insert_duplicate()
   {
      Set<int> s;
      s.insert(10);
      s.insert(10);
      s.insert(10);
      
      bool passed = s.size() == 1 && s.contains(10);
      print_test("Insert Duplicate", passed);
   }

   // Test 5: Initializer list constructor
   void test_initializer_list()
   {
      Set<int> s = {10, 5, 15, 3, 7, 12, 17};
      bool passed = s.size() == 7 && s.contains(10) && s.contains(17);
      print_test("Initializer List Constructor", passed);
   }

   // Test 6: Erase leaf node
   void test_erase_leaf()
   {
      Set<int> s = {10, 5, 15, 3, 7};
      s.erase(3);
      
      bool passed = s.size() == 4 && !s.contains(3) && s.contains(5);
      print_test("Erase Leaf Node", passed);
   }

   // Test 7: Erase node with one child (left)
   void test_erase_one_child_left()
   {
      Set<int> s = {10, 5, 3};
      s.erase(5);
      
      bool passed = s.size() == 2 && !s.contains(5) && s.contains(3) && s.contains(10);
      print_test("Erase Node with One Child (Left)", passed);
   }

   // Test 8: Erase node with one child (right)
   void test_erase_one_child_right()
   {
      Set<int> s = {10, 15, 17};
      s.erase(15);
      
      bool passed = s.size() == 2 && !s.contains(15) && s.contains(17) && s.contains(10);
      print_test("Erase Node with One Child (Right)", passed);
   }

   // Test 9: Erase node with two children
   void test_erase_two_children()
   {
      Set<int> s = {10, 5, 15, 3, 7, 12, 17};
      s.erase(10);
      
      bool passed = s.size() == 6 && !s.contains(10) && 
                    s.contains(5) && s.contains(15) && s.contains(12);
      print_test("Erase Node with Two Children", passed);
   }

   // Test 10: Erase root node
   void test_erase_root()
   {
      Set<int> s = {10};
      s.erase(10);
      
      bool passed = s.size() == 0 && s.empty() && !s.contains(10);
      print_test("Erase Root Node", passed);
   }

   // Test 11: Erase non-existent element
   void test_erase_nonexistent()
   {
      Set<int> s = {10, 5, 15};
      s.erase(100);
      
      bool passed = s.size() == 3;
      print_test("Erase Non-existent Element", passed);
   }

   // Test 12: Clear
   void test_clear()
   {
      Set<int> s = {10, 5, 15, 3, 7, 12, 17};
      s.clear();
      
      bool passed = s.size() == 0 && s.empty();
      print_test("Clear", passed);
   }

   // Test 13: Copy constructor
   void test_copy_constructor()
   {
      Set<int> s1 = {10, 5, 15};
      Set<int> s2(s1);
      
      bool passed = s2.size() == 3 && s2.contains(10) && 
                    s2.contains(5) && s2.contains(15);
      print_test("Copy Constructor", passed);
   }

   // Test 14: Copy assignment
   void test_copy_assignment()
   {
      Set<int> s1 = {10, 5, 15};
      Set<int> s2;
      s2 = s1;
      
      bool passed = s2.size() == 3 && s2.contains(10);
      print_test("Copy Assignment", passed);
   }

   // Test 15: Move constructor
   void test_move_constructor()
   {
      Set<int> s1 = {10, 5, 15};
      Set<int> s2(std::move(s1));
      
      bool passed = s2.size() == 3 && s2.contains(10) && s1.size() == 0;
      print_test("Move Constructor", passed);
   }

   // Test 16: Move assignment
   void test_move_assignment()
   {
      Set<int> s1 = {10, 5, 15};
      Set<int> s2;
      s2 = std::move(s1);
      
      bool passed = s2.size() == 3 && s2.contains(10);
      print_test("Move Assignment", passed);
   }

   // Test 17: Contains
   void test_contains()
   {
      Set<int> s = {10, 5, 15};
      bool passed = s.contains(10) && s.contains(5) && 
                    s.contains(15) && !s.contains(100);
      print_test("Contains", passed);
   }

   // Test 18: Count
   void test_count()
   {
      Set<int> s = {10, 5, 15};
      bool passed = s.count(10) == 1 && s.count(100) == 0;
      print_test("Count", passed);
   }

   // Test 19: Lower bound
   void test_lower_bound()
   {
      Set<int> s = {10, 20, 30, 40, 50};
      bool passed = true;
      
      try {
         passed = passed && (s.lower_bound(25) == 30);
         passed = passed && (s.lower_bound(30) == 30);
         passed = passed && (s.lower_bound(10) == 10);
      } catch (...) {
         passed = false;
      }
      
      print_test("Lower Bound", passed);
   }

   // Test 20: Upper bound
   void test_upper_bound()
   {
      Set<int> s = {10, 20, 30, 40, 50};
      bool passed = true;
      
      try {
         passed = passed && (s.upper_bound(25) == 30);
         passed = passed && (s.upper_bound(30) == 40);
         passed = passed && (s.upper_bound(10) == 20);
      } catch (...) {
         passed = false;
      }
      
      print_test("Upper Bound", passed);
   }

   // Test 21: Complex erase sequence
   void test_complex_erase()
   {
      Set<int> s = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65};
      s.erase(30);
      s.erase(70);
      s.erase(50);
      
      bool passed = s.size() == 8 && !s.contains(30) && 
                    !s.contains(70) && !s.contains(50) &&
                    s.contains(35) && s.contains(60);
      print_test("Complex Erase Sequence", passed);
   }

   // Test 22: Insert after clear
   void test_insert_after_clear()
   {
      Set<int> s = {10, 5, 15};
      s.clear();
      s.insert(20);
      s.insert(10);
      
      bool passed = s.size() == 2 && s.contains(20) && s.contains(10);
      print_test("Insert After Clear", passed);
   }

   // Run all tests
   void run_all_tests()
   {
      std::cout << "\n========== Running Set Tests ==========\n" << std::endl;
      
      test_default_constructor();
      test_insert_single();
      test_insert_multiple();
      test_insert_duplicate();
      test_initializer_list();
      test_erase_leaf();
      test_erase_one_child_left();
      test_erase_one_child_right();
      test_erase_two_children();
      test_erase_root();
      test_erase_nonexistent();
      test_clear();
      test_copy_constructor();
      test_copy_assignment();
      test_move_constructor();
      test_move_assignment();
      test_contains();
      test_count();
      test_lower_bound();
      test_upper_bound();
      test_complex_erase();
      test_insert_after_clear();
      
      std::cout << "\n========== Tests Complete ==========\n" << std::endl;
   }
}


int main()
{
    //ListTest::full_test();
    //MapTest::runAllTests();
    //DequeTest::runAllTests();
    SetTest::run_all_tests();
    
    return 0;
}
