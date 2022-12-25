#ifndef __exception_h
#define __exception_h

#include "exception/defaultmes.h"
#include "exception/macroexcep.h"

namespace ustl
{

    /// @brief exception base class in ustl,
    //         using it can catch all subclasses derived from it
    class exception
    {
    protected:
        const char *_M_message;

    public:
        exception() = default;

        exception(exception &&) = default;

        exception(exception const &) = default;

        exception(char const *__mes) 
            : _M_message(__mes) 
        {}

        virtual 
        ~exception() = default;

        virtual char const *
        message()
        { return _M_message ? _M_message : "exception happends"; }
    };



    class bad_alloc
        : public exception
    {
    public:
        bad_alloc(char const *__message = __default_bad_alloc_message)
            : exception(__message) 
        {}
    };



    class nullptr_reference
        : public exception
    {
    public:
        nullptr_reference(char const *__mes = __default_nullptr_reference_message)
            : exception(__mes) 
        {}
    };



    class out_of_range
        : public exception
    {
    public:
        out_of_range(char const *__mes = __default_out_of_range_message)
            : exception(__mes) 
        {}
    };



    class array_length_exception
        : public exception
    {
    public:
        array_length_exception(char const *__mes = __default_array_length_message)
            : exception(__mes) 
        {}
    };


}
#endif