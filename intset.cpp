// file IntSet.cpp
#include "intset.h"
#include <algorithm>

// ---------------------------------------------------------------------------
// Constructor
// Uses default values to account for any negative values given
// Expects only integers given to constructor, no chars or floats allowed 
IntSet::IntSet(int num1, int num2, int num3, int num4, int num5) {

    size = std::max({num1, num2, num3, num4, num5}) + 1;

    if (size <= 0) {
        size = 1;
    }
    IntSetPtr = new bool[size];
    for (int i = 0; i < size; i++) {
        IntSetPtr[i] = false;
    }
    if (num1 >= 0) {
        this->IntSetPtr[num1] = true;
    }
    if (num2 >= 0) {
        this->IntSetPtr[num2] = true;
    }
    if (num3 >= 0) {
        this->IntSetPtr[num3] = true;
    }
    if (num4 >= 0) {
        this->IntSetPtr[num4] = true;
    }
    if (num5 >= 0) {
        this->IntSetPtr[num5] = true;
    }
}

// ---------------------------------------------------------------------------
// Destructor
// Destructor for class IntSet
IntSet::~IntSet() {
    delete[] IntSetPtr; // reclaim space for IntSet
    IntSetPtr = nullptr;
}

// ---------------------------------------------------------------------------
// Copy constructor for class IntSet
// simply calls copy method
IntSet::IntSet(const IntSet &other) { copy(other); }

//----------------------------------------------------------------------------
// operator+
// overloaded +: union of two sets
// the set of elements that are contained in either or both sets (everything)
IntSet IntSet::operator+(const IntSet &other) const {
    IntSet unionSet;
    for (int i = 0; i < size; i++) {
        if (isInSet(i)) {
        unionSet.insert(i);
        }
    }
    for (int j = 0; j < other.getSize(); j++) {
        if (other.isInSet(j)) {
        unionSet.insert(j);
        }
    }
    return unionSet;
}

//----------------------------------------------------------------------------
// operator*
// overloaded *:
// returns the intersection of two sets.
// intersection is set of all elements common to both sets
IntSet IntSet::operator*(const IntSet &other) const {
    IntSet intersection;
    int smallerSize = std::min(size, other.getSize());
    for (int i = 0; i < smallerSize; i++) {
        if (IntSetPtr[i] && other.IntSetPtr[i]) {
        intersection.insert(i);
        }
    }
    return intersection;
}

//----------------------------------------------------------------------------
// operator-
// returns difference of two sets, current object and parameter
// Example: A-B, Result is a new set with all the elements that are in set A
// but not set B
IntSet IntSet::operator-(const IntSet &other) const {
    IntSet difference;
    for (int i = 0; i < size; i++) {
        // if element is in current but not in other, add to result
        if (isInSet(i) && !other.isInSet(i)) {
        difference.insert(i);
        }
    }
    return difference;
}

// ----------------------------------------------------------------------------
// operator+=
// returns union set between A and B (e.g. A += B returns set of all values
// found in either A, B, or both sets)
IntSet& IntSet::operator+=(const IntSet &other) {
    for (int i = 0; i < other.getSize(); i++) {
        if (other.isInSet(i)) {
        this->insert(i);
        }
    }
    return *this;
}

// ----------------------------------------------------------------------------
// operator*=
// returns intersection set between A and B (e.g. A *= B returns set of all
// values found in A but not found in B)
IntSet& IntSet::operator*=(const IntSet &other) {
    int smallerSize = std::min(size, other.getSize());
    for (int i = 0; i < smallerSize; i++) {
        // if number is present in both, it will stay true in IntSetPtr[i]
        if (isInSet(i) && other.isInSet(i)) {
        continue;
        } else { // otherwise, remove it from this IntSet
        remove(i);
        }
    }
    return *this;
}

// ----------------------------------------------------------------------------
// operator-=: returns difference of two sets, current object and parameter
// Example: A -= B, A now stores a set with all the elements that were in
// set A but not set B
IntSet& IntSet::operator-=(const IntSet &other) {
    // logic: if it's in both sets, remove it
    //        if it's in current set and not other set, keep it
    //        if it's in other set and not current set, does matter
    for (int i = 0; i < size; i++) {
        if (isInSet(i) && other.isInSet(i)) {
            remove(i);
        }
    }
    return *this;
}

