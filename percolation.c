#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 100
int root(int p,int A[]){  //return root node of node i //
	while(A[p]!=p){
		p=A[p];
	}
	return(p);

}
int connected(int p,int q,int A[]){
    int p_root = root(p,A);
    int q_root = root(q,A);
    if(p_root==q_root){
    	return(1);
    }
    else{
    	return(0);
    }
}
int quick_union(int p,int q,int A[],int sz[]){
	int p_root = root(p,A);
	int q_root = root(q,A);
	if(p_root!=q_root){
		if(sz[p_root]>sz[q_root]){ //small sz connect large sz//
         A[q_root] = A[A[p]]; //if root p is larger ,then q connect grandparents of p//
         sz[p_root]=sz[p_root]+sz[q_root];
		}
		else{
			A[p_root]=A[A[q]];
			sz[q_root]=sz[q_root]+sz[p_root];
		}
	}

}


int monte_carlo(double p){
  int sz[N*N];//size of maitaining//
  int Condition[N*N];//create a N*N array store the inforamtino about is open or store the union information//
  int union_find[N*N];//store the full information of each element,1 is full 0 is not full//
  double rand_value;
  int Condition_count=0;
  for(int i=0;i<N*N;i++){
  	union_find[i]=i;
  }
  for(int i=0;i<(N*N);i++){
		sz[i]=1;
	}
  for(int i=0;i<(N*N);i++){
    rand_value = rand()/(double)RAND_MAX;
    if(rand_value<=p){
    	Condition[i]=1;//open//
    }
    else{
    	Condition[i]=0;//closed//
    }
  }
  printf("Condition 100 is%d\n",Condition[100]);
  for(int i=0;i<(N*N);i++){
  	Condition_count=Condition_count+Condition[i];
  }
  printf("Condition_count is %d\n",Condition_count);
  for(int i=0;i<N;i++){
  	for(int j=0;j<N;j++){
  		if(Condition[i*N+j]==1){ //if a site is open,then search it's neighbor//
        int top = i-1;
        int bottom = i+1;
        int left = j-1;
        int right = j+1;
        int top_condition = (top<0)?0:Condition[top*N+j];
        int bottom_condition = (bottom<N)?Condition[bottom*N+j]:0;
        int left_condition = (left<0)?0:Condition[i*N+left];
        int right_condition = (right<N)?Condition[i*N+right]:0;
        if(right_condition==1&&union_find[i*N+right]!=(i*N+j)){
        	quick_union(i*N+j,i*N+right,union_find,sz);
        	break;
        }
        else if(top_condition==1&&union_find[top*N+j]!=(i*N+j)){
           quick_union(i*N+j,top*N+j,union_find,sz);
           break;
           }
        else if(left_condition==1&&union_find[i*N+left]!=(i*N+j)){
           quick_union(i*N+j,i*N+left,union_find,sz);
           break;
           }
        else if(bottom_condition==1&&union_find[bottom*N+j]!=i*N+j){
        	quick_union(i*N+j,bottom*N+j,union_find,sz);
        	break;
        }

        }
      }
        
   }
  for(int i=0;i<N;i++){
  	for(int j=0;j<N;j++){
   	if(connected(i,(N-1)*N+j,union_find)){
      return(1);
      break;
   	}
   }

}
}
int percolation(int i,int j,int Percolation[],int Condition[]){
	int top = i-1;
    int bottom = i+1;
    int left = j-1;
    int right = j+1;
    int top_condition = (top<0)?0:Condition[top*N+j];
    int bottom_condition = (bottom<N)?Condition[bottom*N+j]:0;
    int left_condition = (left<0)?0:Condition[i*N+left];
    int right_condition = (right<N)?Condition[i*N+right]:0;
    if(Percolation[i*N+j]){
    	{
    		if(bottom_condition){
    			Percolation[bottom*N+j]=1;
    		}
    		if(left_condition){
    			Percolation[i*N+left]=1;
    		}
    		if (right_condition)
    		{
    			Percolation[i*N+right]=1;
    		}
    		if(top_condition){
    			Percolation[i*top+j]=1;
    		}
    	}

    }
    else{
    	if(bottom_condition&&Percolation[bottom*N+j]){
    		Percolation[i*N+j]=1;
    	}
    	if(left_condition&&Percolation[left*N+j]){
    		Percolation[i*N+j]=1;
    	}
    	if(right_condition&&Percolation[i*N+right]){
    		Percolation[i*N+j]=1;
    	}
    	if(top_condition&&Percolation[top*N+j]){
    		Percolation[i*N+j]=1;
    	}
    }
}
int monte_carlo_2(double p){
  int Condition[N*N];//create a N*N array store the inforamtino about is open or store the union information//
  double rand_value;
  int Percolation[N*N];
  int Condition_count=0;
  int Percolation_count=0;
  for(int i=0;i<N*N;i++){
  	Percolation[i]=0;
  }
  for(int i=0;i<(N*N);i++){
    rand_value = rand()/(double)RAND_MAX;
    if(rand_value<=p){
    	Condition[i]=1;//open//
    }
    else{
    	Condition[i]=0;//closed//
    }
  }
  for (int i = 0; i < N; i++)
  {
  	if(Condition[i]){
  		Percolation[i]=1;
  	}
  }
  
  for(int i=0;i<N;i++){
  	for(int j=0;j<N;j++){
  		percolation(i,j,Percolation,Condition);
  	}
  }
  for(int i=0;i<N;i++){
  	if(Percolation[(N-1)*N+i]){
  		return(1);
  		break;
  	}
  }

}
int main(void){
  double p=0.593;
  int count =0;
  double rand_value;
  srand((unsigned)time(NULL));
  for(int i=0;i<10000;i++){
    rand_value =rand()/(double)RAND_MAX;
  	count=count+monte_carlo_2(p);
  }
  printf("the prob to be connected is %f,count is %d\n",count/10000.0,count);
}