#include "stdio.h"
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"

using namespace std;

int ROW = 35;
int COL = 91;

double rand_uniform () {
  return (double)rand() / (double)RAND_MAX;
}

void ClearTheScreen ( )  {
  printf("\033[%d;%dH",1,1);
  return;
}

int main ( int argc, char** argv ) {
  
  double r1[2];
  double v1[2];
  double R1[2];
  double V1[2];
  double vNorm;
  double dt;
  double max;
  double a0[2];
  double a1[2];
  double A0[2];
  double A1[2];
  double r2[2];
  double v2[2];
  double a2[2];
  double R2[2];
  double V2[2];
  double A2[2];
  double grid[ROW][COL];
  int x;
  int y;
  int X;
  int Y;
  double dt1;
  double max1;
  
  cout << "time_step [days] = ";
  cin >> dt1;
  cout << "stop-time [days] = ";
  cin >> max1;

  dt = 86400 * dt1;
  max = max1 * 86400;

  double G_Newton = 6.673889e-11;
  double powerLaw = -2;
  double M = 1.98855e+30;
  double m = 5.9722e+24;
  double r0[2] = {0.,1.4960e+11};
  double v0[2] = {30e+3,0.};
  double R0[2] = {0.,0.};

  double V0[2] = {-(m/M)*v0[0],-(m/M)*v0[1]};

  double alpha = pow(pow(R0[0] - r0[0],2.)+pow(R0[1]-r0[1],2.),(-powerLaw-1.)+0.5);
  a0[0] = G_Newton*M*(R0[0] - r0[0]) / alpha;
  a0[1] = G_Newton*M*(R0[1] - r0[1]) / alpha;
  A0[0] = G_Newton*m*(r0[0] - R0[0]) / alpha;
  A0[1] = G_Newton*m*(r0[1] - R0[1]) / alpha;

  double time = 0.;

  while ( time < max ) {

    for ( int i = 0; i < ROW; i++) {
      for ( int j = 0; j < COL; j++ ) {
	grid[i][j] = 0;
      }
    }

    if ( time == 0 ) {
      
      r1[0] = r0[0] + 0.5 * v0[0] * dt + 0.25 * a0[0] * pow(dt,2.);
      r1[1] = r0[1] + 0.5 * v0[1] * dt + 0.25 * a0[1] * pow(dt,2.);
      R1[0] = R0[0] + 0.5 * V0[0] * dt + 0.25 * A0[0] * pow(dt,2.);
      R1[1] = R0[1] + 0.5 * V0[1] * dt + 0.25 * A0[1] * pow(dt,2.);
    }
    else {
      r1[0] = r0[0] + 0.5 * v0[0] * dt;
      r1[1] = r0[1] + 0.5 * v0[1] * dt;
      R1[0] = R0[0] + 0.5 * V0[0] * dt;
      R1[1] = R0[1] + 0.5 * V0[1] * dt;
    }
    
    alpha = pow(pow(R1[0]-r1[0],2.)+pow(R1[1]-r1[1],2.),(-powerLaw-1.)+0.5);
    if ( !alpha ) break; // CRASH!
    a1[0] = G_Newton*M*(R1[0]-r1[0])/alpha;
    a1[1] = G_Newton*M*(R1[1]-r1[1])/alpha;
    A1[0] = G_Newton*m*(r1[0]-R1[0])/alpha;
    A1[1] = G_Newton*m*(r1[1]-R1[1])/alpha;
    
    v2[0] = v0[0] + a1[0] * dt;
    v2[1] = v0[1] + a1[1] * dt;
    V2[0] = V0[0] + A1[0] * dt;
    V2[1] = V0[1] + A1[1] * dt;
    
    r2[0] = r1[0] + 0.5 * v2[0] * dt;
    r2[1] = r1[1] + 0.5 * v2[1] * dt;
    R2[0] = R1[0] + 0.5 * V2[0] * dt;
    R2[1] = R1[1] + 0.5 * V2[1] * dt;
    
   
    
    X = int(floor((R0[0]/6.2e9)+0.5)) + int(floor(double(COL)/2.));
    Y =-int(floor((R0[1]/12.4e9)+0.5)) + int(floor(double(ROW)/2.));
    x = int(floor((r0[0]/6.2e9)+0.5)) + int(floor(double(COL)/2.));
    y =-int(floor((r0[1]/12.4e9)+0.5)) + int(floor(double(ROW)/2.));
    if ( x < COL && y < ROW && x >= 0 && y >= 0 )
      grid[y][x] = 1;
    //system("sleep 1");
    ClearTheScreen();
    for ( int i = 0; i < ROW; i++ ) {
      for ( int j = 0; j < COL; j++ ) {
	if ( grid[i][j] == 1 ) cout << "E";
	else if ( j == X && i == Y ) cout << "S";
	else cout << " ";
      }
      cout << endl;
    } //draw the new grid to the screen by row
    
    time += dt;
    r0[0] = r2[0]; r0[1] = r2[1];
    v0[0] = v2[0]; v0[1] = v2[1];
    R0[0] = R2[0]; R0[1] = R2[1];
    V0[0] = V2[0]; V0[1] = V2[1];
    
  }
  
  return -1;
  
}
