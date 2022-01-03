/*
12124kb	740ms
40pts:
�����Ƕ����ģ���ͬ�ڵ�i�е�Ԫ��һ������ӵ�f(i)�У����Ƕ�������λ�õĹ���ͬ������һ���ǹ̶��ģ�ֻ�Ǽӵ��в�ͬ���ѡ���ͬ���������еĹ�������ͬ�ġ�
�������(һά��)�ж��ٸ�����ת�Ƶ�ĳ��λ��i���ҳ��������(��ά)����K����-> ��40pts��Ҳ����д��QAQ 
��ʵ���ö� Ȼ��ÿ���ڵ�ά������ָ�룬��һ���ͷ�������������������x==yʱ�����ء�(��ʵҲ�а취 ���Ҫ����֮�ࣿ)
���x�ǳ�ʼ��s_x���򲻶���չ push(x,y+1)�����x!=y����push(x+1,y)(ά��һ���������ԣ��о���6������)
������x!=yʱ�����飬��Ϊ�����ǿ����ڷ������ģ�
(Ҳ������push��n��ȥ����չ�ɡ���)
100pts:
n�ܴ��޷�ֱ�����ĳ��λ�õ�val[].
��n�ķ�Χ��f(x)������ֻ�в��Ǻܶ���(��Ų���20000?)��������ֻ����2.3.5.7������ͨ����λDP���y=2^i*3^j*5^k*7^lʱ�ж��ٸ�x����λ�˻�=y(x<=n).
dp[len][0/1][i][j][k][l]��ʾ��ǰ��n�ĵ�lenλ��ǰ���Ƿ�ﵽ���Ͻ磬�Լ�y�����Ӹ����ֱ�Ϊi,j,k,lʱ��x������
���ͳ������y��val[]��
ע��dp��ϸ��: ������ǰ��0���������λ��Ҫ����ǰ��0�Ĺ��ף���dp[now][0][0][0][0][0]++(�����Ͻ�)�����λ��ʼ��ʱ��dp[now][1][0][0][0][0]=1(�Ͻ�)��
(��û��ֱ��д���롣�������xxy������)
�������ȡģ����ȡ��������������ȡģ��val[]��������в���ȡģ��(��������)
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define mod (1000000007)
typedef long long LL;
const int N=1e5+7;

int K,cnt,f[11][5]/*��һλ��Ӱ�����ֵ*/,A[20];
//LL n,val[N],dp[2][2][40][26][18][15];
LL n,val[N],dp[2][2][41][27][19][16];
struct Node
{
	int x,y; LL v;
	Node(int _x,int _y): x(_x),y(_y),v(val[x]*val[y]) {}
	bool operator <(const Node &a)const{
		return v<a.v;//val���� 
	}
};
std::priority_queue<Node> q;

inline bool cmp(const int &a,const int &b){
	return a>b;
}
inline void Pre()
{//0:2 1:3 2:5 3:7
	f[2][0]=1, f[4][0]=2, f[6][0]=1, f[8][0]=3,
	f[3][1]=1, f[6][1]=1, f[9][1]=2,
	f[5][2]=1, f[7][3]=1;
}
inline LL FP(LL x,int k)
{
	LL t=1;
	for(; k; k>>=1,x=x*x)
		if(k&1) t=t*x;
	return t;
}
void DP()
{//2:40 3:26 5:18 7:15
	Pre();
	LL t=n; int len=0;
	while(t) A[len++]=t%10,t/=10;//��һ����sb�ˡ����±��0��ʼ����A[0]������ 
	std::reverse(A,A+len);
	int now=0,nxt=1;
	for(int p=0; p<len; ++p,std::swap(now,nxt))//��tm����l����������
	{
		
		if(!p) dp[now][1][0][0][0][0]=1;
		else ++dp[now][0][0][0][0][0];
		memset(dp[nxt],0,sizeof dp[nxt]);
		for(int s=0; s<=1; ++s)
			for(int i=0; i<=40; ++i)
				for(int j=0; j<=26; ++j)
					for(int k=0; k<=18; ++k)
						for(int l=0; l<=15; ++l)
							if(dp[now][s][i][j][k][l])//��ô��ô����
								for(int w=1,lim=s?A[p]:9; w<=lim; ++w)//����ȡģ  //���ⲻ����0��
									dp[nxt][s&&w==lim][i+f[w][0]][j+f[w][1]][k+f[w][2]][l+f[w][3]]+=dp[now][s][i][j][k][l];
	}
	LL tmp2=1,sum;
	for(int i=0; i<=40; ++i)
	{
		LL tmp3=tmp2;
		for(int j=0; j<=26; ++j)
		{
			LL tmp5=tmp3;
			for(int k=0; k<=18; ++k)
			{
				LL tmp7=tmp5;
				for(int l=0; l<=15; ++l)
				{
					if(sum=(dp[now][0][i][j][k][l]+dp[now][1][i][j][k][l])%mod) val[++cnt]=sum;
					if((tmp7*=7)>n) break;
				}
				if((tmp5*=5)>n) break;
			}
			if((tmp3*=3)>n) break;
		}
		if((tmp2<<=1)>n) break;
	}
}

int main()
{
	scanf("%lld%d",&n,&K);
	DP();
	std::sort(val+1,val+1+cnt,cmp);
	LL res=0;
	q.push(Node(1,1));
	while(!q.empty())
	{
		Node rt=q.top(); q.pop();
		(res+=rt.v)%=mod;
		if(!--K) break;
		if(rt.x!=rt.y){
			(res+=rt.v)%=mod;
			if(!--K) break;
			q.push(Node(rt.x+1,rt.y));
		}
		if(rt.x==1) q.push(Node(rt.x,rt.y+1));
	}
	printf("%lld",res);

	return 0;
}
