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



} // namespace ustl


#endif