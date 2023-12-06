//OverRancid#0590
#include <bits/stdc++.h>    //Parental Advisory
using namespace std;       //Explicit Content

template<typename T> class SegmentTree{
public:
    SegmentTree(vector<T> &arr, int x=0){
        segTree.clear();
        int64_t n = arr.size(), i;
        type = x;
        __builtin_popcount(n)==1? N=n: N=1<<(64-__builtin_clzll(n));
        segTree.reserve(N<<1);
        for(i=0; i<N; i++){
            i<n? segTree[i+N] = arr[i]: segTree[i+N]=type_initializer();
        }
        for(i=N-1; i>0; i--){
            segTree[i] = type_updater(segTree[i<<1], segTree[(i<<1)^1]);
        }    
    }
    void update(int idx, T value){    //sets arr[idx] = value.
        idx += N;
        segTree[idx] = value;
        for(idx>>=1; idx; idx>>=1){
            segTree[idx] = type_updater(segTree[idx<<1], segTree[(idx<<1)^1]);
        }
    }
    T query(int l, int r){           //returns query on [l, r] subset of [0, n-1]
        T sum = type_initializer();
        l+=N;   r+=N;
        while(l<=r){
            if(l&1) sum = type_updater(sum, segTree[l++]);
            if(!(r&1)) sum = type_updater(sum, segTree[r--]);
            l>>=1;   r>>=1;
        }
        return sum;
    }
private:
    T type_updater(T val1, T val2){
        switch(type){
            case -1:
                return max(val1, val2);
            case 0:
                return val1+val2;
            case 1:
                return __gcd(val1, val2);
            case 2:
                return val1 ^ val2;
            case 3:
                return val1 | val2;
            case 4:
                return val1 * val2;
            case 5:
                return val1 & val2;
            case 6:
                return min(val1, val2);
            default:
                return -1;
        }
    }
    T type_initializer(){
        switch(type){
        case -1:
            return INT_MIN; //range max
        case 0:             //range sum
        case 1:             //range gcd
        case 2:             //range XOR
        case 3:             //range OR
            return 0;
        case 4:             //range product
            return 1;
        case 5:             //range AND
        case 6:             //range min
            return INT_MAX; 
        default:            //error catching
            return -1;
        }
    }
    int N;
    short type;
    vector<T> segTree;
};
