#include<bits/stdc++.h>
using namespace std;
#define maxd 1000
#define n 12
struct dd{
	char name[20];
	char jianjie[30];
	int bh;
	int d;
	int flag;
}vi[20][20]; 
int graph[20][20]; 
//int zuiduanlu[20];
int prev[20];
//��ʼ������ 
void inputdata(){
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			vi[i][j].d=maxd;
			graph[i][j]=maxd;
		}
	}
	for(i=1;i<=n;i++){
		vi[i][i].d=0;
		graph[i][i]=0;
	}
	vi[0][1].bh=1;
	strcpy(vi[0][1].name,"������");
	strcpy(vi[0][1].jianjie,"�����ĵط�");
	vi[0][2].bh=2;
	strcpy(vi[0][2].name,"8��");
	strcpy(vi[0][2].jianjie,"ûȥ���ĵط�"); 
	vi[0][3].bh=3;
	strcpy(vi[0][3].name,"ͼ���");
	strcpy(vi[0][3].jianjie,"��ĵط�");
	vi[0][4].bh=4;
	strcpy(vi[0][4].name,"�ۺ�¥");
	strcpy(vi[0][4].jianjie,"�����ĵط�");
	vi[0][5].bh=5;
	strcpy(vi[0][5].name,"7��");
	strcpy(vi[0][5].jianjie,"����������Ľ�ѧ¥");
	vi[0][6].bh=6;
	strcpy(vi[0][6].name,"4��");
	strcpy(vi[0][6].jianjie,"����Եĵط�");
	vi[0][7].bh=7;
	strcpy(vi[0][7].name,"�ʶ�");
	strcpy(vi[0][7].jianjie,"���յĵط�");
	vi[0][8].bh=8;
	strcpy(vi[0][8].name,"3��");
	strcpy(vi[0][8].jianjie,"�����ѧԺ");
	vi[0][9].bh=9;
	strcpy(vi[0][9].name,"����");
	strcpy(vi[0][9].jianjie,"������ĵط�");
	vi[0][10].bh=10;
	strcpy(vi[0][10].name,"����");
	strcpy(vi[0][10].jianjie,"������ĵط�");
	vi[0][11].bh=11;
	strcpy(vi[0][11].name,"����");
	strcpy(vi[0][11].jianjie,"������ĵط�");
	vi[0][12].bh=12;
	strcpy(vi[0][12].name,"6��");
	strcpy(vi[0][12].jianjie,"����ĵط�");
	vi[1][2].d=20;vi[2][1].d=20;
	vi[1][12].d=25;vi[12][1].d=25;
	vi[2][12].d=10;vi[12][2].d=10;
	vi[1][9].d=30;vi[9][1].d=30;
	vi[9][12].d=35;vi[12][9].d=35;
	vi[9][10].d=5;vi[10][9].d=5;
	vi[9][11].d=7;vi[11][9].d=7;
	vi[11][6].d=11;vi[6][11].d=11;
	vi[2][3].d=9;vi[3][2].d=9;
	vi[6][7].d=13;vi[7][6].d=13;
	vi[3][4].d=17;vi[4][3].d=17;
	vi[3][5].d=21;vi[5][3].d=21;
	vi[7][5].d=25;vi[5][7].d=25;
	vi[7][8].d=28;vi[8][7].d=28;
	vi[5][8].d=32;vi[8][5].d=32;
	vi[10][11].d=4;vi[11][10].d=4; 
	graph[1][2]=20;graph[2][1]=20;
	graph[1][12]=25;graph[12][1]=25;
	graph[2][12]=10;graph[12][2]=10;
	graph[1][9]=30;graph[9][1]=30;
	graph[9][12]=35;graph[12][9]=35;
	graph[9][10]=5;graph[10][9]=5;
	graph[9][11]=7;graph[11][9]=7;
	graph[11][6]=11;graph[6][11]=11;
	graph[2][3]=9;graph[3][2]=9;
	graph[6][7]=13;graph[7][6]=13;
	graph[3][4]=17;graph[4][3]=17;
	graph[3][5]=21;graph[5][3]=21;
	graph[7][5]=25;graph[5][7]=25;
	graph[7][8]=28;graph[8][7]=28;
	graph[5][8]=32;graph[8][5]=32;
	graph[10][11]=4;graph[11][10]=4;
}
//��ͼ 
void mapp(){
	printf("------------------------------------------\n");
	printf("| 1.��   || 2.8��  ||3.ͼ���||4.�ۺ�¥  |\n");
	printf("|   ��   ||--------||--------||----------|\n");
	printf("|   ��   ||        |          |          |\n");
	printf("|--------||12.6��  |          | 5.7��    |\n");
	printf("| 9.��   ||        |     ��   |----------|\n");
	printf("|   ��   ||--------|          |^^^^^^^^^^|\n");
	printf("|   ��   | ^^^^^^^^  ------    ^^^^^^^^^^|\n");
	printf("|--------||        ||7.��  |             |\n");
	printf("|��| ��  ||6.4��   ||  ��  |  |------|   |\n");
	printf("|��| ��  ||--------||------|  | 8.3  |   |\n");
	printf("|��| ��  |                    |   �� |   |\n");
	printf("|10|--11-|                    |------|   |\n");
	printf("------------------------------------------\n");
}
//�������Ʋ�ѯ
void searchName(){
	printf("�������ƣ�");
	char name[10];
	scanf("%s",name);
	int i;
	for(i=1;i<=n;i++){
		if(strcmp(name,vi[0][i].name)==0){
			printf("%s\n",vi[0][i].jianjie);
			return;
		}
	}
	if(i>n){
		printf("nothing\n");
		return; 
	}
}
//�����Ų�ѯ
void searchNum(){
	int x;
	printf("�����ţ�");
	scanf("%d",&x);
	printf("%s\n%s\n",vi[0][x].name,vi[0][x].jianjie);
	return;
}

