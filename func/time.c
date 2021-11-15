#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>

void printt(char *s, struct timeval *tv) {
    
    fprintf(stderr, "%s: %9ld.%01ld\n", s, tv->tv_sec, tv->tv_usec/100000);
}

int main(int argc, char** argv) {

	int status;
	pid_t pid;
	struct timeval before, after;
	struct rusage ru;

	if (argc<=1){
	    exit(0);
    }

	gettimeofday(&before, 0);

	pid = fork();

	if (pid < 0) {
		perror("time");
		exit(1);
	}
	if (pid == 0) {
		execvp(argv[2], &argv[2]);
		perror(argv[2]);
		exit(1);
	}

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (wait3(&status, 0, &ru) != pid);

	gettimeofday(&after, 0);

	if ((status&0377) != 0) {
        fprintf(stderr, "\nCommand terminated abnormally.\n");
    }
	after.tv_sec -= before.tv_sec;
	after.tv_usec -= before.tv_usec;

	if (after.tv_usec < 0) {
        after.tv_sec--, after.tv_usec += 1000000;
    }
    
    fprintf(stderr, "\n");
	printt("real", &after);
	printt("user", &ru.ru_utime);
	printt("sys ", &ru.ru_stime);
	fprintf(stderr, "\n");
	exit (status>>8);
}
