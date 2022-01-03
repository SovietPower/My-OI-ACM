/*
840ms	12800KB
https://www.cnblogs.com/SovietPower/p/9743673.html
Ϊ�˷��㣬���ǽ�x�������ҷ�ת���ٽ����и߶�ȡ����������Ȼ��ά�������ҵ�LIS������ÿ�������ұ�ɾ��Ԫ�ء�
����������p���ֵ��������ֻ��9���������ߣ�����ֻ��ת�Ƶ���9����������9�����⣬�����Դ�1~p-1���κ���ת�ƣ�����9�����������ߵ���ͬ�����Դ���ǰ���κ���ת�ƣ���
���ǰ���9������DPֵ����ɾ����Ȼ��ӵ͵��ߴ�1~pos[h]-1ת�Ʋ����¡����߶ȸ��¾�ֻ��Ҫ����λ�úϲ��Ϸ��ˡ�
���Ƕ�λ�ý��߶���ά��ÿ��λ�õ�DPֵ����ֻ�е����޸ġ�����max��
���ڿ���������k��������λ��Ϊp����Ϊֻ���ұ����9��������ת�ƣ�ͬ�������ǵ�DPֵ����ɾ����Ȼ��ɾ��λ��p��DPֵ��
�����ұ�10������һ������ߵģ���Ȼ���ǿ��Դ�ǰ��������ת�ƣ�����Ҫ����߶�С�����ǡ�
����Զ�ά�߶�������������ֻ��Ҫ����һ���߶�����ÿ���߶�ά��ͬ����DPֵ����ͬλ�ø߶Ȳ�ͬ�����Ϳ��Դ����ң�ֱ�����߶�����ѯ�������ˡ�
������һ���߶����ϸ�����DPֵ������һ���ϸ�һ�¼��ɡ�
���Ӷ�$O(10n\log n)$��
�ܽ᣺����ߵ�10�þ���ά��λ��DPֵ���߶�����ת�ƣ�����ҵ�10�þ���ά���߶�DPֵ���߶�����ת�ơ�������һ����һ�õ�DPֵ����ά��һ���ģ���
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 50000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+15;

int pos[N],h[N];
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int f[N],mx[S];
	#undef S

	#define Update(rt) mx[rt]=std::max(mx[ls],mx[rs])
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {mx[rt]=v; return;}
		int m=l+r>>1;
		if(p<=m) Modify(lson,p,v);
		else Modify(rson,p,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int R)
	{
		if(r<=R) return mx[rt];
		int m=l+r>>1;
		if(m<R) return std::max(Query(lson,R),Query(rson,R));
		return Query(lson,R);
	}
	void Insert(int p,int n)//�����²����p��ѯDPֵ������ 
	{
		Modify(0,n,1,p,f[p]=Query(0,n,1,p-1)+1);
	}
}Tp,Th;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	#define Sp 0,n,1
	#define Sh 0,m+10,1
	int n=read(),m=read();//pos[i]:��i������λ�� h[i]:iλ�õ����ĸ߶� 
	for(int t=1; t<=m; ++t)
		if(read()==1)//plant
		{
			int p=n-read()+1,ht=t+10-read();
			pos[ht]=p, h[p]=ht, st.insert(p);
			for(int i=ht+1; i<=ht+9; ++i)
				if(pos[i]) Tp.Modify(Sp,pos[i],0);
			for(int i=ht; i<=ht+9; ++i)
				if(pos[i])
				{
					Tp.Insert(pos[i],n);
					Th.f[i]=Tp.f[pos[i]];
					Th.Modify(Sh,i,Th.f[i]);
				}
			printf("%d\n",Tp.mx[1]);
		}
		else
		{
			int k=read();
			std::set<int>::iterator it=st.end();
			while(k--) --it, Th.Modify(Sh,h[*it],0);
			Tp.Modify(Sp,*it,0), pos[h[*it]]=0;
			for(st.erase(it++); it!=st.end(); ++it)
			{
				Th.Insert(h[*it],m+10);
				Tp.f[*it]=Th.f[h[*it]];
				Tp.Modify(Sp,*it,Tp.f[*it]);
			}
			printf("%d\n",Tp.mx[1]);
		}

	return 0;
}
