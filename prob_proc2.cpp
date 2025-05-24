#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

std::ifstream fin("proc2.in");
std::ofstream fout("proc2.out");

int N, M;

// bool cnt( Task a, Task b){
//     if ( a.s > b.s ){
//         return 0;
//     }
//     else if ( b.s > a.s ){
//         return 1;
//     }
//     else{
//         if (a.d < b.d ){
//             return 1;
//         }
//         else if ( a.d > b.d ){
//             return 0;
//         }
//         else {
//             if ( a.i < b.i ){
//                 return 1;
//             }
//             else return 0;
//         }
//     }
// }


int main(){
    fin >> N >> M;

    using Task = std::tuple<int, int, int>;

    std::vector<Task> tasks(M);

    for ( int i = 0; i < M; i++){
        int s, d;
        fin >> s >> d;
        tasks[i] = {s,d,i};
    }

    std::sort(tasks.begin(), tasks.end());

    // for ( int i = 0; i < M; i++ ){
    //     std::cout << std::get<0>(tasks[i]) << std::get<1>(tasks[i]) << std::get<2>(tasks[i]) << '\n';
    // }

    std::priority_queue<int, std::vector<int>, std::greater<>> free;
    for ( int i = 0; i < N; i++ ){
        free.push(i);
    }

    using pair_fi = std::pair<int, int>;
    std::priority_queue<pair_fi, std::vector<pair_fi>, std::greater<>> allocated;

    std::vector<int> result(M);
    bool ok = true;

    for ( const auto& [s,d,i] : tasks ){
        while ( !allocated.empty() && allocated.top().first <= s ){
            free.push(allocated.top().second);
            allocated.pop();
        }

        if ( free.empty() ){
            ok = false;
            break;
        }
        int proc = free.top();
        free.pop();

        result[i] = proc;

        allocated.emplace(s+d, proc);
    }

    if ( ok == false ){
        fout << "Imposibil";
    }
    else{
        for ( int proc : result ){
            fout << proc + 1 << '\n';
        }
    }   

    fin.close();
    fout.close();

    return 0;
}