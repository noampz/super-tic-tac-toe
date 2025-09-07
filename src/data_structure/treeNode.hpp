#pragma once
#include <vector>

template<typename T>
class TreeNode
{
    public:
    T value;
    int eval;
    std::vector<TreeNode<T>*> children;

    TreeNode(const T& val) : value(val) {}
    ~TreeNode()
    {
        for (TreeNode<T>* child : children)
            delete child;
    }
};