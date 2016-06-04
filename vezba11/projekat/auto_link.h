/*************************************************************************

USAGE:
~~~~~~

Before including this header you must define one or more of define the following macros:

LIB_NAME:           Required: A string containing the basename of the library,
                          for example boost_regex.
LIB_TOOLSET:        Optional: the base name of the toolset.
DYN_LINK:           Optional: when set link to dll rather than static library.
LIB_DIAGNOSTIC:     Optional: when set the header will print out the name
                          of the library selected (useful for debugging).
AUTO_LINK_NOMANGLE: Specifies that we should link to LIB_NAME.lib,
                          rather than a mangled-name version.
AUTO_LINK_TAGGED:   Specifies that we link to libraries built with the --layout=tagged option.
                          This is essentially the same as the default name-mangled version, but without
                          the compiler name and version, or the Boost version.  Just the build options.

These macros will be undef'ed at the end of the header, further this header
has no include guards - so be sure to include it only once from your library!

Algorithm:
~~~~~~~~~~

Libraries for Microsoft compilers are automatically
selected here, the name of the lib is selected according to the following
formula:

LIB_PREFIX
   + LIB_NAME
   + "_"
   + LIB_TOOLSET
   + LIB_THREAD_OPT
   + LIB_RT_OPT

These are defined as:

LIB_PREFIX:     "lib" for static libraries otherwise "".

LIB_NAME:       The base name of the lib ( for example boost_regex).

LIB_TOOLSET:    The compiler toolset name (vc6, vc7, bcb5 etc).

LIB_THREAD_OPT: "-mt" for multithread builds, otherwise nothing.

LIB_RT_OPT:     A suffix that indicates the runtime library used,
                      contains one or more of the following letters after
                      a hyphen:

                      s      static runtime (dynamic if not present).
                      g      debug/diagnostic runtime (release if not present).
                      y      Python debug/diagnostic runtime (release if not present).
                      d      debug build (release if not present).
                      p      STLport build.
                      n      STLport build without its IOStreams.


***************************************************************************/

#if defined(_MSC_VER)
//
// C language compatability (no, honestly)
//
#  define MSVC _MSC_VER
#  define STRINGIZE(X) DO_STRINGIZE(X)
#  define DO_STRINGIZE(X) #X
#endif
//
// Only include what follows for known and supported compilers:
//
#if defined(MSVC)

#ifndef LIB_NAME
#  error "Macro LIB_NAME not set (internal error)"
#endif

//
// error check:
//
#if defined(__MSVC_RUNTIME_CHECKS) && !defined(_DEBUG)
#  pragma message("Using the /RTC option without specifying a debug runtime will lead to linker errors")
#  pragma message("Hint: go to the code generation options and switch to one of the debugging runtimes")
#  error "Incompatible build options"
#endif
//
// select toolset if not defined already:
//
#ifndef LIB_TOOLSET
#  if defined(MSVC) && (MSVC < 1600)
    // Note: no compilers before 1600 are supported


#  elif defined(MSVC) && (MSVC < 1700)

     // vc10:
#    define LIB_TOOLSET "vc100"

#  elif defined(MSVC) && (MSVC < 1800)

     // vc11:
#    define LIB_TOOLSET "vc110"

#  elif defined(MSVC) && (MSVC < 1900)

     // vc11:
#    define LIB_TOOLSET "vc120"


#  elif defined(MSVC)

     // vc13:
#    define LIB_TOOLSET "vc140"

#  endif
#endif // LIB_TOOLSET

//
// select thread opt:
//
#if defined(_MT) || defined(__MT__)
#  define LIB_THREAD_OPT "-mt"
#else
#  define LIB_THREAD_OPT
#endif

#if defined(_MSC_VER) || defined(__MWERKS__)

#  ifdef _DLL

#     if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && (defined(_STLP_OWN_IOSTREAMS) || defined(__STL_OWN_IOSTREAMS))

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-gydp"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define LIB_RT_OPT "-gdp"
#        elif defined(_DEBUG)\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-gydp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#            define LIB_RT_OPT "-gdp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define LIB_RT_OPT "-p"
#        endif

