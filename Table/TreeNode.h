template<class T> class TreeTable;

template<class T>
class TreeNode
{
    friend class TreeTable<T>;

public:
    TreeNode();
    TreeNode(const T&, std::string);

private:
    std::string _key;
    T _data;
    TreeNode<T>* _left;
    TreeNode<T>* _right;
};

template<class T>
TreeNode<T>::TreeNode() :
    _left(nullptr),
    _right(nullptr)
{
}

template<class T>
TreeNode< T >::TreeNode(const T& data, std::string key) :
    _key(key),
    _data(data),
    _left(nullptr),
    _right(nullptr)
{
}