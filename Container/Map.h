#pragma once
#include <iostream>
#include <map>
#include <stack>

namespace MyStl
{
    
    template<typename K, typename T>
    class Map
    {
        // MEMBERS VARIABLES //
    public:
        typedef std::pair<const K, T> value_type;
                
        
    private:
        struct Node
        {
            value_type data;
            Node* left;
            Node* right;
            Node(const value_type& pair) : data(pair), left(nullptr), right(nullptr){};
        };

    public:
        class iterator
        {
        public:
            typedef value_type* pointer;
            typedef value_type& reference;

        private:
            Node* current;
            std::stack<Node*> stack;
    
            friend class Map;
            
        public:
            iterator() : current(nullptr) {}
            iterator(Node* root, bool end = false)
            {
                if (end || root == nullptr)
                {
                    current = nullptr;
                    return;
                }
        
                // Inizializza: vai al nodo più a sinistra (minimo)
                current = root;
                while (current != nullptr)
                {
                    stack.push(current);
                    current = current->left;
                }
        
                // current è nullptr, lo stack contiene il percorso
                // Pop per ottenere il primo elemento
                if (!stack.empty())
                {
                    current = stack.top();
                    stack.pop();
                }
            }
            ~iterator()
            {
                delete current;
            }

            // functions //
            bool operator==(const iterator& other) const
            {
                return current == other.current;
            }
    
            bool operator!=(const iterator& other) const
            {
                return current != other.current;
            }
            
            reference operator*()
            {
                return current->data;
            }
    
            pointer operator->()
            {
                return &(current->data);
            }
            
            iterator& operator++()  // Pre-incremento: ++it
            {
                if (current == nullptr)
                    return *this;
                
                if (current->right != nullptr)
                {
                    current = current->right;
                    while (current->left != nullptr)
                    {
                        stack.push(current);
                        current = current->left;
                    }
                }
                
                else if (!stack.empty())
                {
                    current = stack.top();
                    stack.pop();
                }
                
                else
                {
                    current = nullptr;
                }
        
                return *this;
            }
            
            iterator operator++(int)  // Post-incremento: it++
                {
                iterator temp = *this;
                ++(*this);
                return temp;
                }
            
        }; // implemented like a Forward Iterator

    public:
        Node* root;
        int _size;
        
    protected:
        // MEMBERS VARIABLES //

