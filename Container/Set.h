#pragma once
#include <initializer_list>
#include <stdexcept>
#include <utility>

/*
 *  Description:
 *  Sets are containers that store unique elements following a specific order.
 *  In a set, the value of an element also identifies it (the value is itself the key, of type T), and each value 
    must be unique. The value of the elements in a set cannot be modified once in the container (the 
    elements are always const), but they can be inserted or removed from the container.

    Implementation:
    Bianry Search Tree (BST)

    
 */
namespace MyStl
{
   template <typename T>
   class Set
   {
      // MEMBERS VARIABLES //
   public:
      struct Node
      {
         T val;
         Node* left;
         Node* right;
         Node* parent;

         Node() : val(T()), left(nullptr), right(nullptr), parent(nullptr) {}
         Node(const T& value) : val(value), left(nullptr), right(nullptr), parent(nullptr) {}
      };
   protected:

   private:
      Node* _root;
      size_t _size;
      // MEMBERS VARIABLES //

      // MEMBERS FUNCTIONS //
   public:
      Set() : _root(nullptr), _size(0) {}
      Set(const std::initializer_list<T>& keys)
      : _root(nullptr), _size(0)
      {
         for (const auto& k : keys)
            insert(k);
      }
      Set(const Set& other)
      {
         _root = copy_helper(other._root, nullptr);
         _size = other._size;
      }
      Set(Set&& other) noexcept : _root(other._root), _size(other._size)
      {
         other._root = nullptr;
         other._size = 0;
      }
      Set& operator=(const Set& other)
      {
         if (this != &other)
         {
            clear();
            _root = copy_helper(other._root, nullptr);
            _size = other._size;
         }
         return *this;
      }
      Set& operator=(Set&& other) noexcept
      {
         if (this != &other)
         {
            clear();
            _root = other._root;
            _size = other._size;
            
            delete other._root;
            other._root = nullptr;
            other._size = 0;
         }
         return *this;
      }
      ~Set(){ clear(); }

      // CAPACITY //
      size_t size() const{return _size;}
      bool empty() const{ return _size == 0; }

      // MODIFIERS //
      void insert(const T& key)
      {
         
      }
      void erase(const T& key)
      {
         
      }
      
      // ELEMENT ACCESS //
      T& find(const T& key)
      {
         // Use helper to find the node
         Node* result_node = find_helper(_root, key);
         if (result_node)
         {
            return result_node->val;
         }
         return nullptr; // Key not found
      }
      T& lower_bound(const T& key)
      {
         // lower bound: first element not less than key
         Node* node = _root;
         Node* candidate = nullptr;
         while (node)
         {
            if (node->val >= key)
            {
               // Potential candidate
               candidate = node;
               // Move left to find a smaller candidate that still satisfies the condition of not less than key
               node = node->left;
            }
            else
            {
               // Move right to find a candidate
               node = node->right;
            }
         }
         if (!candidate)
            throw std::out_of_range("lower_bound: not found");
         return candidate->val;
      }
      T& upper_bound(const T& key)
      {
         // upper bound: first element greater than key
         Node* node = _root;
         Node* candidate = nullptr;
         while (node)
         {
            if (node->val >= key)
            {
               // Potential candidate
               candidate = node;
               node = node->right;
            }
            else
            {
               // Move left to find a smaller candidate that still satisfies the condition of greater than key 
               node = node->left;
            }
         }
         if (!candidate)
            throw std::out_of_range("lower_bound: not found");
         return candidate->val;
      }
      std::pair<const T&, const T&> equal_range(const T& key)
      {
         
      }
      bool contains(const T& key) const {
         return find(key) != nullptr;
      }
      size_t count(const T& key) const {
         return contains(key) ? 1 : 0;
      }

      // OTHER FUNCTIONS //
      void clear()
      {
         clear_helper(_root);
         _root = nullptr;
         _size = 0;
      }
      
   protected:

   private:
      void clear_helper(Node* node)
      {
         if (node == nullptr)
            return;
         clear_helper(node->left);
         clear_helper(node->right);
         delete node;
      }
      Node* find_helper(Node* node, const T& key)
      {
         // Base case: node is null or key is present at node
         if (node == nullptr || node->val == key)
            return node;

         // Key is greater than node's key
         if (node->val > key)
            return find_helper(node->left, key);
         // Key is smaller than node's key
         return find_helper(node->right, key);
      }
      Node* copy_helper(Node* other_node, Node* parent)
      {
         if (!other_node) return nullptr;

         Node* new_node = new Node(other_node->key);
         new_node->parent = parent;
         new_node->left  = copy_helper(other_node->left, new_node);
         new_node->right = copy_helper(other_node->right, new_node);
         return new_node;
      }
      // MEMBERS FUNCTIONS //
   };
}

