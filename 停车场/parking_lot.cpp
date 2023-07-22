#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int N;//ͣ�������� 
int Price;//ÿСʱ�ķ��� 
//int j=0;
//int k=1;
//���� 
typedef struct{
	int license;
	int time;
	int flag;//1��ʾ�뿪��0��ʾͣ�� 
}cars;
//ͣ���� 
typedef struct{
	cars data[100];//�洢license 
	int top;//0��ʾ1����Ҳû�� 
}parkStack;
//��ʱͣ����
typedef struct{
	cars data[100];
	int top;
}temporaryStack; 
//���
typedef struct waitCar{
//	cars data[100];
	cars t;
	struct waitCar *next;
}waitCar; 
typedef struct{
	waitCar *front;
	waitCar *rear;
}waitCarQueue;
//��ʼ��ͣ����ջ 
void initParkStack(parkStack *s){
	s->top=0;
}
//��ʼ��������� 
void initWaitCarQueue(waitCarQueue *q){
	q->front=new waitCar;
	q->rear=q->front;
	q->front->next=NULL;
}
//��ʼ����ʱջ 
void initTemporaryStack(temporaryStack *s){
	s->top=0;
} 
//ͣ����������1����������0 
int stackFull(parkStack *s){
	if(s->top==N){
		return 1;
	}return 0;
}
//ͣ�����շ���1�����շ���0 
int stackEmpty(parkStack *s){
	if(s->top==0){
		return 1;
	}return 0;
}
//�������� 
void arrive(parkStack *ps,waitCarQueue *wcq,int license){
	waitCar *p;
	int time;
	p=new waitCar;
	p->next=NULL;
	if(ps->top<N){
		ps->top++;
		printf("����ʱ�䣺");
		scanf("%d",&time);
		ps->data[ps->top].license=license;
		ps->data[ps->top].time=time;
		printf("ͣ���ɹ������ƺ�%d��λ��%d��ʱ��%d\n",license,ps->top,time);
	}else{
//		j++;
//		p->data[j].license=license;
//		p->next=NULL;
//		wcq->rear->next=p;
//		wcq->rear=p;
		p->t.license=license;
		p->next=NULL;
		wcq->rear->next=p;
		wcq->rear=p;
		printf("�����������ƺ�%d\n",license);
	}
}
//�����뿪
void leave(parkStack *ps,waitCarQueue *wcq,int license,int time){
	temporaryStack ts;
	initTemporaryStack(&ts);
	int timeSum;
	int i;
	waitCar *r,*s;
	//�жϳ��Ƿ���ͣ���� 
	for(i=1;i<=ps->top;i++){
		if(ps->data[i].license==license) break;
	}
	//�������ͣ������ 
	if(i<=ps->top){
		ts.top=0;
		while(ps->data[ps->top].license!=license){
			ts.top++;
			ts.data[ts.top]=ps->data[ps->top];
			printf("����Ϊ%d�ĳ�������ʱͣ����\n",ps->data[ps->top].license);
			ps->top--;
		}
		timeSum=time-ps->data[ps->top].time;
		printf("����Ϊ%d�ĳ���ͣ������ͣ��ʱ��Ϊ%d������Ϊ%d\n",ps->data[ps->top].license,timeSum,timeSum*Price);
		ps->top--;
		while(ts.top>0){
			ps->top++;
			ps->data[ps->top]=ts.data[ts.top];
			printf("����Ϊ%d�ĳ��ص�ͣ����\n",ts.data[ts.top].license); 
			ts.top--;
		}
		if(wcq->front==wcq->rear){
			printf("�����û�г�����ͣ����\n");
		}else{
			r=wcq->front->next;
			wcq->front->next=wcq->front->next->next;
			if(wcq->rear==r){
				wcq->rear=wcq->front;
				wcq->rear->next=NULL;
			}
			ps->top++;
//			ps->data[ps->top]=r->data[k];
//			ps->data[ps->top].time=time;
//			printf("%d����ͣ����");
//			k++;
			ps->data[ps->top]=r->t;
			ps->data[ps->top].time=time;
			printf("����ϵ�%d����ͣ����\n",r->t.license);
		}
		return;
	}else{
		if(wcq->front==wcq->rear){
			printf("û��������\n");
		}else{
			r=wcq->front;
			while(r!=wcq->rear){
				if(r->next->t.license==license) break;
				r=r->next;
				if(r==wcq->rear){
					printf("û��������\n");
					return;
				}
			}
			s=r->next;
			if(s==wcq->rear){
				wcq->rear=r;
				r->next==NULL;
				printf("�����%d���뿪�����շ�\n",s->t.license);
				free(s);
				return;
			}
			r->next=r->next->next;
			printf("�����%d���뿪�����շ�\n",s->t.license);
			free(s);
		}
	}
	
} 

int main(){
	int license,time;
	parkStack ps;
	waitCarQueue wcq;
	temporaryStack ts;
	initParkStack(&ps);
	initWaitCarQueue(&wcq);
	initTemporaryStack(&ts);
	waitCar *p,*q;
	printf("ͣ����������");
	scanf("%d",&N); 
	printf("ͣ��ÿСʱ��ȡ�ķ��ã�");
	scanf("%d",&Price); 
	printf("˵����\nA.��������\nD.�����뿪\nE.�˳�ϵͳ\n"); 
	char point;
	while(1){
		scanf("%c",&point);
		if(point=='E') return 0;
		else if(point=='A'){
			printf("��������\n���복�ƺţ�");
			scanf("%d",&license);
			arrive(&ps,&wcq,license);
		}else if(point=='D'){
			printf("�����뿪\n���복�ƺţ�");
			scanf("%d",&license);
			printf("�����뿪ʱ�䣺");
			scanf("%d",&time);
			leave(&ps,&wcq,license,time);
		}
		
	} 
	return 0;
}
/*
A 1 5
A 2 10
D 1 15
A 3 20
A 4 25
A 5 30
D 2 35
D 4 40
E 0 0
*/ 
