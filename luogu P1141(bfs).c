#include <stdio.h>

char map[1005][1005];
int bfs[1005][1005];
int save[2000005]; 
int n, m, dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int p = 0, q = 0;

void BFS(int a, int b) {
    int start = 0, end = 2, x = a, y = b;
    bfs[x][y] = 1; save[0] = a; save[1] = b;
    while (start < end) {
        x = save[start++]; y = save[start++];
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && bfs[nx][ny] == 0 && map[x][y] != map[nx][ny]) {
                bfs[nx][ny] = 1;
                save[end++] = nx; save[end++] = ny;
            }
        }
    }
    for (int i = 0; i < end; i += 2) {
        bfs[save[i]][save[i+1]] = end / 2;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", map[i]);
    
    do {
        if (bfs[p][q] == 0) BFS(p, q);
        q++;
        if (q == n) {
            q = 0; p++;
        }
    } while (p != n);
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &p, &q);
        printf("%d\n", bfs[p-1][q-1]);
    }
    return 0;
}
