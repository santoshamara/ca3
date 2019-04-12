#include<iostream>
using namespace std;

static int n;
int i,j,total_time=0;//Time quantum
float avgtat=0,avgwt=0;
int queue[100];
int time=0,front=0,rear=0,q_count=0;//q_count=no. of elements in the queue
void finding(struct data a[]);
void display(struct data abc[]);
struct data
{
    int arri_t,bur_t,comp_t,tat,wt;
    char process_name[30];
    float ntat;
}temp;

main()
{
  cout<<"Enter total number of processes\n";
  cin>>n;
  struct data aa[n];
  for(i=0;i<n;i++)
  {
      cout<<"Enter the Details for  the process "<<i+1<<endl;
       cout<<"Enter the  process name\n";
      cin>>aa[i].process_name;
       cout<<"Enter the  Arrival Time and Burst Time\n";
      cin>>aa[i].arri_t;
	  cin>>aa[i].bur_t;
  }
  //Queue Sorting
  for(i=0;i<n;i++)
  {
      for(j=1;j>=1;j--)
      {
          if(aa[j].arri_t<aa[j-1].arri_t)
          {
              temp=aa[j-1];
              aa[j-1]=aa[j];
              aa[j]=temp;
          }

      else if(aa[j].arri_t==aa[j-1].arri_t)
      {
          if(aa[j].bur_t<aa[j-1].bur_t)
          {
              temp=aa[j-1];
              aa[j-1]=aa[j];
              aa[j]=temp;
          }
      }

      }


  }
// Finding total time
    total_time+=aa[0].arri_t+aa[0].bur_t;
    for(i=1;i<n;i++)
    {
        if(aa[i].arri_t>total_time)
            total_time=aa[i].arri_t;
            total_time+=aa[i].bur_t;
    }
// Finding the completion Time
  finding(aa);
}
void push(int q)
{
    queue[rear++]=q;
}
int pop()
{
    int x;
    x=queue[front++];
    return x;
}
void check(struct data a[])
{
    while(a[j].arri_t<=time&&j<n)
    {
        q_count++;
        push(j++);
    }
}
void finding(struct data a[])
{
    int temp_st[n],flag=0,count=0,p_process;
    j=0;
    int tq;
    cout<<"Enter the Time quantum";
    cin>>tq;
    for(i=0;i<n;i++)
    {
        temp_st[i]=a[i].bur_t;
    }
    time=a[0].arri_t;
    q_count=1;
    push(j++);
    while(time<=total_time)
    {
        if(flag==1||q_count!=0)
        {
            if(flag==0&&count==0)
            {
                p_process=pop();
                count=0;
                flag=1;
            }
            temp_st[p_process]--;
            if(temp_st[p_process]==0)
            {
              time++;
              count=0;
              a[p_process].comp_t=time;
              flag=0;
              q_count--;
              check(a);
              continue;
            }
            count++;
            if(count==tq)
            {
                count=0;
                time++;
                check(a);
                push(p_process);
                flag=0;

            }
            else
            {
                time++;
                check(a);
            }
        }
        else
        {
            time++;
            check(a);
        }
    }
display(a);
}
void display(struct data a[])
{
    cout<<"pname\tAT\tBT\tCT\tTAT\tWT\n";
    for(i=0;i<n;i++)
    {
        a[i].tat=a[i].comp_t-a[i].arri_t;
        a[i].wt=a[i].tat-a[i].bur_t;
        avgwt=avgwt+a[i].wt;
        avgtat=avgtat+a[i].tat;
     cout<<a[i].process_name<<"\t"<<a[i].arri_t<<"\t"<<a[i].bur_t<<"\t"<<a[i].comp_t<<"\t"<<a[i].tat<<"\t"<<a[i].wt<<"\n";
    }

    avgwt=avgwt/n;
     avgtat=avgtat/n;
    cout<<"The average Weight time for the Scheduling is="<<avgwt<<"  and Average Turnaround Time="<<avgtat<<"\n";
}

