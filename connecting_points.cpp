#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using namespace std;

typedef pair<double, int> iPair;

double minimum_distance(vector<int> x, vector<int> y)
{
    double result = 0.;
    vector<vector<int>> adj(x.size(), vector<int>());
    vector<vector<double>> w(adj.size());
    vector<bool> visited(x.size());

    double help;

    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

    vector<double> cost(x.size());

    cost[0] = 0;
    pq.push(make_pair(0, 0));
    for (size_t i = 1; i < cost.size(); i++)
    {
        cost[i] = INT32_MAX;
        //pq.push(i);
    }

    for (size_t i = 0; i < x.size(); i++)
    {
        visited[i] = false;
        for (size_t j = i + 1; j < y.size(); j++)
        {
            w[i].push_back(sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)));
            w[j].push_back(sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)));

            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }

    int v, u;
    while (!pq.empty())
    {
        u = pq.top().second;
        pq.pop();
        visited[u] = true;

        for (size_t i = 0; i < adj[u].size(); i++)
        {
            v = adj[u][i];
            //cout << "u: " << u << " v: " << v << " cost[v]: " << cost[v] << endl;

            if (visited[v] == false && cost[v] > w[u][i])
            {
                cost[v] = w[u][i];
               // cout << "u: " << u << " v: " << v << " cost[v]: " << cost[v] << endl;
                pq.push(make_pair(cost[v], v));
            }
            // cout << "u: " << u << " v: " << v << " cost[v]: " << cost[v] << endl;
        }
    }

    // cout << "Cost: " << endl;
    for (size_t i = 0; i < x.size(); i++)
    {
        //cout << cost[i] << endl;
        result += cost[i];
    }

    return result;
}

int main()
{
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
