#ifndef JS_A_H
#define JS_A_H
#include "a/a.h"
#if !defined __EMSCRIPTEN__
#define __EMSCRIPTEN__
#endif /* __EMSCRIPTEN__ */
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Wpadded")
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#if !defined EM_PORT_API
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#if A_PREREQ_GNUC(2, 95) || __has_warning("-Wmissing-prototypes")
#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#endif /* -Wmissing-prototypes */
#if defined(__cplusplus)
#include <emscripten/val.h>
#include <emscripten/bind.h>
#if __has_warning("-Wglobal-constructors")
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#endif /* -Wglobal-constructors */
#define EM_PORT_API(T) extern "C" T EMSCRIPTEN_KEEPALIVE
#else /* !__cplusplus */
#define EM_PORT_API(T) T EMSCRIPTEN_KEEPALIVE
#endif /* __cplusplus */
#else /* !__EMSCRIPTEN__ */
#if defined(__cplusplus)
#define EM_PORT_API(T) extern "C" T
#else /* !__cplusplus */
#define EM_PORT_API(T) T
#endif /* __cplusplus */
#endif /* __EMSCRIPTEN__ */
#endif /* EM_PORT_API */
#endif /* a.h */
