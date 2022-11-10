enum _color
{
    _Black,
    _Red
};

struct _Rbt_node_base
{
    using _Node_color = _color;
    using _Node_ptr = _Rbt_node_base *;
    using _CNode_ptr = const _Rbt_node_base *;

    _Node_color _M_color;
    _Node_ptr _M_parent;
    _Node_ptr _M_left;
    _Node_ptr _M_right;
    int _M_val;

    _Rbt_node_base()
        : _M_left(this), _M_right(this),
          _M_color(_Red){};

    _Rbt_node_base(int v)
        : _M_val(v), _M_color(_Red) {}

    void
    _M_setcolor(_color __c)
    {
        if (this)
            this->_M_color = __c;
    }

    static _Node_color
    _S_color(_Rbt_node_base *__p)
    {
        return __p != 0 ? __p->_M_color : _Black;
    }

    static void
    _S_swap(_Rbt_node_base *__l,
            _Rbt_node_base *__r) noexcept
    {
        int __tmp = __l->_M_val;
        __l->_M_val = __r->_M_val;
        __r->_M_val = __tmp;
    }
};

void _rbt_recolor(_Rbt_node_base *__n, _Rbt_node_base *__h) noexcept;

_Rbt_node_base *_rbt_get_insert_pos(int val, _Rbt_node_base *__r);

void _rbt_insert(bool __is_l, _Rbt_node_base *__new, _Rbt_node_base *__ist, _Rbt_node_base *__header) noexcept;

void _rbt_erase_unique(bool __is_l, _Rbt_node_base *__del, _Rbt_node_base *__header) noexcept;

void _rbt_insert(int val, _Rbt_node_base *__h)
{
    _Rbt_node_base *__pos = _rbt_get_insert_pos(val, __h->_M_parent);
    if (nullptr == __pos)
        _rbt_insert(true, new _Rbt_node_base(val), __h, __h);
    else
    {
        bool __is_l = val < __pos->_M_val;
        _rbt_insert(__is_l, new _Rbt_node_base(val), __pos, __h);
    }
    ++__h->_M_val;
}

_Rbt_node_base *_rbt_get_insert_pos(int val, _Rbt_node_base *__r)
{
    _Rbt_node_base *__pos{0};
    while (__r)
    {
        __pos = __r;
        if (val < __r->_M_val)
            __r = __r->_M_left;
        else
            __r = __r->_M_right;
    }
    return __pos;
}

void _rbt_insert(bool __is_l, _Rbt_node_base *__new,
                 _Rbt_node_base *__ist,
                 _Rbt_node_base *__header) noexcept
{
    if (__is_l)
    {
        if (__header->_M_parent)
        {
            if (__ist == __header->_M_left)
                __header->_M_left = __new;
            __ist->_M_left = __new;
        }
        else
        {
            __ist->_M_parent = __new;
            __ist->_M_right = __ist->_M_left = __new;
        }
    }
    else
    {
        if (__ist == __header->_M_right)
            __header->_M_right = __new;
        __ist->_M_right = __new;
    }
    __new->_M_parent = __ist;
    _rbt_recolor(__new, __header);
}

void _rbt_rotate_left(_Rbt_node_base *__n,
                      _Rbt_node_base *__h) noexcept
{
    typedef _Rbt_node_base *_Node_ptr;
    _Node_ptr __parent = __n->_M_parent,
              __new = __n->_M_right;

    __new->_M_right->_M_setcolor(__new->_M_color);
    __new->_M_setcolor(__n->_M_color);

    __n->_M_parent = __new;
    __new->_M_parent = __parent;

    if (__new->_M_left)
        __new->_M_left->_M_parent = __n;

    if (__parent == __h)
        __h->_M_parent = __new;
    else if (__n == __parent->_M_left)
        __parent->_M_left = __new;
    else
        __parent->_M_right = __new;

    __n->_M_right = __new->_M_left;
    __new->_M_left = __n;
}

void _rbt_rotate_right(_Rbt_node_base *__n,
                       _Rbt_node_base *__h) noexcept
{
    typedef _Rbt_node_base *_Node_ptr;
    _Node_ptr __parent = __n->_M_parent,
              __new = __n->_M_left;

    __new->_M_left->_M_setcolor(__new->_M_color);
    __new->_M_setcolor(__n->_M_color);

    __n->_M_parent = __new;
    __new->_M_parent = __parent;

    if (__new->_M_right)
        __new->_M_right->_M_parent = __n;

    if (__parent == __h)
        __h->_M_parent = __new;
    else if (__n == __parent->_M_left)
        __parent->_M_left = __new;
    else
        __parent->_M_right = __new;

    __n->_M_left = __new->_M_right;
    __new->_M_right = __n;
}

