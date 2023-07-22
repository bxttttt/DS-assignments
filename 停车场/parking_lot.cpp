#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int N;//停车场容量 
int Price;//每小时的费用 
//int j=0;
//int k=1;
//汽车 
typedef struct{
	int license;
	int time;
	int flag;//1表示离开，0表示停着 
}cars;
//停车场 
typedef struct{
	cars data[100];//存储license 
	int top;//0表示1辆车也没有 
}parkStack;
//临时停车场
typedef struct{
	cars data[100];
	int top;
}temporaryStack; 
//便道
typedef struct waitCar{
//	cars data[100];
	cars t;
	struct waitCar *next;
}waitCar; 
typedef struct{
	waitCar *front;
	waitCar *rear;
}waitCarQueue;
//初始化停车场栈 
void initParkStack(parkStack *s){
	s->top=0;
}
//初始化便道队列 
void initWaitCarQueue(waitCarQueue *q){
	q->front=new waitCar;
	q->rear=q->front;
	q->front->next=NULL;
}
//初始化临时栈 
void initTemporaryStack(temporaryStack *s){
	s->top=0;
} 
//停车场满返回1，不满返回0 
int stackFull(parkStack *s){
	if(s->top==N){
		return 1;
	}return 0;
}
//停车场空返回1，不空返回0 
int stackEmpty(parkStack *s){
	if(s->top==0){
		return 1;
	}return 0;
}
//车辆到达 
void arrive(parkStack *ps,waitCarQueue *wcq,int license){
	waitCar *p;
	int time;
	p=new waitCar;
	p->next=NULL;
	if(ps->top<N){
		ps->top++;
		printf("输入时间：");
		scanf("%d",&time);
		ps->data[ps->top].license=license;
		ps->data[ps->top].time=time;
		printf("停车成功，车牌号%d，位置%d，时间%d\n",license,ps->top,time);
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
		printf("进入便道，车牌号%d\n",license);
	}
}
//车辆离开
void leave(parkStack *ps,waitCarQueue *wcq,int license,int time){
	temporaryStack ts;
	initTemporaryStack(&ts);
	int timeSum;
	int i;
	waitCar *r,*s;
	//判断车是否在停车场 
	for(i=1;i<=ps->top;i++){
		if(ps->data[i].license==license) break;
	}
	//如果车在停车场内 
	if(i<=ps->top){
		ts.top=0;
		while(ps->data[ps->top].license!=license){
			ts.top++;
			ts.data[ts.top]=ps->data[ps->top];
			printf("车牌为%d的车进入临时停车场\n",ps->data[ps->top].license);
			ps->top--;
		}
		timeSum=time-ps->data[ps->top].time;
		printf("车牌为%d的车在停车场的停车时间为%d，费用为%d\n",ps->data[ps->top].license,timeSum,timeSum*Price);
		ps->top--;
		while(ts.top>0){
			ps->top++;
			ps->data[ps->top]=ts.data[ts.top];
			printf("车牌为%d的车回到停车场\n",ts.data[ts.top].license); 
			ts.top--;
		}
		if(wcq->front==wcq->rear){
			printf("便道上没有车进入停车场\n");
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
//			printf("%d进入停车场");
//			k++;
			ps->data[ps->top]=r->t;
			ps->data[ps->top].time=time;
			printf("便道上的%d进入停车场\n",r->t.license);
		}
		return;
	}else{
		if(wcq->front==wcq->rear){
			printf("没有这辆车\n");
		}else{
			r=wcq->front;
			while(r!=wcq->rear){
				if(r->next->t.license==license) break;
				r=r->next;
				if(r==wcq->rear){
					printf("没有这辆车\n");
					return;
				}
			}
			s=r->next;
			if(s==wcq->rear){
				wcq->rear=r;
				r->next==NULL;
				printf("便道上%d车离开，不收费\n",s->t.license);
				free(s);
				return;
			}
			r->next=r->next->next;
			printf("便道上%d车离开，不收费\n",s->t.license);
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
	printf("停车场容量：");
	scanf("%d",&N); 
	printf("停车每小时收取的费用：");
	scanf("%d",&Price); 
	printf("说明：\nA.车辆到达\nD.车辆离开\nE.退出系统\n"); 
	char point;
	while(1){
		scanf("%c",&point);
		if(point=='E') return 0;
		else if(point=='A'){
			printf("车辆到达\n输入车牌号：");
			scanf("%d",&license);
			arrive(&ps,&wcq,license);
		}else if(point=='D'){
			printf("车辆离开\n输入车牌号：");
			scanf("%d",&license);
			printf("输入离开时间：");
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
