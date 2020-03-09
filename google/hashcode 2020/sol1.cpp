#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define finline __attribute__((always_inline))
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << (x) << ", "
#define dblb(s) cout << "[" << (s) << "] "
#define dba(alias, x) cout << (alias) << ": " << (x) << ", "
template<typename F> inline string __generic_tostring(F f) { stringstream ss; ss << f; return ss.str(); }
template<typename F> inline string __join_comma(F f) {return __generic_tostring(f);}
template<typename F, typename... R> string __join_comma(F f, R... r) { return __generic_tostring(f) + ", " + __join_comma(r...); }
#define dbp(alias, ...) cout << (alias) << ": (" << __join_comma(__VA_ARGS__) << "), "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

const int MN = 1e5 + 1;
int B, L, D;
vi vals;

Cmpfn(bookCmpByVal, int) {
    return vals[a] < vals[b];
}

struct Library {
    int id;
    int sz, signupTime, maxScan;
    vi books;

    // other stuff
    int totVal;
    vi psum;
    ld heuristic;

    void read(istream &in) {
        in >> sz >> signupTime >> maxScan;
        books = vi(sz);
        repi(0, sz)
            in >> books[i];
        sort(all(books), bookCmpByVal);
        reverse(all(books));

        // val stuff
        for (auto x : books)
            totVal += vals[x];

        // psum
        psum.resize(sz);
        repi(0, sz)
            psum[i] = vals[books[i]];
        partial_sum(all(psum), psum.begin());

        // heuristic
        // int reqDays = (books.size() + maxScan - 1) / maxScan;
        heuristic = ld(totVal) / signupTime;
    }
    int take1() {
        int ret = books.back();
        books.pop_back();
        return vals[ret];
    }
    int take() {
        int ret = 0;
        repi(0, maxScan)
            ret += take1();
        return ret;
    }
};

struct BookList {
    int libraryId;
    vi books;
    int size() { return books.size(); }
};
struct Answer {
    int tot;
    vec<BookList> lists;
    void init() {
        tot = 0;
    }
    void init(vec<BookList> &_) {
        init();
        lists = _;
        for (auto x : lists)
            for (auto xx : x.books)
                tot += vals[xx];
    }
    int size() { return lists.size(); }
};

vec<Library> libraries;

Cmpfn(cmpByTot, Library) {
    return a.totVal < b.totVal;
}

Cmpfn(cmpByHeuristic, Library) {
    return a.heuristic < b.heuristic;
}

Cmpfn(ansCmpByTot, Answer) {
    return a.tot < b.tot;
}

template <typename T> void shuffle(vec<T> &v, int times) {
    static mt19937 mt;
    uniform_int_distribution<int> dis(0, v.size() - 1);
    while (times--) {
        swap(v[dis(mt)], v[dis(mt)]);
    }
}

bitset<MN> used;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(B, L, D);
    vals.resize(B);
    int trueTot = 0;
    repi(0, B) {
        scan(vals[i]);
        trueTot += vals[i];
    }
    libraries.resize(L);
    repi(0, L) {
        libraries[i].read(cin);
        libraries[i].id = i;
    }

    // sort libraries
    sort(all(libraries), cmpByHeuristic);
    reverse(all(libraries));
    
    // calc
    int trials = 10000;
    Answer best; best.init();
    while (trials--) {
        // setup book list
        // shuffle(libraries, 30);

        // init other variables
        used.reset();

        // now we do stuff
        Answer curAns;
        vec<BookList> bookLists;
        int start = 0;
        for (auto &lib : libraries) {
            start += lib.signupTime;
            if (start >= D) break;
            int left = D - start, canDo = min(int(lib.books.size()), left * lib.maxScan);
            // db(start); db(left); db(D); dbln;
            
            // account for this
            if (canDo > 0) {
                BookList bl;
                bl.libraryId = lib.id;
                for (int book : lib.books) {
                    if (int(bl.books.size()) == canDo) break;
                    if (!used[book]) {
                        bl.books.pb(book);
                        used[book] = true;
                    }
                }
                if (!bl.books.empty())
                    bookLists.pb(bl);
            }
        }
        curAns.init(bookLists);

        best = max(best, curAns, ansCmpByTot);
    }

    // print
    println(best.size());
    for (auto lib : best.lists) {
        println(lib.libraryId, lib.size());
        for (int book : lib.books)
            print(book, ' ');
        print('\n');
    }

    cerr << "Total of all books: " << trueTot << endl;
    cerr << "Got total: " << best.tot << endl;

    return 0;
}
