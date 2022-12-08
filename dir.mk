# root dir
__va_root_dir := ${PWD}
# root dir


# executable file path
__va_executable_dir := ${__va_root_dir}/debug
# executable file path


# libary path
__va_libary_dir := ${__va_root_dir}/lib
# libary path





# impl code path
__impl_dir := ${__va_root_dir}/src
# impl code path


# header path
__va_container_dir := ${__va_root_dir}/container

__va_exception_dir := ${__va_root_dir}/exception

__va_functor_dir := ${__va_root_dir}/functor

__va_adapter_dir := ${__va_root_dir}/adapter

__va_algorithm_dir := ${__va_root_dir}/algorithm

__va_allocator_dir := ${__va_root_dir}/allocator

__va_fwddecl_dir := ${__va_root_dir}/forward_decl

__va_iterator_dir := ${__va_root_dir}/iterator

__va_type_dir := ${__va_root_dir}/type

__va_tmp_dir := ${__va_root_dir}/tmp
# header path


# export variable
################################################################


# libary path for program
export
__dlib_dir := ${__va_libary_dir}/dynamic

export
__slib_dir := ${__va_libary_dir}/static
# libary path for program

# object file path
export
__obj_dir := ${__va_root_dir}/obj
# object fiel path

# include path for program
export 
__include_path := $(addprefix -I ,${__va_container_dir} ${__va_exception_dir} \
 ${__va_adapter_dir} ${__va_algorithm_dir} ${__va_allocator_dir} \
 ${__va_functor_dir} ${__va_fwddecl_dir} ${__va_root_dir} \
 ${__va_type_dir} ${__va_tmp_dir} ${__va_iterator_dir})
# include path for program


#################################################################
# export variable