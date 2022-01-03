/*
1616kb	684ms
���������ˡ���
DFS()������������ö��ÿ��������ı������(���䵱ǰ����ķ���)��
���Է��ַ��������������ֻ��ӵ��˶��ٷ��޹أ�ֻ�뵱ǰ�����Ķ��������͵÷����е�����йء����Լ��仯������
DFS()���Ǵ�ĳ֧�����������Ķ���һһ���б��� ����÷֣������굱ǰ����������ĵ÷������ϣ�����Ƿ������
���û�ͽ�����һ֧���飬��ʵ���Ǽ���ȥ����ǰ��֧����ķ�������
n(n<=10)֧���������������Ϊ(28^9?)10^14���𣬿���ֱ����longlong�档

������Ϊʲô����Ҫ�����ţ�
*/
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define mod (1000000007)
typedef long long LL;
const int N=11;

int n,val[N];
std::map<LL,int> sta[N];//Ӧ����ÿһλ��һ��map?
std::map<LL,int>::iterator it;

inline bool cmp(int a,int b){
	return a<b;
}
LL Get_Hash(int p)
{
	int tmp[N];
	for(int i=p; i<=n; ++i) tmp[i]=val[i];
	std::sort(tmp+p,tmp+n+1,cmp);//tmp+p������tmp+p+1 
	LL res=0;
	for(int i=p; i<=n; ++i) res=res*28+tmp[i];//tmp[i] not val[i]!!(��tm�⻹��д�� ��˵��ô��T)
	return res;
}
int DFS(int l,int r)
{
	if(val[l]>(r-l)*3) return 0;//��������ļ�֦�������ܺϷ���
	if(l==r)
	{
//		if(val[l]) return 0;//ֻ�аѷ���ǡ�÷�����źϷ�!
		if(l==n) return 1;
		LL s=Get_Hash(l+1);
		if((it=sta[l].find(s))!=sta[l].end()) return it->second;//~~�õ�����Ч�ʷ����ͣ���⡣��~~��������xp���°ɣ�������Ͽ첻�� 
		return sta[l][s]=DFS(l+1,n);//�ⲻ���õ�������ֵ��
	}
	int res=0;
	if(val[l]>=3)
	{
		val[l]-=3;
		res+=DFS(l,r-1), res>=mod?res-=mod:0;
		val[l]+=3;
	}
	if(val[l]&&val[r])
	{
		--val[l], --val[r];
		res+=DFS(l,r-1), res>=mod?res-=mod:0;
		++val[l], ++val[r];
	}
	if(val[r]>=3)
	{
		val[r]-=3;
		res+=DFS(l,r-1), res>=mod?res-=mod:0;
		val[r]+=3;
	}
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&val[i]);
	std::sort(val+1,val+1+n,cmp);
	printf("%d",DFS(1,n));

	return 0;
}
