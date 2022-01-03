/*
147544kb	9488ms
$Description$
����һ����Ϊn�����У����ѯ��[l,r]������ֻ����һ�ε�����ǿ�����ߡ�
$Solution$
��Ҳ��֪������ô˵����������Ԥ���� ����ϯ�����׶�/set����i��lΪi��rΪ[i,n]�Ĵ𰸣�����������ĳ�����ϵ����maxv�ˣ���
���������������Ϳ���������ϯ������ǰ׺���������ʣ�ÿ����i�Ľ���ֻ��Ҫ����iλ�á�
��ô����������ǽ����е���������[��һ�γ���λ��,nxt[]-1]�м����������
����˵�i�ƶ�ʱ��A[i-1]�Ĺ���û�ˣ�Ҫɾ�����������A[i-1]�ں�����֣���Ҫ��[nxt[A[i-1]],nxt[nxt[A[i-1]]]-1]�ϼ���A[i-1]��(A[i]�Ѿ������ˣ�Ҫô�ڽ������ʱҪô����ǰ��������)
Ҳ����ÿ����ÿ���ڵ㶼�׶ѣ���ֻ��Ҫ��������ϯ��ʱ�Ӽ�ɾɾ����������ǰ׺����Ҫ�õ�ֻ�Ǹ��ݶѵõ���ÿ���ڵ��maxv[]�����Զѻ���4n��Ϳ��ԡ���
��CF���ⲻͬ��������̶�l�����㣬����̶�r��Щ������ֻ��Ҫnxt(���ǰ��һ��las�������������)��
��һ����ϯ�������޸ġ�������Ϣ���ǵ�ǰ����ʱֱ�Ӹ��ڵ㸳ֵ,return����ѯ����ʱ������·�ڵ��mx[]��������û�����
ע���½��ڵ�ʱcopy x��mx[]����Ϊÿ��ɾ������ȫɾ����һ�εļ��룬so��δ�ݹ鵽��ȫ��������ǰcopy mx�ǶԵģ��������鷳�𡣡��Ժ��ǲ��ǸùԹ�дUpdate()����

ѯ�ʵ������������Կ�������ά�ȣ�����ĳ��ά�ռ�����Ȩֵ���ĵ㣬������K-D Tree��������˵�ⲻӦ�����⣬���Կ���ֻ�����������ܵı���ϯ���졣��
��������K-D Tree���õ�Ӧ�ðɣ����뿴�ˣ��ȷ��š���
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=1e5+5;

int n,Q,A[N],las[N],nxt[N],rcnt,root[N*3],pos[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Tree//Persistent Segment Tree
{
	#define S N*100//��Ҳ��֪�������������޸ĵ���ϯ�����ж��ٽڵ�(2��log��) 
	#define lson son[x][0]
	#define rson son[x][1]
	#define ToL l,m,rt<<1
	#define ToR m+1,r,rt<<1|1
	struct Heap
	{
		std::priority_queue<int> h,d;
		inline void Insert(int x) {h.push(x);}
		inline void Delete(int x) {d.push(x);}
		inline void Maintain(){
			while(!h.empty()&&!d.empty()&&h.top()==d.top()) h.pop(),d.pop();
		}
		inline int Top(){
			Maintain(); return h.empty()?0:h.top();
		}
	}hp[N<<2];
	int tot,son[S][2],mx[S];

//	inline void Update(int x){//Updateûɶ�ð� �ֲ���������Ϣ 
//		mx[x]=std::max(mx[lson],mx[rson]);
//	}
	void Insert(int &y,int x,int l,int r,int rt,int L,int R,int v)//rt:һ���߶����Ľڵ� �洢�� 
	{
		y=++tot;
		if(L<=l && r<=R){
			hp[rt].Insert(v), mx[y]=hp[rt].Top(), son[y][0]=lson, son[y][1]=rson;
			return ;
		}
		int m=l+r>>1; mx[y]=mx[x];//!
		if(L<=m)
			if(m<R) Insert(son[y][0],lson,ToL,L,R,v), Insert(son[y][1],rson,ToR,L,R,v);
			else son[y][1]=rson, Insert(son[y][0],lson,ToL,L,R,v);
		else son[y][0]=lson, Insert(son[y][1],rson,ToR,L,R,v);
	}
	void Delete(int &y,int x,int l,int r,int rt,int L,int R,int v)
	{
		y=++tot;
		if(L<=l && r<=R){
			hp[rt].Delete(v), mx[y]=hp[rt].Top(), son[y][0]=lson, son[y][1]=rson;
			return;
		}
		int m=l+r>>1; mx[y]=mx[x];//!
		if(L<=m)
			if(m<R) Delete(son[y][0],lson,ToL,L,R,v), Delete(son[y][1],rson,ToR,L,R,v);
			else son[y][1]=rson, Delete(son[y][0],lson,ToL,L,R,v);
		else son[y][0]=lson, Delete(son[y][1],rson,ToR,L,R,v);
	}
	int Query(int x,int l,int r,int pos)
	{
		if(!x) return 0;//���ûɶ�ð�...
		if(l==r) return mx[x];
		int m=l+r>>1;
		if(pos<=m) return std::max(mx[x],Query(lson,l,m,pos));
		else return std::max(mx[x],Query(rson,m+1,r,pos));
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(), Q=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<=n; ++i) las[i]=n+1;
	for(int i=n; i; --i) nxt[i]=las[A[i]], las[A[i]]=i;
	for(int i=n; i; --i)//ֱ��ö��ֵ�����Ϳ��԰� ��˵���Ų���ѻ������ 
		if(las[i]<=n) T.Insert(root[rcnt],root[rcnt++],1,n,1,las[i],nxt[las[i]]-1,i);//����˳�� 
	pos[1]=root[rcnt];//root[rcnt] not rcnt��_��
	for(int i=1; i<n; ++i)
	{
		T.Delete(root[rcnt],root[rcnt++],1,n,1,i,nxt[i]-1,A[i]);
		if(nxt[i]<=n)
			T.Insert(root[rcnt],root[rcnt++],1,n,1,nxt[i],nxt[nxt[i]]-1,A[i]);
		pos[i+1]=root[rcnt];
	}
	for(int ans=0,i=1,l,r; i<=Q; ++i)
	{
		l=(read()+ans)%n+1, r=(read()+ans)%n+1;
		if(l>r) std::swap(l,r);//l>r&&(std::swap(l,r),1);
		printf("%d\n",ans=T.Query(pos[l],1,n,r));
	}
	return 0;
}
