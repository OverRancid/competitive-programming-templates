# Segment Trees
## Theory
[Theory](https://www.geeksforgeeks.org/segment-tree-data-structure/) can only take us so far.
## Implementation

 - ### Types
	A segment tree can answer various types of range queries. Various queries have been efficiently implemented. The type of query has to be mentioned when building the tree.
	
	|code| query type|
	|--|--|
	|-1|range maximum|
	| 0|range sum (default) |
	| 1|range gcd |
	| 2|range XOR |
	| 3|range OR |
	| 4|range product |
	| 5|range AND |
	| 6|range minimum |
 - ### Constructing
   	A segment tree can be constructed from a given array in $\Theta(n)$ time and $\Theta(2^{\lceil\log_2{n}\rceil}) \approx \Theta(n)$ space. 
	The list of allowed types are:
	 - int types: short, int, long, long long and their unsigned counterparts.
	 - float types: float, double, long double - only on select queries.


	```cpp
 	SegmentTree<type_T> var_name(vector<T>&arr, int type);
 	SegmentTree<long long> tree(vec);
	```
	By default the type is set to 0 - range sum. Other trees can be constructed by passing the corresponding type value.
	```cpp
	SegmentTree<long long> tree(vec, 2); //tree for range xor type queries
	```
- ### Query
	The ranged query is answered for $[l, r] \subset [0, n-1]$ in $\mathcal{O}(\log{n})$.
	The function returns the query, without printing anything.
	
	Note the 0 based indexing and closed range.
	```cpp
	type_T answer = tree.query(3, 5); 
	//returns query for vec[3] to vec[5]
	```
- ### Update
	A point update can be made to any index $i \in [0, n-1]$ in $\mathcal{O}(\log{n})$. 
	
	Note the 0 based indexing.
	```cpp
	type_T value;
		//initialize value
	tree.update(i, value);
	```
	The update sets the value of `vec[i]` equal to the passed `value` and does not increment it. To increment the value using the current implementation, we would have to first fetch the value stored in the index and adjust our function accordingly.
	```cpp
	type_T temp = tree.query(i, i);
	tree.update(i, value + temp);
	```
	
