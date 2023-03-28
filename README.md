# NameTable
Each compiler has a name table component that keeps track of a program's identifiers and their related information such as line number and scope. The objective of this assignment was to recreate a name table for the compiler, achieving optimal efficiency.

<h2>Approach</h2>
I created a struct Variables to record an identifier's name and line number. The variable would be placed into a bucket of the hashtable, with the line number as hash ID. I created a vector of iterators that points to each variable.

<h2>Time Complexity</h2>
With a vector of iterators, the time efficiency of the name table drastically improved. One naive approach was to maintain a vector of names and vector for line numbers. For the provided test case instruction mix, this took an average of 9200 ms. Meanwhile, the vector of iterators and hash table took an average of 90 ms. 

To see why:
```
enterScope() - O(1) //add new scope marker
exitScope() - O(N)  //remove all elements up to scope marker (inclusive)
declare() - O(N)    //check for existing variable name within scope
find() - O(N)       //search within bucket for match
  -vector:          //searches half of all entries in vector on average for match
  +hashtable        //due to good hash function, only searches a very small subset of entries
  ```
