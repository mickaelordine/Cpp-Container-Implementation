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

namespace MyStl
{
    template<typename T>
    class Deque
    {
        // MEMBERS VARIABLE //
    public:
        class iterator
        {
            iterator();
            ~iterator();
        };
    

    private:
        T** map;
        size_t map_size;
        size_t first_chunk;
        size_t last_chunk;
        size_t first_offset;
        size_t last_offset;
        size_t _size;
        
        // MEMBERS VARIABLE //

        // MEMBERS FUNCTIONS //
    public:
        Deque() 
            : map(nullptr)
            , map_size(DEFAULT_MAP_SIZE)
            , first_chunk(0)
            , last_chunk(0)
            , first_offset(0)
            , last_offset(0)
            , _size(0)
        {
            allocate_map(map_size);
            
            // Start from center
            first_chunk = map_size / 2;
            last_chunk = first_chunk;
            
            // Allocate first chunk
            map[first_chunk] = new T[DEFAULT_CHUNK_SIZE];
            
            // Start from middle of chunk
            first_offset = DEFAULT_CHUNK_SIZE / 2;
            last_offset = first_offset;
        }   // default constructor
        Deque(const Deque& other)
            : map(nullptr)
            , map_size(other.map_size)
            , first_chunk(other.first_chunk)
            , last_chunk(other.last_chunk)
            , first_offset(other.first_offset)
            , last_offset(other.last_offset)
            , _size(other._size)
        {
            allocate_map(map_size);
            
            // Copy only used chunks
            for (size_t i = first_chunk; i <= last_chunk; ++i)
            {
                if (other.map[i] != nullptr)
                {
                    map[i] = new T[DEFAULT_CHUNK_SIZE];
                    
                    // Copy elements
                    for (size_t j = 0; j < DEFAULT_CHUNK_SIZE; ++j)
                    {
                        map[i][j] = other.map[i][j];
                    }
                }
            }
        }   // copy constructor
        Deque& operator=(const Deque& other)
        {
            if (this != &other)
            {
                // Clear current content
                clear();
                deallocate_map();
                
                // Copy from other
                map_size = other.map_size;
                first_chunk = other.first_chunk;
                last_chunk = other.last_chunk;
                first_offset = other.first_offset;
                last_offset = other.last_offset;
                _size = other._size;
                
                allocate_map(map_size);
                
                for (size_t i = first_chunk; i <= last_chunk; ++i)
                {
                    if (other.map[i] != nullptr)
                    {
                        map[i] = new T[DEFAULT_CHUNK_SIZE];
                        for (size_t j = 0; j < DEFAULT_CHUNK_SIZE; ++j)
                        {
                            map[i][j] = other.map[i][j];
                        }
                    }
                }
            }
            return *this;
        } // copy assignment
        ~Deque()
        {
            clear();
            deallocate_map();
        } // destructor

        // access functions //
        T& operator[](size_t index)
        {
            size_t chunk_index = first_chunk + (first_offset + index) / DEFAULT_CHUNK_SIZE;
            size_t offset_index = (first_offset + index) % DEFAULT_CHUNK_SIZE;
            if (chunk_index > last_chunk || (chunk_index == last_chunk && offset_index > last_offset))
                throw std::out_of_range("Deque::[] - index out of range");
            return map[chunk_index][offset_index];
        }
        T& at(size_t index)
        {
            size_t chunk_index = first_chunk + (first_offset + index) / DEFAULT_CHUNK_SIZE;
            size_t offset_index = (first_offset + index) % DEFAULT_CHUNK_SIZE;
            if (chunk_index > last_chunk || (chunk_index == last_chunk && offset_index > last_offset))
                throw std::out_of_range("Deque::at - index out of range");
            return map[chunk_index][offset_index];
        }
        
        T& front() { return map[first_chunk][first_offset]; }
        const T& front() const { return map[first_chunk][first_offset]; }
        
        T& back() { return map[last_chunk][last_offset]; }
        const T& back() const { return map[last_chunk][last_offset]; }
        
        // modifiers //
        void push_front(T value)
        {
            // Check if current chunk is full at front
            if (first_offset == 0)
            {
                // Need new chunk
                if (first_chunk == 0)
                    reallocate_map();
                
                --first_chunk;
                
                if (map[first_chunk] == nullptr)
                    map[first_chunk] = new T[DEFAULT_CHUNK_SIZE];
                
                first_offset = DEFAULT_CHUNK_SIZE;
            }
            
            --first_offset;
            map[first_chunk][first_offset] = value;
            ++_size;
        }
        void push_back(T value)
        {
            // Check if current chunk is full at back
            if (last_offset == DEFAULT_CHUNK_SIZE - 1)
            {
                // Need new chunk
                if (last_chunk == map_size - 1)
                    reallocate_map();
                
                ++last_chunk;
                
                if (map[last_chunk] == nullptr)
                    map[last_chunk] = new T[DEFAULT_CHUNK_SIZE];
                
                last_offset = 0;
            }
            
            ++last_offset;
            map[last_chunk][last_offset] = value;
            ++_size;
        }
        
        void insert(size_t index, T value)
        {
            
        }
        
        void pop_front()
        {
            
        }
        void pop_back()
        {
            
        }
        
        void erase(size_t index)
        {
            
        }
        void erase(size_t start, size_t end)
        {
            
        }
        
        // Capacity //
        size_t size() const { return _size; }
        bool empty() const { return _size == 0; }

        // debug functions //
         void print() const
        {
            std::cout << "\n=== Deque Structure ===\n";
            std::cout << "Map size: " << map_size << "\n";
            std::cout << "Size: " << _size << "\n";
            std::cout << "First chunk: " << first_chunk << ", offset: " << first_offset << "\n";
            std::cout << "Last chunk: " << last_chunk << ", offset: " << last_offset << "\n";
            std::cout << "\nChunks:\n";
            
            for (size_t i = 0; i < map_size; ++i)
            {
                if (map[i] != nullptr)
                {
                    std::cout << "  [" << i << "]: allocated";
                    if (i == first_chunk) std::cout << " (first)";
                    if (i == last_chunk) std::cout << " (last)";
                    std::cout << "\n";
                }
            }
        }

    private:
        // helper functions for memory management //
        void allocate_map(size_t size)
        {
            map = new T*[size];
            for (size_t i = 0; i < size; ++i)
                map[i] = nullptr;
        }
        void deallocate_map()
        {
            if (map == nullptr)
                return;
            
            for (size_t i = 0; i < map_size; ++i)
            {
                if (map[i] != nullptr)
                    delete[] map[i];
            }
            delete[] map;
            map = nullptr;
        }
        void reallocate_map()
        {
            
        }
        void clear()
        {
            if (map == nullptr)
                return;
            
            // Deallocate only used chunks
            for (size_t i = first_chunk; i <= last_chunk; ++i)
            {
                if (map[i] != nullptr)
                {
                    delete[] map[i];
                    map[i] = nullptr;
                }
            }
            
            // Reset to initial state
            first_chunk = map_size / 2;
            last_chunk = first_chunk;
            
            if (map[first_chunk] == nullptr)
                map[first_chunk] = new T[DEFAULT_CHUNK_SIZE];
            
            first_offset = DEFAULT_CHUNK_SIZE / 2;
            last_offset = first_offset;
            _size = 0;
        }
        
        // MEMBERS FUNCTIONS //
    };
}

