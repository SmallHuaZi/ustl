#ifndef __USTL_HIDDEN_NAMESPACE_HPP__
#define __USTL_HIDDEN_NAMESPACE_HPP__

#define STD       ::ustl::std::
#define CORE      ::ustl::core::

namespace ustl
{
    namespace core
    {
        namespace sorting {} // namespace sorting
        namespace hasher {} // namespace hasher

        namespace internal
        {
            namespace algorithm
            {
                namespace hash {} // namespace hash
            } // namespace algorithm

            namespace container
            {
                namespace base {} // namespace base
            } // namespace container

            namespace math {} // namespace math
            namespace arch {} // namespace arch
            namespace atomic {} // namespace atomic
            namespace compare {} // namespace compare
            namespace utility {} // namespace utility 
            namespace iterator {} // namespace iterator
            namespace type_traits {} // namespace type_traits 

        } // namespace internal
    } // namespace core


    namespace std
    {
        namespace internal
        {
            namespace math
            {
                using namespace core::internal::math;
            } // namespace math

            namespace algorithm
            {
                using namespace core::internal::algorithm;
            } // namespace algorithm

            namespace atomic
            {
                using namespace core::internal::atomic;
            } // namespace atomic

            namespace compare
            {
                using namespace core::internal::compare;
            } // namespace compare

            namespace utility
            {
                using namespace core::internal::utility;
            } // namespace utility

            namespace iterator
            {
                using namespace core::internal::iterator;
            } // namespace iterator

            namespace type_traits
            {
                using namespace core::internal::type_traits;
            } // namespace type_traits

            namespace container 
            {
                using namespace core::internal::container;
                namespace base
                {
                    using namespace core::internal::container::base; 
                } // namespace base
                
            } // namespace container

            namespace scope {} // namespace scope

        } // namespace internal
    } // namespace std

} // namespace ustl



#endif