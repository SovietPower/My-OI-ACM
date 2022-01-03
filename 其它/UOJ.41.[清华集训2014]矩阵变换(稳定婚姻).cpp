/*
107ms	2028kb
�ȶ��������⣺��n������n��Ů����ÿ����/Ů����ÿ��Ů/������һ����ͬ��ϲ���̶ȡ���ÿ����ѡ����ż��
�������� x,yδƥ�䣬��xϲ��yʤ��ϲ��x��ǰ����ż��yϲ��xҲʤ��y��ǰ����ż ���걸ƥ�䣬�������һ���ȶ�ƥ�䡣
�ȶ�ƥ��һ�����ڣ��Ҵ���һ��$O(n^2)$���㷨��
��ѡһ��δƥ�������x����x��ϲ���̶ȴӴ�Сö��ÿ��Ů��������ǰŮ��û����ż��ϲ��xʤ��ϲ����ǰ��ż������xƥ�䡣ֱ������������ƥ�䡣
��һ���������б�ʾ������n������ʾŮ����ϲ���̶�Ϊ���и�ϲ����ǰ����������ϲ�������λ�ÿ�����С�
eg.���x��һ�п����һЩ������ѡ���ˣ�������ϲ��x��Ҫ������ì����Ҫxϲ��(ѡ)������ǰ������
���Ӷ�$O(nm)$��
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=205,M=405;

int A[N][M],pos[N][N],lk[N],ans[N];
std::queue<int> q;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	for(int T=read(),n,m; T--; )
	{
		n=read(), m=read();
		for(int i=1; i<=n; ++i)
			for(int j=1; j<=m; ++j)
				pos[i][A[i][j]=read()]=j;
		memset(lk,0,sizeof lk);
		for(int i=1; i<=n; ++i) q.push(i);
		while(!q.empty())
		{
			int x=q.front(); q.pop();
			ans[x]=0;
			for(int i=1,v; i<=m; ++i)
				if(v=A[x][i])
				{
					if(!lk[v]) {lk[v]=x, ans[x]=v; break;}
					else if(pos[x][v]>pos[lk[v]][v])
					{
						q.push(lk[v]), lk[v]=x, ans[x]=v;
						break;
					}
				}
		}
		for(int i=1; i<=n; ++i) printf("%d ",ans[i]); putchar('\n');
	}
	return 0;
}
