/*
其实只需要multiset即可 
对于询问1，删除、插入差值，输出最小元素 
对于询问2，插入后用前驱后继更新 
1.注意哨兵元素 
2.注意multiset中删除时是删除某元素的一个位置，而不是这个元素！这个值会全部都删掉 
不开O2慢成狗 开了也不是很快 
*/
#include<set>
#include<cstdio>
#include<cctype>
#include<algorithm>
const int N=5e5+5,M=N*3,INF=1e9;

int n,q,st[N],ed[N],Min=INF;
std::multiset<int> delta,A;
std::multiset<int>::iterator it;

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}
void Ins(int v)
{
	it=A.lower_bound(v);
	Min=std::min(Min,*it-v);
	Min=std::min(Min,v-(*--it));
	A.insert(v);
}
void Modify()
{
	int p=read(),v=read();
	if(p!=n)
		delta.erase(delta.find(std::abs(st[p+1]-ed[p]))),
		delta.insert(std::abs(st[p+1]-v));
	delta.insert(std::abs(ed[p]-v));
	ed[p]=v;
	if(Min) Ins(v);
}

int main()
{
//	freopen("form.in","r",stdin);
//	freopen("form.out","w",stdout);

	n=read(),q=read();
	A.insert(-INF), A.insert(INF);
	st[1]=ed[1]=read(),A.insert(st[1]);
	for(int i=2;i<=n;++i)
		st[i]=ed[i]=read(),delta.insert(std::abs(st[i]-st[i-1])),Ins(st[i]);
	char s[20];int p,v;
	while(q--)
	{
		scanf("%s",s);
		if(s[0]=='I') Modify();
		else if(s[4]=='G') printf("%d\n",*delta.begin());
		else printf("%d\n",Min);
	}

	return 0;
}
