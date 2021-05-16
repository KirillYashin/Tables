#pragma once
#include <string>
#include "TreeNode.h"
#include <stack>
#include <cstddef>


template<class T>
class TreeTable
{
protected:
    TreeNode<T>* _root;

    void put_helper(TreeNode<T>**, const T&, std::string);
    void del_helper(TreeNode<T>**, std::string);
    void find_helper(TreeNode<T>**, std::string);
    void destruction(TreeNode<T>*);
    void print_helper(TreeNode<T>*, int) const;

public:
    TreeTable();
    ~TreeTable();

    void Put(const T&, std::string);
    void Del(std::string);
    void Find(std::string);
    void Print() const;

    T finder;
};

template<class T>
TreeTable<T>::TreeTable() :
    _root(nullptr)
{
}

template<class T>
TreeTable<T>::~TreeTable()
{
    destruction(_root);
}

template<class T>
void TreeTable<T>::destruction(TreeNode< T >* node)
{
    if (node != nullptr)
    {
        destruction(node->_left);
        destruction(node->_right);

        delete node;
    }
}

template<class T>
void TreeTable<T>::Put(const T& data, std::string key)
{
    put_helper(&_root, data, key);
}

template<class T>
void TreeTable<T>::put_helper(TreeNode< T >** node, const T& data, std::string key)
{
    if (*node == nullptr)
        *node = new TreeNode<T>(data, key);
    else
    {
        if ((*node)->_key > key)
            put_helper(&((*node)->_left), data, key);
        else
        {
            if ((*node)->_key < key)
                put_helper(&((*node)->_right), data, key);
        }
    }
}

template<class T>
void TreeTable<T>::Del(std::string key)
{
    del_helper(&_root, key);
}

template<class T>
void TreeTable<T>::del_helper(TreeNode< T >** node, std::string key)
{
    if ((*node)->_key == key)
    {
        TreeNode<T>* del_node = *node;

        if ((*node)->_left == nullptr && (*node)->_right == nullptr)
        {
            *node = nullptr;

            delete del_node;
        }
        else
        {
            if ((*node)->_left == nullptr)
            {
                *node = (*node)->_right;

                delete del_node;
            }
            else
            {
                if ((*node)->_right == nullptr)
                {
                    *node = (*node)->_left;

                    delete del_node;
                }
                else
                {
                    TreeNode<T>* p = *node;
                    TreeNode<T>* i = (*node)->_left;

                    while (i->_right != 0)
                    {
                        p = i;
                        i = i->_right;
                    }

                    *node = i;
                    p->_right = i->_left;
                    i->_right = del_node->_right;
                    i->_left = p;

                    delete del_node;
                }
            }
        }
    }
    else
    {
        if ((*node)->_key > key)
            del_helper(&((*node)->_left), key);
        else
        {
            if ((*node)->_key < key)
                del_helper(&((*node)->_right), key);
        }
    }
}

template<class T>
void TreeTable<T>::Print() const
{
    print_helper(_root, 0);
}

template<class T>
void TreeTable<T>::print_helper(TreeNode<T>* node, int spaces) const
{
    while (node != 0)
    {
        print_helper(node->_right, spaces + 5);

        for (int i = 1; i < spaces; ++i)
            std::cout << ' ';

        std::cout << node->_key << "-";
        for (int j = 0; j < node->_data.size(); j++) {
            std::cout << node->_data[j] << " ";
        }
        std::cout << std::endl;

        node = node->_left;
        spaces += 5;
    }
}

template<class T>
void TreeTable<T>::Find(std::string key)
{
    find_helper(&_root, key);
    std::cout << finder << std::endl;
}

template<class T>
void TreeTable<T>::find_helper(TreeNode<T>** node, std::string key)
{
    if (*node == nullptr) {
        finder = -1;
    }
        
    else {
        if ((*node)->_key == key)
        {
            finder = (*node)->_data;
        }
        else {
            if ((*node)->_key > key) {
                find_helper(&((*node)->_left), key);
            }
                
            else
            {
                find_helper(&((*node)->_right), key);
            }    
        }
    }
}