template<typename T, T (*f)(T, T), T (*e)()> class SparseTable{
public:
    SparseTable(std::vector<T> arr){
        n = arr.size();
        k = 63-__builtin_clzll(1ULL*n);
        table = std::vector<std::vector<T>>(k+1, std::vector<T>(n+1));

        std::copy(arr.begin(), arr.end(), table[0].begin());

        for(int i = 1; i <= k; i++){
            for(int j = 0; j + (1<<i) <= n; j++){
                table[i][j] = f(table[i-1][j], table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    T query(int l, int r){
        int i = 63 - __builtin_clzll(1ULL*(r-l+1));
        return f(table[i][l], table[i][r - (1<<i) + 1]);
    }

private:
    std::vector<std::vector<T>> table;
    int k, n;
}
