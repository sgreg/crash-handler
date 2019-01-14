/*
 * Hackaday - Crash Your Code
 * Sample error handler implementation as alternative to assert()
 */
#ifndef CRASH_H
#define CRASH_H

/** Maximum number of functions call to include in the backtrace */
#define MAX_CALL_TRACES 20

/**
 * Print simple error output consisting of a given message in printf()
 * formatting style, and exit the program unsuccessfully.
 *
 * If SIMPLE_CRASH macro is defined (on the command line, or before
 * including the header), the crash(format, ...) macro uses this function.
 *
 * @param format format string for the error message along with all additional
 *        parameters as defined for printf() and the likes
 */
void simple_crash(char *format, ...) __attribute__((noreturn));

/**
 * Print fancy error output including the file, line number, and function name
 * of the location the crash is called from, along with a given message in
 * printf() formatting style, and exit the program unsuccessfully.
 *
 * By default, the crash(format, ...) macro uses this function and adds all
 * the location information automatically.
 *
 * @param file file name of the crash location
 * @param line line number of the crash location in the file
 * @param function function name of the crash location
 * @param format format string for the error message along with all additional
 *        parameters as defined for printf() and the likes
 */
void fancy_crash(const char *file, int line, const char *function, char *format, ...) __attribute__((noreturn));

#ifdef SIMPLE_CRASH
#define crash(format, ...) simple_crash(format"\n", ## __VA_ARGS__)
#else
#define crash(format, ...) fancy_crash(__FILE__, __LINE__, __func__, format, ## __VA_ARGS__)
#endif

#endif /* CRASH_H */

