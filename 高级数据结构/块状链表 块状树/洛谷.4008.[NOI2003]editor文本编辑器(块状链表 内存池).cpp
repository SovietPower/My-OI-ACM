/*
72ms	4.32MB
st(n)表示sqrt(n)
为使块状链表不会退化，通常将每块的大小S维持在[st(n)/2,2st(n)]中，这样块数C也一定[st(n)/2,2st(n)]中 
在此使用另一种方法(方便)维持这种性质：保证任意相邻两块的size相加>st(n)，并且每块大小<=st(n) 
这样可保证块数C在[st(n),2st(n)]中 
在每次块状链表结构改变后执行maintain，顺序扫描链表，将相邻两块能合并就合并 

1.注意Insert的读入，会有回车 
2.为避免各种翻车，还是加上判断!=-1好 
3.可以根据操作分布，适当调大块的大小 
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
	sz[0]=0, nxt[0]=-1;//新建一个0节点，方便 表头就是0 
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
			Merge(cur,Nxt), Nxt=nxt[cur];//最好不用nxt[Nxt]，因为已经合并、删掉了，虽然不影响答案，但还是不该写 
}
int Get_Index(int &pos)//找到pos所在的块，并将pos定位为块内位置 
{
	int cur=0;
	while((~cur) && pos>sz[cur])//把cur定位到某一块的末尾，不用下一块开头了(pos>=sz) 
		pos-=sz[cur], cur=nxt[cur];
	return cur;
}
void Update(int cur,int Nxt,int len,char *s)//给新的块Nxt设置数据及指针 
{
	nxt[Nxt]=nxt[cur], nxt[cur]=Nxt, sz[Nxt]=len;
	memcpy(data[Nxt],s,len);
}
void Split(int cur,int pos)
{
	if(cur==-1||pos==sz[cur]) return;//不能判!pos！因为后边会直接用nxt[cur]，不分裂会跳过该块；而在=sz时不分是没问题的 
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
		Update(cur,Nxt,MaxSize,str+sum);//先分成尽可能多的整块 
		sum+=MaxSize, cur=Nxt;
	}
	if(len-sum)//剩余的单独放到一块 
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
