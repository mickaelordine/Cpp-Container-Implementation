#pragma once

/*
 *  Deque template class
 *  brief graphic explanation of what is a Deque
 *  map -> [chunk_ptr0][chunk_ptr1][chunk_ptr2][chunk_ptr3][chunk_ptr4][chunk_ptr5][chunk_ptr6][chunk_ptr7]
 *  chunk_ptr* -> [element0, element1, element2, element3, element4, element5, element6, element7]
 *  the chunk size is fixed and defined by the user at the creation of the Deque
 *  the map size is dinamyc and grow as needed
 *  the map is a contiguis array of pointer to chunks
 */

#define DEFAULT_DEQUE_SIZE 8
#define DEFAULT_CHUNK_SIZE 20


template<typename T>
class Deque<T>
{
    // MEMBERS VARIABLE //
public:

protected:

private:

    // MEMBERS VARIABLE //

    // MEMBERS FUNCTIONS //
public:

protected:

private:

    // MEMBERS FUNCTIONS //
};
