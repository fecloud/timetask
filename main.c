/*
 * main.c
 *
 *  Created on: Apr 26, 2015
 *      Author: ouyangfeng
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#include "task.h"
#include "log.h"

int save_pid(const char * path)
{
	pid_t pid = getpid();
	FILE *fp = fopen(path, "w+");
	if (!fp)
	{
		printf("open file fail\n");
		return 0;
	}
	char str[10];
	sprintf(str, "%d", pid);
	fwrite(str, strlen(str), 1, fp);
	fclose(fp);
	fp = NULL;

	return 1;
}

/**
 * 查看文件是否可读取
 */
int try_read_conf(const char *filename)
{
	const FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot open %s\n", filename);
		return 0;
	}
	return 1;
}

void fork_proccess(char **argv)
{
	pid_t fpid; //fpid表示fork函数返回的值
	fpid = fork();
	if (fpid < 0)
		fprintf(stderr, "error in fork!");
	else if (fpid == 0)
	{
		char pid_path[200] =
		{ };
		sprintf(pid_path, "%s.pid", argv[0]);
		printf("%s\n", pid_path);
		save_pid(pid_path);
		if (read_task(argv[1]))
		{
			exec_task();
		}
		removeall_task();
	}
}

void send_signal(int pid,int signal)
{
  if(kill(pid,signal) == 0)
  printf("send signal success.\n");
  else
  printf("send signal failed.\n");
}

/**
 * 杀死进程
 */
int kill_proccess(char **argv)
{
	char pid_path[200] =
	{ };
	sprintf(pid_path, "%s.pid", argv[0]);
	printf("%s\n", pid_path);
	FILE *fp = fopen(pid_path, "r");
	if(fp == NULL){
		return -1;
	}

	char str_line[1024] =
	{ };
	while (!feof(fp))
	{
		if(fgets(str_line, 1024, fp) == NULL)//读取一行
		{
			break;
		}
		if (strlen(str_line) > 0)
		{
			break;
		}
		memset(str_line, 0, 1024);
	}

	int pid = atoi(str_line);
	log_d("pid:%d", pid);
	send_signal(pid,SIGKILL);

	fclose(fp);

	return remove(pid_path);
}

int main(int argc, char **argv)
{

	if (argc <= 1)
	{
		printf("\nUsage:%s <task file>\n", argv[0]);
		return -1;
	}

	if (strcmp("stop", argv[1]) == 0)
	{
		return kill_proccess(argv);
	}

	if (!try_read_conf(argv[1]))
	{
		return 1;
	}
	kill_proccess(argv);
	fork_proccess(argv);

	return 0;
}

