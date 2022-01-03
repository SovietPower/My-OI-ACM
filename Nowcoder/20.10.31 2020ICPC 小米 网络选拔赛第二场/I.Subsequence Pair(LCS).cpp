/*
$Description$
����������$S,T$����$S,T$�е�����������$s,t$ʹ��$s$���ֵ���С�ڵ���$t$����$|s|+|t|$���
$|S|,|T|\leq2000$��
$Solution$
$s\leq t$����$s,t$����һ�����ȣ�����Ϊ$0$�����������к���$s_i<t_j$����ʱ$s_i$��$t_j$���������$n-i+1+m-j+1$���ַ������Լӽ�ȥ��
��$s_i=t_j$��$t_j$����$m-j+1$�����Լӽ�ȥ������������������оͿ����ˡ�
ע��$s,t$��Ϊ�մ����𰸳�ֵΪ$m$����
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
