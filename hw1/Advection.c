#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define M    400
#define XMAX 1.0
#define XMIN 0.0
#define A    1.0
#define tmax 1.0
#define dt   0.000001
#define PI   3.1415926


void upwind(double *out, double *in){
  int i;
  double h = (XMAX - XMIN)/M;

  for(i = 0; i < M; i++)
    {
      if(i == 0)
	out[i] = in[i] + dt*A/(h)*(in[M-1] - in[i]);
      else
	out[i] = in[i] + dt*A/(h)*(in[i-1] - in[i]);
    }
  return;
}

void central(double * out, double *in){
  int i;
  double h = (XMAX - XMIN)/M;
  
  for(i = 0; i < M; i++){
    if(i == 0)
      out[i] = in[i] + dt*A/(2*h)*(in[M-1] - in[i+1]);
    else if(i == M-1)
      out[i] = in[i] + dt*A/(2*h)*(in[i-1] - in[0]);
    else
      out[i] = in[i] + dt*A/(2*h)*(in[i-1] - in[i+1]);
  }
  return;
}

void upwind_biased(double *out, double *in){
  int i;
  double h = (XMAX - XMIN)/M;

  for(i = 0; i < M; i++){
    if(i == 0)
      out[i] = in[i] + dt*A/(h)*(-1.0/6.0*in[M-2] + in[M-1] \
				 - 1.0/2.0*in[i] - 1.0/3.0*in[i+1]);
    else if(i == 1)
      out[i] = in[i] + dt*A/(h)*(-1.0/6.0*in[M-1] + in[i-1] \
				 - 1.0/2.0*in[i] - 1.0/3.0*in[i+1]);
    else if(i == M-1)
      out[i] = in[i] + dt*A/(h)*(-1.0/6.0*in[i-2] + in[i-1] \
				 - 1.0/2.0*in[i] - 1.0/3.0*in[0]);
    else
      out[i] = in[i] + dt*A/(h)*(-1.0/6.0*in[i-2] + in[i-1] \
				 - 1.0/2.0*in[i] - 1.0/3.0*in[i+1]);
  }
  return;
}


output(double *file, int Ncell, int version){

  int i;
  char command[120];
  char name[120];
  double h = (XMAX - XMIN)/M;
  
  sprintf(command, "rm advection_v%d_M%d.dat", version,Ncell);
  system(command);
  sprintf(name, "advection_v%d_M%d.dat", version, Ncell);
  FILE *fp;
  fp = fopen(name,"a+"); //can't use 'a+';
  for(i = 0; i < M; i++)
    {
      fprintf(fp, "%f\t%f\n", XMIN + i*h, file[i]);
    }
  return;
}  
  
void main(){

  int i;
  double h = (XMAX - XMIN) /(M);
  double *new;
  double *old;
  double *exact;
  double t;
  new = (double *)malloc(M*sizeof(double));
  old = (double *)malloc(M*sizeof(double));
  exact = (double *)malloc(M*sizeof(double));

  for(i = 0; i < M; i++)
    {
      old[i] = pow(sin(PI*(XMIN + i*h)), 100.0);
      exact[i] = pow(sin(PI*(XMIN + i*h - A*tmax)), 100.0);
    }
  output(exact, M, 0);
  
  t = 0.0;
  while(t < tmax){
    t = t + dt;
    upwind(new,old);
    for(i = 0; i < M; i++)
      old[i] = new[i];
  }
  output(new, M, 1);

  t = 0.0;
  for(i = 0; i < M; i++)
      old[i] = pow(sin(PI*(XMIN + i*h)), 100.0);
  while(t < tmax){
    t = t + dt;
    central(new,old);
    for(i = 0; i < M; i++)
      old[i] = new[i];
  }
  output(new, M, 2);

  
  t = 0.0;
  for(i = 0; i < M; i++)
      old[i] = pow(sin(PI*(XMIN + i*h)), 100.0);
  while(t < tmax){
    t = t + dt;
    upwind_biased(new,old);
    for(i = 0; i < M; i++)
      old[i] = new[i];
  }
  output(new, M, 3);

  return;
}
  
