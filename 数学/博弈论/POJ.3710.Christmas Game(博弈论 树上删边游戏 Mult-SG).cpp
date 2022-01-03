/*
$Description$
����n��"��"��"��"�Ľڵ����"����"һ��������֤û�л��ཻ��������ֻ��һ�������㡣
��������������ɾ�ߣ�ɾȥһ���ߺ󣬲����������һ���ֻᱻ�Ƴ�������޷��ƶ������䡣��˭��Ӯ��
$Solution$
���û�л����Ǿ��ǵ��͵�����ɾ����Ϸ 
���ǻ���û�й��ñ�������ֻ��һ������x��������һ��������ĳ��������������������ļ򵥻���
ɾ������һ�ߺ���γ������� -> Mult-SG 
������һ���滷����ôɾȥһ���ߺ�ʣ�µ���������ż����ͬ��������״̬������(SGֵ)һ����Ϊ1�����Ի���SGֵΪ1(���SGֵ��mex) 
������һ��ż������ôɾȥһ���ߺ�ʣ�µ���������ż���෴��������״̬������(SGֵ)һ����Ϊ0�����Ի���SGֵΪ0(mex) 
���ǿ���ɾȥ����ż�������滷����һ���ߣ��ͳ�������ɾ����Ϸ��ģ���� 

����ɾ����Ϸ���ۣ�Ҷ�ӽڵ��SGֵΪ0���м�ڵ��SGֵΪ�� �����ӽڵ�SGֵ+1 ������� 

ע: ������ڵ��Ҫ���ǳ�ջ 
�г���Ϊ2�Ļ�!
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
const int N=105,M=505;

int t,n,m,Enum,H[N],to[M<<1],nxt[M<<1],sg[N],top,sk[N],vis[N];
//vis=0:δ���ʹ� vis=1:���ʹ��Ҳ���ĳ�����ϵĵ�(���������ϵ�) vis=-1:���ʹ�����ĳ�����ϵĵ� 
//����vis[x]=-1��(��) ����ͳ�ƴ�!
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS(int x,int f)
{
	sk[++top]=x, vis[x]=1, sg[x]=0;
	bool flag=0;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]==f && !flag) flag=1;//��һ�����򸸽ڵ� 
		else{
			if(vis[to[i]]==1){//����vis�ʹ��ε�cnt������˻���������Ҫ��ջ 
				int cnt=1,now=x;
				while(now!=to[i])
					++cnt, vis[now]=-1, now=sk[--top];
				if(cnt&1) sg[to[i]]^=1;//�滷 
			}
			else if(!vis[to[i]])
			{
				DFS(to[i],x);
				if(~vis[to[i]]) sg[x]^=(sg[to[i]]+1);//���ϵĲ��ܸ��� 
			}
		}
	if(~vis[x]) --top;//�ǻ��ϵ� ��ʱ��ջ 
}

int main()
{
	while(~scanf("%d",&t))//number of sub-trees
	{
		int res=0;
		while(t--)
		{
			memset(vis,0,sizeof vis),
			memset(H,0,sizeof H), Enum=top=0;
			n=read(),m=read();
			for(int u,v,i=1; i<=m; ++i) u=read(),v=read(),AddEdge(u,v);
			DFS(1,0), res^=sg[1];
		}
		puts(res?"Sally":"Harry");
	}
	return 0;
}/*
1 2 2 1 2 1 2
*/
