#include<iostream>
#include<cmath>
#include<vector> 
#include<fstream>
#include<algorithm>
using namespace std;

template <typename T>
vector<T> BC(vector<T> m) 
{
    m[0] = 0;
    m[m.size()-2] = m[m.size()-1];  
   
    return m;
}

template <typename T>
vector<T> IC(vector<T> n, vector<T> p) 
{
    for(int i = 0; i < n.size(); i++)
        n[i] = exp(-100.0*((p[i]-0.2)*(p[i]-0.2)));
    return n;
}

template <typename T>
class Solver 
{
private:
    vector<T> u;

public:
    Solver(vector<T> x) 
    {
        u = x;
    }

    void set_u(vector<T> y) 
    {
        u = y;
    }

    vector<T> get_u() 
    {
        return u;
    }

    vector<vector<T>> LW(vector<T> u_copy, T h, T del_t, vector<T> t_arr)
   {
    int N = u_copy.size();
    
    vector<int> nt_arr(t_arr.size());

    for(int i = 0; i < t_arr.size(); i++)
        nt_arr[i] = int(t_arr[i]/del_t);

    vector<vector<T>> u_res(t_arr.size(), vector<T>(N, 0.0));

    vector<T> u_new(N, 0.0);

    u_res[0] = u_copy;
    int snap = 1;

    int total_steps = nt_arr[nt_arr.size()-1];

    for(int n = 0; n < total_steps; n++)
    {
        for(int j = 1; j < N-1; j++)
        {
            u_new[j] = u_copy[j]- (del_t/(2*h))*(u_copy[j+1] - u_copy[j-1])+ (pow(del_t,2)/(2*h*h))*(u_copy[j+1] - 2*u_copy[j] + u_copy[j-1]);
        }
        u_new = BC(u_new);
        u_copy = u_new;

        fill(u_new.begin(), u_new.end(), 0.0);

        if(snap < t_arr.size() && n+1 == nt_arr[snap])
        {
            u_res[snap] = u_copy;
            snap++;
        }
    }
    return u_res;
    }
  };

int main() 
{
    int N = 101;
    double h = 0.01;
    double del_t = 0.01;
    vector<double> t_arr = {0, 0.1, 0.3, 0.5};

    vector<double>u_init(N,0);
    Solver<double>s1(u_init);

    vector<double> x(N), u_main(N, 0.0);

    for(int i = 0; i < N; i++)
        x[i] = i * h;

    u_main = IC(u_main, x);
    u_main = BC(u_main);

    s1.set_u(u_main);

    vector<double>u_copy = s1.get_u();

    vector<vector<double>> u_final = s1.LW(u_copy, h, del_t, t_arr);
    
    ofstream file("result.txt");

    if(file.is_open())
    {
      for(int k = 0;k<u_final.size();k++)
      {
       file<<"t = "<<t_arr[k]<<"\n";
       for(int j=0;j<u_copy.size();j++)
        file << x[j] << " " << u_final[k][j] << "\n";
       file<<"\n";
      }
      file.close();
    }


    return 0;
}
