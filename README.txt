Jeremy Spiro, Ravi Jain, rjain8@u.rochester.edu, CSC 254, MW 10:25-11:40, Prof. Michael Scott

In this assignment, we implemented a makeshift garbage collector in C++ utilizing Tombstones. Tombstones are a form of conservative collection that acts as an intermediary to handle checking for deallocation and referencing. 

-------------------------------------------------------------------------------------------------------

EXECUTION:

The test cases that the assignment came with can be compiled with "make x" and executed with "./x", where x is a test program (foo1 through foo8 in this case).


IMPLEMENTATION:

	Our first step was to implement the sample code given in the tombstones header file. We had to establish free as its own template and that returned void. Since it fell outside of the private scope of the tombstone, we had to ensure it kept its "friend" attribute in order to allow access to the references. The free template allowed us to check for the double deletion of pointers. The copy constructor copied a tombstone to another pointer and increment the reference count. Once the reference counts reaches 0, we would call the destructor method to deallocate the pointer. It outputs an error message and terminates if the memory was not successfully freed.  In general, our philosophy was to check for memory leaks by determining if a tombstone would still be accessible with unfreed memory, and checking for dangling pointers and invalid pointer operations by confirming that the pointer contains a valid reference.

Since tombstones are an intermediary step between the topmost pointer reference and the true location of the pointer, the actual data will have to be stored two pointers away from the Pointer<T> class, and the reference count will have to be stored one pointer away.  This is because multiple pointers pointing to the same address will have to be able to access the same refcount and data location.  To facilitate this, we created a separate class for a tombstone (as opposed to a struct or direct pointers) in the hopes that it would have the least implementational overhead.  The tombstone class is what holds the pointer address and the reference count.  Later on, we found that we had to add a boolean instance variable to check whether or not the address being pointed to held valid information (ex. if it had been freed or not), since we were otherwise unable to distinguish between a null and a dangling pointer, though besides that our implementation structure did not change significantly throughout the project.

	Our operator functions implement field dereferencing. We have try catch errors in place for when a null pointer is dereferenced. In assignment (=), we check the right hand and left hand sides of the equality. The (=) operator method additionally catches memory leaking before the assignment if the memory was not freed. Our other comparisons check if:
1) Pointer to pointer
2) Pointer to int
3) int to pointer
4) int to int (which is already handled by C++ and does no work on pointer comparisons, so no additional work needed to be done)



