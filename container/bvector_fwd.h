#ifndef __bool_vector_fwd_h
#define __bool_vector_fwd_h

#include "include/config.h"

namespace ustl
{
    // non-template class
    struct _Bool_vector_basic
    {
        typedef     bool                    value_type;
        typedef     bool *                  pointer;
        typedef     bool &                  reference;
        typedef     bool const *            const_pointer;
        typedef     bool const &            const_reference;

        struct _BoolVectorBasicImpl
        {
            void
            _M_reset();

            void
            _M_swap();

            void
            _M_move();

        public:
            size_t          *_M_bool_map;
            size_t          *_M_use_map;
            size_t           _M_map_size;
        };

        typedef     _BoolVectorBasicImpl        impl_type;


    protected: 
        impl_type       _M_data_plus;
    };
    
} // namespace uslt




#endif