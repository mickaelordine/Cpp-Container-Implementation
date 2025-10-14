#include <iostream>
#include <ostream>

namespace MyStl
{
    template<typename T>
    struct Node
    {
        T data;
        Node<T>* next;
        Node<T>* prev;

        Node() : data(), next(nullptr), prev(nullptr) {} // default constructor
        ~Node() = default;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {} // copy constructor
        Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {} // Move constructor
        
    };
    
    template<typename T>
    class List
    {
        // MEMBERS VARIABLES //
    public:
        
    protected:
        
    private:
        Node<T>* m_head;
        Node<T>* m_tail;
        size_t m_size;
        // MEMBERS VARIABLES //

        // MEMBERS FUNCTIONS //
    public:
        // ===== CONSTRUCTORS =====
        List() : m_head(nullptr), m_tail(nullptr), m_size(0){ std::cout << "List constructor called " << std::endl;} // default constructor
        List(const List& other) : m_head(nullptr), m_tail(nullptr), m_size(0)
        {
            Node<T>* temp = other.m_head;
            while (temp != nullptr)
            {
                // we copy all the element inside the new list
                push_back(temp->data);
                temp = temp->next;
            }
        } // copy constructor
        List(const List&& other) noexcept : m_head(other.m_head), m_tail(other.m_tail), m_size(other.Size())
        {
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        } // move construtor
        List& operator=(const List& other)
        {
            if (this != &other)
            {
                clear();
                Node<T>* temp = other.m_head;
                while (temp != nullptr)
                {
                    // we copy all the element inside the new list
                    push_back(temp->data);
                    temp = temp->next;
                }
            }
            return *this;
        } // copy assignment
        List& operator=(List&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                m_head = other.m_head;
                m_tail = other.m_tail;
                m_size = other.m_size;
                other.m_head = nullptr;
                other.m_tail = nullptr;
                other.m_size = 0;
            }
            return *this;
        } // move assignment
        ~List()
        {
            clear();
            std::cout << "List destructor called" << std::endl;
        }

        // ===== GETTER =====
        inline Node<T>* Head(){ return m_head; }
        inline Node<T>* Tail() { return m_tail; }

        // ===== CAPACITY =====
        inline size_t Size() const { return m_size; }
        inline bool Empty() const { return m_size == 0; }

        // ===== ELEMENT ACCESS =====
        T& front()
        {
            
        }
        const T& front() const
        {
            
        }
        T& back()
        {
            
        }
        const T& back() const
        {
            
        }

        // ===== ELEMENT MODIFIERS =====
        void push_back(const T& value)
        {
            
        }
        void push_front(const T& value)
        {
            
        }
        void push_back(const T&& value)
        {
            
        }
        void push_front(const T&& value)
        {
            
        }
        void pop_front()
        {
            
        }
        void pop_back()
        {
            
        }
        void clear()
        {
            while (m_head != nullptr)
            {
                Node<T>* head_cpy = m_head;
                m_head = m_head->next;
                delete head_cpy;
            }
        }

        // ===== UTILS =====
        void print_in_order() const
        {
            
        }
        void print_reverse() const
        {
            
        }
    protected:
        
    private:
        
        // MEMBERS FUNCTIONS //
    };
    
}


