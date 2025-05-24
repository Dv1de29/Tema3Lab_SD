#include <iostream>
#include <vector>
#include <algorithm>

int N;

bool valid_interval( int lb, int hb, std::vector<int>& A, std::vector<int>& B, int N){
    for ( int k = 0; k < N; k++ ){
        if (!((lb <= A[k] && hb >= A[k]) || (lb <= B[k] && hb >= B[k]))){
            return false;
        }
    }
    return true;
}

int main(){
    std::vector<int> v;
    std::cin >> N;
    std::vector<int> A(N);
    std::vector<int> B(N);

    for ( int i = 0; i < N; i++ ){
        std::cin >> A[i] >> B[i];
        v.push_back(A[i]);
        v.push_back(B[i]);
    }

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    int ans = 1e9 + 7;
    int i = 0;
    for ( int j = 0; j < 2*N; j++ ){
        while ( i <= j && valid_interval(v[i], v[j], A, B, N)){
            ans = std::min(ans, v[j] - v[i]);
            i++;
        }
    }

    std::cout << ans;
}