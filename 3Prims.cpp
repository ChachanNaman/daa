#include <iostream>
using namespace std;

class graph{
    int cities;
    int cost[10][10];
    public:
        graph(){
            cout << "Enter no. of cities: ";
            cin >> cities;
            for(int i = 0; i < cities; i++){
                for(int j = 0; j < cities; j++){
                    cost[i][j] = 999; 
                }
            }
        }

        void create(){
            char ch;
            for(int i = 0; i < cities; i++){
                for(int j = 0; j < cities; j++){
                    if(i != j and cost[i][j] == 999){
                        cout << "Is there connection between " << i << " and " << j << "? (y/n): ";
                        cin >> ch;
                        if (ch == 'y'){
                            cout << "Enter cost: ";
                            cin >> cost[i][j];
                            cost[j][i] = cost[i][j];
                        } 
                    }
                }
            }
        }

        void display(){
            cout <<  "The adjacency matrix is: \n";
            for(int i = 0; i < cities; i++){
                for(int j = 0; j < cities; j++){
                    cout << cost[i][j] << "\t";
                }
                cout << endl;
            }
        }

        void primsAlgorithm(){
            int start = 0;
            int nearest[cities];
            int n = cities;
            int t[cities][3];
            int r = 0;
            int minCost = 0;
            int min;
            int index;
            nearest[start] = -1;

            for(int i = 0; i <= n; i++){
                if(i != start) nearest[i] = start;
            }

            for(int i = 0; i < n - 1; i++){
                min = 999;
                for(int j = 0; j < n; j++){
                    if(nearest[j] != -1 and cost[j][nearest[j]] < min){
                        index = j;
                        min = cost[j][nearest[j]];
                    }
                }

                t[r][0] = nearest[index];
                t[r][1] = index;
                t[r][2] = min;
                r++;
                minCost += cost[index][nearest[index]];
                nearest[index] = -1;

                cout << "The nearest array after pass " << i + 1 << " is: " << endl;
                for(int i = 0; i < n; i++){
                    cout << nearest[i] << " ";
                }
                cout << endl;

                for(int j = 0; j < n; j++){
                    if(nearest[j] != -1 and (cost[j][nearest[j]] > cost[j][index])) nearest[j] = index;
                }
            }

            cout << "The t matrix is: " << endl;
            cout << "Source\t\t\tDestination\t\tCost\n";
            for(int i = 0; i < n - 1; i++){
                for(int j = 0; j < 3; j++){
                    cout << t[i][j] << "\t\t\t";
                }
                cout << endl;
            }
            cout << "The cost is: " << minCost << endl;;
        }
};

int main(){
    graph g;
    int ch;
    while(1){
        cout << "1. Accept matrix\n2. Display matrix\n3. Find MST\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;
        switch(ch){
            case 1:
                g.create();
                break;
            case 2:
                g.display();
                break;
            case 3:
                g.primsAlgorithm();
                break;
            case 4:
                cout << "Thank You!";
                return 0;
        }
    }
}
