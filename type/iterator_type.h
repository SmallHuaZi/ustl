#ifndef __iterator_type_h
#define __iterator_type_h

#include "iterator/iterator.h"
#include "type/itr_traits.h"
#include "type/type.h"

namespace ustl
{
   template <typename _Iterator>
   using _iterator_tag_t = typename itr_traits<_Iterator>::iterator_tag; 


   template <typename _Iterator>
   using RequireInputItr = ustl::enable_if_t<__is_convertible<_iterator_tag_t<_Iterator>, 
                                                _input_iterator>::value>;


   
   template <typename _Iterator, typename _DifT>
   static inline _Iterator &
   _M_advance(_Iterator &__itr, _DifT __dif, ustl::false_type)
   { 
      if(__dif < 0)
         while(__dif++)
            --__itr;
      else
         while(__dif--)
            ++__itr;
      return   __itr;
   }


   template <typename _Iterator, typename _DifT>
   static inline _Iterator &
   _M_advance(_Iterator &__itr, _DifT __dif, ustl::true_type)
   { return    __itr += __dif; }


   template <typename _Iterator, typename _DifT>
   static inline _Iterator &
   advance(_Iterator &__itr, _DifT __dif)
   { return    _M_advance(__itr, __dif, is_same<_iterator_tag_t<_Iterator>, _random_iterator>()()); }

} // namespace ustl


#endif