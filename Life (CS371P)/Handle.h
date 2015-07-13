// ---------
// Handle.h
// ---------

#ifndef Handle_h
#define Handle_h

#include <algorithm> // swap

using namespace std;

template <typename T>
class Handle {
    friend bool operator == (const Handle& lhs, const Handle& rhs) {
        return (!lhs._p && !rhs._p) || (*lhs._p == *rhs._p);}

    friend bool operator != (const Handle& lhs, const Handle& rhs) {
        return !(lhs == rhs);}

    public:
        typedef T                 value_type;

        typedef value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef value_type&       reference;
        typedef const value_type& const_reference;

        pointer _p;

    protected:
        pointer get () {
            return _p;}

        const_pointer get () const {
            return _p;}

    public:
        Handle (pointer p) {
            _p = p;}

        Handle (const Handle& that) {
            if (!that._p)
                _p = 0;
            else
                _p = that._p->clone();}

        ~Handle () {
            delete _p;}

        Handle& operator = (Handle that) {
            swap(that);
            return *this;}

        void swap (Handle& that) {
            std::swap(_p, that._p);}};

#endif // Handle_h