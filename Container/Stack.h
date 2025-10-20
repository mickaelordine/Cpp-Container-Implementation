#pragma once
#include "Deque.h"
#include <stdexcept>

namespace MyStl
{
    template <typename T>
    class Stack
    {
        // MEMBERS VARIABLES //
    public:
        
        
    protected:
        
    
    private:
        MyStl::Deque<T> _container;
        
        // MEMBERS VARIABLES //

        // MEMBERS FUNCTIONS //
    public:
        // CONSTRUCTORS
        Stack() : _container()
        {
            
        } // default constructor
        Stack(const Stack& other) : _container(other._container)
        {
        } // copy constructor
        Stack(Stack&& other) noexcept :  _container(std::move(other._container))
        {
        } // Move constructor
        Stack& operator=(const Stack& other)
        {
            if (this != &other)
            {
                _container = other._container;
            }
            
            return *this;
        } // copy assignment
        Stack& operator=(Stack&& other) noexcept
        {
            if (this != &other)
            {
                _container = std::move(other._container);    
            }
            
            return *this;
        } // move assignment
        ~Stack() = default; // destructor set at default because Deque already handle memory management

        // ELEMENT ACCESS
        T& top()
        {
            if (empty())
                throw std::out_of_range("Stack has no elements");
            return _container.back();
        }
        const T& top() const
        {
            if (empty())
                throw std::out_of_range("Stack has no elements");
            return _container.back();
        }

        // CAPACITY
        bool empty() const
        {
            return _container.size() == 0;
        }        
        size_t size() const
        {
            return _container.size();
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
            if (empty())
                throw std::out_of_range("Stack has no elements");
            _container.pop_back();
        }        
        void swap(Stack& other) noexcept
        {
            std::swap(_container, other._container);
        }    
        
    protected:
        
        
    private:
        
        
        // MEMBERS FUNCTIONS //
    };
}

