/* #undef HAVE_GMTIME_R */
/* #undef HAVE_TIMEGM */
/* #undef HAVE_LOCALTIME_R */
/* #undef HAVE_REALPATH */
/* #undef HAVE__USLEEP */
/* #undef HAVE_FNMATCH */
/* #undef HAVE_FTRUNCATE */
#define HAVE_POSIX_CHDIR
#define HAVE_WINDOWS_CHDIR
#define HAVE_POSIX_GETCWD
#define HAVE_WINDOWS_GETCWD
/* #undef HAVE_TZNAME */
#define HAVE_ROUND
#define HAVE_VA_COPY
/* #undef HAVE_SIGBUS */
/* #undef HAVE_PTHREAD */
/* #undef HAVE_PID_T */
/* #undef HAVE_EXECINFO */
/* #undef HAVE_FORK */
#define HAVE_POSIX_MKDIR
#define HAVE_WINDOWS_MKDIR
/* #undef HAVE_GETPWUID */
/* #undef HAVE_FSYNC */
#define HAVE_CHMOD
/* #undef HAVE_MODE_T */
#define HAVE_CXX_SHARED_PTR
#define HAVE_POSIX_UNLINK
#define HAVE_WINDOWS_UNLINK
/* #undef HAVE_SIGHANDLER_T */

#define HAVE_POSIX_ACCESS
#define HAVE_WINDOWS__ACCESS
/* #undef HAVE_WINDOWS_GET_TEMP_PATH */
#define HAVE_WINDOWS_TZNAME

#ifdef HAVE_VA_COPY
#define UTIL_VA_COPY(target,src) va_copy(target,src)
#else
#define UTIL_VA_COPY(target,src) target = src
#endif

#ifdef HAVE_FORK
#ifdef HAVE_PTHREAD
#ifdef HAVE_EXECINFO
#ifdef HAVE_GETPWUID

#endif
#endif
#endif
#endif