//���·��
void dijstra(){
	int x,y,z,i;
	printf("�����������\n");
	while(1){
		scanf("%d%d",&y,&x);
		if(x<1||x>n){
			printf("��������\n");
			continue;
		}else if(y<1||y>n){
			printf("��������\n");
			continue;
		}else break;
	}
	for(i=1;i<=n;i++) vi[0][i].flag=0;
	z=x;
	int j;
	int minposition,mind;
	
	j=0;
	for(i=1;i<=n;i++){
		prev[i]=x;
	}
	vi[0][x].flag=1;//���õ����̾�����ȷ��
	while(1){
		
		mind=maxd;
		 
		for(i=1;i<=n;i++){
			if(vi[0][i].flag==1) continue;
			if(vi[x][i].d<mind){
				mind=vi[x][i].d;
				minposition=i;
			}
		}
//		zuiduanlu[j]=minposition;
//		printf("%d\n",minposition);
		vi[x][minposition].d=vi[minposition][x].d=mind;
		vi[0][minposition].flag=1;
		for(i=1;i<=n;i++){
			if(vi[0][i].flag==1) continue;
			if(vi[x][i].d>=(mind+vi[minposition][i].d)){
				vi[x][i].d=vi[i][x].d=mind+vi[minposition][i].d;
				prev[i]=minposition;
			}
			
		}
		if(vi[0][y].flag==1) break;
	}
	printf("%d\n",vi[x][y].d);
	i=y;
	printf("%d",y);
	while(1){
		i=prev[i];
		printf("->%d",i);
		if(i==x) break;
	}
	printf("\n");
}
//���м�·��
bool visited[20];
int passed[20];
int pass;
void dfs(int start,int end){
	visited[start]=true;
	pass++;
	passed[pass]=start;
	int i;
	if(start==end){
		for(i=0;i<pass;i++){
			printf("%d->",passed[i]);
		}
		printf("%d\n",end);
		pass--;
		visited[start]=false;
		return;
	}
	for(i=1;i<=n;i++){
		if(!visited[i]&&graph[start][i]<maxd){
			dfs(i,end);
		}
	}
	pass--;
	visited[start]=false;
	return;
}
int main(){
	int x,y,z;
	inputdata();
	printf("˵����\n");
	printf("1.������Ϣ��ѯ\n");
	printf("2.���·����ѯ\n");
	printf("3.���п��ܵļ�·��\n");
	printf("4.�˳�ϵͳ\n");
	mapp();
	while(1){
		printf("���������");
		scanf("%d",&x);
		if(x==4){
			return 0;
		}else if(x==1){
			printf("���������\n");
			printf("1.�������Ʋ�ѯ\n");
			printf("2.�����Ų�ѯ\n");
			scanf("%d",&y);
			if(y==1){
				searchName();
			}else if(y==2){
				searchNum();
			}
		}else if(x==2){
			
			dijstra();
		}else if(x==3){
			pass=-1;
			for(z=1;z<=n;z++) visited[z]=false;
			printf("�����������\n");
			while(1){
				scanf("%d%d",&z,&y);
				if(z<1||z>n){
					printf("��������\n");
					continue;
				}else if(y<1||y>n){
					printf("��������\n");
					continue;
				}else break;
			}
			dfs(z,y);
		}
		
	}
	return 0;
}
