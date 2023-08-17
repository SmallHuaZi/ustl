#ifndef __USTL_CORE_INTERNAL_CONTAINER_TUPLE_HPP__
#define __USTL_CORE_INTERNAL_CONTAINER_TUPLE_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_UTILITY_MOVE_HPP__
#include <ustl/core/internal/utility/move.hpp>
#endif

namespace ustl
{
namespace core
{
namespace internal
{
namespace container
{

    template <unsigned int Idx, typename Element>
    struct TupleElementData
    {
        USTL_GENERAL_ASSOCIATION_TYPE(TupleElementData);
        typedef Element         element_type;
        typedef Element *       pointer;
        typedef Element &       reference;
        typedef Element const * const_pointer;
        typedef Element const & const_reference;

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static reference 
        _S_value(Ref self) USTL_NOEXCEPT 
        { return self._M_val; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static const_reference 
        _S_value(ConstRef self) USTL_NOEXCEPT
        { return self._M_val; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        _M_copy(ConstRef other) USTL_NOEXCEPT
        { this->_M_val = other._M_val; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        _M_move(Self &&other) USTL_NOEXCEPT
        { this->_M_val = internal::utility::move(other._M_val); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        _M_swap(Ref other) USTL_NOEXCEPT 
        {
            element_type tmp(other._M_val);
            other._M_val = this->_M_val;
            this->_M_val = tmp;
        }

    protected:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        TupleElementData() USTL_NOEXCEPT = default;

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        TupleElementData(const_reference e) USTL_NOEXCEPT
            : _M_val(e) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        TupleElementData(element_type &&e) USTL_NOEXCEPT
            : _M_val(internal::utility::forward(e)) 
        {}

    protected:
        element_type _M_val;
    };


    template <unsigned int Idx, typename Head, typename... Tails>
    struct TupleImpl
        : public TupleImpl<Idx + 1, Tails...>,
          public TupleElementData<Idx, Head>
    {
        typedef Head          element_type;
        typedef Head *        pointer;
        typedef Head &        reference;
        typedef Head const *  const_pointer;
        typedef Head const &  const_reference;

    private:
        USTL_GENERAL_ASSOCIATION_TYPE(TupleImpl);
        typedef TupleImpl<Idx + 1, Tails...>    Base;
        typedef TupleElementData<Idx, Head>     DataNode;

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static reference 
        _S_value(DataNode &self) USTL_NOEXCEPT
        { return DataNode::_S_value(self); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static const_reference 
        _S_value(DataNode const &self) USTL_NOEXCEPT
        { return DataNode::_S_value(self); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static Base & 
        _S_to_base(Ref self) USTL_NOEXCEPT
        { return self; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static Base const &
        _S_to_base(ConstRef self) USTL_NOEXCEPT
        { return self; }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        void
        _M_copy(ConstRef other) USTL_NOEXCEPT
        {
            _S_value(*this) = _S_value(other);
            Base::_M_copy(_S_to_base(other));
        }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        void
        _M_move(Self &&other) USTL_NOEXCEPT
        {
            using internal::utility::move;
            _S_value(*this) = move(_S_value(other));
            Base::_M_move(move(_S_to_base(other)));
        }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        void
        _M_swap(Ref self) USTL_NOEXCEPT
        {
            DataNode::_M_swap(self);
            Base::_M_swap(_S_to_base(self));
        }

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl() USTL_NOEXCEPT 
            : Base(), DataNode() 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(const_reference h, Tails const &...t) USTL_NOEXCEPT
            : Base(t...), DataNode(h) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(element_type &&h, Tails &&...t) USTL_NOEXCEPT
            : Base(internal::utility::forward(t)...), 
              DataNode(internal::utility::forward(h)) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(ConstRef other) USTL_NOEXCEPT
        { _M_copy(other); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(TupleImpl &&other) USTL_NOEXCEPT
        { _M_move(other); }
    };


    template <unsigned int Idx, typename Head>
    struct TupleImpl<Idx, Head>
        : public TupleElementData<Idx, Head>
    {
        typedef Head          element_type;
        typedef Head *        pointer;
        typedef Head &        reference;
        typedef Head const *  const_pointer;
        typedef Head const &  const_reference;

    private:
        USTL_GENERAL_ASSOCIATION_TYPE(TupleImpl);
        typedef TupleElementData<Idx, Head>    DataNode;

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static reference 
        _S_value(DataNode &self) USTL_NOEXCEPT
        { return DataNode::_S_value(self); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        static const_reference 
        _S_value(DataNode const &self) USTL_NOEXCEPT
        { return DataNode::_S_value(self); }

        USTL_ALWAYS_INLINE
        void
        _M_copy(ConstRef other) USTL_NOEXCEPT
        { _S_value(*this) = _S_value(other); }

        USTL_ALWAYS_INLINE
        void
        _M_move(Self &&other) USTL_NOEXCEPT
        { _S_value(*this) = internal::utility::move(_S_value(other)); }

        USTL_ALWAYS_INLINE
        void
        _M_swap(Ref other) USTL_NOEXCEPT
        { DataNode::_M_swap(other); }

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl() USTL_NOEXCEPT
            : DataNode() 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(const_reference h) USTL_NOEXCEPT
            : DataNode(h) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(element_type &&h) USTL_NOEXCEPT
            : DataNode(internal::utility::forward(h)) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(TupleImpl const &other) USTL_NOEXCEPT
        { this->_M_copy(other); }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR 
        TupleImpl(TupleImpl &&other) USTL_NOEXCEPT
        { this->_M_move(other); }
    };


    template <typename... Elems>
    class Tuple
        : public TupleImpl<0, Elems...>
    {
        typedef     TupleImpl<0, Elems...>    Base;
        USTL_GENERAL_ASSOCIATION_TYPE(Tuple);

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple() USTL_NOEXCEPT
            : Base() 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple(Elems const &...args) USTL_NOEXCEPT
            : Base(args...) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple(Elems &&...args) USTL_NOEXCEPT
            : Base(internal::utility::forward(args)...) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple(Tuple const &other) USTL_NOEXCEPT
            : Base(other) 
        {}

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple(Tuple &&other) USTL_NOEXCEPT
            : Base(internal::utility::forward(other))
        {}

    public:
        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple &
        operator=(ConstRef t)
        {
            Base::_M_copy(t);
            return *this;
        }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        Tuple &
        operator=(Tuple &&t)
        {
            using internal::utility::forward;
            Base::_M_move(forward(t));
            return *this;
        }

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        void
        swap(Ref t)
        { Base::_M_swap(t); }
    };


    template <unsigned int Idx, typename... Elems>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    typename internal::type_traits::TypeSeqIndexer<Idx, Elems...>::type &
    get(Tuple<Elems...> &t) USTL_NOEXCEPT
    { 
        using internal::type_traits::TypeSeqIndexer;

        typedef typename TypeSeqIndexer<Idx, Elems...>::type 
            element_type;

        return TupleImpl<Idx, element_type>::_S_value(t); 
    }

    template <unsigned int Idx, typename... Elems>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    typename internal::type_traits::TypeSeqIndexer<Idx, Elems...>::type const &
    get(Tuple<Elems...> const &t) USTL_NOEXCEPT
    { 
        using internal::type_traits::TypeSeqIndexer;

        typedef typename TypeSeqIndexer<Idx, Elems...>::type 
            element_type;

        return TupleImpl<Idx, element_type>::_S_value(t); 
    }


    template <unsigned int Idx, typename... Elems>
    struct TupleEqHelper
    {
        typedef Tuple<Elems...>     TupleType;

        USTL_CONSTEXPR
        bool
        operator()(TupleType const &x, TupleType const &y)
        {
            return get<Idx>(x) == get<Idx>(y) && TupleEqHelper<Idx - 1, Elems...>{}(x, y);
        }
    };

    template <typename... Elems>
    struct TupleEqHelper<0, Elems...>
    {
        typedef Tuple<Elems...>     TupleType;

        USTL_ALWAYS_INLINE USTL_CONSTEXPR
        bool
        operator()(TupleType const &x, TupleType const &y)
        {
            return get<0>(x) == get<0>(y);
        }
    };

    template <typename... Elems>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    bool
    operator==(Tuple<Elems...> const &x, Tuple<Elems...> const &y) USTL_NOEXCEPT
    {
        using internal::type_traits::TypeSeqLength;

        USTL_CONSTEXPR unsigned int const LENGTH = TypeSeqLength<Elems...>::value;
        static_assert(LENGTH != 0, "[ustl-error] Empty tuple cause undefined behavior.\n");

        return TupleEqHelper<LENGTH - 1, Elems...>{}(x, y);
    }

    template <typename... Elems>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    bool
    operator!=(Tuple<Elems...> const &x, Tuple<Elems...> const &y) USTL_NOEXCEPT
    {
        return !(x == y);
    }

} // namespace ustl::core::internal::container
} // namespace ustl::core::internal
} // namespace ustl::core
} // namespace ustl


#endif