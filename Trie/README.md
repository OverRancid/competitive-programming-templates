# Trie Data Structure
## Theory
[Theory](https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/) can only take us so far.

## Implementation
- ### Constructing
  Initialising a Trie allocates an empty TrieNode. The TrieNode subclass contains the following :
  - array of 26 TrieNode pointers initially set to null
  - integer count, counting the number of strings ending at that charachter initally set to 0.
  - integer prefix_count, counting the number of strings which have the current data as prefix initally set to 0.
  The TrieNode subclass also contains a boolean method `empty`. This method returns true if the prefix_count is 0. The prefix count is 0 iff all 26 pointers in the array are null.

  ```
    Trie var_name;
  ```

- ### Insert
  A string of lower case latin aplhabets can be added into the Trie using the `insert` method. This take $O(N)$ time and upto $O(NK)$ memory where $N$ is the size of the string and $K$ is the memory of each TrieNode.
  ```
    var.insert(str);
  ```

- ### Search and Search Prefix
  The method `search` can be used to determine the number of strings of a given data.
  The method `search_prefix` can be used to determine the number of strings that have a given data as their prefix.
  Both of these methods take $O(N)$ time.
  ```
    int num1 = var.search(str);
    int num2 = var.search_prefix(str);
  ```

- ### Delete
  The method `remove` can be used to delete a given string from the Trie. Special care must be taken while using this as if you pass a string which does not exist in the Trie, it will lead to unexpected behaviour. This method also deletes all pointers which are no longer needed. This is also an $O(N)$ process.
  
  ```
    var.remove(str);
  ```
