/*
������д��O(n^2K)��DP���̡�Ȼ����Ȼ���ߵ��ǵ����ģ�����ά�����ߵ�Ϳ����ˡ���
����ôѧ���Ǽٵĵ����������s�F���䣩�s��ة���
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 5000000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=4003;

int n,K,A[N][N],sum[N][N],f[2][N],Now;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node{
	int l,r,pos;//pos������[l,r]������ת�Ƶ� 
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline int Cost(int i,int p){//��i֮ǰ���ָ�p,p+1�� 
	return f[Now][p]+sum[p+1][i];
}
inline int Find(Node t,int x)
{
	int l=t.l, r=t.r, mid;
	while(l<=r)//l==rʱӦ��Checkһ�Σ�
		if(mid=l+r>>1, Cost(mid,x)<Cost(mid,t.pos)) r=mid-1;//!
		else l=mid+1;
	return l;
}

int main()
{
	n=read(),K=read();
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j) A[i][j]=A[i][j-1]+read();
	for(int i=1; i<=n; ++i)
		for(int j=i+1; j<=n; ++j)
			sum[i][j]=sum[i][j-1]+A[j][j]-A[j][i-1];
	for(int i=1; i<=n; ++i) f[1][i]=sum[1][i];
	Now=1;
	for(int j=1; j<K; ++j, Now^=1)
	{
		int h=1,t=1; q[1]=(Node){1,n,1};
		for(int i=2; i<=n; ++i)
		{
			if(i>q[h].r) ++h;
			f[Now^1][i]=Cost(i,q[h].pos);
			if(Cost(n,i)<Cost(n,q[t].pos))//ΪʲôҪ��n�ȣ������⡣
			{
				while(h<=t && Cost(q[t].l,i)<Cost(q[t].l,q[t].pos)) --t;//��β�����l��i����pos�����ˣ������ߵ��ǵ����ģ�����[l,r]�϶���Ҫ��ѡpos��ѡi�� 
				if(h>t) q[++t]=(Node){i,n,i};
				else
				{
					int Pos=Find(q[t],i);
					q[t].r=Pos-1, q[++t]=(Node){Pos,n,i};
				}
			}
		}
	}
	printf("%d",f[Now][n]);

	return 0;
}
