/*
852kb	0ms
$Description$
��һ���ֵ�����С����Ϊ$2^k$�Ĵ���������ʹ�����г�Ϊ$k$��01���������г��ֹ���
$Solution$
���г�Ϊ$k$��01��һ����$2^k$��������ÿһλ��Ҫ��һ���µ�01����
ÿ��01������ȥ����һλ������һ��0/1�õ��µ�01���������д���ͼ����Ϊһ������ŷ����·��ֱ�ӱ����ܸ�ŷ����·���ɡ�
*/
#include <cstdio>
const int N=(1<<11)+5;

int all,ans[N];
bool vis[N];

bool DFS(int x,int t)
{
	if(vis[x]) return 0;
	vis[x]=1, ans[t]=x&1;
	if(t==all+1) return 1;
	if(DFS((x<<1)&all,t+1)) return 1;
	if(DFS(((x<<1)&all)|1,t+1)) return 1;
	vis[x]=0;
	return 0;
}

int main()
{
	int k; scanf("%d",&k);
	all=(1<<k)-1, printf("%d ",all+1), DFS(0,1);//DFS(all-1,1);
	for(int i=1; i<k; ++i) putchar('0');
	for(int i=1; i<=all-k+2; ++i) putchar(ans[i]+'0');
	return 0;
}
