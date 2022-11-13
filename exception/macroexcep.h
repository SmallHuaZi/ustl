#ifndef __macro_exception_h
#define __macro_exception_h

#define __ustl_try try
#define __ustl_catch_all catch (...)
#define __ustl_catch(except) catch (except & __e)

#define __ustl_throw_again throw;

#define __throw_exception(mes) throw exception(mes)

#define __throw_bad_alloc(mes) throw bad_alloc(mes)

#define __throw_nullptr_assignment(mes) throw nullptr_assignment(mes)

#define __throw_index_outof(mes) throw access_outof_bounds(mes)

#define __throw_array_length(mes) throw array_length_exception(mes)

#endif
