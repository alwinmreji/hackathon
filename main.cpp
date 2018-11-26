// iostream standard header for Microsoft
#pragma once
#ifndef _IOSTREAM_
#define _IOSTREAM_
#ifndef RC_INVOKED
#include <istream>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)
_STD_BEGIN

  #ifdef _M_CEE_PURE
__PURE_APPDOMAIN_GLOBAL extern istream cin, *_Ptr_cin;
__PURE_APPDOMAIN_GLOBAL extern ostream cout, *_Ptr_cout;
__PURE_APPDOMAIN_GLOBAL extern ostream cerr, *_Ptr_cerr;
__PURE_APPDOMAIN_GLOBAL extern ostream clog, *_Ptr_clog;

__PURE_APPDOMAIN_GLOBAL extern wistream wcin, *_Ptr_wcin;
__PURE_APPDOMAIN_GLOBAL extern wostream wcout, *_Ptr_wcout;
__PURE_APPDOMAIN_GLOBAL extern wostream wcerr, *_Ptr_wcerr;
__PURE_APPDOMAIN_GLOBAL extern wostream wclog, *_Ptr_wclog;

  #else /* _M_CEE_PURE */
		// OBJECTS
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 istream cin, *_Ptr_cin;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream cout, *_Ptr_cout;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream cerr, *_Ptr_cerr;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 ostream clog, *_Ptr_clog;

__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wistream wcin, *_Ptr_wcin;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream wcout, *_Ptr_wcout;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream wcerr, *_Ptr_wcerr;
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2 wostream wclog, *_Ptr_wclog;

		// CLASS _Winit
class _CRTIMP2_PURE _Winit {
public:
	__thiscall _Winit();
	__thiscall ~_Winit();
private:
	__PURE_APPDOMAIN_GLOBAL static int _Init_cnt;
	};
  #endif /* _M_CEE_PURE */

_STD_END
 #pragma warning(pop)
 #pragma pack(pop)

#endif /* RC_INVOKED */
#endif /* _IOSTREAM_ */

/*
 * Copyright (c) 1992-2009 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.20:0009 */
/***
*stdlib.h - declarations/definitions for commonly used library functions
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for commonly
*       used library functions which either don't fit somewhere else, or,
*       cannot be declared in the normal place for other reasons.
*       [ANSI]
*
*       [Public]
*
****/

#pragma once

#ifndef _INC_STDLIB
#define _INC_STDLIB

#include <crtdefs.h>
#include <limits.h>

/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)

#ifdef  __cplusplus
extern "C" {
#endif

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* Definition of the argument values for the exit() function */

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


#ifndef _ONEXIT_T_DEFINED

#if !defined (_M_CEE_PURE)
typedef int (__cdecl * _onexit_t)(void);
#else
typedef int (__clrcall * _onexit_t)(void);
typedef _onexit_t _onexit_m_t;
#endif

#if defined (_M_CEE_MIXED)
typedef int (__clrcall * _onexit_m_t)(void);
#endif

#if     !__STDC__
/* Non-ANSI name for compatibility */
#define onexit_t _onexit_t
#endif

#define _ONEXIT_T_DEFINED
#endif


/* Data structure definitions for div and ldiv runtimes. */

#ifndef _DIV_T_DEFINED

typedef struct _div_t {
        int quot;
        int rem;
} div_t;

typedef struct _ldiv_t {
        long quot;
        long rem;
} ldiv_t;

typedef struct _lldiv_t {
        long long quot;
        long long rem;
} lldiv_t;

#define _DIV_T_DEFINED
#endif

/*
 * structs used to fool the compiler into not generating floating point
 * instructions when copying and pushing [long] double values
 */

#ifndef _CRT_DOUBLE_DEC

#ifndef _LDSUPPORT

#pragma pack(4)
typedef struct {
    unsigned char ld[10];
} _LDOUBLE;
#pragma pack()

#define _PTR_LD(x) ((unsigned char  *)(&(x)->ld))

#else

/* push and pop long, which is #defined as __int64 by a spec2k test */
#pragma push_macro("long")
#undef long
typedef long double _LDOUBLE;
#pragma pop_macro("long")

#define _PTR_LD(x) ((unsigned char  *)(x))

#endif

typedef struct {
        double x;
} _CRT_DOUBLE;

typedef struct {
    float f;
} _CRT_FLOAT;

/* push and pop long, which is #defined as __int64 by a spec2k test */
#pragma push_macro("long")
#undef long

typedef struct {
        /*
         * Assume there is a long double type
         */
        long double x;
} _LONGDOUBLE;

#pragma pop_macro("long")

#pragma pack(4)
typedef struct {
    unsigned char ld12[12];
} _LDBL12;
#pragma pack()

#define _CRT_DOUBLE_DEC
#endif

/* Maximum value that can be returned by the rand function. */

#define RAND_MAX 0x7fff

/*
 * Maximum number of bytes in multi-byte character in the current locale
 * (also defined in ctype.h).
 */
#ifndef MB_CUR_MAX
#define MB_CUR_MAX ___mb_cur_max_func()
#if !defined(_M_CEE_PURE)
_CRTIMP extern int __mb_cur_max;
#else
_CRTIMP int* __cdecl __p___mb_cur_max(void);
#define __mb_cur_max (*__p___mb_cur_max())
#endif /* !defined(_M_CEE_PURE) */
_CRTIMP int __cdecl ___mb_cur_max_func(void);
_CRTIMP int __cdecl ___mb_cur_max_l_func(_locale_t);
#endif  /* MB_CUR_MAX */

/* Minimum and maximum macros */

#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

/*
 * Sizes for buffers used by the _makepath() and _splitpath() functions.
 * note that the sizes include space for 0-terminator
 */
#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */

/*
 * Argument values for _set_error_mode().
 */
#define _OUT_TO_DEFAULT 0
#define _OUT_TO_STDERR  1
#define _OUT_TO_MSGBOX  2
#define _REPORT_ERRMODE 3

/*
 * Argument values for _set_abort_behavior().
 */
#define _WRITE_ABORT_MSG    0x1 /* debug only, has no effect in release */
#define _CALL_REPORTFAULT   0x2

/*
 * Sizes for buffers used by the getenv/putenv family of functions.
 */
#define _MAX_ENV 32767

#if !defined(_M_CEE_PURE)
/* a purecall handler procedure. Never returns normally */
typedef void (__cdecl *_purecall_handler)(void);

/* establishes a purecall handler for the process */
_CRTIMP _purecall_handler __cdecl _set_purecall_handler(_In_opt_ _purecall_handler _Handler);
_CRTIMP _purecall_handler __cdecl _get_purecall_handler(void);
#endif

#if defined(__cplusplus)
extern "C++"
{
#if defined(_M_CEE_PURE)
    typedef void (__clrcall *_purecall_handler)(void);
    typedef _purecall_handler _purecall_handler_m;
    _MRTIMP _purecall_handler __cdecl _set_purecall_handler(_In_opt_ _purecall_handler _Handler);
#endif
}
#endif

#if !defined(_M_CEE_PURE)
/* a invalid_arg handler procedure. */
typedef void (__cdecl *_invalid_parameter_handler)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);

/* establishes a invalid_arg handler for the process */
_CRTIMP _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_In_opt_ _invalid_parameter_handler _Handler);
_CRTIMP _invalid_parameter_handler __cdecl _get_invalid_parameter_handler(void);
#endif

#if defined(__cplusplus)
extern "C++"
{
#if defined(_M_CEE_PURE)
    typedef void (__clrcall *_invalid_parameter_handler)(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);
    typedef _invalid_parameter_handler _invalid_parameter_handler_m;
    _MRTIMP _invalid_parameter_handler __cdecl _set_invalid_parameter_handler(_In_opt_ _invalid_parameter_handler _Handlerh);
#endif
}
#endif

/* External variable declarations */
#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED
_CRTIMP extern int * __cdecl _errno(void);
#define errno   (*_errno())

errno_t __cdecl _set_errno(_In_ int _Value);
errno_t __cdecl _get_errno(_Out_ int * _Value);
#endif

_CRTIMP unsigned long * __cdecl __doserrno(void);
#define _doserrno   (*__doserrno())

errno_t __cdecl _set_doserrno(_In_ unsigned long _Value);
errno_t __cdecl _get_doserrno(_Out_ unsigned long * _Value);

/* you can't modify this, but it is non-const for backcompat */
_CRTIMP _CRT_INSECURE_DEPRECATE(strerror) char ** __cdecl __sys_errlist(void);
#define _sys_errlist (__sys_errlist())

_CRTIMP _CRT_INSECURE_DEPRECATE(strerror) int * __cdecl __sys_nerr(void);
#define _sys_nerr (*__sys_nerr())

#if     defined(_DLL) && defined(_M_IX86)

_CRTIMP int *          __cdecl __p___argc(void);
_CRTIMP char ***       __cdecl __p___argv(void);
_CRTIMP wchar_t ***    __cdecl __p___wargv(void);
_CRTIMP char ***       __cdecl __p__environ(void);
_CRTIMP wchar_t ***    __cdecl __p__wenviron(void);
_CRTIMP char **        __cdecl __p__pgmptr(void);
_CRTIMP wchar_t **     __cdecl __p__wpgmptr(void);


#endif  /* _M_IX86 && _DLL */

#if !defined(_M_CEE_PURE)
_CRTIMP extern int __argc;          /* count of cmd line args */
_CRTIMP extern char ** __argv;      /* pointer to table of cmd line args */
_CRTIMP extern wchar_t ** __wargv;  /* pointer to table of wide cmd line args */
#else
_CRTIMP int* __cdecl __p___argc(void);
_CRTIMP char*** __cdecl __p___argv(void);
_CRTIMP wchar_t*** __cdecl __p___wargv(void);
#define __argv (*__p___argv())
#define __argc (*__p___argc())
#define __wargv (*__p___wargv())
#endif

#if !defined(_M_CEE_PURE)
#ifdef  _POSIX_
extern char ** environ;             /* pointer to environment table */
#else
_CRTIMP extern char ** _environ;    /* pointer to environment table */
_CRTIMP extern wchar_t ** _wenviron;    /* pointer to wide environment table */
#endif  /* _POSIX_ */

_CRT_INSECURE_DEPRECATE_GLOBALS(_get_pgmptr) _CRTIMP extern char * _pgmptr;      /* points to the module (EXE) name */
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_wpgmptr) _CRTIMP extern wchar_t * _wpgmptr;  /* points to the module (EXE) wide name */


#else

_CRTIMP char*** __cdecl __p__environ(void);
_CRTIMP wchar_t*** __cdecl __p__wenviron(void);
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_pgmptr) _CRTIMP char** __cdecl __p__pgmptr(void);
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_wpgmptr) _CRTIMP wchar_t** __cdecl __p__wpgmptr(void);

#define _environ   (*__p__environ())
#define _wenviron  (*__p__wenviron())
#define _pgmptr    (*__p__pgmptr())
#define _wpgmptr   (*__p__wpgmptr())

#endif /* !defined(_M_CEE_PURE) */

errno_t __cdecl _get_pgmptr(_Deref_out_z_ char ** _Value);
errno_t __cdecl _get_wpgmptr(_Deref_out_z_ wchar_t ** _Value);


#if !defined(_M_CEE_PURE)
_CRT_INSECURE_DEPRECATE_GLOBALS(_get_fmode) _CRTIMP extern int _fmode;          /* default file translation mode */
#else
_CRTIMP int* __cdecl __p__fmode(void);
#define _fmode (*__p__fmode())
#endif /* !defined(_M_CEE_PURE) */

_CRTIMP errno_t __cdecl _set_fmode(_In_ int _Mode);
_CRTIMP errno_t __cdecl _get_fmode(_Out_ int * _PMode);

/* _countof helper */
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
template <typename _CountofType, size_t _SizeOfArray>
char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
}
#endif
#endif

