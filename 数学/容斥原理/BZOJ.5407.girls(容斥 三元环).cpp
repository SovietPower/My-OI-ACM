/*
24736kb	2884ms
$Description$
��n���㣬������m�������������㡣ÿһ��û�����ߵ���Ԫ��(i,j,k)(i<j<k)�Դ𰸵Ĺ���ΪA*i+B*j+C*k����������������Ԫ��Ĺ��׺͡�
$Solution$
ֱ������������Ԫ�����ɺ��ѡ����������з���ȥ������ Ans=���з���-������1������+������2������-��3���ߣ�"����"��Ȼ�ȽϺ���������
�������з�����A,B,C���Էֱ�ͳ�ƣ���ö���ĸ���A/B/C��ʣ�µ������ϡ�
��������1�����ߣ�����ö��ÿ���㼰�����($O(n+m)$)����Ϊ����˫��ߣ����Զ���i,to=link[i]��ֻ��i<toʱ����i��ΪA/A/B��to��ΪB/C/Cʱ��ֵ�����ˡ�
��������2�����ߣ�ö�������ߵĹ����˵�(so�ý�����ͼ)�����һ�¡��������������ߵĺͣ�������to�Ĺ��ס�
�����������ߣ�ֱ��$O(m\sqrt{m})$ö����Ԫ����
*/
#include <set>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <iostream>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 250000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Vec std::vector<int>
#define Output printf("%I64u\n",ans)
typedef long long LL;
typedef unsigned long long ull;
const int N=2e5+5;

int m,dgr[N],Link[N];
ull n,A,B,C,sumA[N],sumB[N],sumC[N];
Vec vec[N];
std::set<int> s[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline ull readull()
{
	ull now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read()-1, m=read(), A=readull(), B=readull(), C=readull();//id:0~n
	for(int u,v; m--; )
		u=read(), v=read(), vec[u].push_back(v), vec[v].push_back(u), s[u].insert(v), s[v].insert(u);
	for(int i=0; i<=n; ++i) dgr[i]=vec[i].size(), std::sort(vec[i].begin(),vec[i].end());

	ull ans=0;
//All
	for(ull i=0; i<=n-2; ++i) ans+=A*i*((n-i)*(n-i-1)>>1);//All
	for(ull i=1; i<n; ++i) ans+=B*i*i*(n-i);
	for(ull i=2; i<=n; ++i) ans+=C*i*(i*(i-1)>>1);
//One & Two
	for(ull i=1; i<=n; ++i) sumA[i]=sumA[i-1]+i*A, sumB[i]=sumB[i-1]+i*B, sumC[i]=sumC[i-1]+i*C;
	for(ull i=0; i<=n; ++i)
	{
		const Vec &to=vec[i]; ull cnt0=0,cnt1=0;
		for(int j=0,len=to.size()-1; j<=len; ++j)
		{
			ull v=to[j];
			if(v<i) ++cnt0, ans+=A*v*(len-j)+B*v*j;//ͬ�£�����iΪB/C��v��len-j�ֿ���ΪA��
			else//v>i
			{//Ҫ��һ��λ��ʹ��i<to[x]<v��������v<iʱ����v��ΪA/B�Ĵ�(д�����ֿ��ܾͱȽ������) 
				++cnt1;
				ans-=(A*i+B*v)*(n-v)+sumC[n]-sumC[v];
				ans-=(A*i+C*v)*(v-i-1)+sumB[v-1]-sumB[i];
				if(i) ans-=(B*i+C*v)*i+sumA[i-1];

				ans+=C*v*j+B*v*(len-j);//����i��ΪA����B��v������j�ֿ�����ΪC(ǰj����ѡһ������ȷ��i��A or B)��
			}
		}
		ans+=i*(A*(cnt1*(cnt1-1)>>1)+B*cnt0*cnt1+C*(cnt0*(cnt0-1)>>1));
		//����ֻ����i��Ϊ���߶˵�ʱ������Ĺ��ף���û����i�ġ�(ö�ٱ��ö�ٵ�iʱҲ����i��ΪҪö�ٵ����߶˵���)
	}
//Three
	for(int i=0,size=sqrt(m); i<=n; ++i)
	{
		const Vec &to=vec[i]; int len=to.size();
		for(int j=len-1; ~j; --j) Link[to[j]]=i;
		for(int j=len-1; ~j; --j)
			if(i<to[j])
			{
				int v=to[j];
				if(dgr[v]<=size)
				{
					for(int k=vec[v].size()-1; ~k; --k)
						if(v<vec[v][k]) ans-=A*i+B*v+C*vec[v][k];
						else break;
				}
				else
				{
					for(int k=len-1; ~k; --k)
						if(v<to[k])
							if(s[v].count(to[k])) ans-=A*i+B*v+C*to[k];
							else ;
						else break;
				}
			}
	}

	printf("%llu",ans);

	return 0;
}
