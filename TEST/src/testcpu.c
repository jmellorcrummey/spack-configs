/* testcpu.c - program to use CPU time, and print its arguments and environment */

#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#if 0
#include	<procfs.h>
#endif

void	cputime0(int);
void	cputime1(int);
void	cputime2(int);

int
main(int argc, char **argv, char **envp)
{
	int	i;
	char	**p;

	fprintf(stderr, "printargenv, argc = %d, pid = %d\n",
		argc, getpid() );

	for (i = 0; i<5 ; i ++) {
	    cputime0(0);
	}

	p = argv;
	for (i = 0; i < argc; i ++) {
	    fprintf(stderr, "  argv[%d] = %s\n", i, *p);
	    p ++;
	}
	fprintf(stderr, "\n");

	for (i = 0; i<5 ; i ++) {
	    cputime2(0);
	}

	p = envp;
	for (i = 0; ; i ++) {
	    if (*p == NULL) break;
	    if (strlen (*p) < 100) {
	        fprintf(stderr, "  envp[%d] = %s\n", i, *p);
	    } else {
	        fprintf(stderr, "  envp[%d] ==> too long\n", i);
	    }
	    p ++;
	}

#if 0
	/* print some sizes */
	fprintf(stderr, "\nsizes: id_t(%d), int(%d) timestruc_t(%d), ulong_t(%d) uint64_t(%d)\n",
	    sizeof(id_t), sizeof(int), sizeof(timestruc_t), sizeof(ulong_t), sizeof(uint64_t) );
	fprintf(stderr, "sizes: long long(%d), prusage_t(%d)\n",
	    sizeof(long long), sizeof(prusage_t) );
#endif
	for (i = 0; i<5 ; i ++) {
	    cputime1(0);
	}
	return 0;
}


void
cputime0(int k)
{
	int	i;	/* temp value for loop */
	int	j;	/* temp value for loop */
	volatile float	x;	/* temp variable for f.p. calculation */

	if(k == 0) {
		k = 160;
	}
	for (i = 0; i < k; i ++) {
		x = 0.0;
		for(j=0; j<1000000; j++) {
			x = x + 1.0;
		}
	}
	return;
}

void
cputime1(int k)
{
	cputime2(k);

	return;
}

void
cputime2(int k)
{
	int	i;	/* temp value for loop */
	int	j;	/* temp value for loop */
	volatile float	x;	/* temp variable for f.p. calculation */

	if(k == 0) {
		k = 160;
	}
	for (i = 0; i < k; i ++) {
		x = 0.0;
		for(j=0; j<1000000; j++) {
			x = x + 1.0;
		}
	}
	return;
}
