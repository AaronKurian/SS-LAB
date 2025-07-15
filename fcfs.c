#include <stdio.h>

struct Process{
	int name;
	int AT;
	int BT;
	int CT;
	int TAT;
	int WT;
}p[20],t;


void main(){
	int n;
	printf("enter no. of processes:");
	scanf("%d",&n);	
	for(int i=0;i<n;i++){
		printf("enter process %d details:\n",i+1);
		p[i].name=i+1;
		printf("enter Arrival Time:");
		scanf("%d",&p[i].AT);
		printf("enter Burst Time:");
		scanf("%d",&p[i].BT);
		}
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1-i;j++){
			if(p[j].AT>p[j+1].AT){
				t=p[j];
				p[j]=p[j+1];
				p[j+1]=t;
			}
		}
	}
	
	int currt=0;
	float tat=0;
	float wt=0;
	for(int i=0;i<n;i++){
		currt+=p[i].BT;
		p[i].CT=currt;
		p[i].TAT=p[i].CT-p[i].AT;
		p[i].WT=p[i].TAT-p[i].BT;
		tat+=p[i].TAT;
		wt+=p[i].WT;
	}
	printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].name,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT);
		tat=tat+p[i].TAT;
		wt=wt+p[i].WT;
	}
	printf("Gantt chart : \n");
	for(int i=0;i<n;i++){
		printf("|\tP%d\t",p[i].name);
	}
	printf("|\n");
	printf("0\t");
	for(int i=0;i<n;i++){
		printf("\t%d\t",p[i].CT);
	}
	printf("\n");
	printf("Avg. TAT=%f\n",tat/n);
	printf("Avg. WT=%f\n",wt/n);
}
