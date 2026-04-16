#include<iostream>
#include<new>
#include<string>
#include<iomanip>
using namespace std;
int m;//m项成绩

struct Student{
    double * scores;
};//定义一个学生结构体
Student * students = nullptr;
int capacity = 2;//为students 数组分配的总空间
int Num = 0;//当前学生人数

string * itemNames = nullptr;

int main()
{
    int idx;
    cin>>m;
    itemNames = new string[m];
    students = new Student[capacity];  //这里写capacity就好
    for(int i=0;i<m;i++)
    {
        cin>>itemNames[i];
    }
    int op;//操作命令
    while(cin>>op)
    {
        switch (op)
        {
        case 1:
            /* 插入学生*/
            //1.空间扩容
            if(Num == capacity)
            {
                int newcapacity=capacity*2;
                Student * newstudents = new Student[newcapacity];
                for(int i=0;i<Num;i++)  newstudents[i] = students[i];
                delete[] students;//把原来所指向的空间删除
                students=newstudents;
                capacity=newcapacity;
            }
            students[Num].scores = new double [m];
            for(int i=0;i<m;i++)    cin>>students[Num].scores[i];
            Num++;
            cout<<"Inserted"<<endl;
            break;
        case 2:
            cin>>idx;
            if(idx<1||idx>Num)  {cout<<"Invalid index"<<endl;break;}
            delete[] students[idx-1].scores;
            //循环平移数组
            for(int i=idx-1;i<Num-1;i++)//gai
                students[i]=students[i+1];
            Num--;
            cout<<"Deleted"<<endl;
            break;
        case 3:
            cin>>idx;
            if(idx<1||idx>Num)  {cout<<"Invalid index"<<endl;break;}
            for(int j=0;j<m;j++)    cin>>students[idx-1].scores[j];
            cout<<"Modified"<<endl;
            break;
        case 4:
            cin>>idx;
            if(idx<1||idx>Num)  {cout<<"Invalid index"<<endl;break;} 
            cout<<"Query result:"<<endl;
            for(int i=0;i<m;i++)
                    cout<<itemNames[i]<<(i == m-1 ? "" : " ");
            cout<<endl;
            for (int  j = 0; j < m; j++)
            {
                cout<<fixed<<setprecision(1)<<students[idx-1].scores[j]<<(j == m-1 ? "" : " ");
            }        
            cout<<endl;
            break;
        case 5:
            if (Num==0)
                cout<<"No students"<<endl;
            else {
                cout<<"All students:"<<endl;
                for(int i=0;i<m;i++)
                    cout<<itemNames[i]<<(i == m-1 ? "" : " ");//学到了
                cout<<endl;
                for(int i=0;i<Num;i++){
                    cout<<i+1<<" ";
                    for (int  j = 0; j < m; j++)
                    {
                        cout<<fixed<<setprecision(1)<<students[i].scores[j]<<(j == m-1 ? "" : " ");
                    }
                    cout<<endl;
                }    
            }
            break;
        case 6:
            int k;
            cin>>k;
            for(int i=0;i<Num-1;i++){
                for(int j=0;j<Num-i-1;j++)
                {
                    if(students[j].scores[k-1]<students[j+1].scores[k-1])
                    {
                        Student temp = students[j];
                        students[j] = students[j+1];
                        students[j+1] = temp;
                    }
                }
            }
            cout << "Sorted by item " << k << ":" << endl;
            for(int i=0;i<m;i++)
                    cout<<itemNames[i]<<(i == m-1 ? "" : " ");//学到了
                cout<<endl;
                for(int i=0;i<Num;i++){
                    cout<<i+1<<" ";
                    for (int  j = 0; j < m; j++)
                    {
                        cout<<fixed<<setprecision(1)<<students[i].scores[j]<<(j == m-1 ? "" : " ");
                    }
                    cout<<endl;
                }
            break;
        case 7:
            for(int i=0;i<Num;i++)  delete [] students[i].scores;
            delete [] students;
            delete [] itemNames;
            return 0;
        default:
            break;
        }
    }
}