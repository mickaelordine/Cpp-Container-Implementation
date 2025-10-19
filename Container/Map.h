#pragma once
#include <iostream>
#include <map>
#include <stack>

namespace MyStl
{
    

template<typename K>
class Key
{
    
};




template<typename K, typename T>
class Map
{
public:
    typedef std::pair<const K, T> value_type;
    class iterator
    {
    public:

    protected:
        
    private:
    };

    
    
private:
    struct Node
    {
        value_type data;
        Node* left;
        Node* right;
        Node(const value_type& pair) : data(pair), left(nullptr), right(nullptr){};
    };

    
    
public:
    Node* root;
    int _size;
    
protected:

public:
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

    // Utils //
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

    // modifiers //
    void erase(const K& key);
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
    
};

}
