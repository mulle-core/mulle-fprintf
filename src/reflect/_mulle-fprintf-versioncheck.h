/*
 *   This file will be regenerated by `mulle-project-versioncheck`.
 *   Any edits will be lost.
 */
#ifndef mulle_fprintf_versioncheck_h__
#define mulle_fprintf_versioncheck_h__

#if defined( MULLE__SPRINTF_VERSION)
# ifndef MULLE__SPRINTF_VERSION_MIN
#  define MULLE__SPRINTF_VERSION_MIN  ((3UL << 20) | (1 << 8) | 1)
# endif
# ifndef MULLE__SPRINTF_VERSION_MAX
#  define MULLE__SPRINTF_VERSION_MAX  ((4UL << 20) | (0 << 8) | 0)
# endif
# if MULLE__SPRINTF_VERSION < MULLE__SPRINTF_VERSION_MIN
#  error "mulle-sprintf is too old"
# endif
# if MULLE__SPRINTF_VERSION >= MULLE__SPRINTF_VERSION_MAX
#  error "mulle-sprintf is too new"
# endif
#endif

#endif
