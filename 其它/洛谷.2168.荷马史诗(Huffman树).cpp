/*
���ڴ�Ȩ������(ÿ���ڵ㶼����Ȩֵ����): 
(1)�ڵ�Ĵ�Ȩ·������Ϊ�ýڵ㵽����֮���·������(���)��ڵ���Ȩ�ĳ˻� 
(2)����·������(Weighted Path Length of Tree,���ΪWPL)�Ǵ�������ÿһ���ڵ��·������֮�� 
����WPL=��Wi*Li 

����������:�϶̵ı����ܹ���ʡ�洢�ռ䡢���Ч�� 
�������б���ȳ������ʾn����ͬ�ַ���Ҫlog2nλ����Ϊ�̶����ȱ��룬��ASCII�� 
���ÿ���ַ�ʹ��Ƶ����ͬ����̶����ȱ����ǿռ�Ч����ߵķ��� 
����ʵ����ÿ���ַ�ʹ��Ƶ�������кܴ���죬�������ó���Ƶ�ʽ��б��� 
�����ֵ��ַ�����϶̣��������ֵ��ַ�����ϳ������ֱ��뷽ʽΪ���ȳ����룬����������뷨 

������������: 
������n��Ȩֵ:w1,w2,...,wn������һ����n��Ҷ�ڵ�Ķ�������ÿ��Ҷ�ڵ�ȨֵΪwi�����Ȩ·��������С�Ķ������ͽ�"������������" 
����Ҫ�ص㣺Ҷ��ȨԽ���Խ�������ڵ㣬ȨԽСԽԶ����ڵ� 
����̰�Ĺ��죺(1)���켯��S={T1,T2,...,Tn}������ÿ�ö�����Ti��ֻ��һ��ȨֵΪWi�ĸ��ڵ㣬����Ϊ������ 
(2)��S��ѡȡ���ڵ�Ȩֵ��С�����ö��������ֱ���Ϊ������������һ�����������ڵ�ȨֵΪ�����������ڵ�Ȩֵ֮�� 
(3)��S��ɾȥ���������������������ɵ��� 
(4)�ظ�(2)(3)��ֱ��S��ֻ��һ���� 

���ڱ��������k���Ʊ��룬�������k������ÿ�ο��Ժϲ�k������ 
Ҫע�����ֱ�Ӷ�n���ڵ���кϲ������һ�κϲ����ܻ�������k����������� 
��ʱ�����ϲ��ⲻ��k�������ͻᵼ�´��� 
�������Ȳ���y��ȨֵΪ0������ڵ㣺n-x(k-1)+y=1, y=k-1-(n-1)%(k-1)
��Ҫ�������С������ʱ��Ϊ�ڶ��ؼ��ּ��� 
*/
#include<queue>
#include<cstdio>
#include<cctype>
#include<algorithm>
//using namespace std;
const int N=1e5+20;
//#define mp make_pair
//#define pr pair<long long,int>
//
//int n,k;
//priority_queue<pr,vector<pr>,greater<pr> > q;
#define mp std::make_pair//std::�ٶ��൱ 
#define pr std::pair<long long,int>

int n,k;
std::priority_queue<pr,std::vector<pr>,std::greater<pr> > q;


inline long long read()
{//long long !
	long long now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

int main()
{
//	freopen("21683.in","r",stdin);

	n=read(),k=read();
	long long w;
	for(int i=1;i<=n;++i) w=read(),q.push(mp(w,1));
	int y=(n-1)%(k-1);
	if(y)//�������һ�㲻��ʱ��� 
		y=k-1-y;//ע��Ҫ�ӵ�ֵ 
	for(int i=1;i<=y;++i) q.push(mp(0,1));
	n+=y;
	int mxdep;
	long long tmp,ans=0;
	while(n>1)
	{
		tmp=0, mxdep=1;
		for(int i=1;i<=k;++i)
		{
			tmp+=q.top().first;
			if(mxdep<q.top().second) mxdep=q.top().second;
			q.pop();
		}
		q.push(mp(tmp,mxdep+1));
		ans+=tmp;
		n-=k-1;
	}
	printf("%lld\n%d",ans,mxdep);

	return 0;
}
