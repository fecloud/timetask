/*
 * task.h
 *
 *  Created on: Apr 26, 2015
 *      Author: ouyangfeng
 */

#ifndef TASK_H_
#define TASK_H_

#include <time.h>

/*
 ** Make sure we can call this stuff from C++.
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct Interval_Task {

	time_t last_time;
	long interval; //间隔时间
	char *cmdline;

} Interval_Task;

/*
 * 读取任务
 */
int read_task(const char *filename);

/*
 * 去除字符左右两达的空格
 */
int trim(char * ptr);

/*
 * 解析命令行
 */
Interval_Task * parse_cmd(char *cmd);
/*
 * 添加任务
 */
int add_task(Interval_Task *task);

/*
 * 删了所有任务
 */
int removeall_task();

/*
 * 释放
 */
int free_interval_task(Interval_Task *task);

/*
 *执行
 */
void exec_task();
/*
 ** Make sure we can call this stuff from C++.
 */
#ifdef __cplusplus
}
#endif

#endif /* TASK_H_ */
