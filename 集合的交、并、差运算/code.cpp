#include <bits/stdc++.h>
using namespace std;

struct linklist{
	char data;
	linklist *next;
}*A,*B;
//��ʼ������ 
void initList(linklist *&s){
	s=new linklist;
	s->next=NULL;
	printf("��ʼ���ɹ�\n");
}
void print(linklist *s);
//����1 ���뼯��A 
void inputA(){
	initList(A);
	int n,i,x,flag;
	linklist *p,*q;
	printf("�����ַ�����");
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
//����2 ���뼯��B 
void inputB(){
	initList(B);
	int n,i,x,flag;
	linklist *p,*q;
	printf("�����ַ�����");
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

//�������
void print(linklist *s){
	linklist *p;
	p=s->next;
	if(p==NULL) printf("�ռ�\n");
	else{
		while(p!=NULL){
			printf("%c",p->data);
			p=p->next;
		}
		printf("\n");
	}
	return;
} 
//����3 ���� 
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
//����4 ���� 
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
//����5 6 � 
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
	printf("˵����\n1.���뼯��A������С��100���ͼ���A\n2.���뼯��B������С��100���ͼ���B\n3.�󽻼�\n4.�󲢼�\n5.��A-B\n6.��B-A\n7.�˳�\n");
	int x;
	linklist *p;
	while(1){
		printf("���������");
		scanf("%d",&x);
		if(x==7) return 0;
		else if(x==1){
			inputA();
			printf("����ɹ�\n");
			print(A);
		}else if(x==2){
			inputB();
			printf("����ɹ�\n");
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
