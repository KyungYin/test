#ifndef __LOG_H_
#define __LOG_H_

#include <stdio.h>
#include <string.h>

#define BASENAME(str)       (strrchr(str, '/') ? strrchr(str, '/') + 1 : str)   
#define __BASE_FILE_NAME__   BASENAME(__FILE__)


#ifdef DEBUG

/**
 * ANSI COLOR DEFINITIONS
 */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define LOG_DEBUG(fmt, args...)      do { \
                                         printf(fmt, ##args); \
                                     } while(0)

#define LOG_INFO(fmt, args...)       do { \
                                         printf(fmt, ##args); \
                                     } while(0)

#define LOG_WARNNIG(fmt, args...)    do { \
										 printf(ANSI_COLOR_YELLOW); \
                                         printf("%s:%d:%s() " fmt, __BASE_FILE_NAME__, __LINE__, __FUNCTION__, ##args); \
										 printf(ANSI_COLOR_GREEN); \
                                     } while(0)

#define LOG_ERROR(fmt, args...)      do { \
										 printf(ANSI_COLOR_RED); \
                                         printf("%s:%d:%s() " fmt, __BASE_FILE_NAME__, __LINE__, __FUNCTION__, ##args); \
										 printf(ANSI_COLOR_RESET); \
                                     } while(0)
#else

#define LOG_DEBUG(fmt, ...)          do { /* NOP */ } while(0)
#define LOG_INFO(fmt, ...)           do { /* NOP */ } while(0)
#define LOG_WARNNIG(fmt, ...)        do { /* NOP */ } while(0)
#define LOG_ERROR(fmt, ...)          do { /* NOP */ } while(0)

#endif

#endif /* __LOG_H_ */
