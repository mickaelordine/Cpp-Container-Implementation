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
            iterator(){}
            ~iterator(){}
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
        Deque(Deque&& other) noexcept
            : map(other.map)
            , map_size(other.map_size)
            , first_chunk(other.first_chunk)
            , last_chunk(other.last_chunk)
            , first_offset(other.first_offset)
            , last_offset(other.last_offset)
            , _size(other._size)
        {
            // Reset other to empty state
            other.map = nullptr;
            other.map_size = 0;
            other.first_chunk = 0;
            other.last_chunk = 0;
            other.first_offset = 0;
            other.last_offset = 0;
            other._size = 0;
        } // Move constructor
        Deque& operator=(Deque&& other) noexcept
        {
            if (this != &other)
            {
                // Clean up current resources
                clear();
                deallocate_map();
        
                // Steal resources from other
                map = other.map;
                map_size = other.map_size;
                first_chunk = other.first_chunk;
                last_chunk = other.last_chunk;
                first_offset = other.first_offset;
                last_offset = other.last_offset;
                _size = other._size;
        
                // Reset other to empty state
                other.map = nullptr;
                other.map_size = 0;
                other.first_chunk = 0;
                other.last_chunk = 0;
                other.first_offset = 0;
                other.last_offset = 0;
                other._size = 0;
            }
            return *this;
        } // Move assignment operator
        ~Deque()
        {
            clear();
            deallocate_map();
        } // destructor

        // access functions //
        T& operator[](size_t index) const
        {
            size_t chunk_index = first_chunk + (first_offset + index) / DEFAULT_CHUNK_SIZE;
            size_t offset_index = (first_offset + index) % DEFAULT_CHUNK_SIZE;
            if (chunk_index > last_chunk || (chunk_index == last_chunk && offset_index > last_offset))
                throw std::out_of_range("Deque::[] - index out of range");
            return map[chunk_index][offset_index];
        }
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
        const T& at(size_t index) const
        {
            size_t chunk_index = first_chunk + (first_offset + index) / DEFAULT_CHUNK_SIZE;
            size_t offset_index = (first_offset + index) % DEFAULT_CHUNK_SIZE;
            if (chunk_index > last_chunk || (chunk_index == last_chunk && offset_index > last_offset))
                throw std::out_of_range("Deque::at - index out of range");
            return map[chunk_index][offset_index];
        }
        
        T& front() { return (*this)[0]; }
        const T& front() const { return (*this)[0]; }
        
        T& back() { return (*this)[_size - 1]; }
        const T& back() const { return (*this)[_size - 1]; }
        
        // modifiers //
        void push_front(const T& value)
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
        void push_back(const T& value)
        {
            // Check if current chunk is full at back
            if (last_offset == DEFAULT_CHUNK_SIZE)
            {
                // Need new chunk
                if (last_chunk == map_size - 1)
                    reallocate_map();
                
                ++last_chunk;
                
                if (map[last_chunk] == nullptr)
                    map[last_chunk] = new T[DEFAULT_CHUNK_SIZE];
                
                last_offset = 0;
            }
            
            map[last_chunk][last_offset] = value;
            ++last_offset;
            ++_size;
        }

        // the insert function always move the element to the right, but if you ask to insert in front o back, we do it in O(1) with push_front and push_back
        void insert(size_t index, const T& value)
        {
            if (index > _size)
                throw std::out_of_range("Deque::insert - index out of range");

            if (index == 0) {
                push_front(value);
                return;
            }
            if (index == _size) {
                push_back(value);
                return;
            }

            // shift right side
            push_back(back()); // we copy the last element to create space
            for (size_t i = _size - 2; i > index; --i) // we start from _size - 2 because we just added one element at the back
                (*this)[i + 1] = (*this)[i];
            (*this)[index] = value;
        }
        
        void pop_front()
        {
            if (_size == 0)
                throw std::out_of_range("Deque::pop_front - deque is empty");
    
            ++first_offset;
            --_size;
            
            if (first_offset == DEFAULT_CHUNK_SIZE)
            {
                // if we are at the end of the chunk, move to next chunk
                if (first_chunk < last_chunk)
                {
                    //delete[] map[first_chunk];
                    map[first_chunk] = nullptr;
            
                    ++first_chunk;
                    first_offset = 0;
                }
                // else, we are at the last chunk, do nothing
            }
        }
        void pop_back()
        {
            if (_size == 0)
                throw std::out_of_range("Deque::pop_back - deque is empty");
    
            --last_offset;
            --_size;
            
            if (last_offset == static_cast<size_t>(-1))
            {
                // if we are at the begin of the chunk, move to the previous chunk
                if (last_chunk > first_chunk)
                {
                    //delete[] map[first_chunk];
                    map[last_chunk] = nullptr;
            
                    --last_chunk;
                    last_offset = DEFAULT_CHUNK_SIZE;
                }
                // else, we are at the first chunk, do nothing
            }
        }

        // the function erase will always shit elements to the left, if you call it at the end or start insteas O(1) thanks to pops
        void erase(size_t index)
        {
            if (index > _size)
                throw std::out_of_range("Deque::erase - index out of range");

            if (index == 0) {
                pop_front();
                return;
            }
            if (index == _size) {
                pop_back();
                return;
            }
            // shift to left side
            for (size_t i = index; i < _size - 1; ++i)
                (*this)[i] = (*this)[i + 1];
            pop_back();
        }
        void erase(size_t start, size_t end)
        {
            if (start > end || end > _size)
                throw std::out_of_range("Deque::erase(range) - invalid range");

            size_t count = end - start;
            if (count == 0)
                return;

            if (start == 0)
            {
                for (size_t i = 0; i < count; ++i) pop_front();
                return;
            }
            if (end == _size)
            {
                for (size_t i = 0; i < count; ++i) pop_back();
                return;
            }
            // shift to left side
            for (size_t i = start; i < _size - count; ++i)
                (*this)[i] = (*this)[i + count];
            for (size_t i = 0; i < count; ++i)
                pop_back();
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
            size_t new_size = map_size * 2;
            T** new_map = new T*[new_size];
    
            for (size_t i = 0; i < new_size; ++i)
                new_map[i] = nullptr;
            
            size_t offset = new_size / 4;
            for (size_t i = first_chunk; i <= last_chunk; ++i)
            {
                new_map[offset + (i - first_chunk)] = map[i];
            }
    
            size_t num_used = last_chunk - first_chunk + 1;
            first_chunk = offset;
            last_chunk = offset + num_used - 1;
    
            delete[] map;
            map = new_map;
            map_size = new_size;
        }
        
        
        // MEMBERS FUNCTIONS //
    };
}

