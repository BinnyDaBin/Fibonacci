#include <stdio.h> 
#include <omp.h>
#include <iostream>

using namespace std;

long fib (int n) { 
	return (n < 2 ? 1 : fib (n - 1) + fib (n - 2)); 
}

int main (int argc, char *argv[]) {
	int max; 
	sscanf (argv[1], "%d", &max); 

	double t1 = omp_get_wtime();
	for (int n = 1; n <= max; n++)
			printf ("T%d: %dth %ld\n", omp_get_thread_num(), n, fib (n));
	t1 = omp_get_wtime() - t1;

	double t2 = omp_get_wtime();
	#pragma omp parallel for schedule(static, 1) num_threads(5)
	  	for (int n = 1; n <= max; n++)
			printf ("T%d: %dth %ld\n", omp_get_thread_num(), n, fib (n));
	t2 = omp_get_wtime() - t2;

	double t3 = omp_get_wtime();
	#pragma omp parallel for schedule(auto) num_threads(5)
	  	for (int n = 1; n <= max; n++)
			printf ("T%d: %dth %ld\n", omp_get_thread_num(), n, fib (n));
	t3 = omp_get_wtime() - t3;

	double t4 = omp_get_wtime();
	#pragma omp parallel for schedule(dynamic, 5) num_threads(5)
	  	for (int n = 1; n <= max; n++)
			printf ("T%d: %dth %ld\n", omp_get_thread_num(), n, fib (n));
	t4 = omp_get_wtime() - t4;

	double t5 = omp_get_wtime();
	#pragma omp parallel for schedule(guided) num_threads(5)
	  	for (int n = 1; n <= max; n++)
			printf ("T%d: %dth %ld\n", omp_get_thread_num(), n, fib (n));
	t5 = omp_get_wtime() - t5;

	double t6 = omp_get_wtime();
	#pragma omp parallel for schedule(runtime) num_threads(5)
	  	for (int n = 1; n <= max; n++)
			printf ("T%d: %dth %ld\n", omp_get_thread_num(), n, fib (n));
	t6 = omp_get_wtime() - t6;

	cout << "Sequential Time: " << t1 << endl;
	cout << "Schedule static Time: " << t2 << endl;
	cout << "Schedule auto Time: " << t3 << endl;
	cout << "Schedule dynamic Time: " << t4 << endl;
	cout << "Schedule guided Time: " << t5 << endl;
	cout << "Schedule runtime Time: " << t6 << endl;

	double min_t1 = min(t1,t2);
	double min_t2 = min(t3,t4);
	double min_t3 = min(t5,t6);
	double min_t4 = min(min_t1, min_t2);
	double min_t = min(min_t3, min_t4);
	cout << "Fastest time: " << min_t << endl;

	double s = t1/min_t;
	double e = s/5;
	cout << "S = " << s << endl;
	cout << "E = " << e << endl;

	return 0;
}