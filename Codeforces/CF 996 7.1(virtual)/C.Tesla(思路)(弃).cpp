/*
4*n*K=20000��Ҳ����ÿ������඼���������и�������һ�顣��Ȼ�����ֻ��Ҫ���г���2,3������һȦ��
Ҳ����˵���г����л��ᵽ������е�����һ��λ�ã�ֻ��Ҫ���г�һ����һȦ��������2K�����Ұ��κ�һ��λ�ø���ס��
���һ�����Ա߾�����ͣ��λ����ô����ֱ�ӹ�ȥ��
���������ҪK*2n+K=10100�Ρ�
����д����������ô���� ��ģ�⡣��
�ݹ飬�����ǿհ׸�������һȦ�����ˡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define pt std::pair<int,int>
#define mp std::make_pair
const int N=55;

int n,K,A[5][N];
pt pos[N<<1];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define OK(p,x,y) (p.first==x && p.second==y)
pt Check(int &res)
{
	pos[0]=mp(0,0);
	bool f=0; pt blank=mp(0,0);
	for(int i=1; i<=n; ++i)
		if(OK(pos[A[2][i]],1,i))
		{
			--res, ptintf("%d %d %d\n",A[2][i],1,i), A[2][i]=0;
			if(!f) f=1, blank=mp(2,i);
		}
	for(int i=1; i<=n; ++i)
		if(OK(pos[A[3][i]],4,i))
		{
			--res, ptintf("%d %d %d\n",A[3][i],4,i), A[3][i]=0;
			if(!f) f=1, blank=mp(3,i);
		}
	return blank;
}
inline void Move_LD()
{
	if(!A[3][1]) return;
	if(OK(pos(A[3][1]),4,1)) --res, ptintf("%d %d %d\n",A[3][1],4,1), A[3][1]=0;
	else ptintf("%d %d %d\n",A[3][1],2,1), A[2][1]=A[3][1];
}
inline void Move_RU()
{
	if(!A[2][n]) return;
	if(OK(pos(A[2][n]),1,n)) --res, ptintf("%d %d %d\n",A[2][n],1,n), A[2][n]=0;
	else ptintf("%d %d %d\n",A[2][n],3,n), A[3][n]=A[2][n];
}
void Move(int &res,pt blank)
{
	int x=blank.first, y=blank.second;
	if(x==2)
	{
		for(int i=y-1; i; --i)
		{
			if(!A[2][i]) continue;
			if(OK(pos[A[2][i]],1,i)) --res, ptintf("%d %d %d\n",A[2][i],1,i), A[2][i]=0;
			else ptintf("%d %d %d\n",A[2][i],2,i+1), A[2][i+1]=A[2][i];
		}
		Move_LD();
		for(int i=2; i<=n; ++i)
		{
			if(!A[3][i]) continue;
			if(OK(pos[A[3][i]],4,i)) --res, ptintf("%d %d %d\n",A[3][i],4,i), A[3][i]=0;
			else ptintf("%d %d %d\n",A[3][i],3,i-1), A[3][i-1]=A[3][i];
		}
		Move_RU();
		for(int i=n-1; i>y; --i)
		{
			if(!A[2][i]) continue;
			if(OK(pos[A[2][i]],1,i)) --res, ptintf("%d %d %d\n",A[2][i],1,i), A[2][i]=0;
			else ptintf("%d %d %d\n",A[2][i],2,i+1), A[2][i+1]=A[2][i];
		}
	}
	else
	{
		for(int i=y+1; i<=n; ++i)
		{
			if(!A[3][i]) continue;
			if(OK(pos[A[3][i]],4,i)) --res, ptintf("%d %d %d\n",A[3][i],4,i), A[3][i]=0;
			else ptintf("%d %d %d\n",A[3][i],3,i-1), A[3][i-1]=A[3][i];
		}
		
	}
}
void Solve()
{
	int res=K; pt blank;
	if(K==n<<1 && (blank=Check(res),res==K)) {puts("-1"); return;}
	for(; res; Move(res,blank));
}

int main()
{
	n=read(), K=read();
	for(int i=1; i<=n; ++i) pos[read()]=mp(1,i);
	for(int i=1; i<=n; ++i) A[2][i]=read();
	for(int i=1; i<=n; ++i) A[3][i]=read();
	for(int i=1; i<=n; ++i) pos[read()]=mp(4,i);
	Solve();

	return 0;
}
