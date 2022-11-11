#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#define MAX 200

int n, p, capMatrix[MAX+1][MAX+1], capMatrix2[MAX+1][MAX+1], capMatrix3[MAX+1][MAX+1];
double v, a, b, waterFlow[MAX+1][MAX+1], flubberFlow[MAX+1][MAX+1];

int visited[MAX+1];
int flow_dfs(int c[MAX+1][MAX+1], int x, int e, int flow) {
  if (x == e) return flow;
  if (visited[x]) return 0;
  visited[x] = true;
  for (int y = 1; y <= n; y++) if (c[x][y]) {
    int f = flow_dfs(c, y, e, min(flow, c[x][y]));
    if (f) {
      c[x][y] -= f;
      c[y][x] += f;
      return f;
    }
  }
  return 0;
}

int flow(int c[MAX+1][MAX+1], int x, int e) {
  memset(visited, 0, sizeof(visited));
  return flow_dfs(c, x, e, 1000000000);
}

double pipe_dfs(int x, int e, double flubber) {
  visited[x] = true;
  if (x == e) return flubber;
  for (int y = 1; y <= n && flubber > 1e-7; y++) {
    if (!visited[y] && waterFlow[x][y] > 1e-7) {
      double f = pipe_dfs(y, e, min(waterFlow[x][y], flubber));
      if (f > 0) {
        waterFlow[x][y] -= f; waterFlow[y][x] += f;
        flubberFlow[x][y] += f; flubberFlow[y][x] -= f;
		
        return f;
      }
    }
  }
 
  return 0;
}

int main(int argc, char **argv) 
{
    string line;
    ifstream inputfile;
    inputfile.open(argv[1]);
    inputfile >> n >> p >> v >> a;
    cout<<"\n\n \tINPUT\n"<<endl;
    cout<<n<<" "<<p<<" "<<v<<" "<<a<<endl;
    b = 1.0-a;
    memset(capMatrix, 0, sizeof(capMatrix));
    vector<int> X(p), Y(p), C(p);
    for (int i = 0; i < p; i++) {
      inputfile >> X[i] >> Y[i] >> C[i];
      cout<<X[i]<<" "<<Y[i]<<" "<<C[i]<<endl;
      capMatrix[X[i]][Y[i]] = capMatrix[Y[i]][X[i]] = C[i];
    }

    memcpy(capMatrix2, capMatrix, sizeof(capMatrix));
    memcpy(capMatrix3, capMatrix, sizeof(capMatrix));
    int mnF = 0, mnW = 0, mxF = 0, mxW = 0, f;
    while ((f = flow(capMatrix, 1, 3))) mxF += f;
    while ((f = flow(capMatrix, 2, 3))) mnW += f;
    while ((f = flow(capMatrix2, 2, 3))) mxW += f;
    while ((f = flow(capMatrix2, 1, 3))) mnF += f;
    f = mxF + mnW;
    double F = max((double)mnF, min((double)mxF, a*f / (double)(a+b)));
    double v1, v2;
    if (mnF == mxF) {
      v1 = v2 = 0.5;
    } else {
      v1 = (F-mnF)/(mxF-mnF);
      v2 = (mxF-F)/(mxF-mnF);
    }
    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= n; y++) {
      waterFlow[x][y] = capMatrix3[x][y] - (v1*capMatrix[x][y] + v2*capMatrix2[x][y]);
    }
    memset(flubberFlow, 0, sizeof(flubberFlow));
    for (double rem = F; rem > 1e-7; ) {
      memset(visited, 0, sizeof(visited));
      rem -= pipe_dfs(1, 3, rem);
    }
	  cout<<"\n\n \tOUTPUT\n"<<endl;
	  cout<<"Rate of flubber    Rate of water"<<endl;
    for (int i = 0; i < p; i++) {
      printf("%.9lf\t",  flubberFlow[X[i]][Y[i]] / v);
      printf("%.9lf\n", waterFlow[X[i]][Y[i]]);
    }
    printf("%.9lf\n", pow(F/v, a) * pow(f-F, b));
}