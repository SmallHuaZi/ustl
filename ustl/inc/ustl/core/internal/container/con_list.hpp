#ifndef __USTL_CORE_INTERNAL_CONTAINER_LIST_HPP__ 
#define __USTL_CORE_INTERNAL_CONTAINER_LIST_HPP__ 


namespace ustl
{
namespace core
{
namespace internal
{
 
    template <typename _Tp>
    class List
    {
    private:
        struct ListNode;
        struct ListImpl;

        template <bool _Mut>
        struct ListIterator;

        typedef ListHeader     _Header_type;

    public:
        typedef _Tp     value_type;
        typedef _Tp *   pointer;
        typedef _Tp &   reference;
        typedef _Tp const *     const_pointer;
        typedef _Tp const &     const_reference;

        typedef List                   self_type;
        typedef ListNode             node_type;
        typedef ListNode *           node_pointer;
        typedef ListIterator<true>   iter_mut;
        typedef ListIterator<false>  iter_const;
        typedef size_t      size_type;
        typedef diff_t      difference_type;


    public:
        /**
         * @brief:
         * @param __node: 
         * @return:
        */
        iter_mut 
        push_back(node_pointer __node);


        /**
         * @brief:
         * @param __node:
         * @return
        */
        iter_mut 
        push_front(node_pointer __node);


        /**
         * @brief:
         * @param __pos:
         * @param __node:
         * @return:
        */
        iter_mut
        insert(iter_const __pos, node_pointer __node);


        /**
         * @brief:
         * @param __idx:
         * @param __node:
         * @return:
        */
        iter_mut
        insert(size_t __idx, node_pointer __node);


        /**
         * @brief:
         * @return:
        */
        iter_mut 
        pop_back();


        /**
         * @brief:
         * @return:
        */
        iter_mut 
        pop_front();


        /**
         * @brief:
         * @param __node:
         * @return:
        */
        iter_mut
        erase(node_pointer __node);


        /**
         * @brief:
         * @param __node:
         * @return:
        */
        iter_mut
        erase(iter_const __pos);


        /**
         * @brief:
         * @param __beg:
         * @param __end:
         * @return:
        */
        iter_mut
        erase_range(iter_const __beg, iter_const __end);


        /**
         * @brief:
         * @param __idx:
         * @return:
        */
        iter_mut
        index_of(size_type __idx);


        /**
         * @brief:
         * @param __idx:
         * @return:
        */
        iter_const
        index_of(size_type __idx) const;


        /**
         * @brief:
         * @param __val:
         * @return:
        */
        iter_mut
        find(const_reference __val);


        /**
         * @brief:
         * @param __val:
         * @retrun:
        */
        iter_const
        find(const_reference __val) const;


    private:
        _Header_type     _M_header;         ///< 
    };


    template <typename _Tp>
    struct List<_Tp>::ListNode
        : public ListNodeBasic 
    {

    private:
        value_type      _M_data;
    };

} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif