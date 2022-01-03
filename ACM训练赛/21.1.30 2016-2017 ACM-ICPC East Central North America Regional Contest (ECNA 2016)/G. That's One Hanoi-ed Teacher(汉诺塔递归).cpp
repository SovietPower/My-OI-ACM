/*
30ms	0KB
��Ҫ��ϰһ�º�ŵ������ŵ���ĵݹ��������ģ�
```cpp
void DFS(int n,int a,int b,int c)//��n��Բ�̴�a->c
{
	if(n==1)
	{
		printf("%d: %d->%d\n",n,a,c);
		return;
	}
	DFS(n-1,a,c,b);
	printf("%d: %d->%d\n",n,a,c);
	DFS(n-1,b,a,c);
}
```
�ܹ����ǣ���Բ��$n-1$��$a$�Ƶ�$b$����Բ��$n$��$a$�Ƶ�$c$�����Բ��$n-1$��$b$�Ƶ�$c$��
��������⣬��$n$��ʼ�жϣ����$n$����$a$����������$2^{n-1}-1$����$n-1$�����Ӵ�$b$�Ƶ�$c$����$1$����$n$�Ƶ�$c$�����$n$��$b$�ϣ��������Ž⣻���$n$��$c$�����ٿ�$n-1$���ɡ�
���Ƶصݹ�һ�£�ע���޸ĵ�ǰ�Ĳ���$a,b,c$�Ϳ����ˡ�
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=105;

int vis[N];
LL ans;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool DFS(int n,int a,int b,int c)
{
	if(!n) return 1;
	if(vis[n]==a) return ans+=1ll<<(n-1),DFS(n-1,a,c,b);//n����a��n-1��a�Ƶ�bȥ 
	else if(vis[n]==c) return DFS(n-1,b,a,c);//n�Ѿ���c��n-1��b�ƻص�cȥ 
	return 0;
}

int main()
{
	int a=read(); for(int i=1; i<=a; ++i) vis[read()]=1;
	int b=read(); for(int i=1; i<=b; ++i) vis[read()]=2;
	int c=read(); for(int i=1; i<=c; ++i) vis[read()]=3;
	if(!DFS(a+b+c,1,2,3)) puts("No");
	else printf("%lld\n",ans);

	return 0;
}
