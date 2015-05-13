/*
 * task.c
 *
 *  Created on: Apr 26, 2015
 *      Author: ouyangfeng
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "log.h"
#include "task.h"

int taskcount = 0;
Interval_Task *tasks[1024];

int read_task(const char *filename)
{

	log_d("read_task filename:%s", filename);
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot open %s\n", filename);
		return 0;
	}

	char str_line[1024] =
	{ };             //每行最大读取的字符数
	while (!feof(fp))
	{
		if (fgets(str_line, 1024, fp) == NULL)             //读取一行
		{
			break;
		}
		if (strlen(str_line) > 0)
		{
			trim(str_line);
			add_task(parse_cmd(str_line));
			log_d("%s", str_line); //输出
		}
		memset(str_line, 0, 1024);
	}
	fclose(fp);
	return 1;
}

int add_task(Interval_Task *task)
{
	if (task)
	{
		tasks[taskcount] = task;
		taskcount++;
	}
	return 1;
}

int removeall_task()
{
	int i = 0;
	for (; i < taskcount; i++)
	{
		free_interval_task(tasks[i]);
	}

	return 1;
}

int trim(char *ptr)
{
	int start, end, i;
	if (ptr)
	{
		for (start = 0; isspace(ptr[start]); start++)
			;
		for (end = strlen(ptr) - 1; isspace(ptr[end]); end--)
			;
		for (i = start; i <= end; i++)
			ptr[i - start] = ptr[i];
		ptr[end - start + 1] = '\0';
		return 1;
	}
	else
		return 0;
}

Interval_Task * parse_cmd(char *cmd)
{
	if (cmd)
	{
		Interval_Task *task = (Interval_Task*) malloc(sizeof(Interval_Task));
		memset(task, 0, sizeof(Interval_Task));
		int start;
		for (start = 0; !isspace(cmd[start]); start++)
			;
		char *interval = (char *) malloc(start + 1);
		strncpy(interval, cmd, start + 1);
		task->interval = atol(interval);

		int cmdline_size = strlen(cmd) - start + 1;
		char *cmdline = (char *) malloc(cmdline_size);
		int i = 0;
		for (; i < cmdline_size; i++)
		{
			cmdline[i] = cmd[i + start];
		}
		trim(cmdline);
		task->cmdline = cmdline;
		return task;
	}
	return NULL;
}

int free_interval_task(Interval_Task *task)
{

	if (task)
	{
		task->interval = 0;
		free(task->cmdline);
	}

	return 1;
}

void exec_task()
{

	if (taskcount > 0)
	{
		int i = 0;
		time_t current;
		Interval_Task *task;
		while (1)
		{
			current = time(NULL);
			for (; i < taskcount; i++)
			{
				task = tasks[i];
				time_t j_time = (current - task->last_time);
				if (j_time >= task->interval)
				{
					log_d("exec cmdline:%s", task->cmdline);
					int result = system(task->cmdline);
					log_d("system result:%d", result);
					task->last_time = current;
				}
			}
			i = 0;
			sleep(1);

		}
	}
}
