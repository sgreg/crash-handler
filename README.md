# Hackaday Sample Crash Handler

Crash with purpose: a small example crash handling module in C to have useful error output when things go wrong. Check out [the Hackaday article on the subject]() for more information.

On crash, the code will print your custom error message along with some details that looks something like this:

```
Error --------------------------------------------
    check for value failed: 110


Location -----------------------------------------
    main.c:11  foo()

Backtrace ----------------------------------------
 1  ./main(foo+0x57) [0x55d0f691a250]
 2  ./main(main+0x33) [0x55d0f691a285]
 3  /usr/lib/libc.so.6(__libc_start_main+0xf3) [0x7f905139b223]
 4  ./main(_start+0x2e) [0x55d0f691a12e]
```

## Content

* `crash.h` crash handler header file
* `crash.c` crash handler source file
* `sample.c` sample usage of the crash handler

## Usage

The `sample.c` file has a very basic example of how to use the crash handler, but basically, you include the `crash.h` file and call the `crash()` macro whenever something crashworthy happens in your code.

```
#include "crash.h"

...

    if (!valid_data) {
        crash("invalid data %d", data);
    }
```

## Compiling

Add the `crash.c` when you compile and you're done:

```
$ gcc -o sample sample.c crash.c
```

That, however, won't give you the function names in the backtrace, so instead of `./main(foo+0x57)` you will get `./main(+0x1250)`. To have the function names included, you need to add the `-rdynamic` compiler option:

```
$ gcc -o sample -rdynamic sample.c crash.c
```

### Simpler output

If you don't want / need all the details about the location and backtrace, you can define the `SIMPLE_CRASH` macro:

```
$ gcc -o sample -rdynamic -DSIMPLE_CRASH sample.c crash.c
```

Now you will only get your custom error message as output:

```
check for value failed: 132
```