        // MEMBERS FUNCTIONS //
    public:
        // CONSTRUCTORS & DESTRUCTOR //
        Map() : root(nullptr), _size(0){} // default constructor
        Map(value_type val)
        {
            insert(val);
        } // value constructor
        Map(const Map& other) : root(nullptr), _size(0)
        {
            if (other.root == nullptr)
                return;
            
            copy_helper(other.root);
        }    // Copy constructor
        Map& operator=(const Map& other)
        {
            if (this != &other)
            {
                clear();
            
                if (other.root != nullptr)
                    copy_helper(other.root);
            }
            return *this;
        }   // Copy assignment
        Map(Map&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                root = other.root;
                _size = other._size;
                
                other.root = nullptr;
                other._size = 0;
            }
        }   // Move constructor
        Map& operator=(Map&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                root = other.root;
                _size = other._size;
                
                other.root = nullptr;
                other._size = 0;
            }
            return *this;
        }    // Move assignment
        ~Map()
        {
            clear();
            //delete root; // la clear fa già la delete sulla root, noi qui stavamo facendo una deallocazione su memoria già deallocata
            root = nullptr;
        } //destructor

        // UTILS //
        value_type find(const K key)
        {
            Node* elem = find_helper(root, key);
            if (!elem)
            {
                std::cout << key << " not found" << std::endl;
                return std::pair<const K, T>(K(), T());
            }
            return elem->data;
        }
        T& at(const K& key)
        {
            Node* elem = find_helper(root, key);
            if (!elem)
            {
                std::_Throw_range_error("Not find the key in the map");
            }
            return elem->data.second;
        }
        const T& at(const K& key) const
        {
            Node* elem = find_helper(root, key);
            if (!elem)
            {
                std::_Throw_range_error("Not find the key [" << key << "] in the map" << std::endl);
            }
            return elem->data.second;
        }
        void clear()
        {
            clear_helper_recursive(root);
            _size = 0;
            root = nullptr;
        }
        int size() const { return _size; }
        bool empty() const { if (root == nullptr) return true; else return false;}

        // MODIFIERS //
        void erase(const K& key)
        {
            root = erase_helper(root, key);
        }
        iterator erase(iterator pos);
        T& operator[](const K& key)
    {
            Node* found = find_helper(root, key);
            if (!found)
            {
                value_type pair(key, T());
                insert(pair);
                found = find_helper(root, key);
            }
            return found->data.second;
    }
        void insert(const value_type& pair)
        {
            root = insert_helper(root, pair);
        }

        // ITERATORS //
        iterator begin()
        {
            return iterator(root, false);  // Inizia dal minimo
        }
        iterator end()
        {
            return iterator(root, true);   // End iterator (nullptr)
        }


    private:
        Node* insert_helper(Node* node, const value_type& pair)
        {
            if (node == nullptr)
            {
                ++_size;
                return new Node(pair);
            }
                
            if (pair.first < node->data.first)
                node->left = insert_helper(node->left, pair);
            else if (pair.first > node->data.first)
                node->right = insert_helper(node->right, pair);
            else
            {
                // override the value if the key are the same
                node->data.second = pair.second;
            }
            
            
            return node;
        }
        Node* find_helper(Node* node, const K key)
        {
            if (node == nullptr)
                return nullptr;
        
            if (key < node->data.first)
                return find_helper(node->left, key);
            else if (key > node->data.first)
                return find_helper(node->right, key);
            else
                return node;
        }
        void clear_helper_recursive(Node* node)
        {
            if (node == nullptr)
                return;
            
            clear_helper_recursive(node->left);
            clear_helper_recursive(node->right);
            delete node;
        }
        void clear_helper_with_stack()
        {
            if (root == nullptr)
                return;
            
            std::stack<Node*> stack;
            stack.push(root);
            while (!stack.empty())
            {
                Node* _node = stack.top(); // we take the element in top
                stack.pop(); // we remove it from the stack

                // Post-order traversal
                if (_node->left != nullptr)
                    stack.push(_node->left);
                if (_node->right != nullptr)
                    stack.push(_node->right);
                delete _node;
            }
        }
        void copy_helper(Node* other_node)
        {
            if (other_node == nullptr)
                return;
            
            copy_helper(other_node->left);
            insert(other_node->data);
            copy_helper(other_node->right);
        }
        Node* erase_helper(Node* node, const K& key)
        {
            // base case, no node found with the given key
            if (node == nullptr)
            {
                std::cout << "Key " << key << " not found for erase\n";
                return nullptr;
            }
            
            if (key < node->data.first)
            {
                node->left = erase_helper(node->left, key); // con questo noi stiamo dicendo di sostituire il sx figlio con il risultato della cancellazione
                return node;
            }
            else if (key > node->data.first)
            {
                node->right = erase_helper(node->right, key); // con questo noi stiamo dicendo di sostituire il dx figlio con il risultato della cancellazione
                return node;
            }
            
            // Found! now we have to check the 3 cases
            
            // Case 1, leaf node
            if (node->left == nullptr && node->right == nullptr)
            {
                std::cout << "Erasing leaf node: " << key << "\n";
                delete node;
                --_size;
                return nullptr;
            }
            
            // Case 2a: only right child
            if (node->left == nullptr)
            {
                std::cout << "Erasing node with right child: " << key << "\n";
                Node* temp = node->right;
                delete node;
                --_size;
                return temp;
            }
            
            // Case 2a: only left child
            if (node->right == nullptr)
            {
                std::cout << "Erasing node with left child: " << key << "\n";
                Node* temp = node->left;
                delete node;
                --_size;
                return temp;
            }
            
            // Caso 3: Due figli
            std::cout << "Erasing node with two children: " << key << "\n";
            
            // Trova il successore (minimo del sottoalbero destro)
            Node* successor = find_min(node->right);
            std::cout << "  Successor found: " << successor->data.first << "\n";
            
            // Copia i dati del successore nel nodo corrente
            const_cast<K&>(node->data.first) = successor->data.first;
            node->data.second = successor->data.second;
            
            // Cancella il successore (ricorsivamente)
            node->right = erase_helper(node->right, successor->data.first);
            
            return node;
        }

        Node* find_min(Node* node) const
        {
            if (node == nullptr)
                return nullptr;
                
            while (node->left != nullptr)
                node = node->left;
                
            return node;
        }
        Node* find_max(Node* node) const
        {
            if (node == nullptr)
                return nullptr;
                
            while (node->right != nullptr)
                node = node->right;
                
            return node;
        }

        // MEMBERS FUNCTIONS //
    };

}
