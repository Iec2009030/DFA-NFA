/ *This Programme takes a recursive approach, which forces a exponential time
 * Complexity, which can be changed to n^3 by going for a Dynammic Programming 
 approach */

#include <iostream>
#define V 4
using namespace std;


int countwalks(int graph[][V], int u, int v, int k)

{
        int count  = 0;

        if (k == 0 && u == v)
                return 1;
        if (k == 0 && u != v)
                return 0;
        if (k ==1 && graph[u][v] == 1)
                return 1;
        else {
                for (int i =0; i<V; i++){
                        if(graph[u][i] == 1){
                                count += countwalks(graph,i,v,k-1);
                        }
                }
        }
        return count;
}



int main()
{
    /* Let us create the graph shown in above diagram*/
     int graph[V][V] = { {0, 1, 1, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 1},
                        {0, 0, 0, 0}
                      };
    int u = 0, v = 3, k = 2;
    cout << countwalks(graph, u, v, k)<<endl;
    return 0;
}
