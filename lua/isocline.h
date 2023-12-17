#if !defined LUA_VERSION_NUM || (LUA_VERSION_NUM <= 501)
#define lua_rawlen lua_objlen
#undef lua_readline
#undef lua_saveline
#undef lua_freeline
#endif /* LUA_VERSION_NUM */
void lua_initline(lua_State *L);
void ic_history_add(char const *entry);
char *ic_readline(char const *prompt_text);
#define lua_initreadline(L) lua_initline(L)
#define lua_readline(L, b, p) (((b) = ic_readline(p)) != NULL)
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
#define lua_saveline(L, line) ic_history_add(line)
#else /* !LUA_VERSION_NUM */
#define lua_saveline(L, idx)    \
    if (lua_rawlen(L, idx) > 0) \
        ic_history_add(lua_tostring(L, idx));
#endif /* LUA_VERSION_NUM */
#define lua_freeline(L, b) free(b)
