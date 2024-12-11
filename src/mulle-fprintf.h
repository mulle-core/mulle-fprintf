/*
 * template: demo/library/PROJECT_SOURCE_DIR/PROJECT_NAME.h
 * vendor/extension: mulle-sde/c-demo
 */
#ifndef mulle_fprintf_h__
#define mulle_fprintf_h__

#include "include.h"

#include <stdint.h>

/*
 *  (c) 2021 Nat! Mulle kybernetiK 
 *
 *  version:  major, minor, patch
 */
#define MULLE__FPRINTF_VERSION  ((0UL << 20) | (2 << 8) | 1)


static inline unsigned int   mulle_fprintf_get_version_major( void)
{
   return( MULLE__FPRINTF_VERSION >> 20);
}


static inline unsigned int   mulle_fprintf_get_version_minor( void)
{
   return( (MULLE__FPRINTF_VERSION >> 8) & 0xFFF);
}


static inline unsigned int   mulle_fprintf_get_version_patch( void)
{
   return( MULLE__FPRINTF_VERSION & 0xFF);
}

MULLE__FPRINTF_GLOBAL
uint32_t   mulle_fprintf_get_version( void);


#include <stdio.h>
#include <stdarg.h>

MULLE__FPRINTF_GLOBAL
int   mulle_printf( char *format, ...);

MULLE__FPRINTF_GLOBAL
int   mulle_fprintf( FILE *fp, char *format, ...);

MULLE__FPRINTF_GLOBAL
int   mulle_vfprintf( FILE *fp, char *format, va_list args);

MULLE__FPRINTF_GLOBAL
int   mulle_mvfprintf( FILE *fp, char *format, mulle_vararg_list arguments);

static inline
int   mulle_vprintf( char *format, va_list args)
{
   return( mulle_vfprintf( stdout, format, args));
}

static inline
int   mulle_mvprintf( char *format, mulle_vararg_list arguments)
{
   return( mulle_mvfprintf( stdout, format, arguments));
}


/*
 * The following files are auto-generated.
 * The _mulle-fprintf-provide header is generated by
 * mulle-match-to-c during a reflect.
 */
#include "_mulle-fprintf-provide.h"

/*
 * The versioncheck header can be generated with
 * mulle-project-dependency-versions, but it is optional.
 */
#ifdef __has_include
# if __has_include( "_mulle-fprintf-versioncheck.h")
#  include "_mulle-fprintf-versioncheck.h"
# endif
#endif

#endif
