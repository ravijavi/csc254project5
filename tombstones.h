/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

#include <iostream>
template <class T> class Tombstone;
template <class T> class Pointer;
template <class T> void free(Pointer<T>&pointer) {
    if (pointer.tomb->ptr != 0) {
        //std::cout << "deleted\n";
        delete pointer.tomb->ptr;
        pointer.tomb->ptr = 0;
    } else {
        std::cerr << "ERROR: double pointer deletion attempt\n";
        std::exit(-1);
    }
    // check for double deletion of pointers
    
}

template<class T>
class Tombstone {
public:
    T* ptr;
    int refcount;
    Tombstone<T>() {
        //std::cout << "new empty tombstone\n";
        ptr = 0;
        refcount = 0;
    }
    Tombstone<T>(T* p) {
        //std::cout << "new nonempty tombstone\n";
        ptr = p;
        refcount = 1;
    }
};

template <class T>
class Pointer {
private:
    Tombstone<T>* tomb;

public:
    // default constructor
    Pointer<T>() {
        //std::cout << "default constructor\n";
        tomb = new Tombstone<T>();
    }
    
    // copy construtor
    Pointer<T>(Pointer<T>&pointer) {
        //std::cout << "copy constructor\n";
        tomb = pointer.tomb;
        tomb->refcount++;
    }
    
    // bootstrapping constructor
    Pointer<T>(T* p) {
        //std::cout << "bootstrapping constructor\n";
        tomb = new Tombstone<T>(p);
    }
        // argument should always be a call to new
        
        
    // destructor
    ~Pointer<T>() {
        //std::cout << "destructor executed\n";
        tomb->refcount--;
        // delete once the reference count reaches zero
        if (tomb->refcount == 0) { // TODO: replace with a call to free()?
            delete tomb->ptr;
            delete tomb;
        }
        
    }
    
    // dereferencing
    T& operator*() const {
        try {
            //std::cout << "dereference: " << *(tomb->ptr) << "\n";
            return *(tomb->ptr);
        } catch (const char* msg) {
            std::cerr << msg << "\n";
            std::cerr << "dereferenced a null pointer\n\n";
            std::exit(-1);
        }
    }
    
    // field dereferencing
    T* operator->() const;
    
    // assignment (=)
    Pointer<T>& operator=(const Pointer<T>&rhs) {
        //std::cout << "assignment\n";
        //std::cout << "rhs:  " << *(rhs.tomb->ptr) << "\n";
        this->tomb->refcount--;
        this->tomb = rhs.tomb;
        //std::cout <<"this: " << *(tomb->ptr) << "\n";
        rhs.tomb->refcount++;
    }
    
    // delete pointed-at object
    // this isn't a declaration, it just declares the outside one as a friend
    friend void free<T>(Pointer<T>&);
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    
    
    // equality comparisons:
    bool operator==(const Pointer<T>&rhs) const {
        //std::cout << "== with pointers\n";
        return tomb->ptr == rhs.tomb->ptr; // TODO: is this comparing the address, not the value?
    }
    
    bool operator!=(const Pointer<T>&rhs) const {
        //std::cout << "left:  " << tomb->ptr << "\n";
        //std::cout << "right: " << rhs.tomb->ptr << "\n";
        return tomb->ptr != rhs.tomb->ptr; // TODO: same as above
    }
    // true iff Pointer is null and int is zero
    bool operator==(const int rhs) const {
        //std::cout << "== with int rhs\n";
        return tomb->ptr == 0 && rhs == 0;
    }
    //friend bool operator==(const int lhs, Pointer<T>&rhs) {
    //    return rhs.pointer == 0 && lhs == 0;
    //}
    
    
    // false iff Pointer is null and int is zero
    bool operator!=(const int rhs) const {
        //std::cout << "!= with int rhs\n";
        return tomb->ptr != 0 || rhs != 0;
    }
    //friend bool operator!=(const int lhs, Pointer<T>&rhs) {
    //    return rhs.pointer != 0 || lhs != 0;
    //}
};


#endif // __TOMBSTONES_H__
