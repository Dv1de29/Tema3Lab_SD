#include <fstream>

using namespace std;

ifstream fin("stramosi.in");
ofstream fout("stramosi.out");

int N,M,P,Q, up[250001][18];

int main(){
    fin >> N >> M;

    for ( int i = 1; i <= N; i++ ){
        fin >> up[i][0];
    }

    for ( int node = 1; node <= N; node++ ){
        for ( int i = 1; i < 18; i++ ){
            up[node][i] = up[up[node][i-1]][i-1];
        }
    }

    while(M--){
        fin >> Q >> P;
        int p = 0;

        while(P){
            if ( 1 & P ){
                Q = up[Q][p];
            }
            P >>= 1;
            p++;
        }
        fout << Q << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}