// ---------------------------------------------------------------------------
// operator=
// Overloaded assignment operator.
IntSet &IntSet::operator=(const IntSet &other) {
    if (&other != this) { // check for self-assignment
        delete[] IntSetPtr; // reclaim space
        copy(other);
    }

    return *this; // enables x = y = z;
}

// ----------------------------------------------------------------------------
// operator==
// Determine if two sets are equal.
bool IntSet::operator==(const IntSet &other) const {
    if (size != other.size)
        return false; // IntSets of different sizes

    // search through both arrays and check if any element is mismatched
    for (int i = 0; i < size; i++)
        if (IntSetPtr[i] != other.IntSetPtr[i])
        return false;
    // IntSets are not equal if mismatched
    return true; // IntSets are equal if no mismatch occurs
}

// ----------------------------------------------------------------------------
// operator!=
// Determine if two IntSets are not equal.
bool IntSet::operator!=(const IntSet &other) const {
    return !(*this == other); // call operator== and return opposite
}

// ----------------------------------------------------------------------------
// getSize
// Return the size of the IntSet
int IntSet::getSize() const { return size; }

// ----------------------------------------------------------------------------
// insert
// an element into a set, has bool return value,,
// e.g., bool success = A.insert(5);  (Note:  ignore invalid integers,
// return false, e.g., bool success = A.insert(-10);
// If a value is already in the set and is inserted, return true).
bool IntSet::insert(int num) {
    bool inserted;
    if (num < 0) { // invalid insert attempt (negative)
        inserted = false;
    } else if (size <= num) { // old bool array too small

        int oldSize = size;
        size = num + 1; // new size
        bool *newSet = new bool[size];
        // copy all old elements over
        for (int i = 0; i < oldSize; i++) {
        newSet[i] = IntSetPtr[i];
        }
        // fill new array ~starting from end of old array
        for (int i = oldSize; i < size; i++) {
        newSet[i] = false;
        }
        newSet[num] = true; // update new position
        delete[] IntSetPtr; // free space
        IntSetPtr = newSet; // redirect pointer
        inserted = true;
    } else { // fits within current bool array size
        IntSetPtr[num] = true;
        inserted = true;
    }
    return inserted;
}

// ---------------------------------------------------------------------------
// remove
// remove an element from a set, bool return value,
// e.g.,  bool success = A.remove(10); (Note:  ignore invalid
// integers, return false, e.g,.  bool success = A.remove(-10); ).
// note: does not change internal size if largest element is removed
bool IntSet::remove(int num) {
    bool result;
    if (!isInSet(num)) {
        result = false;
    } else {
        IntSetPtr[num] = false;
        result = true;
    }
    return result;
}

// ---------------------------------------------------------------------------
// isEmpty
// determine if a set is empty or not,
// bool return value e.g. if (A.isEmpty())
bool IntSet::isEmpty() {
    bool result;
    if (size == 1) {
        result = true;
    } else {
        result = false;
    }
    return result;
}

// ---------------------------------------------------------------------------
// isInSet
// determine if an integer is in the set or not,
// e.g.,  if (A.isInSet(5)) (Note: returns false for invalid integers)
bool IntSet::isInSet(int num) const {
    if (num < 0 || num >= size) { // checking bounds
        return false;
    } else {
        return IntSetPtr[num];
    }
}

// ---------------------------------------------------------------------------
// copy
// Called by copy constructor and operator= to do actual copying of IntSet
// Size the IntSet, allocate memory, and copy contents of parameter's IntSet
void IntSet::copy(const IntSet &toCopy) {
    size = toCopy.getSize();
    IntSetPtr = new bool[size];
    for (int i = 0; i < size; i++) {
        IntSetPtr[i] = toCopy.IntSetPtr[i];
    }
}

// ----------------------------------------------------------------------------
// operator>>
// Overloaded input operator for class IntSet;
// inputs values for entire IntSet.
std::istream &operator>>(std::istream &input, IntSet &a) {
  int temp;
  bool insertSuccess;
  input >> temp; // priming the while loop
  while (temp != -1) {
    insertSuccess = a.insert(temp);
    input >> temp; // get next one to repeat loop
  }
  return input;
}

// ----------------------------------------------------------------------------
// operator<<
// Overloaded output operator for class IntSet
std::ostream &operator<<(std::ostream &output, const IntSet &a) {
  output << '{';
  for (int i = 0; i < a.size; i++) {
    if (a.IntSetPtr[i]) {
      output << ' ' << i;
    }
  }
  output << '}';
  return output; // e.g., enables cout << x << y;
}
