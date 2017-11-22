/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

#define NIL 0

#include <iostream>
template <class T> class Tombstone;
template <class T> class Pointer;
template <class T> void free(Pointer<T>&pointer) {
    if (pointer.tomb->ptr != NIL) {
        std::cout << "deleted\n";
        delete pointer.tomb->ptr;
        pointer.tomb->ptr = NIL;
    } else {
        std::cerr << "ERROR: attempted to free an invalid pointer\n";
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
        ptr = NIL;
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
        std::cout << "default constructor\n";
        tomb = new Tombstone<T>();
    }
    
    // copy construtor
    Pointer<T>(Pointer<T>&pointer) {
        std::cout << "copy constructor\n";
        if (pointer.tomb->ptr == NIL) {
            std::cerr << "ERROR: copied a dereferenced pointer\n";
            std::exit(-1);
        }
        tomb = pointer.tomb;
        tomb->refcount++;
    }
    
    // bootstrapping constructor
    Pointer<T>(T* p) {
        std::cout << "bootstrapping constructor\n";
        tomb = new Tombstone<T>(p);
    }
        // argument should always be a call to new
        
        
    // destructor
    ~Pointer<T>() {
        //std::cout << "destructor executed, " << "value=" << (tomb->ptr == 0 ? "NULL" : std::to_string(*(tomb->ptr))) << "\n";
        
        tomb->refcount--;
        std::cout << "new refcount: " << tomb->refcount << "\n";
        // delete once the reference count reaches zero
        if (tomb->refcount <= 0) { // TODO: replace with a call to free()?
            if (tomb->ptr != NIL) { // check if memory was freed properly
                std::cerr << "ERROR: memory not freed\n";
                std::exit(-1);
            }
            delete tomb->ptr;
            delete tomb;
        }
        
    }
    
    // dereferencing
    T& operator*() const {
        if (tomb->ptr == NIL) {
            std::cerr << "ERROR: dangling pointer dereferenced\n";
            std::exit(-1);
        }
        try {
            //std::cout << "dereference: " << *(tomb->ptr) << "\n";
            std::cout << "dangling?  " << (tomb->ptr == NIL) << "\n";
            return *(tomb->ptr);
        } catch (const char* msg) {
            std::cerr << msg << "\n";
            std::cerr << "dereferenced a null pointer\n\n";
            std::exit(-1);
        }
    }
    
    // field dereferencing
    T* operator->() const {
        try {
            return tomb->ptr;
        } catch (const char* msg) {
            std::cerr << "ERROR: field dereferenced a null pointer\n";
            std::exit(-1);
        }
    }
    
    // assignment (=)
    Pointer<T>& operator=(const Pointer<T>&rhs) {
        std::cout << "assignment\n";
        //std::cout << "rhs:  " << *(rhs.tomb->ptr) << "\n";
        this->tomb->refcount--;
        // check if this would set refcount to 0 and create a memory leak
        if (this->tomb->refcount <= 0) {
            std::cerr << "ERROR: memory leak from not freeing memory before assignment\n";
            std::exit(-1);
        }
        
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
        return tomb->ptr == NIL && rhs == 0;
    }
    friend bool operator==(const int lhs, Pointer<T>&rhs) {
        return rhs.pointer == NIL && lhs == 0;
    }
    
    
    // false iff Pointer is null and int is zero
    bool operator!=(const int rhs) const {
        //std::cout << "!= with int rhs\n";
        return tomb->ptr != NIL || rhs != 0;
    }
    friend bool operator!=(const int lhs, Pointer<T>&rhs) {
        return rhs.pointer != NIL || lhs != 0;
    }
};


#endif // __TOMBSTONES_H__
