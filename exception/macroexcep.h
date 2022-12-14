#ifndef __macro_exception_h
#define __macro_exception_h



#define __ustl_throw_again throw;

#define __ustl_throw_exception(mes) throw ustl::exception(mes)

#define __ustl_throw_bad_alloc(mes) throw ustl::bad_alloc(mes)

#define __ustl_throw_nullptr_assignment(mes) throw ustl::nullptr_assignment(mes)

#define __ustl_throw_out_of_range(mes) throw ustl::out_of_range(mes)

#define __ustl_throw_array_length(mes) throw ustl::array_length_exception(mes)

#endif
