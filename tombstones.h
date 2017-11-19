/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__

#define NULL 0

template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

template <class T>
class Pointer {
private:
    T* pointer;

public:
    // default constructor
    Pointer<T>() {
        pointer = NULL;
    }
    
    // copy construtor
    Pointer<T>(Pointer<T>&p) {
        pointer = &p;
    }
    
    // bootstrapping constructor
    Pointer<T>(T* p) {
        pointer = p
    }
        // argument should always be a call to new
        
        
    // destructor
    ~Pointer<T>() {
        ~pointer();
    }
    
    // dereferencing
    T& operator*() const;
    
    // field dereferencing
    T* operator->() const;
    
    // assignment
    Pointer<T>& operator=(const Pointer<T>&);
    
    // delete pointed-at object
    friend void free<T>(Pointer<T>&);
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    
    
    // equality comparisons:
    bool operator==(const Pointer<T>&) const;
    bool operator!=(const Pointer<T>&) const;
    bool operator==(const int) const;
        // true iff Pointer is null and int is zero
    bool operator!=(const int) const;
        // false iff Pointer is null and int is zero
};


#endif // __TOMBSTONES_H__
