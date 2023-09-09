#include<iterator>
#include<vector>
// Define a struct for addition operation
template<typename T>
struct Add{
    T operator()(T a, T b){
        return a + b;
    }
};

// Define a struct for subtraction operation
template<typename T>
struct Sub{
    T operator()(T a, T b){
        return a - b;
    }
};

// Define a function to calculate the lowest bit
template<typename T>
T lowbit(T n){
    return n & (-n);
}

// Define a FenwickTree class
template<typename T, typename Op=Add<T>, typename RevOp=Sub<T>>
struct FenwickTree{
    private:
    Op op;
    RevOp rop;
    T* t;
    size_t n;
    public:
    // Constructor
    FenwickTree(size_t capacity, Op op=Op(), RevOp rop=RevOp()): op(op), rop(rop) {
        t = new T[capacity + 1];
        n = capacity;
    }
    // Destructor
    ~FenwickTree(){delete[] t;}
    // Constructor with iterator range
    template<typename Iter>
    FenwickTree(Iter first, Iter last, Op op=Op(), RevOp rop=RevOp()){
        Iter p = first;
        size_t dist = std::distance(first, last);
        FenwickTree(dist, op, rop);
        for(size_t i = 1; i <= n; i++){
            t[i] += *p;
            size_t j = i + lowbit(i);
            if(j <= dist) t[j] += t[i];
            p++;
        }
    }
    private:
    // Update the value at index x
    void _M_update(size_t x, T k){
        while(x <= n){
            t[x] = op(t[x], k);
            x += lowbit(x);
        }
    }
    // Query the sum at index 1 to k
    T _M_query(size_t k){
        T ret;
        while(k){
            ret = op(ret, t[k]);
            k -= lowbit(k);
        }
        return ret;
    }
    // Query the sum from index a to b
    T _M_query(size_t a, size_t b){
        return rop(_M_query(b), _M_query(a - 1));
    }
    public:
    // Update the value at index idx
    void update(size_t idx, T k){
        _M_update(idx + 1, k);
    }
    // Query the sum from index 1 to a
    T query(size_t a){
        return _M_query(a - 1);
    }
    // Query the sum from index a to b
    T query(size_t a, size_t b){
        return _M_query(a - 1, b - 1);
    }
};

// Example usage
int main() {
    vector<int> a{9,5,4,2,6};
    FenwickTree bit(a.begin(), a.end());
    cout<<bit.query(4)<<endl;
    return 0;
}
