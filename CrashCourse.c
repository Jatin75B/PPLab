#include<stdio.h>
#include<omp.h>

void main(){
	printf("-----System configuration:----\n");
	
	int my_rank=omp_get_thread_num();
	printf("omp_get_thread_num()\nThe main thread executing serial no--> %d\n", my_rank);//windows:0
	/*The omp_get_thread_num function returns the number of the currently executing thread within the team.
	The number returned will always be between 0 and NUM_PARTHDS - 1.
	NUM_PARTHDS is the number of currently executing threads within the team.
	 The master thread of the team returns a value of 0.
	
	If you call omp_get_thread_num from within a serial region,
	 from within a serialized nested parallel region,
	  or from outside the dynamic extent of any parallel region,
	   this function will return a value of 0.*/
	
	int thread_count=omp_get_num_threads();
	printf("\nomp_get_num_threads()\nNumber of threads running in this section-->%d\n", thread_count);//windows:1
	/*omp_get_num_threads inside that loop. Outside a parallel section,
	 you can call omp_get_max_threads for the maximum number of threads to spawn*/
	
	int max_threads = omp_get_max_threads();
	printf("Maximum Number of threads running in this section-->%d\n", max_threads);// window:~
	/*The omp_get_max_threads routine returns the first value of num_list for the OMP_NUM_THREADS environment variable.
	 	This value is the maximum number of threads that can be used to form a new team 
	 		if a parallel region without a num_threads clause is encountered.

If you use omp_set_num_threads to change the number of threads,
	subsequent calls to omp_get_max_threads will return the new value.*/
	
	printf("\nWithout parallel programing:\n"); 
	printf("Hi\n\n");
	
	int num;
	printf("Enter the number of parrallel threads:  "); 
	scanf("%d",&num);
	printf("\tWith parallel programing:\n Using:\t\t#pragma omp parallel num_threads(num)\n\n");
	#pragma omp parallel num_threads(num) 
	{
		thread_count=omp_get_num_threads();
		max_threads = omp_get_max_threads();
		printf("Maximum-->%d, Current Number-->%d in this section\n", max_threads,thread_count);
		
		printf("\tHi---is printed by %d thread\n",omp_get_thread_num());
	}
	
	printf("\tNote: To find which there is executing we use: omp_get_thread_num()");
	
	printf("\n\n\n\'For\' parallelism:\n");
	printf("Enter the number of loops in for:  "); 
	int loop,i;
	scanf("%d",&loop);
	printf("\nWithout parallel programing:\n");
	for(i=0;i<loop;i++){
		printf("\tHi %d---is printed by %d thread\n",i,omp_get_thread_num());
	}
	
	printf("\nEnter the number of parrallel threads:  "); 
	scanf("%d",&num);
	printf("\tWith parallel programing:\n Using:\t#pragma omp parallel for num_threads(num)\n\n");
	#pragma omp parallel for num_threads(num) 
	for(i=0;i<loop;i++)	
		printf("\tHi %d---is printed by %d thread\n",i,omp_get_thread_num());
	
	
}
