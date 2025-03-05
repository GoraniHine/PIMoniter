#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_cpu_usage() 
{
	FILE *fp;
	char line[256];
	long long int user, nice, system, idle, iowait, irq, softirq, steal, total;
	
	// /proc/stat file open cpu usage read
	fp = fopen("/proc/stat", "r");
	
	if(fp == NULL)
	{
		perror("Error opening /proc/stat");
		return;
	}
	
	fgets(line, sizeof(line), fp);
	
	sscanf(line, "cpu %lld %lld %lld %lld %lld %lld %lld %lld",
	 &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
	
	fclose(fp);
	
	total = user + nice + system + idle + iowait + irq + softirq + steal;
	
	long long int used = total -idle;
	
	printf("CPU UsageL %.2f%%\n", (double)used / total * 100);
}

void get_memory_usage() 
{
	FILE *fp;
	char line[256];
	long long int total_memory, free_memory, available_memory;
	
	fp = fopen("/proc/meminfo", "r");
	
	if(fp == NULL)
	{
		perror("Error opening /proc/meminfo");
		return;
	}
	
	while(fgets(line, sizeof(line), fp))
	{
		if(sscanf(line, "MemTotal: %lld kB", &total_memory))
		{
			continue;
		}
		if(sscanf(line, "MemFree: %lld kB", &free_memory))
		{
			continue;
		}
		if(sscanf(line, "MemAvailable: %lld kB", &available_memory))
		{
			continue;
		}
	}
	
	fclose(fp);
	
	long long int used_memory = total_memory - free_memory;
	
	printf("Memory Usage: %.2f%%\n", (double)used_memory / total_memory * 100);
}

int main(void)
{
	while(1)
	{
		get_cpu_usage();
		get_memory_usage();
		sleep(5);
	}
	
	return 0;
}

