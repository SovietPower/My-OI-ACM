/*
关于带权二叉树(每个节点都有其权值的树): 
(1)节点的带权路径长度为该节点到树根之间的路径长度(深度)与节点上权的乘积 
(2)树的路径长度(Weighted Path Length of Tree,简记为WPL)是从树根到每一个节点的路径长度之和 
记作WPL=∑Wi*Li 

哈夫曼编码:较短的编码能够节省存储空间、提高效率 
假设所有编码等长，则表示n个不同字符需要log2n位，称为固定长度编码，如ASCII码 
如果每个字符使用频率相同，则固定长度编码是空间效率最高的方法 
但是实际中每个字符使用频率往往有很大差异，所以利用出现频率进行编码 
常出现的字符编码较短，不常出现的字符编码较长，这种编码方式为不等长编码，如五笔型输入法 

哈弗曼二叉树: 
假设有n个权值:w1,w2,...,wn，构造一棵有n个叶节点的二叉树，每个叶节点权值为wi，则带权路径长度最小的二叉树就叫"哈夫曼二叉树" 
最主要特点：叶子权越大就越靠近根节点，权越小越远离根节点 
利用贪心构造：(1)构造集合S={T1,T2,...,Tn}，其中每棵二叉树Ti都只含一个权值为Wi的根节点，左右为空子树 
(2)在S中选取根节点权值最小的两棵二叉树，分别作为左右子树构造一棵新树，根节点权值为左右子树根节点权值之和 
(3)在S中删去这两棵树，并插入新生成的树 
(4)重复(2)(3)，直到S中只有一棵树 

对于本题可以用k进制编码，其可以用k叉树，每次可以合并k棵子树 
要注意如果直接对n个节点进行合并，最后一次合并可能会有少于k个子树的情况 
这时在最后合并这不到k棵子树就会导致错误 
所以事先插入y个权值为0的虚拟节点：n-x(k-1)+y=1, y=k-1-(n-1)%(k-1)
还要求深度最小，排序时作为第二关键字即可 
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
#define mp std::make_pair//std::速度相当 
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
	if(y)//仅在最后一层不满时添加 
		y=k-1-y;//注意要加的值 
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
