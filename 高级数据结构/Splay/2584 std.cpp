#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define mod 985003
using namespace std;
int n,root,sz,tot,head[mod+1];
struct data1{int v,time,next;char ch[10];}hash[250001];
struct data2{int l,r,v,s,rnd,time;char ch[10];}tr[250001];
void update(int k){tr[k].s=tr[tr[k].l].s+tr[tr[k].r].s+1;}
void rturn(int &k){int t=tr[k].l;tr[k].l=tr[t].r;tr[t].r=k;tr[t].s=tr[k].s;update(k);k=t;}
void lturn(int &k){int t=tr[k].r;tr[k].r=tr[t].l;tr[t].l=k;tr[t].s=tr[k].s;update(k);k=t;}
bool cmp(char a[],char b[])
{for(int i=1;i<max(strlen(a),strlen(b));i++)if(a[i]!=b[i])return 0;return 1;}
int Hash(char ch[])
{
	int s=0; 
	for(int i=1;i<strlen(ch);i++)
    {s*=27;s+=(ch[i]-'A'+1);s%=mod;}
    return s;
}
void del(int &k,int x,int time)
{
     if(tr[k].v==x)
     {
          if(tr[k].time==time)
          {
               if(tr[k].l*tr[k].r==0)k=tr[k].l+tr[k].r;
               else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd){rturn(k);del(k,x,time);}
               else {lturn(k);del(k,x,time);}
          }
          else if(time>tr[k].time){tr[k].s--;del(tr[k].l,x,time);}
          else {tr[k].s--;del(tr[k].r,x,time);}
     }
     else if(x<tr[k].v){tr[k].s--;del(tr[k].l,x,time);}
     else {tr[k].s--;del(tr[k].r,x,time);}
 }
void insert(int &k,char ch[],int x,int time)
{
     if(k==0)
	 {
	      sz++;k=sz;tr[k].v=x;tr[k].s=1;tr[k].rnd=rand();
		  memcpy(tr[k].ch,ch,strlen(ch));tr[k].time=time;
	      return;
	 }
	 tr[k].s++;
     if(x<=tr[k].v){insert(tr[k].l,ch,x,time);if(tr[tr[k].l].rnd<tr[k].rnd)rturn(k);}
     else{insert(tr[k].r,ch,x,time);if(tr[tr[k].r].rnd<tr[k].rnd)lturn(k);}
 }
void INS(char ch[],int x,int time)
{
    int k=Hash(ch);int i=head[k];
    while(i)
    {
    	if(cmp(hash[i].ch,ch))
		{
		   del(root,hash[i].v,hash[i].time);
		   hash[i].time=time;hash[i].v=x;
		   insert(root,ch,x,time);
		   return;
	    }
	    i=hash[i].next;
    }
    tot++;
    hash[tot].time=time;hash[tot].v=x;
    memcpy(hash[tot].ch,ch,strlen(ch));
    hash[tot].next=head[k];head[k]=tot;
    insert(root,ch,x,time);
}
int get(char ch[])
{
	int k=Hash(ch);int i=head[k];
	while(i)
	{
        if(cmp(hash[i].ch,ch))return i;
		i=hash[i].next;
	}
}
int getrank(int k,int x,int time)
{
    if(k==0)return 0;
    if(tr[k].v==x)
    {
        if(tr[k].time>time)return getrank(tr[k].r,x,time);
        else if(tr[k].time<time)return 1+tr[tr[k].r].s+getrank(tr[k].l,x,time);
        else return tr[tr[k].r].s+1;
    }
    else if(tr[k].v<x)return getrank(tr[k].r,x,time);
    else return 1+tr[tr[k].r].s+getrank(tr[k].l,x,time);
}
void ask1(char ch[])
{
    int t=get(ch);
    printf("%d\n",getrank(root,hash[t].v,hash[t].time));
}
int index(int k,int x)
{
     if(tr[tr[k].r].s+1==x)return k;
     else if(x<=tr[tr[k].r].s)return index(tr[k].r,x);
     else return index(tr[k].l,x-tr[tr[k].r].s-1);
 }
void ask2(char ch[])
{
    int s=0;
    for(int i=1;i<strlen(ch);i++){s*=10;s+=ch[i]-'0';}
    for(int i=s;i<=tot&&i<=s+9;i++)
    {
       printf("%s",tr[index(root,i)].ch+1);
       if(i<tot&&i<s+9)printf(" ");
       }
    printf("\n");
}
int main()
{
	scanf("%d",&n);char ch[11];int x;
	for(int i=1;i<=n;i++)
	{
            scanf("%s",ch);
            {
                if(ch[0]=='+'){scanf("%d",&x);INS(ch,x,i);}
                else if(ch[1]>='A'&&ch[1]<='Z')ask1(ch);
                else ask2(ch);
            }
	}
	return 0;
}
