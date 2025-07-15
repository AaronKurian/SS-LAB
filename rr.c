#include <stdio.h>
#include <stdlib.h>

struct Process {
    int name;
    int AT;
    int BT;
    int originalBT;
    int CT;
    int TAT;
    int WT;
    int status;
} p[20];

int pr[100];
int prI[100];
int pi;

int queue[100], front = 0, rear = 0;

void enqueue(int x) {
    queue[rear++] = x;
}

int dequeue() {
    return queue[front++];
}

int isQueueEmpty() {
    return front == rear;
}

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d:\n", i + 1);
        p[i].name = i + 1;
        scanf("%d %d", &p[i].AT, &p[i].BT);
        p[i].originalBT = p[i].BT;
        p[i].status = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int currT = 0, completed = 0;
    enqueue(0);
    p[0].status = 1;



    while (completed < n) {
        if (isQueueEmpty()) {
            currT++;
            for (int i = 0; i < n; i++) {
                if (p[i].AT <= currT && p[i].status == 0) {
                    enqueue(i);
                    p[i].status = 1;
                }
            }
            continue;
        }

        int idx = dequeue();
        int execTime = (p[idx].BT >= tq) ? tq : p[idx].BT;
        currT += execTime;
        p[idx].BT -= execTime;
	pr[pi]=p[idx].name;
	prI[pi]=currT;
	pi++;
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= currT && p[i].status == 0) {
                enqueue(i);
                p[i].status = 1;
            }
        }

        if (p[idx].BT > 0) {
            enqueue(idx);
        } else {
            p[idx].CT = currT;
            p[idx].TAT = p[idx].CT - p[idx].AT;
            p[idx].WT = p[idx].TAT - p[idx].originalBT;
            completed++;
        }
    }
	float tat=0;
	float wt=0;
    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].AT, p[i].originalBT, p[i].CT, p[i].TAT, p[i].WT);
        tat+=p[i].TAT;
        wt+=p[i].WT;
    }
	printf("Gantt chart : \n");
	for(int i=0;i<pi;i++){
		printf("|\tP%d",pr[i]);
	}
	printf("|\n");
	printf("0 ");
	for(int i=0;i<pi;i++){
		printf("\t%d",prI[i]);
	}
	printf("\n");
	printf("Avg. TAT=%f\n",tat/n);
	printf("Avg. WT=%f\n",wt/n);
    return 0;
}
