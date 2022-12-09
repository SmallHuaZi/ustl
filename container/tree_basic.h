#ifndef __tree_basic_h
#define __tree_basic_h


namespace ustl
{

    struct tree_node_basic
    {
        typedef     tree_node_basic     _Node_basic;
        typedef     tree_node_basic *   _Node_basic_pointer;


        tree_node_basic();

        tree_node_basic(_Node_basic_pointer __p);

        tree_node_basic(_Node_basic_pointer __l, _Node_basic_pointer __r, _Node_basic_pointer __p);

        _Node_basic_pointer     _M_parent;
        _Node_basic_pointer     _M_left;
        _Node_basic_pointer     _M_right;
    };

    tree_node_basic *
    _tree_decrement(tree_node_basic *__node);

    tree_node_basic *
    _tree_increment(tree_node_basic *__node);

    void
    _tree_left_rotate(tree_node_basic *__node);

    void
    _tree_right_rotate(tree_node_basic *__node);
    

} // namespace uslt


#endif