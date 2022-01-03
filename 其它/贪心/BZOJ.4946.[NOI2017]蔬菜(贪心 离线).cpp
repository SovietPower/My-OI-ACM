/*
9424kb	1132ms
��Ϊ��ɾ�������ǵ�����ĳ��p��ѯ�ʡ�
��ôÿ��ɾ��xi���߲˾ͱ����ÿ������xi���߲ˡ���ô����ȡ��ǰ���ŵļ��ɣ���ȡ��ȡ��һ��������Ҫ��������ȡ�����ܸ�������ŵ������ռ䡣
������ֻ�迼�������ˡ����������ܵõ�pΪĳ��ֵ�Ĵ𰸡����ѯ����Ȼ��Ҫ���ơ�
��p-1��p���ֻ��������m���߲ˡ���������С��m��ɾ�����ɡ�
ע��ѵĲ���ɾ��˳��
���Ӷ�$O(mqlogn)$��
����һ����ѯ��p�ķ�������ֱ�Ӱ��߲˼�ֵ����Ȼ��ÿ���ҵ������λ����ǰ���ǡ����ĳ������m���ò��鼯�ϲ�����
���Ƶ�ʱ��sortһ�鰤��ɾ�Ϳ��ԡ�
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 400000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define mp std::make_pair
#define pr std::pair<LL,int>
#define MAX 100000
typedef long long LL;
const int N=1e5+3;

int A[N],S[N],tot[N],dec[N],use[N];
LL Ans[N];
std::vector<int> v[N];
std::queue<int> tmp;
std::priority_queue<pr> q1;
std::priority_queue<pr,std::vector<pr>,std::greater<pr> > q2;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),m=read(),Q=read();
	for(int i=1; i<=n; ++i)
	{
		A[i]=read(),S[i]=read(),tot[i]=read(),dec[i]=read();
		if(!dec[i]) v[MAX].push_back(i);//�Ͻ磡
		else v[std::min(MAX,(tot[i]+dec[i]-1)/dec[i])].push_back(i);
	}
	LL ans=0;
	for(int i=MAX; i; --i)
	{
		for(int j=0,k,l=v[i].size(); j<l; ++j)//�����һ�ι��� 
			k=v[i][j], q1.push(mp(A[k]+S[k],k));
		for(int l=m; l&&!q1.empty(); q1.pop())
		{
			int x=q1.top().second;
			if(!use[x])
				use[x]=1, ans+=q1.top().first, q1.push(mp(A[x],x)), --l;
			else
			{
				int cnt=std::min(l,tot[x]-use[x]-(i-1)*dec[x]);
				ans+=1ll*q1.top().first*cnt, l-=cnt;
				if((use[x]+=cnt)!=tot[x]/*x=0���ܻ�����!*/) tmp.push(x);//delete
			}
		}
		while(!tmp.empty()) q1.push(mp(A[tmp.front()],tmp.front())), tmp.pop();
	}
	Ans[MAX]=ans; int sum=0;
	for(int i=1; i<=n; sum+=use[i++])
		if(use[i]==1) q2.push(mp(A[i]+S[i],i));
		else if(use[i]) q2.push(mp(A[i],i));
	for(int i=MAX-1; i; --i)
	{
		Ans[i]=ans=Ans[i+1];
		if(sum<=m*i) continue;//����������
		for(int l=sum-i*m/*ͬ�ϣ�*/; l&&!q2.empty(); )
		{
			int x=q2.top().second;
			if(use[x]==1) ans-=q2.top().first, --l, q2.pop();
			else
			{
				int cnt=std::min(l,use[x]-1);
				ans-=1ll*q2.top().first*cnt, l-=cnt;
				if((use[x]-=cnt)==1) q2.pop(), q2.push(mp(A[x]+S[x],x));
			}
		}
		sum=i*m, Ans[i]=ans;
	}
	while(Q--) printf("%lld\n",Ans[read()]);

	return 0;
}
