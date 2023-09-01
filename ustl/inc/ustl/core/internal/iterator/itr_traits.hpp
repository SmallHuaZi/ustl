#ifndef __USTL_CORE_INTERNAL_ITERATOR_TRAITS_HPP__
#define __USTL_CORE_INTERNAL_ITERATOR_TRAITS_HPP__

#ifndef __USTL_CORE_INTERNAL_TYPETRAITS_BASE_HPP__ 
#include <ustl/core/internal/type_traits/tt_base.hpp>
#endif

#ifndef __USTL_CORE_INTERNAL_ITERATOR_CATEGORY_HPP__
#include <ustl/core/internal/iterator/itr_category.hpp>
#endif

namespace ustl::core::internal::iterator
{

    template <typename _Iter, typename = void>
    struct IterTraitsHelper
    { static_cast(false, "[Error]: The parameter '_Iter' is not a vaild type of Iterator!") };

    template <typename _Iter>
    struct IterTraitsHelper<_Iter, typename internal::type_traits::MakeVoid<
            typename _Iter::value_type,
            typename _Iter::pointer,
            typename _Iter::reference,
            typename _Iter::const_pointer,
            typename _Iter::const_reference,
            typename _Iter::iter_category,
            typename _Iter::diff_type>::type>
    {
        typedef typename _Iter::value_type          value_type;
        typedef typename _Iter::pointer             pointer;
        typedef typename _Iter::reference           reference;
        typedef typename _Iter::const_pointer       const_pointer;
        typedef typename _Iter::const_reference     const_reference;
        typedef typename _Iter::iter_category       iter_category;
        typedef typename _Iter::diff_type           diff_type;
    };


    template <typename _Iter>
    struct IterTraits 
        : IterTraitsHelper<_Iter>
    {
        typedef typename _Iter::value_type           value_type; 
        typedef typename _Iter::pointer              pointer;
        typedef typename _Iter::reference            reference;
        typedef typename _Iter::const_pointer        const_pointer;
        typedef typename _Iter::const_reference      const_reference;
        typedef typename _Iter::iter_category        iter_category;
        typedef typename _Iter::diff_type            diff_type;
    };


    /**
     * @brief: When '_Iter' is a pointer
    */
    template <typename _Iter>
    struct IterTraits<_Iter *>
    {
        typedef _Iter           value_type;
        typedef _Iter *         pointer;
        typedef _Iter &         reference;
        typedef _Iter const *   const_pointer;
        typedef _Iter const &   const_reference;
        typedef isize           diff_type;
        typedef bothway_iter_category   iter_category;
    };
    
} // namespace ustl::core::internal::iterator


#endif