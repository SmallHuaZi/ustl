#include "ustl.h"

namespace ustl
{
    template <size_t _Idx, typename _Element>
    struct _Tuple_data
    {
    public:
        /* using member of function covering,take member of data duplication of name */
        static constexpr _Element &
        _M_value(_Tuple_data &__this) noexcept
        {
            return __this._M_val;
        }

        static constexpr const _Element &
        _M_value(const _Tuple_data &__this) noexcept
        {
            return __this._M_val;
        }

        void
        _M_swap(_Tuple_data &__other) noexcept
        {
            _Element __tmp(__other._M_val);
            __other._M_val = this->_M_val;
            this->_M_val = __tmp;
        }

    protected:
        _Element _M_val;

    protected:
        _Tuple_data() = default;

        _Tuple_data(const _Element &__e)
            : _M_val(__e) {}
    };

    template <size_t _Idx, typename _Head, typename... _Tail>
    struct _Tuple_Impl
        : public _Tuple_Impl<_Idx + 1, _Tail...>,
          public _Tuple_data<_Idx, _Head>
    {
    public:
        typedef _Tuple_Impl<_Idx + 1, _Tail...> _Sub;
        typedef _Tuple_data<_Idx, _Head> _Node;

        static constexpr _Head &
        _M_value(_Node &__this)
        {
            return _Node::_M_value(__this);
        }

        static constexpr const _Head &
        _M_value(const _Node &__this)
        {
            return _Node::_M_value(__this);
        }

        /* derived cast to base and get part of base,for next element */
        static constexpr _Sub &
        _M_subsequent(_Tuple_Impl &__this)
        {
            return __this;
        }

        static constexpr const _Sub &
        _M_subsequent(const _Tuple_Impl &__this)
        {
            return __this;
        }

        /* using tmp recursion let element of all swap,until call
                  _M_swap of partial specialization  */
        void
        _M_copy(const _Tuple_Impl &__other)
        {
            _M_value(*this) = _M_value(__other);
            _Sub::_M_copy(_M_subsequent(__other));
        }

        void
        _M_swap(_Tuple_Impl &__other)
        {
            _Node::_M_swap(__other);
            _Sub::_M_swap(_M_subsequent(__other));
        }

    public:
        constexpr _Tuple_Impl() noexcept
            : _Sub(), _Node() {}

        constexpr _Tuple_Impl(const _Head &__h,
                              const _Tail &...__t)
            : _Sub(__t...), _Node(__h) {}

        constexpr _Tuple_Impl(const _Tuple_Impl &__other)
        {
            this->_M_copy(__other);
        }

        constexpr _Tuple_Impl(_Tuple_Impl &&__other)
        {
            this->_M_swap(__other);
        }
    };

    template <size_t _Idx, typename _Head>
    struct _Tuple_Impl<_Idx, _Head>
        : public _Tuple_data<_Idx, _Head>
    {
    public:
        typedef _Tuple_data<_Idx, _Head> _Node;

        static constexpr _Head &
        _M_value(_Node &__this)
        {
            return _Node::_M_value(__this);
        }

        static constexpr const _Head &
        _M_value(const _Node &__this)
        {
            return _Node::_M_value(__this);
        }

        void
        _M_copy(const _Tuple_Impl &__other)
        {
            _M_value(*this) = _M_value(__other);
        }

        void
        _M_swap(_Tuple_Impl &__other)
        {
            _Node::_M_swap(__other);
        }

    public:
        constexpr _Tuple_Impl() noexcept
            : _Node() {}

        constexpr _Tuple_Impl(const _Head &__h) noexcept
            : _Node(__h) {}

        constexpr _Tuple_Impl(const _Tuple_Impl &__other) noexcept
        {
            this->_M_copy(__other);
        }

        constexpr _Tuple_Impl(_Tuple_Impl &&__other) noexcept
        {
            this->_M_swap(__other);
        }
    };

    template <typename... _Elements>
    class tuple
        : public _Tuple_Impl<0, _Elements...>
    {
    public:
        typedef _Tuple_Impl<0, _Elements...> _Base_type;

    public:
        tuple() noexcept
            : _Base_type() {}

        tuple(const _Elements &...__args) noexcept
            : _Base_type(__args...) {}

        tuple(const tuple &__t) noexcept
            : _Base_type(__t) {}

        tuple(tuple &&__t) noexcept
            : _Base_type(forward(__t)) {}

    public:
        tuple &
        operator=(const tuple &__t)
        {
            this->_M_copy(__t);
            return *this;
        }

        void
        swap(tuple &__t)
        {
            this->swap(__t);
        }
    };

    /* template meta programing:
    using recursion,get target type */
    template <size_t _Idx, typename _Head, typename... _Tail>
    struct _Tuple_eletype
        : _Tuple_eletype<_Idx - 1, _Tail...>
    {
    };

    template <typename _Head, typename... _Tail>
    struct _Tuple_eletype<0, _Head, _Tail...>
    {
        typedef _Head type;
    };

    /** interface for tuple */
    template <size_t _Idx, typename... _Eles>
    inline typename _Tuple_eletype<_Idx, _Eles...>::type &
    get(tuple<_Eles...> &__t) noexcept
    {
        return _Tuple_Impl<_Idx, _Eles...>::_M_value(__t);
    }

}