/* function prototypes */

#ifndef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED
_CRTIMP __declspec(noreturn) void __cdecl exit(_In_ int _Code);
_CRTIMP __declspec(noreturn) void __cdecl _exit(_In_ int _Code);
_CRTIMP void __cdecl abort(void);
#endif

_CRTIMP unsigned int __cdecl _set_abort_behavior(_In_ unsigned int _Flags, _In_ unsigned int _Mask);

#ifndef _CRT_ABS_DEFINED
#define _CRT_ABS_DEFINED
        int       __cdecl abs(_In_ int _X);
        long      __cdecl labs(_In_ long _X);
        long long __cdecl llabs(_In_ long long _X);
#endif

        __int64    __cdecl _abs64(__int64);
#if defined(_M_CEE)
#pragma warning (suppress: 4985)
        _Check_return_ int    __clrcall _atexit_m_appdomain(_In_opt_ void (__clrcall * _Func)(void));
#if defined(_M_CEE_MIXED)
#pragma warning (suppress: 4985)
        [System::Security::SecurityCritical] _Check_return_ int    __clrcall _atexit_m(_In_opt_ void (__clrcall * _Func)(void));
#else
#pragma warning (push)
#pragma warning (disable: 4985)
        [System::Security::SecurityCritical] _Check_return_ inline int __clrcall _atexit_m(_In_opt_ void (__clrcall *_Function)(void))
        {
            return _atexit_m_appdomain(_Function);
        }
#pragma warning (pop)
#endif
#endif
#if defined(_M_CEE_PURE)
        /* In pure mode, atexit is the same as atexit_m_appdomain */
extern "C++"
{
[System::Security::SecurityCritical]
inline  int    __clrcall atexit
(
    void (__clrcall *_Function)(void)
)
{
    return _atexit_m_appdomain(_Function);
}
}
#else
        int    __cdecl atexit(void (__cdecl *)(void));
#endif
#ifndef _CRT_ATOF_DEFINED
#define _CRT_ATOF_DEFINED
_Check_return_ _CRTIMP double  __cdecl atof(_In_z_ const char *_String);
_Check_return_ _CRTIMP double  __cdecl _atof_l(_In_z_ const char *_String, _In_opt_ _locale_t _Locale);
#endif
_Check_return_ _CRTIMP _CRT_JIT_INTRINSIC int    __cdecl atoi(_In_z_ const char *_Str);
_Check_return_ _CRTIMP int    __cdecl _atoi_l(_In_z_ const char *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long   __cdecl atol(_In_z_ const char *_Str);
_Check_return_ _CRTIMP long   __cdecl _atol_l(_In_z_ const char *_Str, _In_opt_ _locale_t _Locale);
#ifndef _CRT_ALGO_DEFINED
#define _CRT_ALGO_DEFINED
#if __STDC_WANT_SECURE_LIB__
_Check_return_ _CRTIMP void * __cdecl bsearch_s(_In_ const void * _Key, _In_bytecount_x_(_NumOfElements * _SizeOfElements) const void * _Base,
        _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
_Check_return_ _CRTIMP void * __cdecl bsearch(_In_ const void * _Key, _In_bytecount_x_(_NumOfElements * _SizeOfElements) const void * _Base,
        _In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(const void *, const void *));

#if __STDC_WANT_SECURE_LIB__
_CRTIMP void __cdecl qsort_s(_Inout_bytecap_x_(_NumOfElements* _SizeOfElements) void * _Base,
        _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void *_Context);
#endif
_CRTIMP void __cdecl qsort(_Inout_bytecap_x_(_NumOfElements * _SizeOfElements) void * _Base,
	_In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__cdecl * _PtFuncCompare)(const void *, const void *));
#endif
        _Check_return_ unsigned short __cdecl _byteswap_ushort(_In_ unsigned short _Short);
        _Check_return_ unsigned long  __cdecl _byteswap_ulong (_In_ unsigned long _Long);
        _Check_return_ unsigned __int64 __cdecl _byteswap_uint64(_In_ unsigned __int64 _Int64);
_Check_return_ _CRTIMP div_t  __cdecl div(_In_ int _Numerator, _In_ int _Denominator);
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_dupenv_s) char * __cdecl getenv(_In_z_ const char * _VarName);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP errno_t __cdecl getenv_s(_Out_ size_t * _ReturnSize, _Out_opt_z_cap_(_DstSize) char * _DstBuf, _In_ rsize_t _DstSize, _In_z_ const char * _VarName);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, getenv_s, _Out_ size_t *, _ReturnSize, char, _Dest, _In_z_ const char *, _VarName)
#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_dupenv_s")
#undef _dupenv_s
#endif

_Check_return_opt_ _CRTIMP errno_t __cdecl _dupenv_s(_Out_ _Deref_post_opt_z_cap_(*_PBufferSizeInBytes) char **_PBuffer, _Out_opt_ size_t * _PBufferSizeInBytes, _In_z_ const char * _VarName);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_dupenv_s")
#endif

