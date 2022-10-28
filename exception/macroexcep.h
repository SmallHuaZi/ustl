#ifndef __macro_exception_h
#define __macro_exception_h

#define __throw_exception(mes) throw exception(mes)

#define __throw_bad_alloc(mes) throw bad_alloc(mes)

#define __throw_nullptr_assignment(mes) throw nullptr_assignment(mes)

#endif