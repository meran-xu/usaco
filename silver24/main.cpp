#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct tile {
    char c;
    int x;
    int y;
};

struct step {
    int x;
    int y;
    set<pair<int, int>> vis;
    char board[3][3];
};

bool win(step tmp) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (tmp.board[i][0] == 'M' && tmp.board[i][1] == 'O' && tmp.board[i][2] == 'O') return true;
        if (tmp.board[i][0] == 'O' && tmp.board[i][1] == 'O' && tmp.board[i][2] == 'M') return true;
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (tmp.board[0][i] == 'M' && tmp.board[1][i] == 'O' && tmp.board[2][i] == 'O') return true;
        if (tmp.board[0][i] == 'O' && tmp.board[1][i] == 'O' && tmp.board[2][i] == 'M') return true;
    }
    // Check diagonals
    if (tmp.board[0][0] == 'M' && tmp.board[1][1] == 'O' && tmp.board[2][2] == 'O') return true;
    if (tmp.board[0][0] == 'O' && tmp.board[1][1] == 'O' && tmp.board[2][2] == 'M') return true;
    if (tmp.board[0][2] == 'M' && tmp.board[1][1] == 'O' && tmp.board[2][0] == 'O') return true;
    if (tmp.board[0][2] == 'O' && tmp.board[1][1] == 'O' && tmp.board[2][0] == 'M') return true;
    return false;
}

int main() {
    int n;
    cin >> n;
    int sx, sy;
    tile arr[n][n];

    // Read input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char first;
            cin >> first;
            if (first == '#') {
                arr[i][j] = {'#', -1, -1};
            } else if (first == '.') {
                arr[i][j] = {'.', -1, -1};
            } else if (first == 'B') {
                sx = i;
                sy = j;
                arr[i][j] = {'.', -1, -1};
            } else if (first == 'M' || first == 'O') {
                int posx, posy;
                cin >> posx >> posy;
                arr[i][j] = {first, posx, posy};
            }
        }
    }

    // Initialize BFS
    queue<step> q;
    step start;
    start.x = sx;
    start.y = sy;
    start.vis.insert({sx, sy});
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            start.board[i][j] = 0; // Initialize board
        }
    }
    q.push(start);

    int ans = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        step cur = q.front();
        q.pop();

        // Check if current step is a winning state
        if (win(cur)) {
            ans++;
            continue; // Continue exploring other paths
        }

        // Explore all four directions
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < n && arr[nx][ny].c != '#' && !cur.vis.count({nx, ny})) {
                step next = cur;
                next.x = nx;
                next.y = ny;
                next.vis.insert({nx, ny});

                // Update board if stepping on 'M' or 'O'
                if (arr[nx][ny].c == 'M' || arr[nx][ny].c == 'O') {
                    int bx = arr[nx][ny].x;
                    int by = arr[nx][ny].y;
                    next.board[bx][by] = arr[nx][ny].c;
                }

                q.push(next);
            }
        }
    }

    cout << ans << endl;
    return 0;
}