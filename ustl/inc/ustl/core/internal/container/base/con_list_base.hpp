#if defined(_MSC_VER)
#pragma once
#endif
#ifndef __USTL_CORE_INTERNAL_CONTAINER_BASE_LIST_BASE_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_BASE_LIST_BASE_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif


namespace ustl
{
namespace core
{
namespace internal
{
namespace container
{
namespace base
{
 
    struct ListNodeBasic 
    {
        USTL_GENERAL_ASSOCIATION_TYPE(ListNodeBasic);

    public:
        ListNodeBasic()
            : _M_prev(this), _M_next(this)
        {}

        ListNodeBasic(Ptr prev, Ptr next)
            : _M_prev(prev), _M_next(next)
        {}

        void
        _M_unhook() USTL_NOEXCEPT;

        void
        _M_hook_before(Ptr __p) USTL_NOEXCEPT;

        void
        _M_hook_after(Ptr __p) USTL_NOEXCEPT;

        USTL_ALWAYS_INLINE
        Ptr  
        prev() USTL_NOEXCEPT
        { return    _M_prev; }

        USTL_ALWAYS_INLINE
        Ptr 
        next() USTL_NOEXCEPT
        { return    _M_next; }

        USTL_ALWAYS_INLINE
        void
        set_prev(Ptr  __p) USTL_NOEXCEPT
        { _M_prev = __p; }

        USTL_ALWAYS_INLINE
        void
        set_next(Ptr  __n) USTL_NOEXCEPT
        { _M_next = __n; }

        USTL_ALWAYS_INLINE
        void
        _M_reset() USTL_NOEXCEPT
        { _M_prev = _M_next = this; }

    public:
        Ptr  _M_prev;
        Ptr  _M_next;
    };    


    struct ListHeader
        : ListNodeBasic
    {
        USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(ListHeader, ListNodeBasic);

    public:
        USTL_ALWAYS_INLINE
        usize
        _M_count() USTL_NOEXCEPT
        { return    _M_node_count; }

        USTL_ALWAYS_INLINE
        usize
        _M_set_count(usize __c) USTL_NOEXCEPT
        { return    _M_node_count = __c; }

        USTL_ALWAYS_INLINE
        void
        _M_inc_size(usize __n) USTL_NOEXCEPT
        { _M_node_count += __n; }

        USTL_ALWAYS_INLINE
        void
        _M_dec_size(usize __n) USTL_NOEXCEPT
        { _M_node_count -= __n; }

        USTL_ALWAYS_INLINE
        Base *
        _M_prev_node() USTL_NOEXCEPT
        { return    _M_prev; }

        USTL_ALWAYS_INLINE
        Base *
        _M_first_node() USTL_NOEXCEPT
        { return    _M_next; }

        void
        _M_reset() USTL_NOEXCEPT;

        void
        _M_move(Ref __other) USTL_NOEXCEPT;

        void
        _M_copy(ConstRef __other) USTL_NOEXCEPT;

        static void
        _S_swap(Ref __l, Ref __r) USTL_NOEXCEPT;

    private:
        usize      _M_node_count;
    };       


    USTL_ALWAYS_INLINE
    void
    ListHeader::
        _M_reset() USTL_NOEXCEPT
    {
        Base::_M_reset();
        _M_node_count = 0;
    }


    USTL_ALWAYS_INLINE
    void
    ListHeader::
        _M_copy(ConstRef __other) USTL_NOEXCEPT
    {
        _M_prev  = __other._M_prev;
        _M_next  = __other._M_next;
        _M_node_count = __other._M_node_count;
    }


    USTL_ALWAYS_INLINE
    void
    ListHeader::
        _M_move(Ref __other) USTL_NOEXCEPT
    {
        _M_copy(__other);
        __other._M_prev->_M_next = this;
        __other._M_next->_M_prev = this;       
        __other._M_reset();
    }


    struct ListCompareBasic
    {
        virtual bool
        operator()(ListNodeBasic const *, ListNodeBasic const *) USTL_INTERFACE;
    };
    

    USTL_API
    extern void
    ustl_list_splice(ListNodeBasic *, ListNodeBasic *, ListNodeBasic *) USTL_NOEXCEPT;


    USTL_API
    extern void
    ustl_list_merge(ListHeader *, ListHeader *, ListCompareBasic &) USTL_NOEXCEPT;


    USTL_API
    extern void
    ustl_list_sort(ListHeader *, ListCompareBasic &) USTL_NOEXCEPT;


    USTL_API
    extern void
    ustl_list_reverse(ListHeader *) USTL_NOEXCEPT;

} // namespace ustl::core::internal::container::base
} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl



#endif