#     elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-gydpn"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define LIB_RT_OPT "-gdpn"
#        elif defined(_DEBUG)\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-gydpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#            define LIB_RT_OPT "-gdpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define LIB_RT_OPT "-pn"
#        endif

#     else

#        if defined(_DEBUG) && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-gyd"
#        elif defined(_DEBUG)
#            define LIB_RT_OPT "-gd"
#        else
#            define LIB_RT_OPT
#        endif

#     endif

#  else

#     if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && (defined(_STLP_OWN_IOSTREAMS) || defined(__STL_OWN_IOSTREAMS))

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-sgydp"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define LIB_RT_OPT "-sgdp"
#        elif defined(_DEBUG)\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#             define LIB_RT_OPT "-sgydp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#             define LIB_RT_OPT "-sgdp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define LIB_RT_OPT "-sp"
#        endif

#     elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#            define LIB_RT_OPT "-sgydpn"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define LIB_RT_OPT "-sgdpn"
#        elif defined(_DEBUG)\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#             define LIB_RT_OPT "-sgydpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#             define LIB_RT_OPT "-sgdpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define LIB_RT_OPT "-spn"
#        endif

#     else

#        if defined(_DEBUG)\
               && defined(DEBUG_PYTHON) && defined(LINKING_PYTHON)
#             define LIB_RT_OPT "-sgyd"
#        elif defined(_DEBUG)
#             define LIB_RT_OPT "-sgd"
#        else
#            define LIB_RT_OPT "-s"
#        endif

#     endif

#  endif

#endif

//
// select linkage opt:
//
#if (defined(_DLL) || defined(_RTLDLL)) && defined(DYN_LINK)
#  define LIB_PREFIX
#elif defined(DYN_LINK)
#  error "Mixing a dll boost library with a static runtime is a really bad idea..."
#else
#  define LIB_PREFIX "lib"
#endif

//
// now include the lib:
//
#if defined(LIB_NAME) \
      && defined(LIB_PREFIX) \
      && defined(LIB_TOOLSET) \
      && defined(LIB_THREAD_OPT) \
      && defined(LIB_RT_OPT)

#ifdef AUTO_LINK_TAGGED
#  pragma comment(lib, LIB_PREFIX STRINGIZE(LIB_NAME) LIB_THREAD_OPT LIB_RT_OPT ".lib")
#  ifdef LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " LIB_PREFIX STRINGIZE(LIB_NAME) LIB_THREAD_OPT LIB_RT_OPT ".lib")
#  endif
#elif defined(AUTO_LINK_NOMANGLE)
#  pragma comment(lib, STRINGIZE(LIB_NAME) ".lib")
#  ifdef LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " STRINGIZE(LIB_NAME) ".lib")
#  endif
#else
#  pragma comment(lib, LIB_PREFIX STRINGIZE(LIB_NAME) "-" LIB_TOOLSET LIB_THREAD_OPT LIB_RT_OPT ".lib")
#  ifdef LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " LIB_PREFIX STRINGIZE(LIB_NAME) "-" LIB_TOOLSET LIB_THREAD_OPT LIB_RT_OPT ".lib")
#  endif
#endif

#else
#  error "some required macros where not defined (internal logic error)."
#endif


#endif // _MSC_VER

//
// finally undef any macros we may have set:
//
#ifdef LIB_PREFIX
#  undef LIB_PREFIX
#endif
#if defined(LIB_NAME)
#  undef LIB_NAME
#endif
// Don't undef this one: it can be set by the user and should be the 
// same for all libraries:
//#if defined(LIB_TOOLSET)
//#  undef LIB_TOOLSET
//#endif
#if defined(LIB_THREAD_OPT)
#  undef LIB_THREAD_OPT
#endif
#if defined(LIB_RT_OPT)
#  undef LIB_RT_OPT
#endif
#if defined(LIB_LINK_OPT)
#  undef LIB_LINK_OPT
#endif
#if defined(LIB_DEBUG_OPT)
#  undef LIB_DEBUG_OPT
#endif
#if defined(DYN_LINK)
#  undef DYN_LINK
#endif


