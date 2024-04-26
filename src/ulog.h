/**
MIT License

Copyright (c) 2019 R. Dunbar Poor <rdpoor@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * \file
 *
 * \brief uLog: lightweight logging for embedded systems
 *
 * A quick intro by example:
 *
 *     #include "ulog.h"
 *
 *     // To use uLog, you must define a function to process logging messages.
 *     // It can write the messages to a console, to a file, to an in-memory
 *     // buffer: the choice is yours.  And you get to choose the format of
 *     // the message.  This example prints to the console.  One caveat: msg
 *     // is a static string and will be over-written at the next call to ULOG.
 *     // You may print it or copy it, but saving a pointer to it will lead to
 *     // confusion and astonishment.
 *     //
 *     void my_console_logger(ulog_level_t level, const char *msg) {
 *         printf("%s [%s]: %s\n",
 *             get_timestamp(),
 *             ulog_level_name(level),
 *             msg);
 *     }
 *
 *     int main() {
 *         ULOG_INIT();
 *
 *         // log to the console messages that are WARNING or more severe.  You
 *         // can re-subscribe at any point to change the severity level.
 *         ULOG_SUBSCRIBE(my_console_logger, ULOG_WARNING);
 *
 *         // log to a file messages that are DEBUG or more severe
 *         ULOG_SUBSCRIBE(my_file_logger, ULOG_DEBUG);
 *
 *         int arg = 42;
 *         ULOG_INFO("Arg is %d", arg);  // logs to file but not console
 *     }
 */

#ifndef ULOG_H_
#define ULOG_H_