/// @bug 先不处理根节点
inline _Rbt_node_base *
_rbt_bro_ptr(_Rbt_node_base *__p) noexcept
{
    _Rbt_node_base *__parent = __p->_M_parent;
    if (__p == __parent->_M_left)
        return __parent->_M_right;
    else
        return __parent->_M_left;
}

void _rbt_reblance_insert(_Rbt_node_base *__n,
                          _Rbt_node_base *__h) noexcept
{
    typedef _Rbt_node_base *_Node_ptr;
    _Node_ptr __parent = __n->_M_parent;
    _Node_ptr __gparnet = __parent->_M_parent;
    if (__parent == __gparnet->_M_right)
    {
        if (__n != __parent->_M_right) // rl
            _rbt_rotate_right(__parent, __h);
        _rbt_rotate_left(__gparnet, __h);
    }
    else
    {
        if (__n == __parent->_M_right) // lr
            _rbt_rotate_left(__parent, __h);
        _rbt_rotate_right(__gparnet, __h);
    }
    __gparnet->_M_setcolor(_Red);
}

void _rbt_recolor(_Rbt_node_base *__n,
                  _Rbt_node_base *__h) noexcept
{
    typedef _Rbt_node_base _Node;
    typedef _Rbt_node_base *_Node_ptr;

    if (__n == __h->_M_parent)
    {
        __n->_M_setcolor(_Black);
        return;
    }

    __n->_M_setcolor(_Red);
    _Node_ptr __p = __n->_M_parent;
    if (_Black == _Node::_S_color(__p))
        return;

    _Node_ptr __uncle = _rbt_bro_ptr(__p);
    if (_Red == _Node::_S_color(__uncle))
    {
        __uncle->_M_setcolor(_Black);
        __p->_M_setcolor(_Black);
        _rbt_recolor(__p->_M_parent, __h);
    }
    else
        _rbt_reblance_insert(__n, __h);
}

_Rbt_node_base *
_rbt_increment(_Rbt_node_base *__p) noexcept
{
    _Rbt_node_base::_Node_ptr __tmp;
    if (__p->_M_right)
    {
        __tmp = __p->_M_right;
        while (__tmp->_M_left)
            __tmp = __tmp->_M_left;
    }
    else
    {
        __tmp = __p->_M_parent;
        while (__p == __tmp->_M_right)
        {
            __p = __tmp;
            __tmp = __tmp->_M_parent;
        }
    }
    return __tmp;
}

/// @brief find presuccor of __p
/// @param __p
_Rbt_node_base *
_rbt_decrement(_Rbt_node_base *__p) noexcept
{
    _Rbt_node_base::_Node_ptr __tmp;
    if (__p->_M_left)
    {
        __tmp = __p->_M_left;
        while (__tmp->_M_right)
            __tmp = __tmp->_M_right;
    }
    else
    {
        __tmp = __p->_M_parent;
        while (__p == __tmp->_M_left)
        {
            __p = __tmp;
            __tmp = __tmp->_M_parent;
        }
    }
    return __tmp;
}

