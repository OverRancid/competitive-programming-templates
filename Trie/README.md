# Trie Data Structure
## Theory
[Theory](https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/) can only take us so far.

## Implementation
-### Constructing
  Initialising a Trie allocates an empty TrieNode. The TrieNode subclass contains the following :
  - array of 26 TrieNode pointers initially set to null
  - integer count, counting the number of strings ending at that charachter initally set to 0.
  - integer prefix_count, counting the number of strings which have the current data as prefix initally set to 0.
  The TrieNode subclass also contains a boolean method empty(). This method returns true if the prefix_count is 0. The prefix count is 0 iff all 26 pointers in the array are null.

  ```
    Trie var_name;
  ```
