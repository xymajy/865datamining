/*
*
*   Write by Jingyao Ma. This is used to generate exact result of K-NNs problem.
*
*   It based on priority queue. The main function just scan the dataset simply to
*   find the K-NNs.
*   
*   At the end of this program, it will display all K-NNs of query points, which 
*   is used to compare with the results of LSH and SH.
*
*   Jingyao Ma     15 March 2016
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include <iostream>  
#include <queue>
#include <vector>  

#define SQR(a) ((a) * (a))

#define IntT int

#define RealT double
#define SQRT sqrt
#define FPRINTF_REAL(file, value) {fprintf(file, "%0.3lf", value);}
#define FSCANF_REAL(file, value) {fscanf(file, "%lf", value);}

#define TimeVarT double
#define TIMEV_START(timeVar)
#define TIMEV_END(timeVar)
// #define RealT long double
// #define SQRT sqrtl
// #define FPRINTF_REAL(file, value) {fprintf(file, "%0.3Lf", value);}
// #define FSCANF_REAL(file, value) {fscanf(file, "%Lf", value);}

struct Node{  
    int x;  
    RealT dis;    
    Node(int nri, RealT& pszName)  
    {  
      x = nri;
      dis = pszName; 
    }  
};  

bool operator<( Node a, Node b){  
    if(a.dis==b.dis) return a.x<b.x;  
    return a.dis<b.dis;  
} 

RealT **points;
int nPoints;
RealT *query;
int nQueries;
int dimension;
RealT R;
RealT p;

int K;

RealT *listOfRadii = NULL;
IntT nRadii = 0;

// nearNeighbors[i] is the list of the near neighbors.
int *nearNeighbors;

void usage(char *programName){
  printf("Usage: %s #pts_in_data_set #queries dimension successProbability radius data_set_file queries_file\n", programName);
}

RealT norm(int dimension, RealT *p1){
  RealT result = 0;

  for (int i = 0; i < dimension; i++){
    result += SQR(p1[i]);
  }

  return sqrt(result);
}

// Reads in the data set (points and the initial parameters for <R>)
// in the <points> from the file <filename>.
void readPoints(char *filename){
  FILE *f = fopen(filename, "rt");
  //fscanf(f, "%d %d %lf %lf\n", &nPoints, &dimension, &R, &p);
  points = (RealT**)malloc(nPoints * sizeof(RealT*));
  for(int i = 0; i < nPoints; i++){
    points[i] = (RealT*)malloc(dimension * sizeof(RealT));
    for(int d = 0; d < dimension; d++){
      FSCANF_REAL(f, &(points[i][d]));
    }
    //printf("norm (%d): %lf\n", i, norm(dimension, points[i]));
  }
}

// Prints the vector <v> of size <size>. The string <s> appears
// in front.
void printRealVector1(char *s, int size, RealT *v){
  printf("%s", s);
  for(int i = 0; i < size; i++){
    if (i > 0){
      printf(" ");
    }
    printf("%lf", v[i]);
  }

  printf("\n");
}

// Returns the Euclidean distance from point <p1> to <p2>.
RealT dist(RealT *p1, RealT *p2){
  RealT result = 0;

  for (int i = 0; i < dimension; i++){
    result += SQR(p1[i] - p2[i]);
  }

  return SQRT(result);
}


// Update the Queue. If the queue size less than K, just push.
// Otherwise, if the new value less than the max value, delete the max
// and push new node into queue.
void updataQ(std::priority_queue<Node>& q, RealT d, int i){
  if(q.size() < K) q.push(Node(i,d));
  else{
    if(q.top().dis > d){
      q.pop();
      q.push(Node(i,d));
    }
  }
}

// Print node in form
void PrintfNode(const Node& na){  
  printf("%09d\tDistance:%lf\n", na.x, na.dis);  
} 

// Output the Queue
void display(std::priority_queue<Node>& q){ // reverse
  std::vector<Node> v;
  v.reserve(K);
  while (!q.empty()){  
    v.push_back(q.top());
    q.pop();  
  } 
  for(int i=K;i>0;i--){
    PrintfNode(v[i-1]);
  }
}

int main(int nargs, char **args){
  if (nargs < 7) {
    usage(args[0]);
    exit(1);
  }
  
  nPoints = atoi(args[1]);
  nQueries = atoi(args[2]);
  dimension = atoi(args[3]);
  p = atof(args[4]);

  K = atoi(args[5]);

  readPoints(args[6]); // read all points
  

  FILE *queryFile = fopen(args[7], "rt");
  //fscanf(queryFile, "%d\n", &nQueries);
  query = (RealT*)malloc(dimension * sizeof(RealT));
  printf("nPoints = %d\n", nPoints);
  //printf("nQueries = %d\n", nQueries);
  for(int i = 0; i < nQueries; i++){
    // read in the query point.
    for(int d = 0; d < dimension; d++){
      FSCANF_REAL(queryFile, &(query[d]));
    }
    //printRealVector1("Query: ", dimension, query);
    
    std::priority_queue<Node> myq;

    TimeVarT time = 0;
    RealT tempdis = 0;

    TIMEV_START(time);
    for(int j = 0; j < nPoints; j++){

      tempdis = dist(query, points[j]);
      updataQ(myq, tempdis, j);
    	//printf("Distance[dist] (%d): %lf\n", j, dist(query, points[j]));
    	//printRealVector1("X: ", dimension, points[j]);
    }
    TIMEV_END(time); // time only finding the near neighbors, and exclude printing from timing.
  
    printf("Total time for K-NN query \t%0.6lf\n",time);
    
  	printf("Query point %d 's %d NNs are:\n", i, K);

    display(myq);
  }
  
}
