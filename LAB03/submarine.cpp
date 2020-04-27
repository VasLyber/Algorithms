#include <iostream>
#include <utility>
#include <queue>
#include <map>
#include <tuple>

using namespace std;

pair<int, int> special_edges[180][180];

map<tuple<int, int, int>, long> cache;

long countPaths(int x, int y, int limit){
    if(x == 0 && y == 0){
        return 1;
    }
    auto itr = cache.find(make_tuple(x, y, limit));
    if (itr != cache.end()){
        return itr->second;
    }
    long res = 0;
    if(special_edges[x][y].first >= 0){
        if(limit > 0){
            res = (countPaths(special_edges[x][y].first, special_edges[x][y].second, limit-1))%1000000103;
        }
        else{
            res = 0;
        }
        cache[make_tuple(x, y, limit)] = res;
        return res;
    }
    else {
        long count = 0;
        if(x > 0){
            res = (countPaths(x-1, y, limit))%1000000103;
            count += res;
        }
        if(y > 0){
            res = (countPaths(x, y-1, limit))%1000000103;
            count += res;
        }
        cache[make_tuple(x, y, limit)] = count;
        return count;
    }
}


int main(int argc, char const *argv[])
{
    int N, M, K, X, s, e;
    long count = 0;
    cin >> N;
    cin >> M;
    cin >> K;
    cin >> X;
    for(int i = 0; i < 180; i++){
        for(int j = 0; j < 180; j++){
            special_edges[i][j] = {-1, -1};
        }  
    }
    for(int i = 0; i < K; i++){
        cin >> s;
        cin >> e;
        int sx = (int) s/M;
        int sy = s%M;
        int ex = (int) e/M;
        int ey = e%M;
        pair<int, int> end;
        end.first = ex;
        end.second = ey; 
        special_edges[sx][sy] = end;
    }
    count = (countPaths(N-1, M-1, X))%1000000103;
    cout << count << endl;
    return 0;
}
