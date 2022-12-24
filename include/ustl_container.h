#ifndef __ustl_container_standard
#define __ustl_container_standard

/**
 * internal container
*/
#include "container/rbtree.h"       // red black tree
#include "container/avltree.h"      // avl tree

/**
 * container
 */
#include "container/pair.h"         // pair
#include "container/tuple.h"        // tuple (compile time container)
#include "container/slist.h"        // signle list
#include "container/vector.h"       // vector
#include "container/bvector.h"      // specialization vector for bool
#include "container/deque.h"        // Double Entry Queue
#include "container/list.h"         // bothway list
#include "container/string.h"       // String
#include "container/hashtable.h"    // Hash table [based on list and red black tree]

#include "container/map.h"          // ordered map based on red black tree
#include "container/set.h"          // ordered set based on red black tree
#include "container/multimap.h"     
#include "container/multiset.h"     
#include "container/unordered_map.h"        // unordered map based on hashtable
#include "container/unordered_set.h"        // unordered set based on hashtable
#include "container/unordered_multimap.h" 
#include "container/unordered_multiset.h"


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