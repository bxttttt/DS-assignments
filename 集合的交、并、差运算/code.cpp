#include <bits/stdc++.h>
using namespace std;

struct linklist{
	char data;
	linklist *next;
}*A,*B;
//初始化链表 
void initList(linklist *&s){
	s=new linklist;
	s->next=NULL;
	printf("初始化成功\n");
}
void print(linklist *s);
//操作1 输入集合A 
void inputA(){
	initList(A);
	int n,i,x,flag;
	linklist *p,*q;
	printf("输入字符串：");
	getchar();
	char a[100];
	gets(a);
	p=A;
	for(i=0;a[i]!='\0';i++){
		if(a[i]<'a'||a[i]>'z') continue;
		q=A->next;
		flag=1;
		while(q!=NULL){
			if(q->data==a[i]){
				flag=0;
				break;
			}
			q=q->next;
		}
		if(flag==0){
			continue;
		}
		p->next=new linklist;
		p=p->next;
		p->data=a[i];
		p->next=NULL;
	}
	print(A);
	return ;
}
//操作2 输入集合B 
void inputB(){
	initList(B);
	int n,i,x,flag;
	linklist *p,*q;
	printf("输入字符串：");
	char a[100];
	getchar();
	gets(a);
	p=B;
	for(i=0;a[i]!='\0';i++){
		if(a[i]<'a'||a[i]>'z') continue;
		q=B->next;
		flag=1;
		while(q!=NULL){
			if(q->data==a[i]){
				flag=0;
				break;
			}
			q=q->next;
		}
		if(flag==0){
			continue;
		}
		p->next=new linklist;
		p=p->next;
		p->data=a[i];
		p->next=NULL;
	}
	print(B);
	return ;
}

//输出集合
void print(linklist *s){
	linklist *p;
	p=s->next;
	if(p==NULL) printf("空集\n");
	else{
		while(p!=NULL){
			printf("%c",p->data);
			p=p->next;
		}
		printf("\n");
	}
	return;
} 
//操作3 交集 
void jiaoji(linklist *a,linklist *b){
	linklist *p,*q;
	int flag=1;
	printf("{");
	for(p=a->next;p!=NULL;p=p->next){
		for(q=b->next;q!=NULL;q=q->next){
			if(p->data==q->data){
				flag=0;
				printf("%c,",p->data);
				break;
			}
		}
	}
	if(flag==0) printf("\b}\n");
	else printf("}\n");
	return;
} 
//copy
void copy(linklist *a,linklist *&s){
	linklist *p,*q;
	q=s;
	for(p=a->next;p!=NULL;p=p->next){
		q->next=new linklist;
		q=q->next;
		q->data=p->data;
	}
	q->next=NULL;
	return ;
}
//操作4 并集 
void bingji(linklist *a,linklist *b){
	linklist *c,*p,*q,*r;
	c=new linklist;
	copy(a,c);
	for(p=b->next;p!=NULL;p=p->next){
		for(q=a->next;q!=NULL;q=q->next){
			if(p->data==q->data){
				break;
			}
		}
		if(q==NULL){
			r=new linklist;
			r->data=p->data;
			r->next=c->next;
			c->next=r;
		}
	}
	print(c);
}
//操作5 6 差集 
void chaji(linklist *a,linklist *b){
	linklist *c,*p,*q,*r;
	c=new linklist;
	copy(a,c);
//	print(c);
//	print(b);
	for(p=c;p->next!=NULL;){
		for(q=b->next;q!=NULL;q=q->next){
//			printf("%d  %d\n",p->next->data,q->data);
			if(p->next->data==q->data){
				r=p->next;
				p->next=p->next->next;
				free(r);
				break;
			}
		}
		if(q==NULL) p=p->next;
	} 
	print(c);
}
int main(){
	printf("说明：\n1.输入集合A个数（小于100）和集合A\n2.输入集合B个数（小于100）和集合B\n3.求交集\n4.求并集\n5.求A-B\n6.求B-A\n7.退出\n");
	int x;
	linklist *p;
	while(1){
		printf("输入操作：");
		scanf("%d",&x);
		if(x==7) return 0;
		else if(x==1){
			inputA();
			printf("输入成功\n");
			print(A);
		}else if(x==2){
			inputB();
			printf("输入成功\n");
			print(B);
		}else if(x==3){
			jiaoji(A,B);
		}else if(x==4){
			bingji(A,B);
		}else if(x==5){
			chaji(A,B);
		}else if(x==6){
			chaji(B,A);
		}
		
	}
	
	return 0;
}
