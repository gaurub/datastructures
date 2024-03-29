#ifndef __COMMON_H__
#define __COMMON_H__

#define LESS_THAN -1
#define EQUALS 0
#define GREATER_THAN 1

#ifdef DEBUG
	#define LOG_DEBUG(message, file, line) fprintf(stderr, "%s:%d %s %s %s\n", file, line, __DATE__, __TIME__, message)
#else
	#define LOG_DEBUG(message, file, line) 
#endif

#endif /* __COMMON_H__ */
