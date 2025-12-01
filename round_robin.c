#include <stdio.h>

#define MAX 50

typedef struct {
    int pid, at, bt, bt_rem, ct, tat, wt;
} Process;

void printTable(Process p[], int n){
    float avg_tat=0, avg_wt=0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        avg_tat+=p[i].tat; avg_wt+=p[i].wt;
    }
    printf("\nAvg TAT = %.2f\nAvg WT = %.2f\n", avg_tat/n, avg_wt/n);
}

void printGantt(int seq[],int st[],int et[],int count){
    printf("\nGantt Chart:\n");
    for(int i=0;i<count;i++) printf(" -------");
    printf("\n|");
    for(int i=0;i<count;i++) printf("  P%-3d |", seq[i]);
    printf("\n");
    for(int i=0;i<count;i++) printf(" -------");
    printf("\n0");
    for(int i=0;i<count;i++) printf("      %2d", et[i]);
    printf("\n");
}

int main(){
    int n,tq;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    Process p[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter AT & BT for P%d: ",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].bt_rem=p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&tq);

    int time=0, completed=0;
    int seq[MAX], st[MAX], et[MAX], count=0;

    while(completed<n){
        int idle=1;
        for(int i=0;i<n;i++){
            if(p[i].bt_rem>0 && p[i].at<=time){
                idle=0;

                st[count]=time;
                seq[count]=p[i].pid;

                if(p[i].bt_rem > tq){
                    p[i].bt_rem -= tq;
                    time += tq;
                } else {
                    time += p[i].bt_rem;
                    p[i].bt_rem = 0;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt  = p[i].tat - p[i].bt;
                    completed++;
                }

                et[count]=time;
                count++;
            }
        }
        if(idle) time++;
    }

    printGantt(seq,st,et,count);
    printTable(p,n);

    return 0;
}
