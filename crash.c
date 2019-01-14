/*
 * Hackaday - Crash Your Code
 * Sample error handler implementation as alternative to assert()
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <execinfo.h>
#include "crash.h"

#define MAX_TRACES (MAX_CALL_TRACES + 1)

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
void
simple_crash(char *format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    exit(EXIT_FAILURE);
}

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
void
fancy_crash(const char *file, int line, const char *function, char *format, ...)
{
    va_list args;
    void *traces[MAX_TRACES];
    int traces_count;
    char **entries;
    int index;

    // print the given message to stderr
    fputs("\nError --------------------------------------------\n    ", stderr);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    // print file/line/function information
    fputs("\n\nLocation -----------------------------------------\n", stderr);
    fprintf(stderr, "    %s:%d  %s()\n", file, line, function);

    // get the traces..
    traces_count = backtrace(traces, MAX_TRACES);
    // ..and their symbols
    entries = backtrace_symbols(traces, traces_count);

    // make sure we got them traces
    if (entries == NULL) {
        // fail if not (we're crashing anyway, so that's alright)
        perror("Cannot get traces");
        exit(EXIT_FAILURE);
    }

    fputs("\nBacktrace ----------------------------------------\n", stderr);

    // print the traces to stderr
    for (index = 1; index < traces_count; index++) {
        // skip the first entry, it's the backtrace() call itself
        fprintf(stderr, "%2d  %s\n", index, entries[index]);
    }

    // ..and we're done with the output
    fputs("\n", stderr);

    // backtrace() allocates memory for entries, gotta free it
    free(entries);

    // and there we go..
    exit(EXIT_FAILURE);
}

