#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

const int N = 1e5+5;

struct Node{
    int min = N, max = -1;
    std::unordered_map<int , int> f;
};

int n,Q,a[N];
Node tree[4*N];

void build_tree(int node, int start, int end){
    if ( start == end ){
        tree[node].min = tree[node].max = a[start];
        tree[node].f[a[start]] = 1;
    }
    else{
        int mid = (start + end) / 2;
        build_tree(2*node, start, mid);
        build_tree(2*node + 1, mid + 1, end);
        tree[node].min = std::min(tree[2*node].min, tree[2*node+1].min);
        tree[node].max = std::max(tree[2*node].max, tree[2*node+1].max);
        tree[node].f = tree[2*node].f;
        for ( const auto& [number, freq] : tree[2*node+1].f ){
            tree[node].f[number] += freq;
        }
    }
}

Node query(int node, int start, int end, int x, int y) {
    if (y < start || end < x) return Node();
    if (x <= start && end <= y) return tree[node];
    int mid = (start + end) / 2;
    // std::cout << "query(" << node << ' ' << start << ' ' << end << ' ' << x << ' ' << y << ")\n";
    Node left = query(2 * node, start, mid, x, y);
    Node right = query(2 * node + 1, mid + 1, end, x, y);
    Node res;
    res.min = std::min(left.min, right.min);
    res.max = std::max(left.max, right.max);
    res.f = left.f;
    for ( const auto& [number, freq] : right.f ){
        res.f[number] += freq;
    }

    return res;
}

int main(){
    std::cin >> n;

    for ( int i = 0; i < n; i++ ){
        std::cin >> a[i];
    }

    build_tree(1, 0, n-1);

    for ( int i = 1; i <= 4*n+1; i++ ){
        // std::cout << i << ": " << tree[i].min << '|' << tree[i].max << "\n";
    }

    std::cin >> Q;

    while(Q--){
        int x,y;
        std::cin >> x >> y;
        x--; y--;

        Node result = query(1, 0, n-1, x, y);
        // std::cout << "Node result: " << result.min << '|' << result.max << '|' << result.f.size() << '\n';
        int len = y-x + 1;
        if( result.max - result.min + 1 == len && result.f.size() == len){
            std::cout << 1;
        }
        else{
            std::cout << 0;
        }
    }
}