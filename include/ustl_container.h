#ifndef __ustl_container_standard
#define __ustl_container_standard

/**
 * container
 */
#include "container/pair.h"
#include "container/tuple.h"
#include "container/slist.h"
#include "container/rbtree.h"
#include "container/avltree.h"
#include "container/vector.h"
#include "container/bvector.h"
#include "container/deque.h"
#include "container/list.h"
#include "container/string.h"

#include "container/map.h"
#include "container/set.h"
#include "container/multimap.h"
#include "container/multiset.h"
#include "container/hashtable.h"

/**
 * adapter
 */
#include "adapter/queue.h"
#include "adapter/stack.h"

namespace ustl
{
    /**
     *  header for ustl container standard
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     */
    typedef basic_string<char, ustl::allocator<char>>
        string;

    typedef basic_string<wchar_t, ustl::allocator<wchar_t>>
        wstring;

} // namespace ustl

#endif