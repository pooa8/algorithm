#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#define MAX 101

using namespace std;

const int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, 1, -1};
int n, m, answer;
int map[MAX][MAX];
int visited[MAX][MAX];
vector<pair<int, int> > pos[MAX][MAX]; // 스위치 정보
queue<pair<int, int> > q;

void total() {
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(map[i][j] == 1) answer++;
}
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);
        pos[x][y].push_back(make_pair(a, b));
    }
    
    while(true) {
        memset(visited, 0, sizeof(visited));
        map[1][1] = 1, visited[1][1] = 1;
        q.push(make_pair(1, 1));
        
        bool flag = false;
        while(!q.empty()) {
            int yy = q.front().first;
            int xx = q.front().second;
            q.pop();
            
            if (!pos[yy][xx].empty()) { // 스위치가 있다면
                for(int i = 0; i < pos[yy][xx].size(); i++) {
                    pair<int, int> next = pos[yy][xx][i];
                    map[next.first][next.second] = 1;
                }
                pos[yy][xx].clear(); // 스위치 제거
                flag = true; // 불을 켰다
            }

            for(int i = 0; i < 4; i++) {
                int ny = yy + dy[i];
                int nx = xx + dx[i];
                if (ny < 1 || ny > n || nx < 1 || nx > n) continue;
                if (map[ny][nx] == 1 && !visited[ny][nx]) { // 이동 가능 좌표 탐색
                    visited[ny][nx] = 1;
                    q.push(make_pair(ny, nx));
                }
            }
        }
        if (!flag) break;
    }
    
    total();
    printf("%d\n", answer);
    return 0;
}