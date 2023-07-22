#include <bits/stdc++.h>
using namespace std;
//结点 
struct hfnode{
	char ch;//名称 
	int weight,parent,lch,rch,flag;
	struct node *head;//编码 
};
struct node{
	struct node *next;
	int data;
};
//树 
struct hftreenode{
	int size; //结点个数 
	hfnode *htnode;
};
//哈夫曼树初始化 
void inithft(hftreenode &hft,int n){
	hft.size=2*n-1;
	hft.htnode=new hfnode[2*n-1];
} 
//创建哈夫曼树,显示静态链表 
void createhft(hftreenode &hft,int n){
	int i;
	for(i=0;i<n;i++){
		printf("输入第%d个结点的字符及权重(用_代替空格)：",i+1);
		cin>>hft.htnode[i].ch>>hft.htnode[i].weight;
//		printf("%c%d",hft.htnode[i].ch,hft.htnode[i].weight);
		hft.htnode[i].lch=hft.htnode[i].rch=hft.htnode[i].parent=-1;
//		hft.htnode[i].flag=0;//还没加入树中 
	}
	for(i=n;i<2*n-1;i++) {
		hft.htnode[i].lch=hft.htnode[i].rch=hft.htnode[i].parent=-1;
	}
	int j;
	int minposition1,minposition2,t;
	int m1,m2;
	for(i=n;i<2*n-1;i++){
		m1=m2=9999;//m2>=m1
		minposition1=minposition2=-1;
		for(j=0;j<i;j++){
			if(hft.htnode[j].parent==-1){
				if(hft.htnode[j].weight<m1){
					minposition2=minposition1;
					minposition1=j;
					m2=m1;
					m1=hft.htnode[j].weight;
				}else if(hft.htnode[j].weight<m2){
					minposition2=j;
					m2=hft.htnode[j].weight;
				}
			}
		}
		hft.htnode[minposition1].parent=i;
		if(minposition2!=-1) hft.htnode[minposition2].parent=i;
		if(minposition2==-1) hft.htnode[i].weight=m1;
		else hft.htnode[i].weight=m1+m2;
		hft.htnode[i].lch=minposition1;
		hft.htnode[i].rch=minposition2;
	}

	FILE *fa=fopen("hfmTree.txt","w");
	printf("下标位置 字符 权值 左孩子 右孩子 双亲\n");
	for(i=0;i<n-1;i++){
		fprintf(fa,"%d  %c  %d  %d  %d  %d\n",i,hft.htnode[i].ch,hft.htnode[i].weight,hft.htnode[i].lch,hft.htnode[i].rch,hft.htnode[i].parent);
		printf("%d  %c  %d  %d  %d  %d\n",i,hft.htnode[i].ch,hft.htnode[i].weight,hft.htnode[i].lch,hft.htnode[i].rch,hft.htnode[i].parent);
	}
	printf("下标位置 权值 左孩子 右孩子 双亲\n");
	for(i=n;i<2*n-1;i++){
		printf("%d  %d  %d  %d  %d\n",i,hft.htnode[i].weight,hft.htnode[i].lch,hft.htnode[i].rch,hft.htnode[i].parent);
		fprintf(fa,"%d  %d  %d  %d  %d\n",i,hft.htnode[i].weight,hft.htnode[i].lch,hft.htnode[i].rch,hft.htnode[i].parent);
	}
	fclose(fa);
} 
//写出字符对应的哈夫曼编码 
void bianma(hftreenode &hft,int n){
	int j,k,i;
	node *q,*p;
	FILE *fa=fopen("hfmTree.txt","a");
	for(i=0;i<n;i++){
		hft.htnode[i].head=new node;
		hft.htnode[i].head->next=NULL;
		j=i;
		while(hft.htnode[j].parent!=-1){
			k=hft.htnode[j].parent;
			if(j==hft.htnode[k].lch){
				q=new node;
				q->next=hft.htnode[i].head->next;
				hft.htnode[i].head->next=q;
				q->data=0;
			}else if(j==hft.htnode[k].rch){
				q=new node;
				q->next=hft.htnode[i].head->next;
				hft.htnode[i].head->next=q;
				q->data=1;
			}
			j=k;
		}
		printf("%c  ",hft.htnode[i].ch);
		fprintf(fa,"%c  ",hft.htnode[i].ch);
		p=hft.htnode[i].head->next;
		while(p!=NULL){
			printf("%d",p->data);
			fprintf(fa,"%d",p->data);
			p=p->next;
		}
		printf("\n");
		fprintf(fa,"\n");
	}
	fclose(fa);
}
//输出字符串的编码 
void bianma1(hftreenode &hft,int n){
//	FILE *fa=fopen("hfmTree.txt","r");
	FILE *fb=fopen("ToBeTran.txt","r");
	FILE *fc=fopen("CodeFile.txt","w");
	char zhengwen[100];
	fgets(zhengwen,100,fb);
	printf("\n%s",zhengwen);
	int i,j;
	node *p;
	
	char ch;
	j=0;
	printf("\n");
	while(ch=zhengwen[j]){
		if(ch=='\0') break;
		if(ch==' '){
			ch='_';
		}
		for(i=0;i<n;i++){
			if(hft.htnode[i].ch==ch){
				p=hft.htnode[i].head->next;
				while(p!=NULL){
					printf("%d",p->data);
					fprintf(fc,"%d",p->data);
					p=p->next;
				}
				break;
			}
		}
		j++;
	}
//	fclose(fa);
	fclose(fb);
	fclose(fc);
	
}
//50个编码一行 
void Print(){
	FILE *fc=fopen("CodeFile.txt","r");
	FILE *fd=fopen("CodePrin.txt","w");
	char zhengwen[600];
	fgets(zhengwen,600,fc);
	int i;
	printf("\n\n");
	for(i=0;zhengwen[i]!='\0';i++){
		if(i%50==0){
		printf("\n");
		fprintf(fd,"\n");
		}
		printf("%c",zhengwen[i]);
		fprintf(fd,"%c",zhengwen[i]);
	}
	fclose(fc);
	fclose(fd);
}
//译码 
void decoding(hftreenode &hft,int n){
	FILE *fa=fopen("CodeFile.txt","r");
	FILE *fb=fopen("TextFile.txt","w");
	char zhengwen[600];
	fgets(zhengwen,600,fa);
	int i=0,j;
	char ch;
//	node *p;
	int position;
//	printf("\n%s",zhengwen);
	printf("\n");
	while(zhengwen[i]!='\0'){
		j=i;
//		p=hft.htnode[2*n-1];
		position=2*n-2;
//		printf("%d",position);
		while(1){
			if(zhengwen[j]=='0'){
				position=hft.htnode[position].lch;
//				printf("%d\n",position);
				if(hft.htnode[position].lch==-1){
					if(hft.htnode[position].ch=='_'){
						printf(" ");
						fprintf(fb," ");
					}
					else{
						fprintf(fb,"%c",hft.htnode[position].ch);
						printf("%c",hft.htnode[position].ch);
					}
					break;
				}
			}else if (zhengwen[j]=='1'){
				position=hft.htnode[position].rch;
//				printf("%d\n",position);
				if(hft.htnode[position].lch==-1){
					if(hft.htnode[position].ch=='_'){
						printf(" ");
						fprintf(fb," ");
					}
					else{
						fprintf(fb,"%c",hft.htnode[position].ch);
						printf("%c",hft.htnode[position].ch);
					}
					break;
				}
			}
			j++;
			
		}
		i=j;
		i++;
	}
	fclose(fa);
	fclose(fb);
}
int main(){
	int n;
	hftreenode hft;
	hfnode hfn[100];
	printf("结点个数：");
	scanf("%d",&n);
	inithft(hft,n);
	createhft(hft,n);
	bianma(hft,n);
	bianma1(hft,n);
	Print();
	decoding(hft,n);
	return 0;
}

/*
27
_ 186
A 64
B 13
C 22
D 32
E 103
F 21
G 15
H 47
I 57
J 1
K 5
L 32
M 20
N 57
O 63
P 15
Q 1
R 48
S 51
T 80
U 23
V 8
W 18
X 1
Y 16
Z 1
*/ 
