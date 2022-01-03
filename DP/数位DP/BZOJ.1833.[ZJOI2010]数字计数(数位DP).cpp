/*
824kb	52ms
$Description$
��$[l,r]$��$0,1,\cdots,9$ÿ�����ֳ��ֵĴ���(ʮ���Ʊ�ʾ)��
$Solution$
��ÿλ�ֱ�DP��ע�⿼��ǰ��0: �����ͳ��ʱ����0�Ĵ𰸼�����Ӧλ�ļ��ɣ��ڵ�iλ��ǰ��0����������10^{i-1}���𰸡�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;

LL Ans[13],A[13],f[13][13],pw[13];
bool vis[13][13];

LL DFS(int pos,LL cnt,bool lim,int K)
{
	if(!pos) return cnt;
	if(!lim && vis[pos][cnt]) return f[pos][cnt];
	int up=lim?A[pos]:9; LL res=0;
	for(int i=0; i<=up; ++i)
		res+=DFS(pos-1,cnt+(i==K),i==up&&lim,K);
	if(!lim) vis[pos][cnt]=1,f[pos][cnt]=res;
	return res;
}

int main()
{
	pw[0]=1;
	for(int i=1; i<=12; ++i) pw[i]=pw[i-1]*10ll;
	LL l,r;
	scanf("%lld%lld",&l,&r);
	if(l>r) std::swap(l,r);
	for(A[0]=0; r; r/=10) A[++A[0]]=r%10;
	for(int i=0; i<=9; ++i)//ÿ�����𰸶��ǲ�ͬ�ġ���������ա�
		memset(vis,0,sizeof vis), Ans[i]=DFS(A[0],0,1,i);
	int bit=A[0];

	for(A[0]=0,--l; l; l/=10) A[++A[0]]=l%10;
	for(int i=0; i<=9; ++i)
		memset(vis,0,sizeof vis), Ans[i]-=DFS(A[0],0,1,i);
	while(bit!=A[0]) Ans[0]-=pw[--bit];
	for(int i=0; i<9; ++i) printf("%lld ",Ans[i]);
	printf("%lld",Ans[9]);

	return 0;
}
