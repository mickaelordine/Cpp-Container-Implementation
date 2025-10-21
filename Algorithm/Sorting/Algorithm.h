#pragma once
#include <functional>
#include <iterator>
#include <vector>

namespace MyStl {
    
    // UTILITY FUNCTIONS

    template <typename T>
    void swap(T& a, T& b) noexcept
    {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }
        
    // SORTING ALGORITHMS

    // Bubble Sort //
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void bubble_sort(Iterator first, Iterator last, Compare comp = Compare{})
    {
        if (first == last) return;

        auto n = std::distance(first, last);
        
        for (int i = 0; i < n - 1; ++i)
        {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; ++j)
            {
                
                Iterator it1 = std::next(first, j);
                Iterator it2 = std::next(first, j + 1);
                if (comp(*it2, *it1))
                {
                    swap(*it1, *it2);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }
    
    // Quick Sort //
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    Iterator partition(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        // scegliere un pivot casuale tra first e last
        Iterator rand_pivot_it = first + (std::rand() % (last - first));
        auto pivot_value = *rand_pivot_it;

        // spostare il pivot alla fine
        swap(*(last - 1), *(rand_pivot_it));
        
        Iterator i = first;

        // partizionare l'intervallo
        for (Iterator j = first; j != last - 1; ++j)
        {
            // se l'elemento corrente è minore del pivot
            if (comp(*j, pivot_value))
            {
                // scambiare l'elemento corrente con l'elemento alla posizione i
                swap(*i, *j);
                ++i;
            }
        }
        // posizionare il pivot nella sua posizione corretta
        swap(*(i), *(last - 1));
        return i;
    }
    
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void quick_sort(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        // caso base, se l'intervallo è vuoto o ha un solo elemento 
        if (first >= last || std::distance(first, last) <= 1)
            return;

        Iterator pivot = partition(first, last, comp);

        // ricorsivamente ordinare le due partizioni
        quick_sort(first, pivot, comp);
        // ricorsivamente ordinare la partizione destra
        quick_sort(pivot + 1, last, comp);
    }

    // insertion sort // 
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void insertion_sort(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        // insertion sort
        // per ogni elemento nell'intervallo
        for (Iterator i = first + 1; i != last; ++i)
        {
            // salvare il valore corrente
            auto key = *i;
            Iterator j = i;
            // spostare gli elementi maggiori di key a destra
            while (j > first && comp(key, *(j-1)))
            {
                // spostare l'elemento a destra
                *j = *(j-1);
                --j;
                if (j < first) break;
            }
            // inserire key nella posizione corretta
            *j = key;
        }
    }

    // selection sort // 
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void selection_sort(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        for (Iterator i = first; i != last - 1; ++i)
        {
            Iterator min_it = i;
            for (Iterator j = i + 1; j != last; ++j)
            {
                if (comp(*j, *min_it))
                {
                    min_it = j;
                }
            }
            if (min_it != i)
            {
                swap(*i, *min_it);
            }
        }
    }

    // merge sort //
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void merge(const Iterator& first, const Iterator& mid, const Iterator& last, Compare comp = Compare{})
    {

        using value_type = typename std::iterator_traits<Iterator>::value_type;
    
        // Copia in 2 vector temporanei left e right
        std::vector<value_type> temp_left(first, mid);
        std::vector<value_type> temp_right(mid, last);
    
        // Usa INDICI per scorrere il vector temporaneo
        size_t left_idx = 0;
        size_t left_end = std::distance(first, mid);
        size_t right_idx = 0;
        size_t right_end = std::distance(mid, last);
    
        // l'iterator ORIGINALE per scrivere nel contenitore
        Iterator dest = first;
    
        // Merge con indici per temp, iterator per destinazione
        while (left_idx < left_end && right_idx < right_end) {
            if (comp(temp_left[left_idx], temp_right[right_idx])) {
                *dest = std::move(temp_left[left_idx]);
                ++left_idx;
            } else {
                *dest = std::move(temp_right[right_idx]);
                ++right_idx;
            }
            ++dest;
        }
    
        // Copia elementi rimanenti
        while (left_idx < left_end) {
            *dest = std::move(temp_left[left_idx]);
            ++left_idx;
            ++dest;
        }
    
        while (right_idx < right_end) {
            *dest = std::move(temp_right[right_idx]);
            ++right_idx;
            ++dest;
        }
    }

    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void merge_sort(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        if (std::distance(first, last) <= 1)
            return;
        
        Iterator mid  = first + std::distance(first, last) / 2;

        // ricorsivamente ordinare la prima metà
        merge_sort(first, mid, comp);
        // ricorsivamente ordinare la seconda metà
        merge_sort(mid, last,  comp);

        // unire le due metà ordinandole
        merge(first, mid, last, comp);
    }

    // heap sort //
    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void heap_sort(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        
    }

    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void heap(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        
    }

    template <typename Iterator, typename Compare = std::less<typename std::iterator_traits<Iterator>::value_type>>
    void intro_sort(const Iterator& first, const Iterator& last, Compare comp = Compare{})
    {
        
    }

    
}
