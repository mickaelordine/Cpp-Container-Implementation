#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>

/*
 *  Deque template class
 *  brief graphic explanation of what is a Deque
 *  map -> [chunk_ptr0][chunk_ptr1][chunk_ptr2][chunk_ptr3][chunk_ptr4][chunk_ptr5][chunk_ptr6][chunk_ptr7]
 *  chunk_ptr* -> [element0, element1, element2, element3, element4, element5, element6, element7]
 *  the chunk size is fixed and defined by the user at the creation of the Deque
 *  the map size is dinamyc and grow as needed
 *  the map is a contiguis array of pointer to chunks
 */

#define DEFAULT_MAP_SIZE    8
#define DEFAULT_CHUNK_SIZE 20


template<typename T>
class Deque<T>
    {
        // MEMBERS VARIABLE //
    public:
    

    protected:

    private:
        T** map;              // map of pointers to chunks
        size_t map_size;      // size of map
        size_t first_block;   // first block index of map
        size_t last_block;    // last block index of map
        size_t first_elem;    // index of the first elem
        size_t last_elem;     // index of the last elem
        size_t count;         // count of elements in the Deque
        
        // MEMBERS VARIABLE //

        // MEMBERS FUNCTIONS //
    public:
    Deque() : map(nullptr), map_size(0), first_block(0), last_block(0), first_elem(0), last_elem(0), count(0)
    {
        // create a Deque with default map size and chunk size
        map_size = DEFAULT_MAP_SIZE;
        map = new T * [map_size];
        for (size_t i = 0; i < map_size; i++)
        {
            map[i] = nullptr;
        }
        first_block = map_size / 2;
        last_block = first_block;
        map[first_block] = new T[DEFAULT_CHUNK_SIZE];
        first_elem = DEFAULT_CHUNK_SIZE / 2; // starting from the middle of the chunk
        last_elem = first_elem;
    }                     // default constructor
    Deque(const Deque &other) 
    {
        map_size = other.map_size;
        map = new T * [map_size];
        for (size_t i = 0; i < map_size; i++)
        {
            if (other.map[i] != nullptr)
            {
                map[i] = new T[DEFAULT_CHUNK_SIZE];
                for (size_t j = 0; j < DEFAULT_CHUNK_SIZE; j++)
                {
                    map[i][j] = other.map[i][j];
                }
            }
            else
            {
                map[i] = nullptr;
            }
        }
        first_block = other.first_block;
        last_block = other.last_block;
        first_elem = other.first_elem;
        last_elem = other.last_elem;
        count = other.count;
    }   // copy constructor
    ~Deque()
    {
        // Dealloca solo i blocchi effettivamente allocati
        for (size_t i = first_block; i <= last_block && map != nullptr; i++)
        {
            if (map[i] != nullptr)
            {
                delete[] map[i];
            }
                
        }
    
        // Poi dealloca la map
        delete[] map;
    } 
    
    
    protected:

    private:

        // MEMBERS FUNCTIONS //
    };



