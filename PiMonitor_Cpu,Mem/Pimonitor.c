#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sleep 함수 사용을 위함

void get_cpu_usage() 
{
	FILE *fp; // File 구조체 파일 스트림을 다루는데 사용
	char line[256];
	long long int user, nice, system, idle, iowait, irq, softirq, steal, total;
	
	// /proc/stat file open cpu usage read
	fp = fopen("/proc/stat", "r"); // /proc/stat을 읽기 모드로 연다
	
	if(fp == NULL)
	{
		perror("Error opening /proc/stat");
		return;
	}
	
	fgets(line, sizeof(line), fp); // fp에서 한줄을 읽어서 line크기만큼 line에 저장
	
	sscanf(line, "cpu %lld %lld %lld %lld %lld %lld %lld %lld", //line에 저장된 문자열을 통해 cpu의 user, nice 등 값을 입력받음
	 &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
	
	fclose(fp);
	
	total = user + nice + system + idle + iowait + irq + softirq + steal;
	
	long long int used = total - idle;
	
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
		if(sscanf(line, "MemTotal: %lld kB", &total_memory)) // MemTotal 값을 total_memory에 저장
		{
			continue;
		}
		if(sscanf(line, "MemFree: %lld kB", &free_memory)) // MemFree 값을 free_memory에 저장
		{
			continue;
		}
		if(sscanf(line, "MemAvailable: %lld kB", &available_memory)) // MemAvailable 값을 available_memory에 저장
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

