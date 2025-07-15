#include <stdio.h>
#include <stdlib.h>

struct Process {
	int name;
	int AT;
	int BT;
	int CT;
	int TAT;
	int WT;
	int pr;
}p[20],tem;


void main() {
	int n;
	printf("Enter n : ");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		printf("Enter details of process %d : \n",i+1);
		p[i].name = i+1;
		printf("AT : ");
		scanf("%d",&p[i].AT);
		printf("BT : ");
		scanf("%d",&p[i].BT);
		printf("Priority : ");
		scanf("%d",&p[i].pr);
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n-i-1;j++){
			if(p[j].AT > p[j+1].AT) {
				tem = p[j];
				p[j] = p[j+1];
				p[j+1] = tem;
			}
		}
	}
	
	int currT = 0;
	int completed[n];
	int compl = 0;
	for(int i=0;i<n;i++){
		completed[i] = 0;
	}
	
	int idx;
	int pri;
	while(compl < n){
		pri = -1;
		idx = -1;
		for(int i=0;i<n;i++){
			if(!completed[i] && p[i].AT <= currT){
				if(pri == -1 || p[i].pr < pri){
					pri = p[i].pr;
					idx = i;
				}
			}
		}
		completed[idx] = 1;
		compl++;
		currT += p[idx].BT;
		p[idx].CT = currT;
		p[idx].TAT = p[idx].CT - p[idx].AT;
		p[idx].WT = p[idx].TAT - p[idx].BT;
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n-i-1;j++){
			if(p[j].CT > p[j+1].CT) {
				tem = p[j];
				p[j] = p[j+1];
				p[j+1] = tem;
			}
		}
	}
	float tat=0;
	float wt=0;
	printf("Process\tCT\tTAT\tWT\n");
	
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t\n",p[i].name,p[i].CT,p[i].TAT,p[i].WT);
		tat+=p[i].TAT;
        wt+=p[i].WT;
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
	
