### 0.4.1




* `mulle_buffer` stdio functions now access the embedded `base` buffer struct instead of casting the handle directly
* ``mulle_buffer_do_*`` stack storage macro updated to initialize the new nested layout

## 0.4.0



* buffer read-after-seek now succeeds instead of returning EOF/EBADF
* seeking in read-only buffers now matches FILE\* behavior instead of failing with EINVAL
* seek-to-end followed by write no longer reports ENOSPC
* dropped obsolete modes-buffer expected output





* source files now explicitly carry BSD-3-Clause license headers
* API documentation reorganized under asset/dox/api/toc/index.md
* README now links to API summary


### 0.3.4



* **BREAKING** removed unused `FILE *fp` parameter from ``mulle_putchar`` signature
* function now correctly matches the underlying `putchar()` semantics
