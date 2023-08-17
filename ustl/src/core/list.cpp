#include <ustl/core/internal/container/base/con_list_base.hpp>

using namespace ustl;
using namespace core;
using namespace internal;
using namespace container;
using namespace base;


typedef ListNodeBasic      Node;
typedef ListNodeBasic *    Ptr;
typedef ListHeader         Header;
typedef ListCompareBasic   Compare;


void 
Node::
    _M_hook_before(Ptr __p) USTL_NOEXCEPT
{
    _M_prev->_M_next = __p;        
    __p->_M_prev = _M_prev;
    _M_prev = __p;
    __p->_M_next = this;
} 


void
Node::
    _M_hook_after(Ptr __p) USTL_NOEXCEPT
{
    __p->_M_prev = this;
    __p->_M_next = _M_next;
    _M_next->_M_prev = __p;
    _M_next = __p;
}


void
Node::
    _M_unhook() USTL_NOEXCEPT
{
    _M_prev->_M_next = _M_next;        
    _M_next->_M_prev = _M_prev;
    _M_reset();
}


void
Header::
    _S_swap(Header &x, Header &y) USTL_NOEXCEPT
{
    if (0 != x._M_count() && 0 != y._M_count()) {
        auto __tmp {x};
        x._M_move(y);
        y._M_move(__tmp);
    }
    else if (0 == y._M_count()) {
        y._M_move(x);
    }
    else {
        x._M_move(y);
    }
}


void
base::ustl_list_splice(Ptr pos, Ptr start, Ptr finish) USTL_NOEXCEPT
{
    auto pos_prev = pos->prev();
    auto start_pre  = start->prev();
    auto finish_pre = finish->prev();

    start_pre->set_next(finish);
    finish->set_prev(start_pre);

    start->set_prev(pos_prev);
    pos_prev->set_next(start);

    pos->set_prev(finish_pre);
    finish_pre->set_next(pos);
}


void
base::ustl_list_merge(Header * x, Header * y, Compare &cmp) USTL_NOEXCEPT
{
    if (x == y) {
        return;
    }

    auto xfirst = x->next();
    auto xend   = x;
    auto yfirst = y->next();
    auto yend   = y;

    while (xfirst != xend && yfirst != yend) {
        if (cmp(xfirst, yfirst)) {
            xfirst = xfirst->next();
        }
        else {
            auto next = yfirst->next();
            ustl_list_splice(xfirst, yfirst, next);
            yfirst = next;
        }
    }

    if (yfirst != yend) {
        ustl_list_splice(xfirst, yfirst, yend);
    }

    x->_M_inc_size(y->_M_count());
    y->_M_reset();
}


void
base::ustl_list_sort(Header *header, Compare &cmp) USTL_NOEXCEPT
{
    if (2 > header->_M_count()) {
        return;
    }

    USTL_CONSTEXPR usize len = sizeof(usize) << 3;

    usize counter;
    usize fill_number = 0;
    Header z;
    Header y[len];
    auto tmp = header->next();

    do {
        header->_M_dec_size(1);
        auto last = tmp;
        tmp = tmp->_M_next;
        last->_M_unhook ();
        z._M_hook_before (last);
        z._M_set_count(1);

        for (counter = 0; 
             counter != fill_number && y[counter]._M_count();
            ++counter) {
            ustl_list_merge(&z, &y[counter], cmp);
        }

        Header::_S_swap(z, y[counter]);
        if (counter == fill_number) {
            ++fill_number;
        }

    } while  (0 != header->_M_count());

    for (counter = 0; counter != fill_number; ++counter) {
        ustl_list_merge (&z, &y[counter], cmp);
    }

    Header::_S_swap(*header, z);
}


void
base::ustl_list_reverse(Header *header) USTL_NOEXCEPT
{
    if (1 >= header->_M_count()) {
        return;
    }

    auto first = header->next();
    auto last  = header->prev();
    Ptr tmp;

    while  (first != last) {
        tmp = last;
        last = last->prev();
        tmp->_M_unhook();
        first->_M_hook_before(tmp);
    }
}