/*
72ms	4.32MB
st(n)��ʾsqrt(n)
Ϊʹ��״�������˻���ͨ����ÿ��Ĵ�СSά����[st(n)/2,2st(n)]�У���������CҲһ��[st(n)/2,2st(n)]�� 
�ڴ�ʹ����һ�ַ���(����)ά���������ʣ���֤�������������size���>st(n)������ÿ���С<=st(n) 
�����ɱ�֤����C��[st(n),2st(n)]�� 
��ÿ�ο�״����ṹ�ı��ִ��maintain��˳��ɨ�����������������ܺϲ��ͺϲ� 

1.ע��Insert�Ķ��룬���лس� 
2.Ϊ������ַ��������Ǽ����ж�!=-1�� 
3.���Ը��ݲ����ֲ����ʵ������Ĵ�С 
*/
#include<cstdio>
#include<cctype>
#include<cstring>
//#define gc() getchar()
#define MAXIN 100000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1024*1024*2+5;
const int MaxSize=/*1700*/4500,MaxNum=/*1700*2*/N*2/MaxSize+100;

int num,nxt[MaxNum],sz[MaxNum],pool[MaxNum];
char data[MaxNum][MaxSize],str[N],IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

inline int New_Block()
{
	return pool[++num];
}
inline void Del_Block(int v)
{
	pool[num--]=v;
}
void Init()
{
	for(int i=1;i<MaxNum;++i) pool[i]=i;
	sz[0]=0, nxt[0]=-1;//�½�һ��0�ڵ㣬���� ��ͷ����0 
}
void Merge(int cur,int Nxt)
{
	memcpy(data[cur]+sz[cur],data[Nxt],sz[Nxt]);
	nxt[cur]=nxt[Nxt], sz[cur]+=sz[Nxt];
	Del_Block(Nxt);
}
void Maintain()
{
	for(int cur=0,Nxt=nxt[0];~cur;cur=nxt[cur],Nxt=nxt[cur])
		while((~Nxt) && sz[cur]+sz[Nxt]<=MaxSize)
			Merge(cur,Nxt), Nxt=nxt[cur];//��ò���nxt[Nxt]����Ϊ�Ѿ��ϲ���ɾ���ˣ���Ȼ��Ӱ��𰸣������ǲ���д 
}
int Get_Index(int &pos)//�ҵ�pos���ڵĿ飬����pos��λΪ����λ�� 
{
	int cur=0;
	while((~cur) && pos>sz[cur])//��cur��λ��ĳһ���ĩβ��������һ�鿪ͷ��(pos>=sz) 
		pos-=sz[cur], cur=nxt[cur];
	return cur;
}
void Update(int cur,int Nxt,int len,char *s)//���µĿ�Nxt�������ݼ�ָ�� 
{
	nxt[Nxt]=nxt[cur], nxt[cur]=Nxt, sz[Nxt]=len;
	memcpy(data[Nxt],s,len);
}
void Split(int cur,int pos)
{
	if(cur==-1||pos==sz[cur]) return;//������!pos����Ϊ��߻�ֱ����nxt[cur]�������ѻ������ÿ飻����=szʱ������û����� 
	int Nxt=New_Block();
	Update(cur,Nxt,sz[cur]-pos,data[cur]+pos);
	sz[cur]=pos;
}
void Insert(int pos,int len)
{
	int cur=Get_Index(pos),sum=0,Nxt;
	Split(cur,pos);
	while(sum+MaxSize<=len)
	{
		Nxt=New_Block();
		Update(cur,Nxt,MaxSize,str+sum);//�ȷֳɾ����ܶ������ 
		sum+=MaxSize, cur=Nxt;
	}
	if(len-sum)//ʣ��ĵ����ŵ�һ�� 
		Nxt=New_Block(), Update(cur,Nxt,len-sum,str+sum);
	Maintain();
}
void Erase(int pos,int len)
{
	int cur=Get_Index(pos),Nxt;
	Split(cur,pos);
	Nxt=nxt[cur];//because of here
	while((~Nxt) && len>sz[Nxt])
		len-=sz[Nxt], Del_Block(Nxt), Nxt=nxt[Nxt];
	Split(Nxt,len);
	Del_Block(Nxt), nxt[cur]=nxt[Nxt];
	Maintain();
}
void Get_Data(int pos,int len)
{
	int cur=Get_Index(pos),sum=sz[cur]-pos;
	if(len<sum) sum=len;
	memcpy(str,data[cur]+pos,sum);
	cur=nxt[cur];
	while((~cur) && sum+sz[cur]<=len)
		memcpy(str+sum,data[cur],sz[cur]), sum+=sz[cur] ,cur=nxt[cur];
	if((~cur) && len-sum)
		memcpy(str+sum,data[cur],len-sum);
	str[len]='\0';
	printf("%s\n",str);
}
inline char Get_opt()
{
	register char c=gc();
	while(c!='M'&&c!='I'&&c!='D'&&c!='G'&&c!='P'&&c!='N') c=gc();
	return c;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4008.in","r",stdin);
#endif

	Init();
	int t=read(),pos=0,len;
	char s[10];
	while(t--)
	{
		switch(Get_opt())
		{
			case 'M':pos=read();break;
			case 'I':len=read();
					 for(int i=0;i<len;++i)
					 {
					 	str[i]=gc();
					 	if(str[i]<32||str[i]>126) --i;
					 }
					 Insert(pos,len);
					 break;
			case 'D':len=read(),Erase(pos,len);break;
			case 'G':len=read(),Get_Data(pos,len);break;
			case 'P':--pos;break;
			case 'N':++pos;break;
		}
	}

	return 0;
}
