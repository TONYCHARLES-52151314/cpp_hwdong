#include<iostream>
#include<algorithm>
#include <iomanip>
using namespace std;

double average (initializer_list<double> scores);
int countPass(initializer_list<double> scores, double passScore = 60.0);
double findMax(const double* arr, int n);
void sortDesc(double* arr, int n);
double average(const double* arr, int n);
int countPass(const double* arr, int n, double passScore = 60.0);

int main()
{
    int m;
    cin>>m;
    
    if (m == 0) {
        cout << "Average: 0.0\n";
        cout << "Pass count: 0\n";
        cout << "Max score: 0.0\n";
        cout << "Sorted:\n";
        return 0;
    }


    double * pscore = new double[m];
    for(int i=0;i<m;i++)    cin>>pscore[i];
    average(pscore,m);
    countPass(pscore, m);
    findMax(pscore, m);
    sortDesc(pscore,m);
    delete[] pscore;
    return 0;
}

double average(initializer_list<double> scores)
{
    int n{0};
    double all{0.0};
    double res{0.0};
    for(auto score : scores)
    {
        all+=score;
        n++;
    }
    if(n>0)
        res = all / n;
    cout<<"Average: "<<fixed<<setprecision(1)<<res<<endl;
    return res;
}

int countPass(initializer_list<double> scores, double passScore)
//函数声明处有初始化默认函数，定义处不需要再来一遍了！！！
{
    int cnt{0};
    for(auto score : scores)
    {
        if(score >= passScore ) cnt++;
    }
    cout<<"Pass count: "<<fixed<<setprecision(1)<<cnt<<endl;
    return cnt;
}
//==================重载===================//
double average(const double* arr, int n) {
    if (n == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) sum += arr[i];
    cout<<"Average: "<<fixed<<setprecision(1)<<sum / n<<endl;
    return sum / n;
}

int countPass(const double* arr, int n, double passScore)
//函数声明处有初始化默认函数，定义处不需要再来一遍了！！！
{
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= passScore) count++;
    }
    cout<<"Pass count: "<<fixed<<setprecision(1)<<count<<endl;
    return count;
}
//=========================================//
double findMax(const double* arr, int n)
{
    double m{0.0};
    for(int i=0;i<n;i++)
    {
        m=max(*(arr+i),m);
    }
    cout<<"Max score: "<<fixed<<setprecision(1)<<m<<endl;
    return m;
}

void sortDesc(double* arr, int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]<arr[j+1])   
            {
                double tmp = *(arr + j);
                arr[j] = *(arr + j + 1);
                arr[j+1] = tmp;
            }   
        }
    }
    cout<<"Sorted: ";
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
}

/*实验总结：
 *巩固initializer_list 的语法
 *巩固函数重载
 *复习冒泡排序和选择排序
 *默认函数只需要初始化一次
 *setprecision的头文件是iomanship
 */