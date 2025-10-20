#pragma once
#include "Deque.h"

namespace MyStl
{
    template <typename T>
    class Queue
    {
        // MEMBERS VARIABLES //
    public:
    
    protected:
    
    private:
        MyStl::Deque<T> _container;
    
        // MEMBERS VARIABLES //

        // MEMBERS FUNCTIONS //
    public:
        Queue() : _container()
        {
            
        } // default constructor
        Queue(const Queue& other) : _container(other._container)
        {
        } // copy constructor
        Queue(Queue&& other) noexcept :  _container(std::move(other._container))
        {
        } // Move constructor
        Queue& operator=(const Queue& other)
        {
            if (this != &other)
            {
                _container = other._container;
            }
            
            return *this;
        } // copy assignment
        Queue& operator=(Queue&& other) noexcept
        {
            if (this != &other)
            {
                _container = std::move(other._container);    
            }
            
            return *this;
        } // move assignment
        ~Queue() = default; // destructor set at default because Deque already handle memory management

        // CAPACITY
        bool empty() const noexcept
        {
            return _container.empty();
        }
        size_t size() const noexcept
        {
            return _container.size();
        }

        // ELEMENT ACCESS
        T& front()
        {
            if (_container.empty())
                throw std::out_of_range("queue is empty");
            return _container.front();
        }
        const T& front() const
        {
            if (_container.empty())
                throw std::out_of_range("queue is empty");
            return _container.front();
        }
        T& back()
        {
            if (_container.empty())
                throw std::out_of_range("queue is empty");
            return _container.back();
        }
        const T& back() const
        {
            if (_container.empty())
                throw std::out_of_range("queue is empty");
            return _container.back();
        }

        // MODIFIERS
        void push(const T& value)
        {
            _container.push_back(value);
        }
        void push(T&& value)
        {
            _container.push_back(std::move(value));
        }
        void pop()
        {
            _container.pop_front();   
        }
        void swap(Queue& other) noexcept
        {
            std::swap(_container, other._container);
        }
        
    protected:
    
    
    private:
    
    
        // MEMBERS FUNCTIONS //
    
    };
}


