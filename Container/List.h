#include <iostream>
#include <ostream>

/*  
 *  implementation of a double linked list to implement a stl list.
 *  I use a sentinel node as pivot where all others node come with a circular dependency from that and other nodes.
 */

namespace MyStl
{
    template<typename T>
    class List;
    
    template<typename T>
    struct Node
    {
        T data;
        Node<T>* next;
        Node<T>* prev;

        Node() : data(), next(this), prev(this) {} // default constructor for sentinel node
        ~Node() = default;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {} // copy constructor
        Node(T&& value) noexcept : data(std::move(value)), next(nullptr), prev(nullptr) {} // Move constructor
        
    };

    
    
    template<typename T>
    class List
    {
        // MEMBERS VARIABLES //
    public:
        // class ListIterator
        // {
        //     ListIterator operator ++()
        //     {
        //     
        //     }
        //     ListIterator operator --()
        //     {
        //     
        //     }
        //     ListIterator operator ++(int)
        //     {
        //     
        //     }
        //     ListIterator operator --(int)
        //     {
        //     
        //     }
        //     List& operator *()
        //     {
        //     
        //     }
        // };
        
    protected:
        
    private:
        Node<T>* m_head;
        size_t m_size;
        // MEMBERS VARIABLES //

        // MEMBERS FUNCTIONS //
    public:
        // ===== CONSTRUCTORS =====
        List() : m_head(new Node<T>()), m_size(0){ std::cout << "List constructor called " << std::endl;} // default constructor
        List(const List& other) : m_head(new Node<T>()), m_size(0)
        {
            Node<T>* current = other.m_head->next;
            while (current != other.m_head)
            {
                push_back(current->data);
                current = current->next;
            }
        } // copy constructor
        List(List&& other) noexcept : m_head(other.m_head), m_size(other.size())
        {
            other.m_head = new Node<T>();
            other.m_size = 0;
        } // move construtor
        List& operator=(const List& other)
        {
            if (this != &other)
            {
                clear();
                Node<T>* current = other.m_head->next;
                while (current != other.m_head)
                {
                    push_back(current->data);
                    current = current->next;
                }
            }
            return *this;
        } // copy assignment
        List& operator=(List&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                delete m_head;
                
                m_head = other.m_head;
                m_size = other.m_size;
                
                other.m_head = new Node<T>();
                other.m_size = 0;
            }
            return *this;
        } // move assignment
        ~List()
        {
            clear();
            delete m_head;
            std::cout << "List destructor called" << std::endl;
        }

        // ===== CAPACITY =====
        inline size_t size() const { return m_size; }
        inline bool empty() const { return m_size == 0; }

        // ===== ITERATORS =====
        //ListIterator<T> begin() { return ListIterator<T> (); }
        //ListIterator<T> end() { return ListIterator<T> (); }

        // ===== ELEMENT ACCESS =====
        
        T& front()
        {
            if (empty())
                throw std::out_of_range("List::front - empty list");
            return m_head->next->data;
        }
        const T& front() const
        {
            if (empty())
                throw std::out_of_range("List::front - empty list");
            return m_head->next->data;
        }
        
        T& back()
        {
            if (empty())
                throw std::out_of_range("List::back - empty list");
            return m_head->prev->data;
        }
        const T& back() const
        {
            if (empty())
                throw std::out_of_range("List::back - empty list");
            return m_head->prev->data;
        }

        // ===== ELEMENT MODIFIERS =====
        
        void push_back(const T& value)
        {
            Node<T>* newNode = new Node<T>(value);
            // we take the last node
            Node<T>* lastNode = m_head->prev; 
            
            newNode->next = m_head;
            newNode->prev = lastNode;
            lastNode->next = newNode;
            m_head->prev = newNode;

            ++m_size;
            return;
        }
        void push_back(const T&& value)
        {
            // normal case
            Node<T>* newNode = new Node<T>(value);
            // we take the last node
            Node<T>* lastNode = m_head->prev; 
            
            newNode->next = m_head;
            newNode->prev = lastNode;
            lastNode->next = newNode;
            m_head->prev = newNode;

            ++m_size;
            return;
        }
        void push_front(const T& value)
        {
            Node<T>* newNode = new Node<T>(value);
            // we take the last node
            Node<T>* firstNode = m_head->next; 
                
            newNode->prev = m_head;
            newNode->next = firstNode;
            firstNode->prev = newNode;
            m_head->next = newNode;
    
            ++m_size;
            return;
        }
        void push_front(const T&& value)
        {
            Node<T>* newNode = new Node<T>(value);
            // we take the last node
            Node<T>* firstNode = m_head->next; 
                
            newNode->prev = m_head;
            newNode->next = firstNode;
            firstNode->prev = newNode;
            m_head->next = newNode;
    
            ++m_size;
            return;
        }
        
        void pop_front()
        {
            if (empty()) 
                throw std::out_of_range("Cannot pop_front from empty list");
    
            Node<T>* firstNode = m_head->next;
    
            // Collega m_head direttamente al secondo nodo
            m_head->next = firstNode->next;
            firstNode->next->prev = m_head;
    
            delete firstNode;
            --m_size;
        }
        void pop_back()
        {
            if (empty()) 
                throw std::out_of_range("Cannot pop_back from empty list");
    
            Node<T>* firstNode = m_head->prev;
    
            // Collega m_head direttamente al penultimo nodo
            m_head->prev = firstNode->prev;
            firstNode->prev->next = m_head;
    
            delete firstNode;
            --m_size;
        }
        
        // ListIterator<T> insert(ListIterator<T> it, const T& value)
        // {
        //
        //
        //     return ListIterator<T> ();
        // }
        // ListIterator<T> erase(ListIterator<T> it)
        // {
        //
        //
        //     return ListIterator<T> ();
        // }
        // ListIterator<T> erase(ListIterator<T> itBegin, ListIterator<T> itEnd)
        // {
        //
        //
        //     return ListIterator<T> ();
        // }
        
        void remove(const T& value)
        {
            
        }
        void reverse()
        {
            
        }
        void sort()
        {
            
        }
        void merge(List& other)
        {
            if (this != &other)
            {
                
            }
        }
        void clear()
        {
            while (!empty())
            {
                pop_front();
            }
        }

        // ===== UTILS =====
        void print() const
        {
            std::cout << "List [" << m_size << " elements]: ";
            Node<T>* current = m_head->next;
            std::cout << " [ Head ] -> ";
            while (current != m_head)
            {
                std::cout << current->data;
                if (current->next != m_head) 
                    std::cout << " <-> ";
                current = current->next;
            }
            std::cout << " <- [ Head ] " << std::endl;
        }
        void print_reverse() const
        {
            std::cout << "List (reverse) [" << m_size << " elements]: ";
            Node<T>* current = m_head->prev;
            std::cout << " [ Head ] -> ";
            while (current != m_head)
            {
                std::cout << current->data;
                if (current->prev != m_head) 
                    std::cout << " <-> ";
                current = current->prev;
            }
            std::cout << " <- [ Head ] ";
            std::cout << std::endl;
        }
        
    protected:
        
        
    private:
        // ===== GETTER =====
        inline Node<T>* head(){ return m_head; }
        // MEMBERS FUNCTIONS //
    };
    
}