#ifdef __cplusplus
extern "C" {
    #endif

typedef enum {
  ULOG_TRACE_LEVEL=100,
  ULOG_DEBUG_LEVEL,
  ULOG_INFO_LEVEL,
  ULOG_WARNING_LEVEL,
  ULOG_ERROR_LEVEL,
  ULOG_CRITICAL_LEVEL,
  ULOG_ALWAYS_LEVEL
} ulog_level_t;

// The following macros enable or disable uLog.  If `ULOG_ENABLED` is
// defined at compile time, a macro such as `ULOG_INFO(...)` expands
// into `ulog_message(ULOG_INFO_LEVEL, ...)`.  If `ULOG_ENABLED` is not
// defined, then the same macro expands into `do {} while(0)` and will
// not generate any code at all.  
//
// There are two ways to enable uLog: you can uncomment the following
// line, or -- if it is commented out -- you can add -DULOG_ENABLED to
// your compiler switches.
//#define ULOG_ENABLED

#ifdef ULOG_ENABLED
  #define ULOG_INIT() ulog_init()
  #define ULOG_SUBSCRIBE(a, b) ulog_subscribe(a, b)
  #define ULOG_UNSUBSCRIBE(a) ulog_unsubscribe(a)
  #define ULOG_LEVEL_NAME(a) ulog_level_name(a)
  #define ULOG(...) ulog_message(NULL, __VA_ARGS__)
  #define ULOG_TRACE(...) ulog_message(NULL, ULOG_TRACE_LEVEL, __VA_ARGS__)
  #define ULOG_DEBUG(...) ulog_message(NULL, ULOG_DEBUG_LEVEL, __VA_ARGS__)
  #define ULOG_INFO(...) ulog_message(NULL, ULOG_INFO_LEVEL, __VA_ARGS__)
  #define ULOG_WARNING(...) ulog_message(NULL, ULOG_WARNING_LEVEL, __VA_ARGS__)
  #define ULOG_ERROR(...) ulog_message(NULL, ULOG_ERROR_LEVEL, __VA_ARGS__)
  #define ULOG_CRITICAL(...) ulog_message(NULL, ULOG_CRITICAL_LEVEL, __VA_ARGS__)
  #define ULOG_ALWAYS(...) ulog_message(NULL, ULOG_ALWAYS_LEVEL, __VA_ARGS__)
  #define ULOG_ARG(a, ...) ulog_message(a, __VA_ARGS__)
  #define ULOG_ARG_TRACE(a, ...) ulog_message(a, ULOG_TRACE_LEVEL, __VA_ARGS__)
  #define ULOG_ARG_DEBUG(a, ...) ulog_message(a, ULOG_DEBUG_LEVEL, __VA_ARGS__)
  #define ULOG_ARG_INFO(a, ...) ulog_message(a, ULOG_INFO_LEVEL, __VA_ARGS__)
  #define ULOG_ARG_WARNING(a, ...) ulog_message(a, ULOG_WARNING_LEVEL, __VA_ARGS__)
  #define ULOG_ARG_ERROR(a, ...) ulog_message(a, ULOG_ERROR_LEVEL, __VA_ARGS__)
  #define ULOG_ARG_CRITICAL(a, ...) ulog_message(a, ULOG_CRITICAL_LEVEL, __VA_ARGS__)
  #define ULOG_ARG_ALWAYS(a, ...) ulog_message(a, ULOG_ALWAYS_LEVEL, __VA_ARGS__)
#else
  // uLog vanishes when disabled at compile time...
  #define ULOG_INIT() do {} while(0)
  #define ULOG_SUBSCRIBE(a, b) do {} while(0)
  #define ULOG_UNSUBSCRIBE(a) do {} while(0)
  #define ULOG_LEVEL_NAME(a) ""
  #define ULOG(a, s, f, ...) do {} while(0)
  #define ULOG_TRACE(a, f, ...) do {} while(0)
  #define ULOG_DEBUG(a, f, ...) do {} while(0)
  #define ULOG_INFO(a, f, ...) do {} while(0)
  #define ULOG_WARNING(a, f, ...) do {} while(0)
  #define ULOG_ERROR(a, f, ...) do {} while(0)
  #define ULOG_CRITICAL(a, f, ...) do {} while(0)
  #define ULOG_ALWAYS(a, f, ...) do {} while(0)
  #define ULOG_ARG(a, s, f, ...) do {} while(0)
  #define ULOG_ARG_TRACE(a, f, ...) do {} while(0)
  #define ULOG_ARG_DEBUG(a, f, ...) do {} while(0)
  #define ULOG_ARG_INFO(a, f, ...) do {} while(0)
  #define ULOG_ARG_WARNING(a, f, ...) do {} while(0)
  #define ULOG_ARG_ERROR(a, f, ...) do {} while(0)
  #define ULOG_ARG_CRITICAL(a, f, ...) do {} while(0)
  #define ULOG_ARG_ALWAYS(a, f, ...) do {} while(0)
#endif

typedef enum {
  ULOG_ERR_NONE = 0,
  ULOG_ERR_SUBSCRIBERS_EXCEEDED,
  ULOG_ERR_NOT_SUBSCRIBED,
} ulog_err_t;

// define the maximum number of concurrent subscribers
#ifndef ULOG_MAX_SUBSCRIBERS
#define ULOG_MAX_SUBSCRIBERS 6
#endif
// maximum length of formatted log message
#ifndef ULOG_MAX_MESSAGE_LENGTH
#define ULOG_MAX_MESSAGE_LENGTH 120
#endif
/**
 * @brief: prototype for uLog subscribers.
 */
typedef void (*ulog_function_t)(ulog_level_t severity, char *msg, const void* arg);

void ulog_init(void);
ulog_err_t ulog_subscribe(ulog_function_t fn, ulog_level_t threshold);
ulog_err_t ulog_unsubscribe(ulog_function_t fn);
const char *ulog_level_name(ulog_level_t level);
void ulog_message(const void* arg, ulog_level_t severity, const char *fmt, ...);
void ulog_lock_mutex();
void ulog_unlock_mutex();
#ifdef __cplusplus
}
#endif

#endif /* ULOG_H_ */
