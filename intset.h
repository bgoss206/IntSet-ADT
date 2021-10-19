//---------------------------------------------------------------------------
/**
 * @file intset.h
 * @brief header file for IntSet class
 * @author Braxton Goss
 */
//---------------------------------------------------------------------------
// IntSet class:
// Object that contains a set of integers. all integers in the set are unique
// and there are no duplicates as it is implemented. Sets can be instantiated
// with 0 to 5 integers. Unset parameters and negatives are ignored. 
// All normal operators (insert, remove, +, -, *, =, +=, *=, -=, ==)

// Assumptions/implementation:
//   -- implemented using a dynamic bool array
//   -- if no parameters are passed, size is set to 1 
//   -- all unpassed parameters or negatives are set to 0 in bool array 
//      to represent that they are not in the set
//   -- user must enter valid integers when using >>
//   -- in <<, only boolean true in the array are displayed between {}
//   -- two IntSets are not considered equal if their size values differ 
//      even if their IntSet is the same after manipulation. 
//      This practice saves unnecessary new and delete operations to resize
//      the internal array. 
//---------------------------------------------------------------------------

#ifndef INTSET_H
#define INTSET_H

#include <iostream>

class IntSet {
    /* operator>>
    // Overloaded input operator for class IntSet; 
    // @pre insertions must be integers, negatives are ingored
    // @post: integers are inserted into the set, regardless of size
    // *this contains all ints entered by user (except -1 sentinal)
    */
    friend std::istream &operator>>(std::istream &input, IntSet &a);

    /* operator<<
    // Overloaded output operator for class IntSet
    // @pre cin >> IntSet *this is called
    // @post 
    */
    friend std::ostream &operator<<(std::ostream &input, const IntSet &a);

public:
    
    /* Constructor with 5 default values
    // @pre none
    // @post object instantiated, can take any 5 parameters, including 
    // negatives. Negatives will be ignored. integers only accepted.
    */
    IntSet(int num1 = -1, int num2 = -1, int num3 = -1, int num4 = -1,
            int num5 = -1);

    
    /* Copy Constructor
    // @pre object passed is properly declared & instantiated 
    // @post deep copy returned to *this object with same set and size
    */
    IntSet(const IntSet &);

    
    /* Destructor
    // @pre IntSetPtr points to bool array memory on the heap
    // @post IntSetPtr is deallocated and set to nullptr
    */
    ~IntSet();

    
    /* operator+
    // @pre both objects are instantiated IntSets
    // @post returned IntSet is a copy of *this and other's intersection       
    // result contains a set of all values in both sets (no duplicates)
    // bool return value e.g. if (A.isEmpty())
    */
    IntSet operator+(const IntSet &other) const;

    
    /* operator*
    // @pre both objects are instantiated 
    // @post returned IntSet is a copy of *this and &other
    // set contains all values in *this that are also in &other
    */
    IntSet operator*(const IntSet &other) const;

    
    /* operator-
    // @pre objects are both instantiated
    // @post returned IntSet is a new set with all numbers that
    // are in *this but not &other
    */
    IntSet operator-(const IntSet &other) const;

    
    /* operator+=
    // @pre both *this and &other are instantiated
    // @post *this will contain all numbers already in it, and all numbers
    // that were in &other. (set will contain no duplicates)
    */
    IntSet& operator+=(const IntSet &other);

    
    /* operator*=
    // @pre both *this and &other are instantiated
    // @post *this will contain all numbers that appear in both
    // itself and &other. All other numbers are removed from *this
    */
    IntSet& operator*=(const IntSet &other);


    /* operator-=
    // @pre both *this and &other are instantiated
    // @post *this will contain all numbers in itself but not in &other
    */
    IntSet& operator-=(const IntSet &other);

    
    /* operator=
    // @pre both objects are instantiated
    // @post *this will be the same IntSet as right, copy() called
    */
    IntSet& operator=(const IntSet &other);


    /* operator==
    // @pre both sets are instantiated 
    // @post bool return if sizes are different, automatically false.
    // if any part of the set is different than the other, false.
    // true only if sets are exactly the same (including size value)
    */
    bool operator==(const IntSet &other) const;


    /* operator!=
    // @pre both sets are instantiated
    // @post opposite of == method. bool returned.
    */

    bool operator!=(const IntSet &other) const;


    /* insert: insert an element into a set, bool return 
    // @pre integer parameter, object is instantiated 
    // @post if number is successfully inserted, return true. False if not.
    // If a value is already in the set and is inserted, return true.
    */
    bool insert(int num);


    /* remove: remove element from set, bool return
    // @pre integer parameter, object is instantiated
    // @post returns bool of removal outcome
    */
    bool remove(int num);

    /*determine if a set is empty or not,
    // @pre IntSet object is instantiated 
    // @post true if empty, false if not empty.
    */
    bool isEmpty();


    /* isInSet: determine if an integer is in the set 
    // @pre parameter is an int and set is instantiated
    // @post returns bool if parameter num is in set
    */
    bool isInSet(int num) const;


    /* getSize: Get the size of the IntSet
    // @pre IntSet is instantiated (any size)
    // @post Returns the size of the IntSet, size is 1 if empty
    // size remains the same if large item is removed 
    // e.g a.size = 50001, a.remove(50000), a.size = 50001
    */
    int getSize() const;

private:
    bool *IntSetPtr; // pointer to bool array of IntSet
    int size;        // size of the IntSet

    /*determine if a set is empty or not,
    // @pre 
    // @post
    // bool return value e.g. if (A.isEmpty())
    */
    // copy
    // used to copy a new IntSet to the current object
    // used in copy constructor and operator=
    void copy(const IntSet &toCopy);
};

#endif
