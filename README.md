# mulle-fprintf

#### 🔢 mulle-fprintf marries mulle-sprintf to stdio.h


Function         | Description
-----------------|-------------
`mulle_printf`   | Like [printf](//www.cplusplus.com/reference/cstdio/printf/) prints to **stdout**
`mulle_vprintf`  | `<stdarg.h>` variant of `mulle_printf`
`mulle_fprintf`  | Prints to `FILE`
`mulle_vfprintf` | `<stdarg.h>` variant of `mulle_fprintf`


| Release Version
|-----------------------------------
|[![Build Status](https://github.com/mulle-core/mulle-fprintf/workflows/CI/badge.svg?branch=release)](//github.com/mulle-core/mulle-fprintf)  ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-core/mulle-fprintf/workflows/CI/badge.svg?branch=release)

### Memo

mulle-sprintf must be "force" linked (all-load) with mulle-fprintf, 
otherwise the plugin conversions don't appear. mulle-sde will do this automatically.


### You are here

![Overview](overview.dot.svg)


## Add

Use [mulle-sde](//github.com/mulle-sde) to add mulle-fprintf to your project:

``` sh
mulle-sde dependency add --c --github mulle-core mulle-fprintf
```

## Install

### mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-fprintf
and all its dependencies:

``` sh
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-core/mulle-fprintf/archive/latest.tar.gz
```

### Manual Installation


Install the requirements:

Requirements                                           | Description
-------------------------------------------------------|-------------------
[mulle-sprintf](//github.com/mulle-core/mulle-sprintf) | mulle-sprintf

Install into `/usr/local`:

``` sh
cmake -B build \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      -DCMAKE_PREFIX_PATH=/usr/local \
      -DCMAKE_BUILD_TYPE=Release &&
cmake --build build --config Release &&
cmake --install build --config Release
```

### Steal

Read [STEAL.md](//github.com/mulle-c11/dox/STEAL.md) on how to steal the
source code and incorporate it in your own projects.


### Platforms and Compilers

All platforms and compilers supported by
[mulle-c11](//github.com/mulle-c/mulle-c11) and
[mulle-thread](//github.com/mulle-concurrent/mulle-thread).


## Author

[Nat!](//www.mulle-kybernetik.com/weblog) for
[Mulle kybernetiK](//www.mulle-kybernetik.com) and
[Codeon GmbH](//www.codeon.de)
