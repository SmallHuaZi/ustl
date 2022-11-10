#ifndef __debug
#include "ustl.h"
#include "iterator.h"
#endif

#ifndef __exception_h
#define __exception_h

#include "defaultmes.h"
#include "macroexcep.h"

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
        exception(const exception &) = default;
        exception(const char *__mes) : _M_message(__mes) {}
        virtual ~exception() = default;
        virtual const char *message() noexcept __pure_vritual;
    };

    class bad_alloc
        : public exception
    {
    private:
    public:
        bad_alloc() = default;
        bad_alloc(const char *__message)
            : exception(__message) {}

        virtual const char *
        message() noexcept
        {
            return _M_message ? _M_message : __default_bad_alloc_message;
        }
    };

    class nullptr_assignment
        : public exception
    {
    public:
        nullptr_assignment() = default;
        nullptr_assignment(const char *__mes)
            : exception(__mes) {}

        virtual const char *
        message() noexcept
        {
            return _M_message ? _M_message : __default_nullptr_reference_message;
        }
    };

    class access_outof_bounds
        : public exception
    {
    public:
        access_outof_bounds() = default;
        access_outof_bounds(const char *__mes)
            : exception(__mes) {}

        virtual const char *
        message() noexcept
        {
            return _M_message ? _M_message : __default_access_outof_bounds_message;
        }
    };
}
#endif