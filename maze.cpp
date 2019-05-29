#include "maze.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

maze::maze():graph()
{
  cin >> start;
  cin >> exit;
}

void maze::dfs(vector<int> &pred)
{
  pred[start] = -2; // start has been visited, but has no predecessor
  // a vertex u has been visited if and only if pred[u] != -1

  if(start == exit)
    return;
  stack<int> S;
  S.push(start);
  int current, nbr;
  vnodeptr cursor;
  
  while(!S.empty()) {
    current = S.top();
    if(current == exit) {
      return;
    }
      
    cursor = adjList[current];
    while(cursor != nullptr && pred[cursor->v] != -1) {
      cursor = cursor->next;
    }
    if(cursor == nullptr) { // back out
      S.pop(); // search will continue from the beginning of the while loop
    } else {
      nbr = cursor->v;
      pred[nbr] = current;
      S.push(nbr);
    }
  }
}


void maze::print_dfs_exitpath()
{
  vector<int> pred(size,-1);
  dfs(pred);
  if(pred[exit] == -1)
  	cout << "No way out" << endl;
  else
    printPath(exit,pred);
}
  
void maze::bfs(vector<int> &pred)
{
  int nbr, current;
  vnodeptr cursor;
  pred[start] = -2; // start has been visited, but has no predecessor
  // a vertex u has been visited if and only if pred[u] != -1

  if (start == exit)
      return;
  queue<int> Q;

  Q.push(start);

  while (!Q.empty())
  {
    current = Q.front();
  
    if (current == exit)
      return;

    cursor = adjList[current];
    
    while (cursor != nullptr && pred[cursor->v] != -1) 
      cursor = cursor->next;
    
    if (cursor == nullptr) 
      Q.pop();
    else 
    {
      nbr = cursor->v;
      pred[nbr] = current;
      Q.push(nbr);
    }
  }
}

void maze::print_bfs_exitpath()
{
  vector<int> pred(size,-1);
  bfs(pred);
  if(pred[exit] == -1)
  	cout << "No way out" << endl;
  else
    printPath(exit,pred);
}

void maze::printPath(int u,vector<int> pred)
{
  if(pred[u] == -2)
    cout << u << " ";
  else {
    printPath(pred[u],pred);
    cout << u << " ";
  }
}
