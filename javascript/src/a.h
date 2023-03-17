#ifndef JS_A_H
#define JS_A_H
#include "a/a.h"
#if !defined __EMSCRIPTEN__
#define __EMSCRIPTEN__
#endif /* __EMSCRIPTEN__ */
#pragma clang diagnostic ignored "-Wpadded"
#if !defined EM_PORT_API
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#if defined(__cplusplus)
#include <emscripten/val.h>
#include <emscripten/bind.h>
#pragma clang diagnostic ignored "-Wglobal-constructors"
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
