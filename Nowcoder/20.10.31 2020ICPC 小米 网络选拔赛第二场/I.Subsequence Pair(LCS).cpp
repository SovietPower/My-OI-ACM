/*
$Description$
给定两个串$S,T$，求$S,T$中的两个子序列$s,t$使得$s$的字典序小于等于$t$，且$|s|+|t|$最大。
$|S|,|T|\leq2000$。
$Solution$
$s\leq t$，则$s,t$存在一定长度（可以为$0$）公共子序列后有$s_i<t_j$，此时$s_i$和$t_j$后面的所有$n-i+1+m-j+1$个字符都可以加进去。
若$s_i=t_j$则$t_j$后面$m-j+1$个可以加进去。所以求最长公共子序列就可以了。
注意$s,t$可为空串（答案初值为$m$）。
*/
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fir first
#define sec second
#define pb push_back
#define ll long long

const int N = 2e3+10;
char s[N], t[N];
int n, m;
int f[N][N];
int main(){
    while(scanf("%s%s",s+1,t+1) == 2){
        n = strlen(s+1);
        m = strlen(t+1);
        f[0][0] = 0;
        int ans = m;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                f[i][j] = max(f[i-1][j], f[i][j-1]);
                if(s[i] ==  t[j]) f[i][j] = max(f[i][j], f[i-1][j-1]+1);

                ans = max(ans, 2*f[i][j]+(m-j));
                if(t[j] > s[i]) ans = max(ans, f[i-1][j-1]*2 + (n-i+1) + (m-j+1));

                //cout<<f[i][j]<<' ';
            }
            //cout<<endl;
        }
        printf("%d\n",ans);
    }
    return 0;
}
