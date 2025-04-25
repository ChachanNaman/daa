#include <iostream>
using namespace std;
int knapsack(int n , int W  , int weights[] , int profits[]){
        int dp[n+1][W+1];
        for(int i = 0; i<=n; i++){
            for(int j = 0; j<=W ; j++){
                if(i==0 || j==0){
                    dp[i][j]=0;
                }
                else if(weights[i-1]<=j){
                    dp[i][j]=max(dp[i-1][j], dp[i-1][j-weights[i-1]]+ profits[i-1]);
                }
                else{
                    dp[i][j]= dp[i-1][j];
                }
            }
        }
        return dp[n][W];
}

int main(){
    int n , W;
    cout<<"enter number of items : ";
    cin>>n;
    cout<<endl;
    cout<<"enter max weight capacity : ";
    cin>>W;

    int weights[n], profits[n];
    for(int i = 0; i<n;i++){
        cout<<"enter weight of object "<<i+1<<" : ";
        cin>>weights[i];
        cout<<"enter profit of object "<<i+1<<" : ";
        cin>>profits[i];
    }
    cout<<"Max Profit is : "<<knapsack(n ,W, weights , profits)<<endl;

return 0;
}