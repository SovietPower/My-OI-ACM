/*
820kb	4ms
��λDP��sb�ˡ���
ǰ��0����Ӱ��ģ�Ӱ���һλ��ѡ������Ҫ�ǡ��ټ�¼���ޣ�Ȼ����û������ʱ���仯��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

int L,R,A[12],f[12][10];
bool vis[12][10];

int DFS(int pos,int las,bool lim,bool lead)
{
	if(!pos) return 1;
	if(!lim && !lead && vis[pos][las]) return f[pos][las];
	int res=0, up=lim?A[pos]:9;
	for(int i=0; i<=up; ++i)
		if(std::abs(i-las)>=2||lead) res+=DFS(pos-1,i,lim&&i==up,lead&&!i);
	if(!lim && !lead) vis[pos][las]=1, f[pos][las]=res;
	return res;
}
int Solve(int n)
{
	for(A[0]=0; n; n/=10) A[++A[0]]=n%10;
	memset(vis,0,sizeof vis);
	return DFS(A[0],100,1,1);
}

int main()
{
	scanf("%d%d",&L,&R);
	printf("%d",Solve(R)-Solve(L-1));
	return 0;
}
