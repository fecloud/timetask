/*
 * log.h
 *
 *  Created on: 2015年4月25日
 *  Author: oyf_feng
 */

#ifndef LOG_H_
#define LOG_H_

/*
 ** Make sure we can call this stuff from C++.
 */
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef DEBUG
#define log_d(...) \
		((void)printf("%s:%d ",__FILE__, __LINE__)); \
		((void)printf(__VA_ARGS__)); \
		((void)printf("\n"))
#else
#define log_d(...) ((void)0)
#endif

#define std_error(...) fprintf(stderr,__VA_ARGS__); \
		((void)printf("\n"))
/*
 ** Make sure we can call this stuff from C++.
 */
#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
