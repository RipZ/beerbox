#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define NUM_SENSORS 1
#define SLEEP_TIME 10

void get_temp(int sensor);
void sigterm_handler(int i);

FILE *fp;
char temp[16];
char command[256];

int main(int argc, char ** argv) {

    struct sigaction sa;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGHUP);
    sigprocmask(SIG_BLOCK, &newset, 0);
    sa.sa_handler = sigterm_handler;
    sigaction(SIGTERM, &sa, 0);
    char pid_filename[256];
    int sensor;

    pid_t pid = fork();

    if (pid == 0)
    {
	fp = fopen ("/var/run/tempd.pid", "wb");
	sprintf(temp,"%d", getpid());
	fwrite(temp, 1, strlen(temp), fp);
	fclose(fp);

	while (1) {
	    sensor = 0;
	    while (sensor <= NUM_SENSORS) {
		get_temp(sensor);
		sensor++;
	    }
	sleep (SLEEP_TIME);
	}
    }
    else if (pid > 0)
    {
	return (0);
    }
    else
    {
        // fork failed
        printf("fork() failed!\n");
        return 1;
    }

    return (0);
}

void sigterm_handler(int i)
{
    remove ("/var/run/tempd.pid");
    exit (0);
}

void get_temp(int sensor)
{
    sprintf(command,"digitemp_DS9097U -t %d -r2000 -q -c /opt/beerbox/etc/digitemp.conf",sensor);
    fp = popen(command, "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    while (fgets(temp, sizeof(temp)-1, fp) != NULL);
    pclose(fp);
    sprintf(command, "/tmp/sensors/%d", sensor);
    fp = fopen (command, "wb");
    fwrite(temp, 1, strlen(temp), fp);
    fclose(fp);
}
