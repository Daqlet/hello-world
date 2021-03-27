//https://codeforces.com/edu/course/2/lesson/5/4/practice
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct segtree
{
    vector<pair<ll, ll>> tree;
    vector<pair<ll, ll>> Tree;
    int size;
    void init(int n)
    {
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size, {0, 0});
        Tree.assign(2*size, {0, 0});
    }
    void build(vector<int>& a)
    {
        init((int)a.size());
        build(a, 0, 0, size);
    }
    void build(vector<int>& a, int x, int l, int r)
    {
        if(r - l == 1)
        {
            if(l < (int)a.size()) 
            {
                tree[x].first = a[l];
                Tree[x].first = a[l] *1ll* r;
            }
            return;
        }
        int m = l + (r - l)/2;
        build(a, 2*x+1, l, m);
        build(a, 2*x+2, m, r);
        tree[x].first = tree[2*x+1].first + tree[2*x+2].first;
        Tree[x].first = Tree[2*x+1].first + Tree[2*x+2].first; 
    }
    void set(int d, int l, int r)
    {
        set(d, l, r, 0, 0, size);
    }
    void set(int d, int l, int r, int x, int lx, int rx)
    {
        prop(x, lx, rx);
        if(rx <= l || lx >= r) return;
        if(lx >= l && rx <= r) 
        {
            tree[x].second += d;
            Tree[x].second += d;
            prop(x, lx, rx);
            return;
        }
        int m = lx + (rx - lx) / 2;
        set(d, l, r, 2*x+1, lx, m);
        set(d, l, r, 2*x+2, m, rx);
        tree[x].first = tree[2*x+1].first + tree[2*x+2].first;
        Tree[x].first = Tree[2*x+1].first + Tree[2*x+2].first;
    }
    void prop(int x, int l, int r)
    {
        if(tree[x].second)
        {
            if(r - l > 1)
            {
                tree[2*x+1].second += tree[x].second; 
                tree[2*x+2].second += tree[x].second;
                Tree[2*x+1].second += Tree[x].second;
                Tree[2*x+2].second += Tree[x].second;
            }
            tree[x].first += tree[x].second*(r - l);
            Tree[x].first += Tree[x].second*(r*1ll*(r+1)/2 - (l*1ll*(l+1)/2));
            tree[x].second = Tree[x].second = 0;
        }
    }
    ll sum(int l, int r)
    {
        return sum(l, r, 0, 0, size);
    }
    ll sum(int l, int r, int x, int lx, int rx)
    {
        prop(x, lx, rx);
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r)
        {
            return Tree[x].first - tree[x].first*l;
        }
        int m = lx + (rx - lx)/2;
        ll s1 = sum(l, r, 2*x+1, lx, m);
        ll s2 = sum(l, r, 2*x+2, m, rx);
        return s1 + s2;
    }
    void print()
    {
        for(int i = 0; i < 2*size; ++i) cout << tree[i].first << " ";
        cout << endl;
        for(int i = 0; i < 2*size; ++i) cout << Tree[i].first << " ";
        cout << endl;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);    
    //int l, r; cin >> l >> r;
    //cout << (r*(r-1)/2 - (l*(l-1)/2)) << endl;
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    segtree seg; seg.build(a);
    //seg.print();
    while(m--)
    {
        int t; cin >> t;
        if(t == 1)
        {
            int l, r, d; cin >> l >> r >> d;
            seg.set(d, l-1, r);
        }
        else
        {
            int l, r; cin >> l >> r;
            cout << seg.sum(l-1, r) << endl;
        }
        //seg.print();
    }    
    return 0;
}
