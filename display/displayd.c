#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void usr1_handler(int i);
void usr2_handler(int i);
void sigterm_handler(int i);
void display_temp (int sensor, char *sensor_name);
void display_cpu_temp (void);
void display_ref_temp (void);
void get_ref_temp(void);
void set_ref_temp(void);

float ref_temp;
FILE *fp;
char command[256];
char temp[16];

int main(int argc, char ** argv) {

    struct sigaction sa;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGHUP);
    sigprocmask(SIG_BLOCK, &newset, 0);
    sa.sa_handler = usr1_handler;
    sigaction(SIGUSR1, &sa, 0);
    sa.sa_handler = usr2_handler;
    sigaction(SIGUSR2, &sa, 0);
    sa.sa_handler = sigterm_handler;
    sigaction(SIGTERM, &sa, 0);

    pid_t pid = fork();

    if (pid == 0)
    {
	fp = fopen ("/var/run/displayd.pid", "wb");
	sprintf(temp,"%d", getpid());
	fwrite(temp, 1, strlen(temp), fp);
	fclose(fp);

	get_ref_temp();
	display_ref_temp();
	sleep (5);

	while (1) {
	    display_temp(0, "TEMP_IN");
    	    sleep (3);
	    display_temp(1, "TEMP_OUT");
    	    sleep (3);
	    display_cpu_temp();
	    sleep (3);
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

void usr1_handler(int i)
{
    ref_temp++;
    set_ref_temp();
    display_ref_temp();
    sleep (3);
}

void usr2_handler(int i)
{
    ref_temp--;
    set_ref_temp();
    display_ref_temp();
    sleep (3);
}

void sigterm_handler(int i)
{
    remove ("/var/run/displayd.pid");
    exit (0);
}

void display_ref_temp (void)
{
    sprintf(temp, "%.1f", ref_temp);
    sprintf(command, "/opt/beerbox/bin/OLED.py --parameter SETTINGS --value %s", temp);
    fp = popen(command, "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    pclose(fp);
}

void get_ref_temp(void)
{
    fp = popen("cat /opt/beerbox/etc/ref_temp", "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    while (fgets(temp, sizeof(temp)-1, fp) != NULL);
    pclose(fp);
    ref_temp = strtof(temp, NULL);
}

void set_ref_temp(void)
{
    sprintf(temp, "%.1f", ref_temp);
    fp = fopen ("/opt/beerbox/etc/ref_temp", "wb");
    fwrite(temp, 1, strlen(temp), fp);
    fclose(fp);
}

void display_temp (int sensor, char *sensor_name)
{
    sprintf(command, "cat /tmp/sensors/%d", sensor);
    fp = popen(command, "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    while (fgets(temp, sizeof(temp)-1, fp) != NULL);
    pclose(fp);
    sprintf(command, "/opt/beerbox/bin/OLED.py --parameter %s --value %s", sensor_name, temp);
    fp = popen(command, "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    pclose(fp);
}

void display_cpu_temp (void)
{
    fp = popen("cat /sys/class/thermal/thermal_zone1/temp", "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    while (fgets(temp, sizeof(temp)-1, fp) != NULL);
    pclose(fp);
    sprintf(command, "/opt/beerbox/bin/OLED.py --parameter CPU_TEMP --value %s", temp);
    fp = popen(command, "r");
    if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
    }
    pclose(fp);
}
