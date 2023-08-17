#ifndef __USTL_HIDDEN_DEFINE_HPP__
#define __USTL_HIDDEN_DEFINE_HPP__


#define USTL_GENERAL_ASSOCIATION_TYPE(Name)\
    typedef Name           Self;\
    typedef Name *         Ptr;\
    typedef Name &         Ref;\
    typedef Name const *   ConstPtr;\
    typedef Name const &   ConstRef;

#define USTL_GENERAL_ASSOCIATION_TYPE_HAD_BASE(Name, Basic)\
    USTL_GENERAL_ASSOCIATION_TYPE(Name)\
    typedef Basic          Base;\


#define USTL_GENERAL_INTERFACE_ASSOCIATION_TYPE(Type)\
    typedef Type            value_type;\
    typedef Type *          pointer;\
    typedef Type &          reference;\
    typedef Type const *    const_pointer;\
    typedef Type const &    const_reference;\
    typedef usize           size_type;\
    typedef isize           diff_type;

#define USTL_GENERAL_INTERFACE_ASSOCIATION_TYPE_HAD_ALLOCATOR(Type, Alloc)\
    USTL_GENERAL_INTERFACE_ASSOCIATION_TYPE(Type)\
    typedef Alloc           allocator_type;

#endif