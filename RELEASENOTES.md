### 0.3.3




* add compile-time error in src/mulle-buffer-stdio.c to require `<mulle-c11/mulle-c11-bool.h>` be included before `<windows.h>`, preventing confusing build/macro issues on Windows



* ``mulle_buffer_init_with_filepath`` now reports `EISDIR` for directory paths on Windows, matching POSIX behavior
* exported ``mulle_buffer_init_with_filepath`` and FILE-read helpers for shared/dynamic builds
* Windows CI/test runs now skip `fmemopen`-dependent cases and use Windows-specific golden outputs