/// @brief rebalance operating, it`s not going to delete any nodes
/// @param __del the node to be deleted
/// @param __bro of the __del
/// @param __header the header node of rbt
void _rbt_rebalance_erase(_Rbt_node_base *__del,
                          _Rbt_node_base *__header) noexcept
{
    /// @if color(__del) = red
    ///     don`t need rebalance operating
    if (__del == __header->_M_parent || _Red == _Rbt_node_base::_S_color(__del))
        return;

    _Rbt_node_base *__bro = _rbt_bro_ptr(__del);
    _Rbt_node_base *__parent = __del->_M_parent;
    bool __is_rchild = __parent->_M_right == __del ? true : false;
    bool __r_is_red = (__bro && _Red == _Rbt_node_base::_S_color(__bro->_M_right));
    bool __l_is_red = (__bro && _Red == _Rbt_node_base::_S_color(__bro->_M_left));

    if (_Black == _Rbt_node_base::_S_color(__bro))
    {
        if (!__r_is_red && !__l_is_red)
        {
            // using recursion, from low to height, tell tree (height - 1)
            // let tree take it
            __bro->_M_setcolor(_Red);
            if (_Red != __parent->_M_color)
                _rbt_rebalance_erase(__parent, __header);
            else
                __parent->_M_setcolor(_Black);
        }
        else if (__is_rchild)
        {
            if (__r_is_red && !__l_is_red) // lr
            {
                _rbt_rotate_left(__bro, __header);
                __bro->_M_setcolor(_Red);
                __bro = __bro->_M_parent;
            }
            if (__bro && _Red == _Rbt_node_base::_S_color(__bro->_M_left)) // ll
            {
                _rbt_rotate_right(__parent, __header);
                __parent->_M_setcolor(_Black);
            }
        }
        else
        {
            if (__l_is_red && !__r_is_red) // rl
            {
                _rbt_rotate_right(__bro, __header);
                __bro->_M_setcolor(_Red);
                __bro = __bro->_M_parent;
            }
            if (__bro && _Red == _Rbt_node_base::_S_color(__bro->_M_right)) // rr
            {
                _rbt_rotate_left(__parent, __header);
                __parent->_M_setcolor(_Black);
            }
        }
    }
    else // color(__bro) = red, so childs of a sibling is all black
    {
        if (__is_rchild)
        {
            _rbt_rotate_right(__parent, __header);
            __bro->_M_left->_M_setcolor(_Black);
        }
        else
        {
            _rbt_rotate_left(__parent, __header);
            __bro->_M_right->_M_setcolor(_Black);
        }
        __parent->_M_setcolor(_Red);
        _rbt_rebalance_erase(__del, __header);
    }
}

void _rbt_erase_unique(bool __is_l,
                       _Rbt_node_base *__del,
                       _Rbt_node_base *__header) noexcept
{
    /**
     * @brief
     *      @if non-left node, find presurcor of it,
     *      @else delete it and balance tree
     */
    _Rbt_node_base *__tmp = __del;

    if (__del->_M_left)
        __del = _rbt_decrement(__del);
    if (__del->_M_right) // had red leaves right node
        __del = __del->_M_right;

    if (__del == __header->_M_left)
        __header->_M_left = _rbt_increment(__del);
    if (__del == __header->_M_right)
        __header->_M_right = _rbt_decrement(__del);

    _Rbt_node_base::_S_swap(__tmp, __del);

    _rbt_rebalance_erase(__del, __header);

    /* recycle operating  */
    if (__del == __del->_M_parent->_M_left)
        __del->_M_parent->_M_left = 0;
    else if (__del == __del->_M_parent->_M_right)
        __del->_M_parent->_M_right = 0;
    else if (__del == __header->_M_parent)
        __header->_M_parent = 0;

    delete __del;
}

_Rbt_node_base *
_rbt_erase(int __key, _Rbt_node_base *__h) noexcept
{
    _Rbt_node_base *__r = __h->_M_parent;
    while (__r)
    {
        if (__key < __r->_M_val)
            __r = __r->_M_left;
        else if (__key > __r->_M_val)
            __r = __r->_M_right;
        else
            break;
    }
    if (__r)
        _rbt_erase_unique(__r == __r->_M_parent->_M_left, __r, __h);
    return __r;
}

struct rbt_debug
{
    _Rbt_node_base *_M_header;

    rbt_debug()
    {
        _M_header = new _Rbt_node_base;
    }
};
#include <iostream>
int main(int argc, char **argv)
{
    rbt_debug __r;
    _Rbt_node_base *__root;

    int __ary[] = {16, 3, 7, 11, 9, 26, 18, 14, 15, 19, 30, 40, 32, 45};
    for (auto __tmp : __ary)
    {
        __root = __r._M_header->_M_parent;
        _rbt_insert(__tmp, __r._M_header);
    }

    __root = __r._M_header->_M_parent;
    _Rbt_node_base *__min = __r._M_header->_M_left;
    for (int i = 0; i < __r._M_header->_M_val; ++i)
    {
        std::cout << __min->_M_val << std::endl;
        __min = _rbt_increment(__min);
    }

    for (auto __t : __ary)
    {
        if (9 == __t)
            int a = 10;
        _rbt_erase(__t, __r._M_header);
    }
    return 0;
}