#ifndef __USTL_CORE_INTERNAL_ITERATOR_HELPER_HPP__
#define __USTL_CORE_INTERNAL_ITERATOR_HELPER_HPP__

#ifndef __USTL__
#include <ustl/ustl>
#endif

#ifndef __USTL_CORE_INTERNAL_ITERATOR_TRAITS_HPP__
#include <ustl/core/internal/iterator/itr_traits.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_OBJECT_HPP__
#include <ustl/core/internal/type_traits/tt_object.hpp>
#endif

namespace ustl::core::internal::iterator
{

    template <typename Iter, typename = void> 
    struct IsIter 
        : false_type
    {};

    template <typename Iter>
    struct IsIter<Iter, typename IterTraits<Iter>::iter_category>
        : true_type
    {};

    template <typename _InputIter, bool _IsSame = internal::type_traits::
              IsBaseOf<typename IterTraits<_InputIter>::iter_category, input_iter_category>::value>
    struct IsInputIter
    { USTL_CONSTEXPR static bool const value = _IsSame; };

    template <typename _OutputIter, bool _IsSame = internal::type_traits::
              IsBaseOf<typename IterTraits<_OutputIter>::iter_category, output_iter_category>::value>
    struct IsOutputIter
    { USTL_CONSTEXPR static bool const value = _IsSame; };

    template <typename _FwdIter, bool _IsSame = internal::type_traits::
              IsBaseOf<typename IterTraits<_FwdIter>::iter_category, forward_iter_category>::value>
    struct IsForwardIter
    { USTL_CONSTEXPR static bool const value = _IsSame; };
    
    template <typename _BothwayIter, bool _IsSame = internal::type_traits::
              IsBaseOf<typename IterTraits<_BothwayIter>::iter_category, bothway_iter_category>::value>
    struct IsBothwayIter
    { USTL_CONSTEXPR static bool const value = _IsSame; };
    
    template <typename _RandomIter, bool _IsSame = internal::type_traits::
              IsBaseOf<typename IterTraits<_RandomIter>::iter_category, random_iter_category>::value>
    struct IsRandomIter
    { USTL_CONSTEXPR static bool const value = _IsSame; };


    template <typename Iter>
    struct IterOpLt 
    {
        typedef Iter   iter;

        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return *x < *y; }
    };

    template <typename Iter>
    struct IterOpLe 
    {
        typedef Iter   iter;

        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return *x <= *y; }
    };

    template <typename Iter>
    struct IterOpEq
    {
        typedef Iter   iter;

        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return *x == *y; }
    };

    template <typename Iter>
    struct IterOpNe
    {
        typedef Iter   iter;

        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return *x != *y; }
    };

    template <typename Iter>
    struct IterOpGt
    {
        typedef Iter   iter;

        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return *x > *y; }
    };

    template <typename Iter>
    struct IterOpGe
    {
        typedef Iter   iter;

        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return *x >= *y; }
    };
    
    template <typename Iter, typename Compare>
    struct IterOpCmp
    {
        typedef Iter     iter;
        typedef Compare  compare_type;

        USTL_ALWAYS_INLINE
        IterOpCmp(compare_type cmp)
            : _M_cmp(cmp)
        {}
        
        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return _M_cmp(*x, *y); }

    private:
        compare_type _M_cmp;
    };
    
    template <typename Iter, typename Compare>
    struct IterOpReverse
    {
        typedef Iter     iter;
        typedef Compare  compare_type;

        USTL_ALWAYS_INLINE
        IterOpCmp(compare_type cmp)
            : _M_cmp(cmp)
        {}
        
        USTL_ALWAYS_INLINE
        bool
        operator()(iter const &x, iter const &y) USTL_NOEXCEPT
        { return !_M_cmp(*x, *y); }

    private:
        compare_type _M_cmp;
    };


    /// @brief Computes the distance between two input/output/forward/bothway iterators 
    /// @param  first start iterator
    /// @param  last  end iterator 
    template <typename Iter, typename Distance>
    USTL_CONSTEXPR
    Distance 
    itr_distance(Iter first, Iter last, input_iter_category)
    {
        Distance dis = 0;
        for (; first != last; ++dis, ++first)
        {}

        return dis;
    }

    /// @brief Computes the distance between two random access iterators 
    /// @param  first start iterator
    /// @param  last  end iterator 
    template <typename Iter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR 
    Distance
    itr_distance(Iter first, Iter last, random_iter_category)
    { 
        return last - first; 
    }

    template <typename Iter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    Distance
    distance(Iter first, Iter last)
    {
        static_assert(IsIter<Iter>::value, "Template parameter" 
                     " 'Iter' must be a valid iterator type");

        return itr_distance(first, last, typename IterTraits<
                            Iter>::iter_category{});
    }


    /// @brief  Advance an iterator n steps 
    /// @param  iter the specify iterator
    /// @param  n steps 
    template <typename Iter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void
    itr_advance(Iter &iter, Distance n, input_iter_category)
    {
        while (n--) {
            ++iter;
        }
    }

    /// @brief  Advance an iterator n steps 
    /// @param  iter the specify iterator
    /// @param  n steps 
    template <typename Iter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void
    itr_advance(Iter &iter, Distance n, bothway_iter_category)
    {
        if (n < 0) {
            while (n++) {
                --iter;
            }
        }
        else {
            while (n--) {
                ++iter;
            }
        }
    }

    /// @brief  Advance an iterator n steps 
    /// @param  iter the specify iterator
    /// @param  n steps 
    template <typename Iter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void
    itr_advance(Iter &iter, Distance n, random_iter_category)
    { 
        iter -= n; 
    }

    template <typename Iter, typename Distance>
    USTL_ALWAYS_INLINE USTL_CONSTEXPR
    void
    advance(Iter &iter, Distance n)
    {
        static_assert(IsIter<Iter>::value, "Template parameter" 
                     " 'Iter' must be a valid iterator type");        

        itr_advance(iter, n, typename IterTraits<Iter>::iter_category{})
    }


} // namespace ustl::core::internal::iterator


#endif