#ifndef __bool_vector_h
#define __bool_vector_h

#include "container/bvector_fwd.h"


namespace ustl
{
    template <typename _Tp, typename _Alloc>
    class vector; 


    template <bool _Const>
    struct _Bool_vector_iterator
    {



    public:
        size_t           *_M_bool_map;
        size_t           *_M_use_map;
        size_t           *_M_crrent;
        size_t            _M_mask;
    };



    template <typename _Alloc>
    class vector<bool, _Alloc>
        : _Bool_vector_basic
    {



    };


} // namespace ustl



#endif