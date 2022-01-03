/*
15480kb	156ms
�����Ĵ����ʣ�DP+���仯��
��f[s][x][y][hp]��ʾ��s״̬��(x,y)�㣬Ѫ��Ϊhpʱ�Ĵ����ʡ�
s�Ǹ�������������¼ÿ�������޺�/�к�/δ֪��
ת��ʱ�Ƚ����ף���Ҫ��������δ֪ʱ��Ҫ֪����ǰ״̬�������Ϊ�к�/�޺��ĸ��ʣ�����������������ӡ�
�����ĳ��״̬��δ֪�����Ƿ��к��ĸ�����(�������к����ʣ��� �к�/(�к�+�޺�))
DFSö��ÿ��������֪�к�/�޺�/δ֪��״̬��������Ҫ����δ֪�����ڸ�״̬�µĸ��ʡ�
ö��ÿ��δ֪�����壬��ö��2^K�ĸ������飬ֻ�е�����������֪�����״̬ʱ(δ֪����/�޽ⶼ��)���ſ��Ը��µ�ǰ�����к�/�޺��ĸ��ʡ�
�����������о��Ƚ��԰�������K�����������״̬ʱ�ĸ��ʡ�
ע��: �ٻص�һ����(�����)�ǿ��еģ���Ҫ��������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
const int N=33,to[5]={1,0,-1,0,1};

int n,m,K,K_2,H,pi[N],sta[6];
double P[255][6],tmp[2],f[N][N][6][255];
bool vis[N][N][6][255];
char mp[N][N];

void DFS(int x)
{
	if(x==K)
	{
		int now=0;
		for(int i=K-1; ~i; --i) now=now*3+sta[i];
		for(int p=0; p<K; ++p)
			if(sta[p]==2)
			{
				tmp[0]=tmp[1]=0;//�������к�/�޺��ĸ��� 
				for(int i=0; i<K_2; ++i)
				{
					bool f=1;
					for(int j=0; j<K; ++j)
						if(sta[j]==2) ;
						else if(((i>>j)&1)!=sta[j]) {f=0; break;}
					if(f) tmp[(i>>p)&1]+=pi[i];//!
				}
				P[now][p]=tmp[1]/(tmp[0]+tmp[1]);
			}
	}
	else
	{
		sta[x]=0, DFS(x+1);
		sta[x]=1, DFS(x+1);
		sta[x]=2, DFS(x+1);
	}
}
inline int Change(int s,int p,int to)
{
	int t=1; while(p--) t*=3;
	return s-(2-to)*t;
}
#define Now f[x][y][hp][s]
double Solve(int x,int y,int hp,int s)
{
	if(!hp) return 0;
	if(mp[x][y]=='@') return 1.0;
	if(vis[x][y][hp][s]) return f[x][y][hp][s];
	vis[x][y][hp][s]=1;//״̬�Ƚ϶಻�����ذ�����ֱ��������vis=1.
	for(int xn,yn,i=0; i<4; ++i)
	{
		xn=x+to[i], yn=y+to[i+1];
		if(!xn||!yn||xn>n||yn>m||mp[xn][yn]=='#') continue;
		char ch=mp[xn][yn];
		if(ch=='.'||ch=='@'||ch=='$') Now=std::max(Now,Solve(xn,yn,hp,s));
		else if(isalpha(ch)){
			int ts=s,id=ch-'A';
			for(int t=id; t; --t) ts/=3;
			if(!(ts%3)) Now=std::max(Now,Solve(xn,yn,hp,s));
			else if(ts%3==1) Now=std::max(Now,Solve(xn,yn,hp-1,s));
			else Now=std::max(Now,Solve(xn,yn,hp-1,Change(s,id,1))*P[s][id]+Solve(xn,yn,hp,Change(s,id,0))*(1-P[s][id]));
		}
	}
	return Now;
}

int main()
{
	scanf("%d%d%d%d",&n,&m,&K,&H);
	int sx=0,sy;
	for(int i=1; i<=n; ++i)
	{
		scanf("%s",mp[i]+1);
		if(!sx){
			for(int j=1; j<=m; ++j)
				if(mp[i][j]=='$') sx=i,sy=j;
		}
	}
	K_2=1<<K;
	for(int i=0; i<K_2; ++i) scanf("%d",&pi[i]);
	DFS(0);
	int sta=1;
	for(int i=K; i; --i) sta*=3;
//	int sta=0;
//	for(int i=K; i; --i) sta=sta*3+2;
	printf("%.3lf",Solve(sx,sy,H,sta-1));

	return 0;
}
