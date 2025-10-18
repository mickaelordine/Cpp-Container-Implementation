#pragma once
#include <iostream>
#include <map>

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

    void insert(value_type& pair)
    {
        root = insert_helper(root, pair);
    }
    
private:
    struct Node
    {
        value_type data;
        Node* left;
        Node* right;
        Node(const value_type& pair) : data(pair), left(nullptr), right(nullptr){};
    };

    Node* insert_helper(Node* node, value_type& pair)
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
        // find the key recursivly
    }
    
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
    

    
    T operator [](K key)
    {
        T elem;
        Node* node = find_helper(root, key);
        if (node)
        {
            elem = node->data;
        }
        return elem;
    } 

protected:


private:
    
};

}