_Check_return_opt_ _CRTIMP errno_t __cdecl _itoa_s(_In_ int _Value, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _itoa_s, _In_ int, _Value, char, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _itoa, _In_ int, _Value, _Pre_notnull_ _Post_z_, char, _Dest, _In_ int, _Radix)
_Check_return_opt_ _CRTIMP errno_t __cdecl _i64toa_s(_In_ __int64 _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_i64toa_s) char * __cdecl _i64toa(_In_ __int64 _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_Check_return_opt_ _CRTIMP errno_t __cdecl _ui64toa_s(_In_ unsigned __int64 _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_ui64toa_s) char * __cdecl _ui64toa(_In_ unsigned __int64 _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_Check_return_ _CRTIMP __int64 __cdecl _atoi64(_In_z_ const char * _String);
_Check_return_ _CRTIMP __int64 __cdecl _atoi64_l(_In_z_ const char * _String, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP __int64 __cdecl _strtoi64(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP __int64 __cdecl _strtoi64_l(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned __int64 __cdecl _strtoui64(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP unsigned __int64 __cdecl _strtoui64_l(_In_z_ const char * _String, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int  _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP ldiv_t __cdecl ldiv(_In_ long _Numerator, _In_ long _Denominator);
_Check_return_ _CRTIMP lldiv_t __cdecl lldiv(_In_ long long _Numerator, _In_ long long _Denominator);
#ifdef __cplusplus
extern "C++"
{
    inline long abs(long _X)
    {
        return labs(_X);
    }
    inline long long abs(long long _X)
    {
        return llabs(_X);
    }
    inline ldiv_t div(long _A1, long _A2)
    {
        return ldiv(_A1, _A2);
    }
    inline lldiv_t div(long long _A1, long long _A2)
    {
        return lldiv(_A1, _A2);
    }
}
#endif
_Check_return_opt_ _CRTIMP errno_t __cdecl _ltoa_s(_In_ long _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ltoa_s, _In_ long, _Value, char, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _ltoa, _In_ long, _Value, _Pre_notnull_ _Post_z_, char, _Dest, _In_ int, _Radix)
_Check_return_ _CRTIMP int    __cdecl mblen(_In_opt_bytecount_(_MaxCount) _Pre_opt_z_ const char * _Ch, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP int    __cdecl _mblen_l(_In_opt_bytecount_(_MaxCount) _Pre_opt_z_ const char * _Ch, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP size_t __cdecl _mbstrlen(_In_z_ const char * _Str);
_Check_return_ _CRTIMP size_t __cdecl _mbstrlen_l(_In_z_ const char *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP size_t __cdecl _mbstrnlen(_In_z_ const char *_Str, _In_ size_t _MaxCount);
_Check_return_ _CRTIMP size_t __cdecl _mbstrnlen_l(_In_z_ const char *_Str, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
_CRTIMP int    __cdecl mbtowc(_Pre_notnull_ _Post_z_ wchar_t * _DstCh, _In_opt_bytecount_(_SrcSizeInBytes) _Pre_opt_z_ const char * _SrcCh, _In_ size_t _SrcSizeInBytes);
_CRTIMP int    __cdecl _mbtowc_l(_Pre_notnull_ _Post_z_ wchar_t * _DstCh, _In_opt_bytecount_(_SrcSizeInBytes) _Pre_opt_z_ const char * _SrcCh, _In_ size_t _SrcSizeInBytes, _In_opt_ _locale_t _Locale);
_Check_return_opt_ _CRTIMP errno_t __cdecl mbstowcs_s(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_cap_post_count_(_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_count_(_MaxCount) _Pre_z_ const char * _SrcBuf, _In_ size_t _MaxCount );
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(errno_t, mbstowcs_s, _Out_opt_ size_t *, _PtNumOfCharConverted, _Deref_post_z_ wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_CRTIMP, mbstowcs, _Out_opt_z_cap_(_MaxCount), wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount)

_Check_return_opt_ _CRTIMP errno_t __cdecl _mbstowcs_s_l(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_cap_post_count_(_SizeInWords, *_PtNumOfCharConverted) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_count_(_MaxCount) _Pre_z_ const char * _SrcBuf, _In_ size_t _MaxCount, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(errno_t, _mbstowcs_s_l, _Out_opt_ size_t *, _PtNumOfCharConverted, wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_CRTIMP, _mbstowcs_l, _mbstowcs_s_l, _Out_opt_z_cap_(_Size) wchar_t, _Out_z_cap_(_MaxCount), wchar_t, _Dest, _In_z_ const char *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)

_Check_return_ _CRTIMP int    __cdecl rand(void);
#if defined(_CRT_RAND_S)
_CRTIMP errno_t __cdecl rand_s ( _Out_ unsigned int *_RandomValue);
#endif

_Check_return_opt_ _CRTIMP int    __cdecl _set_error_mode(_In_ int _Mode);

_CRTIMP void   __cdecl srand(_In_ unsigned int _Seed);
_Check_return_ _CRTIMP double __cdecl strtod(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr);
_Check_return_ _CRTIMP double __cdecl _strtod_l(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long   __cdecl strtol(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix );
_Check_return_ _CRTIMP long   __cdecl _strtol_l(_In_z_ const char *_Str, _Out_opt_ _Deref_post_z_ char **_EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned long __cdecl strtoul(_In_z_ const char * _Str, _Out_opt_ _Deref_post_z_ char ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP unsigned long __cdecl _strtoul_l(const char * _Str, _Out_opt_ _Deref_post_z_ char **_EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
#ifndef _CRT_SYSTEM_DEFINED
#define _CRT_SYSTEM_DEFINED
_CRTIMP int __cdecl system(_In_opt_z_ const char * _Command);
#endif
_Check_return_opt_ _CRTIMP errno_t __cdecl _ultoa_s(_In_ unsigned long _Val, _Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ultoa_s, _In_ unsigned long, _Value, char, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(char *, __RETURN_POLICY_DST, _CRTIMP, _ultoa, _In_ unsigned long, _Value, _Pre_notnull_ _Post_z_, char, _Dest, _In_ int, _Radix)
_CRTIMP _CRT_INSECURE_DEPRECATE(wctomb_s) int    __cdecl wctomb(_Out_opt_z_bytecap_c_(MB_LEN_MAX) char * _MbCh, _In_ wchar_t _WCh);
_CRTIMP _CRT_INSECURE_DEPRECATE(_wctomb_s_l) int    __cdecl _wctomb_l(_Pre_maybenull_ _Post_z_ char * _MbCh, _In_ wchar_t _WCh, _In_opt_ _locale_t _Locale);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl wctomb_s(_Out_opt_ int * _SizeConverted, _Out_opt_bytecap_post_bytecount_(_SizeInBytes, *_SizeConverted) char * _MbCh, _In_ rsize_t _SizeInBytes, _In_ wchar_t _WCh);
#endif
_Check_return_wat_ _CRTIMP errno_t __cdecl _wctomb_s_l(_Out_opt_ int * _SizeConverted, _Out_opt_z_bytecap_(_SizeInBytes) char * _MbCh, _In_ size_t _SizeInBytes, _In_ wchar_t _WCh, _In_opt_ _locale_t _Locale);
_Check_return_wat_ _CRTIMP errno_t __cdecl wcstombs_s(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_bytecap_post_bytecount_(_DstSizeInBytes, *_PtNumOfCharConverted) char * _Dst, _In_ size_t _DstSizeInBytes, _In_z_ const wchar_t * _Src, _In_ size_t _MaxCountInBytes);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(errno_t, wcstombs_s, _Out_opt_ size_t *, _PtNumOfCharConverted, _Out_opt_bytecap_(_Size) char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_CRTIMP, wcstombs, _Out_opt_z_cap_(_MaxCount), char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount)
_Check_return_wat_ _CRTIMP errno_t __cdecl _wcstombs_s_l(_Out_opt_ size_t * _PtNumOfCharConverted, _Out_opt_bytecap_post_bytecount_(_DstSizeInBytes, *_PtNumOfCharConverted) char * _Dst, _In_ size_t _DstSizeInBytes, _In_z_ const wchar_t * _Src, _In_ size_t _MaxCountInBytes, _In_opt_ _locale_t _Locale);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(errno_t, _wcstombs_s_l, _Out_opt_ size_t *,_PtNumOfCharConverted, _Out_opt_cap_(_Size) char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_CRTIMP, _wcstombs_l, _wcstombs_s_l, _Out_opt_z_cap_(_Size) char, _Out_z_cap_(_MaxCount), char, _Dest, _In_z_ const wchar_t *, _Source, _In_ size_t, _MaxCount, _In_opt_ _locale_t, _Locale)

#if defined(__cplusplus) && defined(_M_CEE)
/*
 * Managed search routines. Note __cplusplus, this is because we only support
 * managed C++.
 */
extern "C++"
{
#if __STDC_WANT_SECURE_LIB__
_Check_return_ void * __clrcall bsearch_s(_In_ const void * _Key, _In_bytecount_x_(_NumOfElements*_SizeOfElements) const void * _Base, _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElements,
        _In_ int (__clrcall * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
_Check_return_ void * __clrcall bsearch  (_In_ const void * _Key, _In_bytecount_x_(_NumOfElements*_SizeOfElements) const void * _Base, _In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__clrcall * _PtFuncCompare)(const void *, const void *));

#if __STDC_WANT_SECURE_LIB__
void __clrcall qsort_s(_Inout_bytecap_x_(_NumOfElements*_SizeOfElements) _Post_bytecount_x_(_NumOfElements*_SizeOfElements) void * _Base,
        _In_ rsize_t _NumOfElements, _In_ rsize_t _SizeOfElment,
        _In_ int (__clrcall * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
#endif
void __clrcall qsort(_Inout_bytecap_x_(_NumOfElements*_SizeOfElements) _Post_bytecount_x_(_NumOfElements*_SizeOfElements) void * _Base,
        _In_ size_t _NumOfElements, _In_ size_t _SizeOfElements,
        _In_ int (__clrcall * _PtFuncCompare)(const void *, const void *));

}
#endif

#ifndef _CRT_ALLOCATION_DEFINED
#define _CRT_ALLOCATION_DEFINED

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma push_macro("calloc")
#pragma push_macro("free")
#pragma push_macro("malloc")
#pragma push_macro("realloc")
#pragma push_macro("_recalloc")
#pragma push_macro("_aligned_free")
#pragma push_macro("_aligned_malloc")
#pragma push_macro("_aligned_offset_malloc")
#pragma push_macro("_aligned_realloc")
#pragma push_macro("_aligned_recalloc")
#pragma push_macro("_aligned_offset_realloc")
#pragma push_macro("_aligned_offset_recalloc")
#pragma push_macro("_aligned_msize")

#undef calloc
#undef free
#undef malloc
#undef realloc
#undef _recalloc
#undef _aligned_free
#undef _aligned_malloc
#undef _aligned_offset_malloc
#undef _aligned_realloc
#undef _aligned_recalloc
#undef _aligned_offset_realloc
#undef _aligned_offset_recalloc
#undef _aligned_msize

#endif
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRT_JIT_INTRINSIC _CRTNOALIAS _CRTRESTRICT    void * __cdecl calloc(_In_ size_t _Count, _In_ size_t _Size);
_CRTIMP                     _CRTNOALIAS                                                                             void   __cdecl free(_Post_ptr_invalid_ void * _Memory);
_Check_return_ _Ret_opt_bytecap_(_Size) _CRTIMP _CRT_JIT_INTRINSIC _CRTNOALIAS _CRTRESTRICT                              void * __cdecl malloc(_In_ size_t _Size);
_Success_(return!=0)
_Check_return_ _Ret_opt_bytecap_(_NewSize) _CRTIMP _CRTNOALIAS _CRTRESTRICT                           void * __cdecl realloc(_Post_ptr_invalid_ void * _Memory, _In_ size_t _NewSize);
_Success_(return!=0)
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                       void * __cdecl _recalloc(_Post_ptr_invalid_ void * _Memory, _In_ size_t _Count, _In_ size_t _Size);
_CRTIMP                     _CRTNOALIAS                                                                             void   __cdecl _aligned_free(_Post_ptr_invalid_ void * _Memory);
_Check_return_ _Ret_opt_bytecap_(_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_malloc(_In_ size_t _Size, _In_ size_t _Alignment);
_Check_return_ _Ret_opt_bytecap_(_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_offset_malloc(_In_ size_t _Size, _In_ size_t _Alignment, _In_ size_t _Offset);
_Success_(return!=0)
_Check_return_ _Ret_opt_bytecap_(_NewSize) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_realloc(_Post_ptr_invalid_ void * _Memory, _In_ size_t _NewSize, _In_ size_t _Alignment);
_Success_(return!=0)
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                       void * __cdecl _aligned_recalloc(_Post_ptr_invalid_ void * _Memory, _In_ size_t _Count, _In_ size_t _Size, _In_ size_t _Alignment);
_Success_(return!=0)
_Check_return_ _Ret_opt_bytecap_(_NewSize) _CRTIMP _CRTNOALIAS _CRTRESTRICT                              void * __cdecl _aligned_offset_realloc(_Post_ptr_invalid_ void * _Memory, _In_ size_t _NewSize, _In_ size_t _Alignment, _In_ size_t _Offset);
_Success_(return!=0)
_Check_return_ _Ret_opt_bytecap_x_(_Count*_Size) _CRTIMP _CRTNOALIAS _CRTRESTRICT                       void * __cdecl _aligned_offset_recalloc(_Post_ptr_invalid_ void * _Memory, _In_ size_t _Count, _In_ size_t _Size, _In_ size_t _Alignment, _In_ size_t _Offset);
_Check_return_ _CRTIMP                                                  size_t __cdecl _aligned_msize(_Pre_notnull_ void * _Memory, _In_ size_t _Alignment, _In_ size_t _Offset);


#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma pop_macro("_aligned_msize")
#pragma pop_macro("_aligned_offset_recalloc")
#pragma pop_macro("_aligned_offset_realloc")
#pragma pop_macro("_aligned_recalloc")
#pragma pop_macro("_aligned_realloc")
#pragma pop_macro("_aligned_offset_malloc")
#pragma pop_macro("_aligned_malloc")
#pragma pop_macro("_aligned_free")
#pragma pop_macro("_recalloc")
#pragma pop_macro("realloc")
#pragma pop_macro("malloc")
#pragma pop_macro("free")
#pragma pop_macro("calloc")

#endif

#endif /*_CRT_ALLOCATION_DEFINED */

#ifndef _WSTDLIB_DEFINED

/* wide function prototypes, also declared in wchar.h  */

_Check_return_wat_ _CRTIMP errno_t __cdecl _itow_s (_In_ int _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _itow_s, _In_ int, _Value, wchar_t, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _itow, _In_ int, _Value, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_ int, _Radix)
_Check_return_wat_ _CRTIMP errno_t __cdecl _ltow_s (_In_ long _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ltow_s, _In_ long, _Value, wchar_t, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _ltow, _In_ long, _Value, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_ int, _Radix)
_Check_return_wat_ _CRTIMP errno_t __cdecl _ultow_s (_In_ unsigned long _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _ultow_s, _In_ unsigned long, _Value, wchar_t, _Dest, _In_ int, _Radix)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _ultow, _In_ unsigned long, _Value, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_ int, _Radix)
_Check_return_ _CRTIMP double __cdecl wcstod(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr);
_Check_return_ _CRTIMP double __cdecl _wcstod_l(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long   __cdecl wcstol(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, int _Radix);
_Check_return_ _CRTIMP long   __cdecl _wcstol_l(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t **_EndPtr, int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned long __cdecl wcstoul(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, int _Radix);
_Check_return_ _CRTIMP unsigned long __cdecl _wcstoul_l(_In_z_ const wchar_t *_Str, _Out_opt_ _Deref_post_z_ wchar_t **_EndPtr, int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_wdupenv_s) wchar_t * __cdecl _wgetenv(_In_z_ const wchar_t * _VarName);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wgetenv_s(_Out_ size_t * _ReturnSize, _Out_opt_z_cap_(_DstSizeInWords) wchar_t * _DstBuf, _In_ size_t _DstSizeInWords, _In_z_ const wchar_t * _VarName);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(errno_t, _wgetenv_s, _Out_ size_t *, _ReturnSize, wchar_t, _Dest, _In_z_ const wchar_t *, _VarName)

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wdupenv_s")
#undef _wdupenv_s
#endif

_Check_return_wat_ _CRTIMP errno_t __cdecl _wdupenv_s(_Out_ _Deref_post_opt_z_cap_(*_BufferSizeInWords) wchar_t **_Buffer, _Out_opt_ size_t *_BufferSizeInWords, _In_z_ const wchar_t *_VarName);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wdupenv_s")
#endif

#ifndef _CRT_WSYSTEM_DEFINED
#define _CRT_WSYSTEM_DEFINED
_CRTIMP int __cdecl _wsystem(_In_opt_z_ const wchar_t * _Command);
#endif
_Check_return_ _CRTIMP double __cdecl _wtof(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP double __cdecl _wtof_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _wtoi(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP int __cdecl _wtoi_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP long __cdecl _wtol(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP long __cdecl _wtol_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);

_Check_return_wat_ _CRTIMP errno_t __cdecl _i64tow_s(_In_ __int64 _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_i64tow_s) wchar_t * __cdecl _i64tow(_In_ __int64 _Val, _Pre_notnull_ _Post_z_ wchar_t * _DstBuf, _In_ int _Radix);
_Check_return_wat_ _CRTIMP errno_t __cdecl _ui64tow_s(_In_ unsigned __int64 _Val, _Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ int _Radix);
_CRTIMP _CRT_INSECURE_DEPRECATE(_ui64tow_s) wchar_t * __cdecl _ui64tow(_In_ unsigned __int64 _Val, _Pre_notnull_ _Post_z_ wchar_t * _DstBuf, _In_ int _Radix);
_Check_return_ _CRTIMP __int64   __cdecl _wtoi64(_In_z_ const wchar_t *_Str);
_Check_return_ _CRTIMP __int64   __cdecl _wtoi64_l(_In_z_ const wchar_t *_Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP __int64   __cdecl _wcstoi64(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP __int64   __cdecl _wcstoi64_l(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP unsigned __int64  __cdecl _wcstoui64(_In_z_ const wchar_t * _Str, _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix);
_Check_return_ _CRTIMP unsigned __int64  __cdecl _wcstoui64_l(_In_z_ const wchar_t *_Str , _Out_opt_ _Deref_post_z_ wchar_t ** _EndPtr, _In_ int _Radix, _In_opt_ _locale_t _Locale);

#define _WSTDLIB_DEFINED
#endif


#ifndef _POSIX_

/*
Buffer size required to be passed to _gcvt, fcvt and other fp conversion routines
*/
#define _CVTBUFSIZE (309+40) /* # of digits in max. dp value + slop */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma push_macro("_fullpath")
#undef _fullpath

#endif

_Check_return_ _CRTIMP char * __cdecl _fullpath(_Out_opt_z_cap_(_SizeInBytes) char * _FullPath, _In_z_ const char * _Path, _In_ size_t _SizeInBytes);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)

#pragma pop_macro("_fullpath")

#endif

_Check_return_wat_ _CRTIMP errno_t __cdecl _ecvt_s(_Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ double _Val, _In_ int _NumOfDights, _Out_ int * _PtDec, _Out_ int * _PtSign);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _ecvt_s, char, _Dest, _In_ double, _Value, _In_ int, _NumOfDigits, _Out_ int *, _PtDec, _Out_ int *, _PtSign)
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_ecvt_s) char * __cdecl _ecvt(_In_ double _Val, _In_ int _NumOfDigits, _Out_ int * _PtDec, _Out_ int * _PtSign);
_Check_return_wat_ _CRTIMP errno_t __cdecl _fcvt_s(_Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ double _Val, _In_ int _NumOfDec, _Out_ int * _PtDec, _Out_ int * _PtSign);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _fcvt_s, char, _Dest, _In_ double, _Value, _In_ int, _NumOfDigits, _Out_ int *, _PtDec, _Out_ int *, _PtSign)
_Check_return_ _CRTIMP _CRT_INSECURE_DEPRECATE(_fcvt_s) char * __cdecl _fcvt(_In_ double _Val, _In_ int _NumOfDec, _Out_ int * _PtDec, _Out_ int * _PtSign);
_CRTIMP errno_t __cdecl _gcvt_s(_Out_z_cap_(_Size) char * _DstBuf, _In_ size_t _Size, _In_ double _Val, _In_ int _NumOfDigits);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(errno_t, _gcvt_s, char, _Dest, _In_ double, _Value, _In_ int, _NumOfDigits)
_CRTIMP _CRT_INSECURE_DEPRECATE(_gcvt_s) char * __cdecl _gcvt(_In_ double _Val, _In_ int _NumOfDigits, _Pre_notnull_ _Post_z_ char * _DstBuf);

_Check_return_ _CRTIMP int __cdecl _atodbl(_Out_ _CRT_DOUBLE * _Result, _In_z_ char * _Str);
_Check_return_ _CRTIMP int __cdecl _atoldbl(_Out_ _LDOUBLE * _Result, _In_z_ char * _Str);
_Check_return_ _CRTIMP int __cdecl _atoflt(_Out_ _CRT_FLOAT * _Result, _In_z_ char * _Str);
_Check_return_ _CRTIMP int __cdecl _atodbl_l(_Out_ _CRT_DOUBLE * _Result, _In_z_ char * _Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _atoldbl_l(_Out_ _LDOUBLE * _Result, _In_z_ char * _Str, _In_opt_ _locale_t _Locale);
_Check_return_ _CRTIMP int __cdecl _atoflt_l(_Out_ _CRT_FLOAT * _Result, _In_z_ char * _Str, _In_opt_ _locale_t _Locale);
        _Check_return_ unsigned long __cdecl _lrotl(_In_ unsigned long _Val, _In_ int _Shift);
        _Check_return_ unsigned long __cdecl _lrotr(_In_ unsigned long _Val, _In_ int _Shift);
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t   __cdecl _makepath_s(_Out_z_cap_(_SizeInWords) char * _PathResult, _In_ size_t _SizeInWords, _In_opt_z_ const char * _Drive, _In_opt_z_ const char * _Dir, _In_opt_z_ const char * _Filename,
        _In_opt_z_ const char * _Ext);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _makepath_s, char, _Path, _In_opt_z_ const char *, _Drive, _In_opt_z_ const char *, _Dir, _In_opt_z_ const char *, _Filename, _In_opt_z_ const char *, _Ext)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(void, __RETURN_POLICY_VOID, _CRTIMP, _makepath, _Pre_notnull_ _Post_z_, char, _Path, _In_opt_z_ const char *, _Drive, _In_opt_z_ const char *, _Dir, _In_opt_z_ const char *, _Filename, _In_opt_z_ const char *, _Ext)

#if defined(_M_CEE)
		_onexit_m_t    __clrcall _onexit_m_appdomain(_onexit_m_t _Function);
	#if defined(_M_CEE_MIXED)
		_onexit_m_t    __clrcall _onexit_m(_onexit_m_t _Function);
	#else
		inline _onexit_m_t    __clrcall _onexit_m(_onexit_t _Function)
		{
			return _onexit_m_appdomain(_Function);
		}
	#endif

#endif
#if defined(_M_CEE_PURE)
        /* In pure mode, _onexit is the same as _onexit_m_appdomain */
extern "C++"
{
inline  _onexit_t    __clrcall _onexit
(
    _onexit_t _Function
)
{
    return _onexit_m_appdomain(_Function);
}
}
#else
        _onexit_t __cdecl _onexit(_In_opt_ _onexit_t _Func);
#endif

#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED
_CRTIMP void __cdecl perror(_In_opt_z_ const char * _ErrMsg);
#endif

#pragma warning (push)
#pragma warning (disable:6540) // the functions below have declspecs in their declarations in the windows headers, causing PREfast to fire 6540 here
_Check_return_ _CRTIMP int    __cdecl _putenv(_In_z_ const char * _EnvString);
_Check_return_wat_ _CRTIMP errno_t __cdecl _putenv_s(_In_z_ const char * _Name, _In_z_ const char * _Value);
        _Check_return_ unsigned int __cdecl _rotl(_In_ unsigned int _Val, _In_ int _Shift);
        _Check_return_ unsigned __int64 __cdecl _rotl64(_In_ unsigned __int64 _Val, _In_ int _Shift);
        _Check_return_ unsigned int __cdecl _rotr(_In_ unsigned int _Val, _In_ int _Shift);
        _Check_return_ unsigned __int64 __cdecl _rotr64(_In_ unsigned __int64 _Val, _In_ int _Shift);
#pragma warning (pop)

_CRTIMP errno_t __cdecl _searchenv_s(_In_z_ const char * _Filename, _In_z_ const char * _EnvVar, _Out_z_cap_(_SizeInBytes) char * _ResultPath, _In_ size_t _SizeInBytes);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(errno_t, _searchenv_s, _In_z_ const char *, _Filename, _In_z_ const char *, _EnvVar, char, _ResultPath)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(void, __RETURN_POLICY_VOID, _CRTIMP, _searchenv, _In_z_ const char *, _Filename, _In_z_ const char *, _EnvVar, _Pre_notnull_ _Post_z_, char, _ResultPath)

_CRT_INSECURE_DEPRECATE(_splitpath_s) _CRTIMP void   __cdecl _splitpath(_In_z_ const char * _FullPath, _Pre_maybenull_ _Post_z_ char * _Drive, _Pre_maybenull_ _Post_z_ char * _Dir, _Pre_maybenull_ _Post_z_ char * _Filename, _Pre_maybenull_ _Post_z_ char * _Ext);
_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t  __cdecl _splitpath_s(_In_z_ const char * _FullPath,
		_Out_opt_z_cap_(_DriveSize) char * _Drive, _In_ size_t _DriveSize,
		_Out_opt_z_cap_(_DirSize) char * _Dir, _In_ size_t _DirSize,
		_Out_opt_z_cap_(_FilenameSize) char * _Filename, _In_ size_t _FilenameSize,
		_Out_opt_z_cap_(_ExtSize) char * _Ext, _In_ size_t _ExtSize);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(errno_t, _splitpath_s,  char, _Dest)

_CRTIMP void   __cdecl _swab(_Inout_cap_(_SizeInBytes) _Post_count_(_SizeInBytes) char * _Buf1, _Inout_cap_(_SizeInBytes) _Post_count_(_SizeInBytes) char * _Buf2, int _SizeInBytes);

#ifndef _WSTDLIBP_DEFINED

/* wide function prototypes, also declared in wchar.h  */

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wfullpath")
#undef _wfullpath
#endif

_Check_return_ _CRTIMP wchar_t * __cdecl _wfullpath(_Out_opt_z_cap_(_SizeInWords) wchar_t * _FullPath, _In_z_ const wchar_t * _Path, _In_ size_t _SizeInWords);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wfullpath")
#endif

_Check_return_wat_ _CRTIMP_ALTERNATIVE errno_t __cdecl _wmakepath_s(_Out_z_cap_(_SIZE) wchar_t * _PathResult, _In_ size_t _SIZE, _In_opt_z_ const wchar_t * _Drive, _In_opt_z_ const wchar_t * _Dir, _In_opt_z_ const wchar_t * _Filename,
        _In_opt_z_ const wchar_t * _Ext);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(errno_t, _wmakepath_s, wchar_t, _ResultPath, _In_opt_z_ const wchar_t *, _Drive, _In_opt_z_ const wchar_t *, _Dir, _In_opt_z_ const wchar_t *, _Filename, _In_opt_z_ const wchar_t *, _Ext)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(void, __RETURN_POLICY_VOID, _CRTIMP, _wmakepath, _Pre_notnull_ _Post_z_, wchar_t, _ResultPath, _In_opt_z_ const wchar_t *, _Drive, _In_opt_z_ const wchar_t *, _Dir, _In_opt_z_ const wchar_t *, _Filename, _In_opt_z_ const wchar_t *, _Ext)
#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
_CRTIMP void __cdecl _wperror(_In_opt_z_ const wchar_t * _ErrMsg);
#endif
_Check_return_ _CRTIMP int    __cdecl _wputenv(_In_z_ const wchar_t * _EnvString);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wputenv_s(_In_z_ const wchar_t * _Name, _In_z_ const wchar_t * _Value);
_CRTIMP errno_t __cdecl _wsearchenv_s(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _EnvVar, _Out_z_cap_(_SizeInWords) wchar_t * _ResultPath, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(errno_t, _wsearchenv_s, _In_z_ const wchar_t *, _Filename, _In_z_ const wchar_t *, _EnvVar, wchar_t, _ResultPath)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(void, __RETURN_POLICY_VOID, _CRTIMP, _wsearchenv, _In_z_ const wchar_t *, _Filename, _In_z_ const wchar_t *, _EnvVar, _Pre_notnull_ _Post_z_, wchar_t, _ResultPath)
_CRT_INSECURE_DEPRECATE(_wsplitpath_s) _CRTIMP void   __cdecl _wsplitpath(_In_z_ const wchar_t * _FullPath, _Pre_maybenull_ _Post_z_ wchar_t * _Drive, _Pre_maybenull_ _Post_z_ wchar_t * _Dir, _Pre_maybenull_ _Post_z_ wchar_t * _Filename, _Pre_maybenull_ _Post_z_ wchar_t * _Ext);
_CRTIMP_ALTERNATIVE errno_t __cdecl _wsplitpath_s(_In_z_ const wchar_t * _FullPath,
		_Out_opt_z_cap_(_DriveSize) wchar_t * _Drive, _In_ size_t _DriveSize,
		_Out_opt_z_cap_(_DirSize) wchar_t * _Dir, _In_ size_t _DirSize,
		_Out_opt_z_cap_(_FilenameSize) wchar_t * _Filename, _In_ size_t _FilenameSize,
		_Out_opt_z_cap_(_ExtSize) wchar_t * _Ext, _In_ size_t _ExtSize);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(errno_t, _wsplitpath_s, wchar_t, _Path)

#define _WSTDLIBP_DEFINED
#endif

/* The Win32 API SetErrorMode, Beep and Sleep should be used instead. */
_CRT_OBSOLETE(SetErrorMode) _CRTIMP void __cdecl _seterrormode(_In_ int _Mode);
_CRT_OBSOLETE(Beep) _CRTIMP void __cdecl _beep(_In_ unsigned _Frequency, _In_ unsigned _Duration);
_CRT_OBSOLETE(Sleep) _CRTIMP void __cdecl _sleep(_In_ unsigned long _Duration);

#endif  /* _POSIX_ */

#if     !__STDC__

#ifndef _POSIX_

/* Non-ANSI names for compatibility */

#ifndef __cplusplus
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#define sys_errlist _sys_errlist
#define sys_nerr    _sys_nerr
#define environ     _environ

#pragma warning(push)
#pragma warning(disable: 4141) /* Using deprecated twice */
_Check_return_ _CRT_NONSTDC_DEPRECATE(_ecvt) _CRT_INSECURE_DEPRECATE(_ecvt_s) _CRTIMP char * __cdecl ecvt(_In_ double _Val, _In_ int _NumOfDigits, _Out_ int * _PtDec, _Out_ int * _PtSign);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_fcvt) _CRT_INSECURE_DEPRECATE(_fcvt_s) _CRTIMP char * __cdecl fcvt(_In_ double _Val, _In_ int _NumOfDec, _Out_ int * _PtDec, _Out_ int * _PtSign);
_CRT_NONSTDC_DEPRECATE(_gcvt) _CRT_INSECURE_DEPRECATE(_fcvt_s)		_CRTIMP char * __cdecl gcvt(_In_ double _Val, _In_ int _NumOfDigits, _Pre_notnull_ _Post_z_ char * _DstBuf);
_CRT_NONSTDC_DEPRECATE(_itoa) _CRT_INSECURE_DEPRECATE(_itoa_s)		_CRTIMP char * __cdecl itoa(_In_ int _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_CRT_NONSTDC_DEPRECATE(_ltoa) _CRT_INSECURE_DEPRECATE(_ltoa_s)		_CRTIMP char * __cdecl ltoa(_In_ long _Val, _Pre_notnull_ _Post_z_ char * _DstBuf, _In_ int _Radix);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_putenv) _CRTIMP int    __cdecl putenv(_In_z_ const char * _EnvString);
_CRT_NONSTDC_DEPRECATE(_swab)										_CRTIMP void   __cdecl swab(_Inout_z_bytecap_(_SizeInBytes) char * _Buf1,_Inout_z_bytecap_(_SizeInBytes) char * _Buf2, _In_ int _SizeInBytes);
_CRT_NONSTDC_DEPRECATE(_ultoa) _CRT_INSECURE_DEPRECATE(_ultoa_s)	_CRTIMP char * __cdecl ultoa(_In_ unsigned long _Val, _Pre_notnull_ _Post_z_ char * _Dstbuf, _In_ int _Radix);
#pragma warning(pop)
onexit_t __cdecl onexit(_In_opt_ onexit_t _Func);

#endif  /* _POSIX_ */

#endif  /* __STDC__ */

#ifdef  __cplusplus
}

#endif

#pragma pack(pop)

#endif  /* _INC_STDLIB */

// ctime standard header
#pragma once
#ifndef _CTIME_
#define _CTIME_
#include <yvals.h>

#ifdef _STD_USING
 #undef _STD_USING
  #include <time.h>
 #define _STD_USING

#else /* _STD_USING */
 #include <time.h>
#endif /* _STD_USING */

 #if _GLOBAL_USING && !defined(RC_INVOKED)
_STD_BEGIN
using _CSTD clock_t; using _CSTD size_t;
using _CSTD time_t; using _CSTD tm;
using _CSTD asctime; using _CSTD clock; using _CSTD ctime;
using _CSTD difftime; using _CSTD gmtime; using _CSTD localtime;
using _CSTD mktime; using _CSTD strftime; using _CSTD time;
_STD_END
 #endif /* _GLOBAL_USING */

#endif /* _CTIME_ */

/*
 * Copyright (c) 1992-2009 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.20:0009 */
/***
*stdio.h - definitions/declarations for standard I/O routines
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines the structures, values, macros, and functions
*       used by the level 2 I/O ("standard I/O") routines.
*       [ANSI/System V]
*
*       [Public]
*
****/

#pragma once

#ifndef _INC_STDIO
#define _INC_STDIO

#include <crtdefs.h>

/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,_CRT_PACKING)

#ifdef  __cplusplus
extern "C" {
#endif


/* Buffered I/O macros */

#define BUFSIZ  512


/*
 * Default number of supported streams. _NFILE is confusing and obsolete, but
 * supported anyway for backwards compatibility.
 */
#define _NFILE      _NSTREAM_

#define _NSTREAM_   512

/*
 * Number of entries in _iob[] (declared below). Note that _NSTREAM_ must be
 * greater than or equal to _IOB_ENTRIES.
 */
#define _IOB_ENTRIES 20

#define EOF     (-1)


#ifndef _FILE_DEFINED
struct _iobuf {
        char *_ptr;
        int   _cnt;
        char *_base;
        int   _flag;
        int   _file;
        int   _charbuf;
        int   _bufsiz;
        char *_tmpfname;
        };
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif


/* Directory where temporary files may be created. */

#ifdef  _POSIX_
#define _P_tmpdir   "/"
#define _wP_tmpdir  L"/"
#else
#define _P_tmpdir   "\\"
#define _wP_tmpdir  L"\\"
#endif

/* L_tmpnam = length of string _P_tmpdir
 *            + 1 if _P_tmpdir does not end in "/" or "\", else 0
 *            + 12 (for the filename string)
 *            + 1 (for the null terminator)
 * L_tmpnam_s = length of string _P_tmpdir
 *            + 1 if _P_tmpdir does not end in "/" or "\", else 0
 *            + 16 (for the filename string)
 *            + 1 (for the null terminator)
 */
#define L_tmpnam   (sizeof(_P_tmpdir) + 12)
#if __STDC_WANT_SECURE_LIB__
#define L_tmpnam_s (sizeof(_P_tmpdir) + 16)
#endif

#ifdef  _POSIX_
#define L_ctermid   9
#define L_cuserid   32
#endif


/* Seek method constants */

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0


#define FILENAME_MAX    260
#define FOPEN_MAX       20
#define _SYS_OPEN       20
#define TMP_MAX         32767  /* SHRT_MAX */
#if __STDC_WANT_SECURE_LIB__
#define TMP_MAX_S       _TMP_MAX_S
#define _TMP_MAX_S      2147483647 /* INT_MAX */
#endif

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* Declare _iob[] array */

#ifndef _STDIO_DEFINED
_CRTIMP FILE * __cdecl __iob_func(void);
#endif  /* _STDIO_DEFINED */


/* Define file position type */

#ifndef _FPOS_T_DEFINED
#undef _FPOSOFF

#if     defined (_POSIX_)
typedef long fpos_t;
#define _FPOSOFF(fp) ((long)(fp))
#else   /* _POSIX_ */

#if     !__STDC__
/* At this point we could switch both to long long, but we won't do that till next version to avoid any potential compat issues */
typedef __int64 fpos_t;
#define _FPOSOFF(fp) ((long)(fp))
#else
typedef long long fpos_t;
#define _FPOSOFF(fp) ((long)(fp))
#endif
#endif  /* _POSIX_ */

#define _FPOS_T_DEFINED
#endif

#ifndef _STDSTREAM_DEFINED
#define stdin  (&__iob_func()[0])
#define stdout (&__iob_func()[1])
#define stderr (&__iob_func()[2])
#define _STDSTREAM_DEFINED
#endif

#define _IOREAD         0x0001
#define _IOWRT          0x0002

#define _IOFBF          0x0000
#define _IOLBF          0x0040
#define _IONBF          0x0004

#define _IOMYBUF        0x0008
#define _IOEOF          0x0010
#define _IOERR          0x0020
#define _IOSTRG         0x0040
#define _IORW           0x0080
#ifdef  _POSIX_
#define _IOAPPEND       0x0200
#endif

/* constants used by _set_output_format */
#define _TWO_DIGIT_EXPONENT 0x1

/* Function prototypes */

#ifndef _STDIO_DEFINED

_Check_return_ _CRTIMP int __cdecl _filbuf(_Inout_ FILE * _File );
_Check_return_opt_ _CRTIMP int __cdecl _flsbuf(_In_ int _Ch, _Inout_ FILE * _File);

#ifdef  _POSIX_
_Check_return_ _CRTIMP FILE * __cdecl _fsopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode);
#else
_Check_return_ _CRTIMP FILE * __cdecl _fsopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode, _In_ int _ShFlag);
#endif

_CRTIMP void __cdecl clearerr(_Inout_ FILE * _File);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl clearerr_s(_Inout_ FILE * _File );
#endif
_Check_return_opt_ _CRTIMP int __cdecl fclose(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fcloseall(void);

#ifdef  _POSIX_
_Check_return_ _CRTIMP FILE * __cdecl fdopen( _In_ int _FileHandle, _In_z_ const char * _Mode);
#else
_Check_return_ _CRTIMP FILE * __cdecl _fdopen(_In_ int _FileHandle, _In_z_ const char * _Mode);
#endif

_Check_return_ _CRTIMP int __cdecl feof(_In_ FILE * _File);
_Check_return_ _CRTIMP int __cdecl ferror(_In_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl fflush(_Inout_opt_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl fgetc(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fgetchar(void);
_Check_return_opt_ _CRTIMP int __cdecl fgetpos(_Inout_ FILE * _File , _Out_ fpos_t * _Pos);
_Check_return_opt_ _CRTIMP char * __cdecl fgets(_Out_z_cap_(_MaxCount) char * _Buf, _In_ int _MaxCount, _Inout_ FILE * _File);

#ifdef  _POSIX_
_Check_return_ _CRTIMP int __cdecl fileno(_In_ FILE * _File);
#else
_Check_return_ _CRTIMP int __cdecl _fileno(_In_ FILE * _File);
#endif

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_tempnam")
#undef _tempnam
#endif

_Check_return_ _CRTIMP char * __cdecl _tempnam(_In_opt_z_ const char * _DirName, _In_opt_z_ const char * _FilePrefix);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_tempnam")
#endif

_Check_return_opt_ _CRTIMP int __cdecl _flushall(void);
_Check_return_ _CRT_INSECURE_DEPRECATE(fopen_s) _CRTIMP FILE * __cdecl fopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl fopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode);
#endif
_Check_return_opt_ _CRTIMP int __cdecl fprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl fputc(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fputchar(_In_ int _Ch);
_Check_return_opt_ _CRTIMP int __cdecl fputs(_In_z_ const char * _Str, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl fread(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP size_t __cdecl fread_s(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _DstSize, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
#endif
_Check_return_ _CRT_INSECURE_DEPRECATE(freopen_s) _CRTIMP FILE * __cdecl freopen(_In_z_ const char * _Filename, _In_z_ const char * _Mode, _Inout_ FILE * _File);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl freopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const char * _Filename, _In_z_ const char * _Mode, _Inout_ FILE * _OldFile);
#endif
_Check_return_ _CRT_INSECURE_DEPRECATE(fscanf_s) _CRTIMP int __cdecl fscanf(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_fscanf_s_l) _CRTIMP int __cdecl _fscanf_l(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fscanf_s(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl _fscanf_s_l(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(pop)
_Check_return_opt_ _CRTIMP int __cdecl fsetpos(_Inout_ FILE * _File, _In_ const fpos_t * _Pos);
_Check_return_opt_ _CRTIMP int __cdecl fseek(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP long __cdecl ftell(_Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP int __cdecl _fseeki64(_Inout_ FILE * _File, _In_ __int64 _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP __int64 __cdecl _ftelli64(_Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP size_t __cdecl fwrite(_In_count_x_(_Size*_Count) const void * _Str, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_ _CRTIMP int __cdecl getc(_Inout_ FILE * _File);
_Check_return_ _CRTIMP int __cdecl getchar(void);
_Check_return_ _CRTIMP int __cdecl _getmaxstdio(void);
#if __STDC_WANT_SECURE_LIB__
_CRTIMP char * __cdecl gets_s(_Out_z_cap_(_Size) char * _Buf, _In_ rsize_t _Size);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(char *, gets_s, char, _Buffer)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(char *, __RETURN_POLICY_SAME, _CRTIMP, gets, _Pre_notnull_ _Post_z_ _Out_z_cap_c_(((size_t)-1)), char, _Buffer)
_Check_return_ int __cdecl _getw(_Inout_ FILE * _File);
#ifndef _CRT_PERROR_DEFINED
#define _CRT_PERROR_DEFINED
_CRTIMP void __cdecl perror(_In_opt_z_ const char * _ErrMsg);
#endif
_Check_return_opt_ _CRTIMP int __cdecl _pclose(_Inout_ FILE * _File);
_Check_return_ _CRTIMP FILE * __cdecl _popen(_In_z_ const char * _Command, _In_z_ const char * _Mode);
_Check_return_opt_ _CRTIMP int __cdecl printf(_In_z_ _Printf_format_string_ const char * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl printf_s(_In_z_ _Printf_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl putc(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl putchar(_In_ int _Ch);
_Check_return_opt_ _CRTIMP int __cdecl puts(_In_z_ const char * _Str);
_Check_return_opt_ _CRTIMP int __cdecl _putw(_In_ int _Word, _Inout_ FILE * _File);
#ifndef _CRT_DIRECTORY_DEFINED
#define _CRT_DIRECTORY_DEFINED
_CRTIMP int __cdecl remove(_In_z_ const char * _Filename);
_Check_return_ _CRTIMP int __cdecl rename(_In_z_ const char * _OldFilename, _In_z_ const char * _NewFilename);
_CRTIMP int __cdecl _unlink(_In_z_ const char * _Filename);
#if !__STDC__
_CRT_NONSTDC_DEPRECATE(_unlink) _CRTIMP int __cdecl unlink(_In_z_ const char * _Filename);
#endif
#endif
_CRTIMP void __cdecl rewind(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _rmtmp(void);
_Check_return_ _CRT_INSECURE_DEPRECATE(scanf_s) _CRTIMP int __cdecl scanf(_In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_scanf_s_l) _CRTIMP int __cdecl _scanf_l(_In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl scanf_s(_In_z_ _Scanf_s_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _scanf_s_l(_In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(pop)
_CRT_INSECURE_DEPRECATE(setvbuf) _CRTIMP void __cdecl setbuf(_Inout_ FILE * _File, _Inout_opt_cap_c_(BUFSIZ) _Post_count_c_(0) char * _Buffer);
_Check_return_opt_ _CRTIMP int __cdecl _setmaxstdio(_In_ int _Max);
_Check_return_opt_ _CRTIMP unsigned int __cdecl _set_output_format(_In_ unsigned int _Format);
_Check_return_opt_ _CRTIMP unsigned int __cdecl _get_output_format(void);
_Check_return_opt_ _CRTIMP int __cdecl setvbuf(_Inout_ FILE * _File, _Inout_opt_z_bytecap_(_Size) char * _Buf, _In_ int _Mode, _In_ size_t _Size);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snprintf_s(_Out_z_bytecap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, ...);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(int, _snprintf_s, _vsnprintf_s, _Deref_post_z_ char, _Dest, _In_ size_t, _MaxCount, _In_z_ _Printf_format_string_ const char *,_Format)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl sprintf_s(_Out_z_bytecap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_z_ _Printf_format_string_ const char * _Format, ...);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(int, sprintf_s, vsprintf_s, _Deref_post_z_ char, _Dest, _In_z_ _Printf_format_string_ const char *, _Format)
_Check_return_ _CRTIMP int __cdecl _scprintf(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(sscanf_s) _CRTIMP int __cdecl sscanf(_In_z_ const char * _Src, _In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_sscanf_s_l) _CRTIMP int __cdecl _sscanf_l(_In_z_ const char * _Src, _In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl sscanf_s(_In_z_ const char * _Src, _In_z_ _Scanf_s_format_string_ const char * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _sscanf_s_l(_In_z_ const char * _Src, _In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snscanf_s) _CRTIMP int __cdecl _snscanf(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snscanf_s_l) _CRTIMP int __cdecl _snscanf_l(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snscanf_s(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snscanf_s_l(_In_bytecount_(_MaxCount) _Pre_z_ const char * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(pop)
_Check_return_ _CRT_INSECURE_DEPRECATE(tmpfile_s) _CRTIMP FILE * __cdecl tmpfile(void);
#if __STDC_WANT_SECURE_LIB__
_Check_return_wat_ _CRTIMP errno_t __cdecl tmpfile_s(_Out_opt_ _Deref_post_valid_ FILE ** _File);
_Check_return_wat_ _CRTIMP errno_t __cdecl tmpnam_s(_Out_z_cap_(_Size) char * _Buf, _In_ rsize_t _Size);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, tmpnam_s, _Deref_post_z_ char, _Buf)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(char *, __RETURN_POLICY_DST, _CRTIMP, tmpnam, _Pre_maybenull_ _Post_z_, char, _Buffer)
_Check_return_opt_ _CRTIMP int __cdecl ungetc(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl vfprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vfprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRTIMP int __cdecl vprintf(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vprintf_s(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(vsnprintf_s) _CRTIMP int __cdecl vsnprintf(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vsnprintf_s(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(int, vsnprintf_s, _Deref_post_z_ char, _Dest, _In_ size_t, _MaxCount, _In_z_ _Printf_format_string_ const char *, _Format, va_list, _Args)
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsnprintf_s(_Out_z_cap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(int, _vsnprintf_s, _Deref_post_z_ char, _Dest, _In_ size_t, _MaxCount, _In_z_ _Printf_format_string_ const char *, _Format, va_list, _Args)
#pragma warning(push)
#pragma warning(disable:4793)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(int, __RETURN_POLICY_SAME, _CRTIMP, _snprintf, _vsnprintf, _Pre_notnull_ _Post_maybez_ char, _Out_cap_(_Count) _Post_maybez_, char, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const char *, _Format)
#pragma warning(pop)
#if __STDC_WANT_SECURE_LIB__
_CRTIMP_ALTERNATIVE int __cdecl vsprintf_s(_Out_z_cap_(_SizeInBytes) char * _DstBuf, _In_ size_t _SizeInBytes, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(int, vsprintf_s, _Deref_post_z_ char, _Dest, _In_z_ _Printf_format_string_ const char *, _Format, va_list, _Args)
#endif
#pragma warning(push)
#pragma warning(disable:4793)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST(int, __RETURN_POLICY_SAME, _CRTIMP, sprintf, vsprintf, _Pre_notnull_ _Post_z_, char, _Dest, _In_z_ _Printf_format_string_ const char *, _Format)
#pragma warning(pop)
_Check_return_ _CRTIMP int __cdecl _vscprintf(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _snprintf_c(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vsnprintf_c(_Out_cap_(_MaxCount) char *_DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _fprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _printf_p(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _sprintf_p(_Out_z_cap_(_MaxCount) char * _Dst, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_p(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsprintf_p(_Out_z_cap_(_MaxCount) char * _Dst, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_Check_return_ _CRTIMP int __cdecl _scprintf_p(_In_z_ _Printf_format_string_ const char * _Format, ...);
_Check_return_ _CRTIMP int __cdecl _vscprintf_p(_In_z_ _Printf_format_string_ const char * _Format, va_list _ArgList);
_CRTIMP int __cdecl _set_printf_count_output(_In_ int _Value);
_CRTIMP int __cdecl _get_printf_count_output(void);

_Check_return_opt_ _CRTIMP int __cdecl _printf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _printf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _printf_s_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vprintf_s_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _fprintf_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fprintf_p_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fprintf_s_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_l(_Inout_ FILE * _File, _In_z_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_p_l(_Inout_ FILE * _File, _In_z_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfprintf_s_l(_Inout_ FILE * _File, _In_z_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_sprintf_s_l) _CRTIMP int __cdecl _sprintf_l(_Pre_notnull_ _Post_z_ char * _DstBuf, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _sprintf_p_l(_Out_z_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _sprintf_s_l(_Out_z_bytecap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_vsprintf_s_l) _CRTIMP int __cdecl _vsprintf_l(_Pre_notnull_ _Post_z_ char * _DstBuf, _In_z_ const char * _Format, _In_opt_ _locale_t, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsprintf_p_l(_Out_z_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char* _Format, _In_opt_ _locale_t _Locale,  va_list _ArgList);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsprintf_s_l(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _scprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _scprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vscprintf_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vscprintf_p_l(_In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snprintf_s_l) _CRTIMP int __cdecl _snprintf_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _snprintf_c_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snprintf_s_l(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_vsnprintf_s_l) _CRTIMP int __cdecl _vsnprintf_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsnprintf_c_l(_Out_cap_(_MaxCount) char * _DstBuf, _In_ size_t _MaxCount, const char *, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vsnprintf_s_l(_Out_z_cap_(_DstSize) char * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const char* _Format,_In_opt_ _locale_t _Locale, va_list _ArgList);

#ifndef _WSTDIO_DEFINED

/* wide function prototypes, also declared in wchar.h  */

#ifndef WEOF
#define WEOF (wint_t)(0xFFFF)
#endif

#ifdef  _POSIX_
_Check_return_ _CRTIMP FILE * __cdecl _wfsopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode);
#else
_Check_return_ _CRTIMP FILE * __cdecl _wfsopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode, _In_ int _ShFlag);
#endif

_Check_return_opt_ _CRTIMP wint_t __cdecl fgetwc(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _fgetwchar(void);
_Check_return_opt_ _CRTIMP wint_t __cdecl fputwc(_In_ wchar_t _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _fputwchar(_In_ wchar_t _Ch);
_Check_return_ _CRTIMP wint_t __cdecl getwc(_Inout_ FILE * _File);
_Check_return_ _CRTIMP wint_t __cdecl getwchar(void);
_Check_return_opt_ _CRTIMP wint_t __cdecl putwc(_In_ wchar_t _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl putwchar(_In_ wchar_t _Ch);
_Check_return_opt_ _CRTIMP wint_t __cdecl ungetwc(_In_ wint_t _Ch, _Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP wchar_t * __cdecl fgetws(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ int _SizeInWords, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl fputws(_In_z_ const wchar_t * _Str, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wchar_t * __cdecl _getws_s(_Out_z_cap_(_SizeInWords) wchar_t * _Str, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(wchar_t *, _getws_s, _Deref_post_z_ wchar_t, _String)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(wchar_t *, __RETURN_POLICY_SAME, _CRTIMP, _getws, _Pre_notnull_ _Post_z_, wchar_t, _String)
_Check_return_opt_ _CRTIMP int __cdecl _putws(_In_z_ const wchar_t * _Str);

_Check_return_opt_ _CRTIMP int __cdecl fwprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fwprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl wprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl wprintf_s(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_ _CRTIMP int __cdecl _scwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl vfwprintf(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vfwprintf_s(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#endif
_Check_return_opt_ _CRTIMP int __cdecl vwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl vwprintf_s(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#endif

#if __STDC_WANT_SECURE_LIB__
_CRTIMP_ALTERNATIVE int __cdecl swprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(int, swprintf_s, vswprintf_s, _Deref_post_z_ wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
#if __STDC_WANT_SECURE_LIB__
_CRTIMP_ALTERNATIVE int __cdecl vswprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _Dst, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
#endif
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(int, vswprintf_s, _Deref_post_z_ wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format, va_list, _Args)

_Check_return_opt_ _CRTIMP int __cdecl _swprintf_c(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_c(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(int, _snwprintf_s, _vsnwprintf_s, _Deref_post_z_ wchar_t, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsnwprintf_s(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(int, _vsnwprintf_s, _Deref_post_z_ wchar_t, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const wchar_t *, _Format, va_list, _Args)
#pragma warning(push)
#pragma warning(disable:4793)
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(int, __RETURN_POLICY_SAME, _CRTIMP, _snwprintf, _vsnwprintf, _Pre_notnull_ _Post_maybez_ wchar_t, _Out_cap_(_Count) _Post_maybez_, wchar_t, _Dest, _In_ size_t, _Count, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
#pragma warning(pop)

_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _wprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_p(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _swprintf_p(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_p(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_ _CRTIMP int __cdecl _scwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, ...);
_Check_return_ _CRTIMP int __cdecl _vscwprintf_p(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _wprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _wprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _wprintf_s_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vwprintf_s_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_p_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _fwprintf_s_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_p_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vfwprintf_s_l(_Inout_ FILE * _File, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRTIMP int __cdecl _swprintf_c_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _swprintf_p_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _swprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_c_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP int __cdecl _vswprintf_p_l(_Out_z_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vswprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_ _CRTIMP int __cdecl _scwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRTIMP int __cdecl _scwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRTIMP int __cdecl _vscwprintf_p_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);

_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snwprintf_s_l) _CRTIMP int __cdecl _snwprintf_l(_Out_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_vsnwprintf_s_l) _CRTIMP int __cdecl _vsnwprintf_l(_Out_cap_(_MaxCount) wchar_t * _DstBuf, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _vsnwprintf_s_l(_Out_z_cap_(_DstSize) wchar_t * _DstBuf, _In_ size_t _DstSize, _In_ size_t _MaxCount, _In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);


#ifndef _CRT_NON_CONFORMING_SWPRINTFS

#define _SWPRINTFS_DEPRECATED _CRT_DEPRECATE_TEXT("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")

#else

#define _SWPRINTFS_DEPRECATED

#endif /* ifndef _CRT_NON_CONFORMING_SWPRINTFS */

/* we could end up with a double deprecation, disable warnings 4141 and 4996 */
#pragma warning(push)
#pragma warning(disable:4141 4996 4793)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(int, __RETURN_POLICY_SAME, _SWPRINTFS_DEPRECATED _CRTIMP, _swprintf, _swprintf_s, _vswprintf, vswprintf_s, _Pre_notnull_ _Post_z_, wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(int, __RETURN_POLICY_SAME, _SWPRINTFS_DEPRECATED _CRTIMP, __swprintf_l, __vswprintf_l, _vswprintf_s_l, _Pre_notnull_ _Post_z_ wchar_t, , wchar_t, _Dest, _In_z_ _Printf_format_string_ const wchar_t *, _Format, _locale_t, _Plocinfo)
#pragma warning(pop)

#if !defined(RC_INVOKED) && !defined(__midl)
#include <swprintf.inl>
#endif

#ifdef _CRT_NON_CONFORMING_SWPRINTFS
#ifndef __cplusplus
#define swprintf _swprintf
#define vswprintf _vswprintf
#define _swprintf_l __swprintf_l
#define _vswprintf_l __vswprintf_l
#endif
#endif

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("_wtempnam")
#undef _wtempnam
#endif

_Check_return_ _CRTIMP wchar_t * __cdecl _wtempnam(_In_opt_z_ const wchar_t * _Directory, _In_opt_z_ const wchar_t * _FilePrefix);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("_wtempnam")
#endif

_Check_return_ _CRTIMP int __cdecl _vscwprintf(_In_z_ _Printf_format_string_ const wchar_t * _Format, va_list _ArgList);
_Check_return_ _CRTIMP int __cdecl _vscwprintf_l(_In_z_ _Printf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, va_list _ArgList);
_Check_return_ _CRT_INSECURE_DEPRECATE(fwscanf_s) _CRTIMP int __cdecl fwscanf(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_fwscanf_s_l) _CRTIMP int __cdecl _fwscanf_l(_Inout_ FILE * _File, _In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP int __cdecl fwscanf_s(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP int __cdecl _fwscanf_s_l(_Inout_ FILE * _File, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(swscanf_s) _CRTIMP int __cdecl swscanf(_In_z_ const wchar_t * _Src, _In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_swscanf_s_l) _CRTIMP int __cdecl _swscanf_l(_In_z_ const wchar_t * _Src, _In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl swscanf_s(_In_z_ const wchar_t *_Src, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _swscanf_s_l(_In_z_ const wchar_t * _Src, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snwscanf_s) _CRTIMP int __cdecl _snwscanf(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_snwscanf_s_l) _CRTIMP int __cdecl _snwscanf_l(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwscanf_s(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _snwscanf_s_l(_In_count_(_MaxCount) _Pre_z_ const wchar_t * _Src, _In_ size_t _MaxCount, _In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
_Check_return_ _CRT_INSECURE_DEPRECATE(wscanf_s) _CRTIMP int __cdecl wscanf(_In_z_ _Scanf_format_string_ const wchar_t * _Format, ...);
_Check_return_opt_ _CRT_INSECURE_DEPRECATE(_wscanf_s_l) _CRTIMP int __cdecl _wscanf_l(_In_z_ _Scanf_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#if __STDC_WANT_SECURE_LIB__
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl wscanf_s(_In_z_ _Scanf_s_format_string_ const wchar_t * _Format, ...);
#endif
_Check_return_opt_ _CRTIMP_ALTERNATIVE int __cdecl _wscanf_s_l(_In_z_ _Scanf_s_format_string_ const wchar_t * _Format, _In_opt_ _locale_t _Locale, ...);
#pragma warning(pop)

_Check_return_ _CRTIMP FILE * __cdecl _wfdopen(_In_ int _FileHandle , _In_z_ const wchar_t * _Mode);
_Check_return_ _CRT_INSECURE_DEPRECATE(_wfopen_s) _CRTIMP FILE * __cdecl _wfopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wfopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode);
_Check_return_ _CRT_INSECURE_DEPRECATE(_wfreopen_s) _CRTIMP FILE * __cdecl _wfreopen(_In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode, _Inout_ FILE * _OldFile);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wfreopen_s(_Deref_out_opt_ FILE ** _File, _In_z_ const wchar_t * _Filename, _In_z_ const wchar_t * _Mode, _Inout_ FILE * _OldFile);

#ifndef _CRT_WPERROR_DEFINED
#define _CRT_WPERROR_DEFINED
_CRTIMP void __cdecl _wperror(_In_opt_z_ const wchar_t * _ErrMsg);
#endif
_Check_return_ _CRTIMP FILE * __cdecl _wpopen(_In_z_ const wchar_t *_Command, _In_z_ const wchar_t * _Mode);
_CRTIMP int __cdecl _wremove(_In_z_ const wchar_t * _Filename);
_Check_return_wat_ _CRTIMP errno_t __cdecl _wtmpnam_s(_Out_z_cap_(_SizeInWords) wchar_t * _DstBuf, _In_ size_t _SizeInWords);
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(errno_t, _wtmpnam_s, _Deref_post_z_ wchar_t, _Buffer)
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(wchar_t *, __RETURN_POLICY_DST, _CRTIMP, _wtmpnam, _Pre_maybenull_ _Post_z_, wchar_t, _Buffer)

_Check_return_opt_ _CRTIMP wint_t __cdecl _fgetwc_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _fputwc_nolock(_In_ wchar_t _Ch, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP wint_t __cdecl _ungetwc_nolock(_In_ wint_t _Ch, _Inout_ FILE * _File);

#undef _CRT_GETPUTWCHAR_NOINLINE

#if !defined(__cplusplus) || defined(_M_CEE_PURE) || defined(_CRT_GETPUTWCHAR_NOINLINE)
#define getwchar()      fgetwc(stdin)
#define putwchar(_c)    fputwc((_c),stdout)
#else   /* __cplusplus */
inline wint_t __CRTDECL getwchar()
        {return (fgetwc(stdin)); }   /* stdin */
inline wint_t __CRTDECL putwchar(wchar_t _C)
        {return (fputwc(_C, stdout)); }       /* stdout */
#endif  /* __cplusplus */

#define getwc(_stm)             fgetwc(_stm)
#define putwc(_c,_stm)          fputwc(_c,_stm)
#define _putwc_nolock(_c,_stm)     _fputwc_nolock(_c,_stm)
#define _getwc_nolock(_stm)        _fgetwc_nolock(_stm)

#if defined(_CRT_DISABLE_PERFCRIT_LOCKS) && !defined(_DLL)
#define fgetwc(_stm)            _getwc_nolock(_stm)
#define fputwc(_c,_stm)         _putwc_nolock(_c,_stm)
#define ungetwc(_c,_stm)        _ungetwc_nolock(_c,_stm)
#endif

#define _WSTDIO_DEFINED
#endif  /* _WSTDIO_DEFINED */

#define _STDIO_DEFINED
#endif  /* _STDIO_DEFINED */


/* Macro definitions */

#if defined(_CRT_DISABLE_PERFCRIT_LOCKS) && !defined(_DLL)
#define feof(_stream)     ((_stream)->_flag & _IOEOF)
#define ferror(_stream)   ((_stream)->_flag & _IOERR)
#define _fileno(_stream)  ((_stream)->_file)
#define fgetc(_stream)     (--(_stream)->_cnt >= 0 \
                ? 0xff & *(_stream)->_ptr++ : _filbuf(_stream))
#define putc(_c,_stream)  (--(_stream)->_cnt >= 0 \
                ? 0xff & (*(_stream)->_ptr++ = (char)(_c)) :  _flsbuf((_c),(_stream)))
#define getc(_stream)    fgetc(_stream)
#define getchar()         getc(stdin)
#define putchar(_c)       putc((_c),stdout)
#endif


#define _fgetc_nolock(_stream)       (--(_stream)->_cnt >= 0 ? 0xff & *(_stream)->_ptr++ : _filbuf(_stream))
#define _fputc_nolock(_c,_stream)    (--(_stream)->_cnt >= 0 ? 0xff & (*(_stream)->_ptr++ = (char)(_c)) :  _flsbuf((_c),(_stream)))
#define _getc_nolock(_stream)       _fgetc_nolock(_stream)
#define _putc_nolock(_c, _stream)   _fputc_nolock(_c, _stream)
#define _getchar_nolock()           _getc_nolock(stdin)
#define _putchar_nolock(_c)         _putc_nolock((_c),stdout)
#define _getwchar_nolock()          _getwc_nolock(stdin)
#define _putwchar_nolock(_c)        _putwc_nolock((_c),stdout)

_CRTIMP void __cdecl _lock_file(_Inout_ FILE * _File);
_CRTIMP void __cdecl _unlock_file(_Inout_ FILE * _File);

_Check_return_opt_ _CRTIMP int __cdecl _fclose_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fflush_nolock(_Inout_opt_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl _fread_nolock(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl _fread_nolock_s(_Out_bytecap_x_(_ElementSize*_Count) void * _DstBuf, _In_ size_t _DstSize, _In_ size_t _ElementSize, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fseek_nolock(_Inout_ FILE * _File, _In_ long _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP long __cdecl _ftell_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _fseeki64_nolock(_Inout_ FILE * _File, _In_ __int64 _Offset, _In_ int _Origin);
_Check_return_ _CRTIMP __int64 __cdecl _ftelli64_nolock(_Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP size_t __cdecl _fwrite_nolock(_In_bytecount_x_(_Size*_Count) const void * _DstBuf, _In_ size_t _Size, _In_ size_t _Count, _Inout_ FILE * _File);
_Check_return_opt_ _CRTIMP int __cdecl _ungetc_nolock(_In_ int _Ch, _Inout_ FILE * _File);

#if defined(_CRT_DISABLE_PERFCRIT_LOCKS) && !defined(_DLL)
#define fclose(_stm)                                            _fclose_nolock(_stm)
#define fflush(_stm)                                            _fflush_nolock(_stm)
#define fread(_DstBuf, _ElementSize, _Count, _File)             _fread_nolock(_DstBuf, _ElementSize, _Count, _File)
#define fread_s(_DstBuf, _DstSize, _ElementSize, _Count, _File) _fread_nolock_s(_DstBuf, _DstSize, _ElementSize, _Count, _File)
#define fseek(_stm,_offset,_origin)                             _fseek_nolock(_stm,_offset,_origin)
#define ftell(_stm)                                             _ftell_nolock(_stm)
#define _fseeki64(_stm,_offset,_origin)                         _fseeki64_nolock(_stm,_offset,_origin)
#define _ftelli64(_stm)                                         _ftelli64_nolock(_stm)
#define fwrite(_buf,_siz,_cnt,_stm)                             _fwrite_nolock(_buf,_siz,_cnt,_stm)
#define ungetc(_c,_stm)                                         _ungetc_nolock(_c,_stm)
#endif

#if     !__STDC__ && !defined(_POSIX_)

/* Non-ANSI names for compatibility */

#define P_tmpdir  _P_tmpdir
#define SYS_OPEN  _SYS_OPEN

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma push_macro("tempnam")
#undef tempnam
#endif

_CRT_NONSTDC_DEPRECATE(_tempnam) _CRTIMP char * __cdecl tempnam(_In_opt_z_ const char * _Directory, _In_opt_z_ const char * _FilePrefix);

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
#pragma pop_macro("tempnam")
#endif

_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_fcloseall) _CRTIMP int __cdecl fcloseall(void);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_fdopen) _CRTIMP FILE * __cdecl fdopen(_In_ int _FileHandle, _In_z_ const char * _Format);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_fgetchar) _CRTIMP int __cdecl fgetchar(void);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_fileno) _CRTIMP int __cdecl fileno(_In_ FILE * _File);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_flushall) _CRTIMP int __cdecl flushall(void);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_fputchar) _CRTIMP int __cdecl fputchar(_In_ int _Ch);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_getw) _CRTIMP int __cdecl getw(_Inout_ FILE * _File);
_Check_return_opt_ _CRT_NONSTDC_DEPRECATE(_putw) _CRTIMP int __cdecl putw(_In_ int _Ch, _Inout_ FILE * _File);
_Check_return_ _CRT_NONSTDC_DEPRECATE(_rmtmp) _CRTIMP int __cdecl rmtmp(void);

#endif  /* __STDC__ */

#ifdef  __cplusplus
}
#endif

#pragma pack(pop)

#endif  /* _INC_STDIO */


//#include<iostream>
//#include<stdlib.h>
//#include<ctime>
//#include<stdio.h>

using namespace std;

class train
{
  struct cargo
  {
    int train_no;
    int boarding;
    int deboarding;
    int day;
    int month;
    int year;
    cargo *next;
    char content[20];
  };

  typedef cargo *CARGO;
  public:

  CARGO get_data(CARGO engine)
  {
    CARGO x = new_cargo();
    time_t t = time(0);
    struct tm * now = localtime(&t);
    // cout<<now;
    int day_t,day = now->tm_mday + 1;
    int month_t,month = now->tm_mon + 1;
    int year_t,year = now->tm_year + 1900;
    yr:
    cout<<"\n\tEnter the date of Journey";
    cout<<"\n\tEnter the Year :";
    cin>>year_t;
    if(year_t<year || year_t>year+1)
    {
      cout<<"INVALID INPUT";
      goto yr;
    }
    mnth:
    cout<<"\n\tEnter the Month :";
    cin>>month_t;
    if (((year_t - year==0)&&(month_t<month)) || (month_t>12))
    {
      cout<<"INVALID INPUT";
      goto mnth;
    }
    d:
    cout<<"\n\tEnter the Day :";
    cin>>day_t;
    if (((month_t-month==0)&&(day_t<day))|| (day_t>31))
    {
        cout<<"INVALID INPUT";
        goto d;
    }
    x->year = year_t;
    x->month = month_t;
    x->day = day_t;
    cout<<"\n\tThe date of journey is: "<<x->day<<"/"<<x->month<<"/"<<x->year;
    cout<<"\n\tEnter the boarding station no.:\t";
    cin>>x->boarding;
    cout<<"\n\tYou have set "<<station_list[--x->boarding]<<" as boarding station";
    cout<<"\n\tEnter the deboarding station no.:\t";
    cin>>x->deboarding;
    cout<<"\n\tYou have set "<<station_list[--x->deboarding]<<" as deboarding station";
    cout<<"\n\tEnter the content of the cargo:\t";
    cin>>x->content;
    if (engine == NULL)
    {
      cout<<"hey";
      return x;
    }
    engine = sorting(engine,x);
    return engine;
  }


  CARGO new_cargo()
  {
    CARGO x = (CARGO)malloc(sizeof(cargo));
    return x;
  }


  void display(CARGO engine)
  {
      if (engine == NULL)
      {
        cout<<"\n\tThere is no content!!";
        return;
      }
      CARGO temp = engine;
      while(temp == NULL)
      {
        cout<<"\n\tContent :"<<temp->content;
        cout<<"\n\tDeboarding station:"<<temp->deboarding<<'\n';
        temp=temp->next;
      }
  }


  CARGO sorting(CARGO engine,CARGO present)
  {
    cout<<"hi";
    CARGO temp,prev;
    if (engine->next == NULL)
    {
      if (engine->deboarding>present->deboarding)
      {
        cout<<"vain";
        present->next = engine;
        return present;
      }
    }
    temp =engine;
    while(temp==NULL)
    {
      cout<<"\t"<<temp->deboarding<<"\t";
      if(temp->deboarding>present->deboarding)
      {
        prev->next=present;
        present->next=temp;
      }
      prev= temp;
      temp = temp->next;
    }
    cout<<"vains";
    return engine;
  }

  CARGO engine;

  char station_list[7][5];
  int train_no;

};

train obj[5];

int a;
char menu();
void train_list();
void booking();

void train_content();

/*********************************************************
This function is used to display the sorted content of the
the freight train.
**********************************************************/
void train_content()
{
  int train_no_t;
  cout<<"\n\tEnter the train number whose content is to be displayed";
  cin>>train_no_t;
  for (int i=0; i<5; i++)
  {
    if (train_no_t == obj[i].train_no)
    {
      a=i;
      break;
    }
  }
  obj[a].display(obj[a].engine);
}


/*********************************************************
This function is allows the user to book the cargo
compartment of the freight train.
**********************************************************/
void booking()
{
  int train_no_t,i=0;
  char choice;
  re:
  cout<<"\n\tDo you want to see train list ?(y/n)";
  cin>>choice;
  if(choice == 'y' || choice == 'Y')
    train_list();
  cout<<"\n\tGo to booking counter ?(y/n)";
  cin>>choice;
  if (choice == 'n' || choice == 'N')
  {
    cout<<"\n\tDisplay train list once more ?(y/n)";
    cin>>choice;
    if (choice == 'y' || choice == 'Y')
      goto re;
    else
    return;
  }
  cout<<"\n\t\tBOOKING COUNTER";
  train_no:
  cout<<"\n\tEnter the train no.:\t";
  cin>>train_no_t;
  for (i=0; i<5; i++)
  {
    cout<<obj[i].train_no<<" "<<train_no_t;
    if(obj[i].train_no == train_no_t)
    {
      a=i;
      break;
    }
  }
  if (a!=i)
  {
    cout<<"\n\tINVALID INPUT";
    goto train_no;
  }
  obj[a].engine = obj[a].get_data(obj[a].engine);
}

/*********************************************************
This function is used to display the main MENU of the
program.
**********************************************************/
char menu()
{
  char a;
  cout<<"\n\t\tMenu\n\t1. TrainList\n\t2. Booking\n\t3. Train Content\n\t4. Exit\nEnter Your choice:\t";
  cin>>a;
  return a;
}

/*********************************************************
This function is used to display the available freight
train.
**********************************************************/
void train_list()
{
 char choice;

 printf("\n\t\tList Of Trains \n1.UBL-YPR - 18048 \n2.UBL-BJPR - 12245\n3.UBL-BGK - 12246 \n4.UBL-GOA  - 22864\n5.UBL-HYB - 12864\n");
 printf("\nEnter Your choice:\t");
 scanf(" %c",&choice);
 switch(choice)
 {
 case '1':for(int i=0; i<7; i++)
          {
             cout<<i+1<<". "<<obj[0].station_list[i]<<'\n';
          }
          break;
  case '2':for(int i=0; i<7; i++)
           {
             cout<<i+1<<". "<<obj[1].station_list[i]<<'\n';
           }
           break;
 case '3':for(int i=0; i<7; i++)
           {
             cout<<i+1<<". "<<obj[2].station_list[i]<<'\n';

           }
          break;
 case '4':for(int i=0; i<7; i++)
          {
              cout<<i+1<<". "<<obj[3].station_list[i]<<'\n';
          }
          break;
   case '5':for(int i=0; i<7; i++)
          {
            cout<<i+1<<". "<<obj[4].station_list[i]<<'\n';
          }
          break;
  default:printf(" please enter the correct choice\n");
 }
}


int main()
{
  /*********************************************************
  here we are defining the train nos. which are availabe in
  the program.
  **********************************************************/
  obj[0].train_no=18048;
  obj[1].train_no=12245;
  obj[2].train_no=12246;
  obj[3].train_no=22864;
  obj[4].train_no=12864;
  // train obj[5];
  char stnt_list_t4[7][5]={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
  // char stnt_list_t1={{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {

		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[1].station_list[i][j]=stnt_list_t4[i][j];//{{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
		  }
	  }
	  //--a;
  //}
  char stnt_list_t1[7][5] ={{"UBL"},{"HVR"},{"RNR"},{"DVG"},{"ASK"},{"TK"},{"YPR"}};
  // obj[0].station_list={{"UBL"},{"HVR"},{"RNR"},{"DVG"},{"ASK"},{"TK"},{"YPR"}};
  //a=5;
  //while (a)
  //{
    for (int i=0; i<7; i++)
    {
      for (int j=0; j<5; j++)
      {
        obj[0].station_list[i][j]=stnt_list_t1[i][j];//{{"UBL"},{"NGR"},{"GDG"},{"BDM"},{"BGK"},{"LMT"},{"BJPR"}};
      }
    }
    //--a;
  //}
  char stnt_list_t2[7][4]={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
//  obj[2].station_list={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {

		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[2].station_list[i][j]=stnt_list_t2[i][j];//{{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
		  }
	  }
	  //--a;
  //}
	  char stnt_list_t5[7][5]={{"UBL"},{"GDG"},{"BGK"},{"MGA"},{"DVG"},{"PNL"},{"GOA"}};
	//  obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
	  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {
		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[3].station_list[i][j]=stnt_list_t5[i][j];//{{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};
		  }
	  }
    char stnt_list_t3[7][5]={{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};
	//  obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
	  //a=4;
  //while (a)
  //{
	  //int i,j;
	  for(int i=0 ;i<7 ; i++)
	  {
		  for(int j=0 ; j<5 ;j++)
		  {
			  obj[4].station_list[i][j]=stnt_list_t3[i][j];//{{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};
		  }
	  }
	  //--a
	  //}
  // obj[2].station_list={{"UBL"},{"NGR"},{"GDG"},{"HRR"},{"BDM"},{"RRB"},{"BGK"}};
  // obj[3].station_list={{"DWR"},{"LWR"},{"LD"},{"CLR"},{"QLM"},{"YG"},{"VSG"}};
  // obj[4].station_list={{"UBL"},{"GDG"},{"BGK"},{"BJPR"},{"GLB"},{"VKB"},{"HYB"}};

  // booking();
  char ch;
  cout<<"Welcome To Freight Train Management System";
  while(1)
  {
    ch = menu();
    switch (ch)
    {
      case '1':train_list();
             break;
      case '2':booking();
             break;
      case '3':train_content();
                break;
      case '4':exit(0);
                  break;
      default : cout<<"\n\n\t!!...INVALID INPUT...!!";
    }
  }
}
