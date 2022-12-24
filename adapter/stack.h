#ifndef __ustl_stack_h
#define __ustl_stack_h

#include "container/deque.h"
#include "tmp/move.h"

namespace ustl
{

    template <typename _Tp, typename _Container = ustl::deque<_Tp>>
    class stack
    {
    public:
        typedef     _Container          container_type;
        typedef     _Tp                 value_type;
        typedef     _Tp &               reference;
        typedef     _Tp const &         const_reference;

        static_assert(ustl::is_same<value_type, typename container_type::value_type>()(), 
                 "The storage type must be consistent!");

    public:
        void 
        push(value_type const &__lval)
        { _M_storage.push_back(__lval); }

        void
        push(value_type &&__rval)
        { _M_storage.push_back(ustl::move(__rval)); }

        void
        pop()
        { _M_storage.pop_back(); }

        template <typename ..._Args>
        void
        emplace(_Args &&...__init_args)
        { _M_storage.emplace_back(ustl::forward<_Args &&>(__init_args)...); }

        bool
        empty() const ustl_cpp_noexcept
        { return    _M_storage.empty(); }

        size_t
        size() const ustl_cpp_noexcept
        { return    _M_storage.size(); }

        reference 
        top() ustl_cpp_noexcept
        { return    _M_storage.back(); }

        const_reference
        top() const ustl_cpp_noexcept
        { return    _M_storage.back(); }

        void
        swap(stack &__other)
        { _M_storage.swap(__other._M_storage); }

        void
        swap(stack &&__other)
        { _M_storage.swap(ustl::move(__other)); }

        friend bool
        operator==(stack const &__l, stack const &__r) ustl_cpp_noexcept
        { return    __l._M_storage == __r._M_storage; }

        friend bool
        operator!=(stack const &__l, stack const &__r) ustl_cpp_noexcept
        { return    __l._M_storage != __r._M_storage; }


    public:
        stack()
            : _M_storage()
        {}

        stack(container_type const &__lc)
            : _M_storage(__lc)
        {}

        stack(container_type &&__rc)
            : _M_storage(ustl::move(__rc))
        {}

        stack(stack const &) = default;

        stack(stack &&) = default;


    private:    
        container_type          _M_storage;
    };

} // namespace ustl

#endif