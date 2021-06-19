/*
	Execution time before parallelization: x.xx [sec] 									
	Execution time after parallelization: x.xx [sec]
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/* ---------------------------------------------------------------------------------------------
   Naive Implementation of kNN algorithm ver. 1.0 
   (A couple of parallelization techniques are to be applied to this implementation.)
   
   - No input files. Instead, input data structures are generated artificially.
   - Input arguments: vector dimension for both reference and input data, 
                      the number of reference vectors, 
		              the number of input vectors
		              k value 
		              the number of classes
   - For later SSE implementation, labels are stored in a separate array.     
------------------------------------------------------------------------------------------------ */

typedef struct dist_info {
float dist;
int label;
} dist_info_t;

/* main data structure declaration */
float *ref;				// reference data
float *in;				// input data
int *label;				// label of the reference data
dist_info_t *result;	// stores (computed) distance and the corresponding label
int *class;				// stores classification result of each input vector
int *counter;			// stored class counts of neighbors


/* callback function used for qsort */
int my_compare_mem(const void *a, const void *b)
{
   float difference;   
   dist_info_t *c, *d;
   
   c=(dist_info_t *)a;
   d=(dist_info_t *)b;

   difference=c->dist - d->dist;

   if (difference>0)
   	return 1;
   else if (difference<0)
   	return -1;
   else
   	return 0;
}



int main (int argc, char *argv[])
{
    int i, j, k, l;
    int vec_dim, num_ref, num_in, k_val, num_class;
    float dist;
    double start, end, sec, usec;
    struct timeval tp;
    int in_index, ref_index;
    int max_label;
    
    /* input argument parsing */
    if (argc!=6) {
    	    printf("Usage: %s  <vec. dim.> <num of ref. vec.> < num of input vec.> <k value> < num of classes>\n", argv[0]);
            return 1;
    }
    else {
    	    vec_dim=atoi(argv[1]);
	    	num_ref=atoi(argv[2]);	    
	    	num_in=atoi(argv[3]);
	    	k_val=atoi(argv[4]);
	    	num_class=atoi(argv[5]);
	    
	    if (num_ref<k_val) {
	       printf("num_ref should be greater or equal to k_val\n");
	       return 1;	    
	    }
    }

    /* data structure allocation */
    ref = _aligned_malloc(vec_dim*num_ref*sizeof(float),16);
    in = _aligned_malloc(vec_dim*num_in*sizeof(float),16);
    label = _aligned_malloc(num_ref*sizeof(int),16);
    result = _aligned_malloc(num_ref*sizeof(dist_info_t),16);
    class = _aligned_malloc(num_in*sizeof(int),16);
    counter = _aligned_malloc(num_class*sizeof(int),16);
    
        
   /* Filling in data structure */
   for (i=0;i<vec_dim*num_ref;i++)
      ref[i]=(rand()%100)/100.0;
      
   for (i=0;i<vec_dim*num_in;i++)
      in[i]=(rand()%100)/100.0;
      
   for (i=0;i<num_ref;i++)
      label[i]=(rand()%num_class);  
          
   
    /* time stamp */
    gettimeofday(&tp, NULL);
    sec=(double)(tp.tv_sec);
    usec=(double)(tp.tv_usec)/1E6;
    start=sec+usec;
    
    
    /* main loop */
    in_index=0;
    for (i=0;i<num_in*vec_dim;i+=vec_dim) {
    
       /* distance calculation */
	   ref_index=0;
       for (j=0;j<num_ref*vec_dim;j+=vec_dim) {
       
          	dist=0;
	  		for (k=0;k<vec_dim;k++) {
	  	     	dist+=(ref[j+k]-in[i+k])*(ref[j+k]-in[i+k]);	  
	  		}
	  
          	result[ref_index].dist=dist;
	  		result[ref_index].label=label[ref_index];
	  		ref_index++;       
       }    
       /* sorting */
       qsort(result, num_ref, sizeof(dist_info_t), my_compare_mem); 
       
       /* classification */
       for (l=0;l<num_class;l++)
          counter[l]=0;
	  
       for (l=0;l<k_val;l++) {
          counter[result[l].label]++;       
       }
       
       max_label=0;
       for (l=1;l<num_class;l++)
          if (counter[l]>counter[max_label])
	      max_label=l;
	      
       class[in_index++]=max_label;	      

    }
  
    /* time stamp */
    gettimeofday(&tp, NULL);
    sec=(double)(tp.tv_sec);
    usec=(double)(tp.tv_usec)/1E6;
    end=sec+usec;  
  
    /*
    for (i=0;i<num_in;i++)
       printf("[%d]: %d\n", i, class[i]);
    */
	   
    printf("Exe. Time: %.8lf\n", end-start);

    return 0;    
    
    
}
    

