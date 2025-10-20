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
         // Create new node
         Node* new_node = new Node(key);
         
         // If tree is empty, set new node as root
         if (_root == nullptr)
            _root = new_node;

         // Otherwise, find the correct position to insert the new node
         else
         {
            Node* current = _root;
            Node* parent = nullptr;

            while (current != nullptr)
            {
               parent = current;
               if (key < current->val)
                  current = current->left;
               else if (key > current->val)
                  current = current->right;
               else
               {
                  // Key already exists, do not insert duplicates
                  delete new_node; // Clean up allocated memory
                  return;
               }
            }

            // Insert the new node as a child of the parent node
            new_node->parent = parent;
            if (key < parent->val)
               parent->left = new_node;
            else
               parent->right = new_node;
         }
         ++_size;
      }
      void erase(const T& key)
      {
         // Find the node to be deleted
         Node* node_to_delete = find_helper(_root, key);
         
         // if the node is not found, return
         if (node_to_delete == nullptr)
            return;
         
         --_size;
         
         // Case 1: Node has no children (leaf node)
         if (node_to_delete->left == nullptr && node_to_delete->right == nullptr)
         {
            if (node_to_delete->parent == nullptr)
            {
               // Node is root
               _root = nullptr;
            }
            else if (node_to_delete == node_to_delete->parent->left)
            {
               node_to_delete->parent->left = nullptr;
            }
            else
            {
               node_to_delete->parent->right = nullptr;
            }
            delete node_to_delete;
            return;
         }
         
         // Case 2: Node has one child
         // Case 2a : Node has only left child
         if (node_to_delete ->left != nullptr && node_to_delete->right == nullptr)
         {
            if (node_to_delete->parent == nullptr)
            {
               // Node is root
               _root = node_to_delete->left;
               _root->parent = nullptr;
            }
            else if (node_to_delete == node_to_delete->parent->left)
            {
               // if node to delete is left child
               // then link parent left to node left of the deleted node
               node_to_delete->parent->left = node_to_delete->left;
               node_to_delete->left->parent = node_to_delete->parent;
            }else
            {
               // if node to delete is right child
               // then link parent right to node left of the deleted node
               node_to_delete->parent->right = node_to_delete->left;
               node_to_delete->left->parent = node_to_delete->parent;
            }
            delete node_to_delete;
            return;
         }
         
         // Case 2b : Node has only right child
         if (node_to_delete ->right != nullptr && node_to_delete->left == nullptr)
         {
            if (node_to_delete->parent == nullptr)
            {
               // Node is root
               _root = node_to_delete->right;
               _root->parent = nullptr;
            }
            else if (node_to_delete == node_to_delete->parent->right)
            {
               // if node to delete is left child
               // then link parent left to node left of the deleted node
               node_to_delete->parent->right = node_to_delete->right;
               node_to_delete->right->parent = node_to_delete->parent;
            }else
            {
               // if node to delete is right child
               // then link parent right to node left of the deleted node
               node_to_delete->parent->left = node_to_delete->right;
               node_to_delete->right->parent = node_to_delete->parent;
            }
            delete node_to_delete;
            return;
         }
         
         // Case 3: Node has two children
         if (node_to_delete->left != nullptr && node_to_delete->right != nullptr)
         {
            // Find the inorder successor (smallest in the right subtree)
            Node* successor = node_to_delete->right;
            while (successor->left != nullptr)
            {
               successor = successor->left;
            }
            
            // Copy the successor's value to the node to be deleted
            node_to_delete->val = successor->val;
   
            // Now we need to remove the successor from the tree
            // The successor has at most a right child (no left child by definition)
   
            if (successor->parent->left == successor)
            {
               // Successor is a left child
               successor->parent->left = successor->right;
            }
            else
            {
               // Successor is a right child
               successor->parent->right = successor->right;
            }
   
            // Update the parent of successor's right child (if it exists)
            if (successor->right != nullptr)
            {
               successor->right->parent = successor->parent;
            }
            
            delete successor;
         }
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
            if (key >= node->val)
            {
               // Move right to find a bigger candidate that still satisfies the condition of greater than key 
               node = node->right;
            }
            else
            {
               // Potential candidate
               candidate = node;
               node = node->left;
            }
         }
         if (!candidate)
            throw std::out_of_range("lower_bound: not found");
         return candidate->val;
      }
      // std::pair<const T&, const T&> equal_range(const T& key)
      // {
      //    
      // }
      bool contains(const T& key) const {
         return find_helper(_root, key) != nullptr;
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
      const Node* find_helper(const Node* node, const T& key) const
      {
         if (node == nullptr || node->val == key)
            return node;

         if (node->val > key)
            return find_helper(node->left, key);
         return find_helper(node->right, key);
      }
      Node* copy_helper(Node* other_node, Node* parent)
      {
         if (!other_node) return nullptr;

         Node* new_node = new Node(other_node->val);
         new_node->parent = parent;
         new_node->left  = copy_helper(other_node->left, new_node);
         new_node->right = copy_helper(other_node->right, new_node);
         return new_node;
      }
      // MEMBERS FUNCTIONS //
   };
}

