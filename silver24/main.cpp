#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct tile{
    char c;
    int x;
    int y;
};
struct step{
    int x;
    int y;
    set<pair<int, int>> vis;
    char board[3][3];
};
/*struct ttt{
    char board[3][3];
};*/
bool win(step tmp){
    for(int i=0; i<3; i++){
        if(tmp.board[i][0]=='M' && tmp.board[i][1]=='O' && tmp.board[i][2]=='O') return true;
        if(tmp.board[i][0]=='O' && tmp.board[i][1]=='O' && tmp.board[i][2]=='M') return true;
    }
    for(int i=0; i<3; i++){
        if(tmp.board[0][i]=='M' && tmp.board[1][i]=='O' && tmp.board[2][i]=='O') return true;
        if(tmp.board[0][i]=='O' && tmp.board[1][i]=='O' && tmp.board[2][i]=='M') return true;
    }
    if(tmp.board[0][0]=='O' && tmp.board[1][1]=='O' && tmp.board[2][2]=='M') return true;
    if(tmp.board[0][0]=='M' && tmp.board[1][1]=='O' && tmp.board[2][2]=='O') return true;
    if(tmp.board[0][2]=='M' && tmp.board[1][1]=='O' && tmp.board[2][0]=='O') return true;
    if(tmp.board[0][2]=='O' && tmp.board[1][1]=='O' && tmp.board[2][0]=='M') return true;
    return false;
}
int main(){
    set<pair<int, int>> base;
    int n;
    cin>>n;
    int sx, sy;
    tile arr[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            char first;
            char tmp1, tmp2, posx, posy;
            cin>>first;
            if(first=='#'){
                cin>>tmp1>>tmp2;
                arr[i][j]={'#', -1, -1};
            }
            if(first=='.'){
                cin>>tmp1>>tmp2;
                arr[i][j]={'.', -1, -1};
            }
            if(first=='B'){
                cin>>tmp1>>tmp2;
                sx=i; sy=j;
                arr[i][j]={'.', -1, -1};
            }
            if(first=='M'){
                cin>>posx>>posy;
                arr[i][j]={'M', posx, posy};
            }
            if(first=='O'){
                cin>>posx>>posy;
                arr[i][j]={'O', posx, posy};
            }
        }
    }
    queue<step> q;
    int ans=0;
    q.push({sx, sy, base, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}});
    while (!q.empty()){
        step cur=q.front();
        q.pop();
        if(cur.x>=0 && cur.y>=0 && cur.x<n && cur.y<n && arr[cur.x][cur.y].c!='#' && !cur.vis.count({cur.x, cur.y})){
            if(arr[cur.x][cur.y].c=='M'){
                cur.board[arr[cur.x][cur.y].x][arr[cur.x][cur.y].y]='M';
                if(win(cur)){
                    ans++;
                    break;
                }
            }
            if(arr[cur.x][cur.y].c=='O'){
                cur.board[arr[cur.x][cur.y].x][arr[cur.x][cur.y].y]='O';
                if(win(cur)){
                    ans++;
                    break;
                }
            }
            step tmmp={cur.x+1, cur.y, cur.vis};
            q.push(tmmp);
        }
    }
    cout<<ans<<endl;
}