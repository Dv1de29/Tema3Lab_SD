#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

std::ifstream fin("timbre.in");
std::ofstream fout("timbre.out");

int N,M,K;

struct Interval{
    int m, cost;
};

struct Compare{
    bool operator()(const Interval& a, const Interval& b){
        return a.cost > b.cost;
    }
};

int main(){
    fin >> N >> M >> K;

    std::vector<Interval> intervals(M);

    for ( int i = 0; i < M; i++ ){
        fin >> intervals[i].m >> intervals[i].cost;
    }

    std::sort(intervals.begin(), intervals.end(), [](const Interval& a,const Interval& b){
        return a.m < b.m;
    });

    // for ( auto it = intervals.begin(); it < intervals.end(); it++ ){
    //     std::cout << it->m;
    // }

    // std::vector<long long> dp(N + 1, INT_MAX);
    // dp[0] = 0;

    // // for ( int i = 0; i <= N; i++ ){
    //     // std::cout << dp[i] << ' ';
    // // }
    // // std::cout << '\n';

    // for ( int i = 0; i < M; i++ ){
    //     int m = intervals[i].m;
    //     int cost = intervals[i].cost;

        
    //     if ( m > N ){
    //         // std::cout << "m was " << m << " before it changed'\n";
    //         m = N;
    //     }

    //     // std::cout << m << ", " << cost << ":\n";

    //     for ( int len = 1; len <= K && len <= m; len++ ){
    //         for ( int q = m - len; q >= 0; q-- ){
    //                 // std::cout << dp[m] << ' ' << dp[m-j] << '\n';
    //             dp[q + len] = std::min(dp[q + len], dp[q] + cost);
    //                 // std::cout << dp[m] << " at j = " << j << "\n\n"; 
    //         }
    //     }
    // }

    // if ( dp[N] == INT_MAX ){
    //     fout << "Imposibil";
    // }
    // else{
    //     fout << dp[N]; 
    // }

    std::priority_queue<Interval, std::vector<Interval>, Compare> pq;

    int pos = 1;
    int interval = 0;
    long long cost = 0;

    while( pos <= N ){
        while ( interval < M && intervals[interval].m >= pos ){
            pq.push(intervals[interval]);
            interval++;
        }

        while ( !pq.empty() && pq.top().m < pos ){
            pq.pop();
        }

        if ( pq.empty() ){
            fout << -1;
            fin.close();
            fout.close();
            return 0;
        }

        Interval i = pq.top(); pq.pop();

        int len = std::min(K, i.m - pos + 1);
        cost += i.cost;
        pos += len;
    }

    fout << cost;

    fin.close();
    fout.close();

    return 0;
}


