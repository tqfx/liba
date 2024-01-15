#include "isocline/src/isocline.c"
#include <ctype.h>
#if !defined lua_h
#include "lua.h"
#endif /* lua_h */

#if !defined LUA_VERSION_NUM || (LUA_VERSION_NUM <= 501)
#define lua_rawlen lua_objlen
#undef lua_readline
#undef lua_saveline
#undef lua_freeline
#endif /* LUA_VERSION_NUM */
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
static char const *keywords[] = {
    "and", "break", "do", "else", "elseif", "end",
    "false", "for", "function", "goto", "if", "in",
    "local", "nil", "not", "or", "repeat", "return",
    "then", "true", "until", "while", NULL};
static int haschr(char const *str, int chr)
{
    for (; *str; ++str)
    {
        if (*str == chr) { return 1; }
    }
    return 0;
}
static int is_id(char const *str)
{
    int c = (int)*str;
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '_') { return 0; }
    for (++str, c = (int)*str; c; ++str, c = (int)*str)
    {
        if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '_') { return 0; }
    }
    return 1;
}
static int match(char const *str, char const *sub, size_t len)
{
    char const *const suf = sub + len;
    if (str[0] == '_' && str[1] == '_')
    {
        if (sub[0] != '_') { return 0; }
        if (sub[1] == '_' && str[2] && sub[2] && str[2] != sub[2]) { return 0; }
    }
    if (str[0] && sub[0] && str[0] != sub[0]) { return 0; }
    for (; *str && sub < suf; ++sub)
    {
        if (*str != *sub)
        {
            for (;;)
            {
                if (*++str == 0) { return 0; }
                if (*str == *sub)
                {
                    ++str;
                    break;
                }
            }
        }
        else { ++str; }
    }
    return sub == suf;
}
static void completion_exec(ic_completion_env_t *cenv, char const *buffer, char const *suffix, char const *sep)
{
    char const *subfix = NULL;
    lua_State *L = ic_completion_arg(cenv);
    if (suffix == NULL) { suffix = buffer; }
    for (char const *s = suffix; *s; ++s)
    {
        if (*s == '.' || *s == ':' || *s == '[')
        {
            subfix = s;
            break;
        }
    }
    if (subfix > suffix)
    {
        unsigned int fix = 0;
        lua_Integer integer = 0;
        if (subfix[-1] == ']')
        {
            ++fix; // 1]
            if (*suffix == '\'' || *suffix == '\"')
            {
                ++fix; // '1' "1"
                ++suffix;
            }
            else if (isdigit(*suffix))
            {
                integer = 1;
            }
        }
        size_t key_len = (size_t)(subfix - suffix);
        if (key_len >= fix) { key_len -= fix; }
        lua_pushlstring(L, suffix, key_len);
        if (integer)
        {
            integer = lua_tointeger(L, -1);
            if (integer)
            {
                lua_pushinteger(L, integer);
                lua_remove(L, -2); // table, string, integer
            }
        }
        sep = subfix;
        suffix = subfix + 1;
        lua_gettable(L, -2); // table, key
        if (*suffix != '.' && *suffix != ':' && *suffix != '[')
        {
            if (lua_type(L, -1) == LUA_TTABLE)
            {
                completion_exec(cenv, buffer, suffix, sep);
            }
            if (lua_getmetatable(L, -1))
            {
                lua_getfield(L, -1, "__index");
                lua_remove(L, -2); // table, value, meta, __index
                if (lua_type(L, -1) == LUA_TFUNCTION)
                {
                    if (strncmp(suffix, "__index", sizeof("__index") - 1) == 0)
                    {
                        int c = (int)suffix[sizeof("__index") - 1];
                        if (c == '.' || c == ':' || c == '[')
                        {
                            suffix += sizeof("__index");
                            sep += sizeof("__index");
                        }
                    }
                    lua_pushvalue(L, -2);
                    lua_pushstring(L, "__index");
                    lua_pcall(L, 2, 1, 0);
                }
                lua_remove(L, -2); // table, value, __index
                if (lua_type(L, -1) == LUA_TTABLE)
                {
                    completion_exec(cenv, buffer, suffix, sep);
                }
            }
        }
        lua_pop(L, 1);
        return;
    }

    void *ud;
    lua_Alloc alloc = lua_getallocf(L, &ud);
    size_t prefix_len = (size_t)((sep ? sep : suffix) - buffer);
    char *prefix = (char *)alloc(ud, NULL, LUA_TSTRING, prefix_len + 1);
    memcpy(prefix, buffer, prefix_len);
    prefix[prefix_len] = 0;

    if (*suffix == '\'' || *suffix == '\"')
    {
        ++suffix; // '1 "1
    }
    size_t suffix_len = strlen(suffix);
    if (suffix_len)
    {
        if (suffix[suffix_len - 1] == ']')
        {
            --suffix_len; // 1]
        }
        if (suffix[suffix_len - 1] == '\'' || suffix[suffix_len - 1] == '\"')
        {
            --suffix_len; // 1' 1"
        }
    }

    for (lua_pushnil(L); lua_next(L, -2); lua_pop(L, 1))
    {
        if (lua_type(L, -2) == LUA_TSTRING)
        {
            int type = lua_type(L, -1);
            if (sep && *sep == ':' && type != LUA_TFUNCTION) { continue; }
            char const *key = lua_tostring(L, -2);
            if (match(key, suffix, suffix_len))
            {
                union
                {
                    char const *p;
                    char *o;
                } s;
                if ((sep && *sep == '[') || (!is_id(key) && sep && *sep))
                {
                    lua_pushfstring(L, "%s%s", key, key);
                    char const *k2 = lua_tostring(L, -1);
                    char const *k1 = key;
                    for (s.p = k2; *k1;)
                    {
                        if (*k1 == '\"') { *s.o++ = '\\'; }
                        *s.o++ = *k1++;
                    }
                    *s.o = 0;
                    lua_pushfstring(L, "%s[\"%s\"", prefix, k2);
                    lua_remove(L, -2); // key, value, k2, replacement
                }
                else if (sep && *sep)
                {
                    lua_pushlstring(L, sep, (size_t)(suffix - sep));
                    if (type == LUA_TFUNCTION)
                    {
                        lua_pushfstring(L, "%s%s%s(", prefix, lua_tostring(L, -1), key);
                    }
                    else
                    {
                        lua_pushfstring(L, "%s%s%s", prefix, lua_tostring(L, -1), key);
                    }
                    lua_remove(L, -2); // key, value, sep, replacement
                }
                else
                {
                    if (type == LUA_TFUNCTION)
                    {
                        lua_pushfstring(L, "%s%s(", prefix, key);
                    }
                    else
                    {
                        lua_pushfstring(L, "%s%s", prefix, key);
                    }
                }
                ic_add_completion_ex(cenv, lua_tostring(L, -1), key, NULL);
                lua_pop(L, 1);
            }
        }
        else if (lua_type(L, -2) == LUA_TNUMBER)
        {
#if defined(LUA_VERSION_NUM) && (LUA_VERSION_NUM > 502)
            lua_pushfstring(L, "%I", lua_tointeger(L, -2));
#else /* !LUA_VERSION_NUM */
            lua_pushfstring(L, "%d", lua_tointeger(L, -2));
#endif /* LUA_VERSION_NUM */
            char const *key = lua_tostring(L, -1);
            if (match(key, suffix, suffix_len))
            {
                lua_pushfstring(L, "%s[%s", prefix, key);
                ic_add_completion_ex(cenv, lua_tostring(L, -1), key, NULL);
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }
    }

    if (!sep)
    {
        for (char const **s = keywords; *s; ++s)
        {
            if (match(*s, suffix, suffix_len))
            {
                ic_add_completion(cenv, *s);
            }
        }
    }

    alloc(ud, prefix, prefix_len + 1, 0);
}

static void completion_func(ic_completion_env_t *cenv, char const *buffer)
{
    lua_State *L = ic_completion_arg(cenv);
#if defined(LUA_RIDX_GLOBALS)
    lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
#else /* !LUA_RIDX_GLOBALS */
    lua_pushvalue(L, LUA_GLOBALSINDEX);
#endif /* LUA_RIDX_GLOBALS */
    completion_exec(cenv, buffer, buffer, 0);
    lua_pop(L, 1);
}

static bool is_block(char const *s, long len)
{
    return len > 0 && (isalnum(*s) || haschr("_.:[\'\"\\]", *s));
}

static void completer(ic_completion_env_t *cenv, char const *buffer)
{
    ic_complete_word(cenv, buffer, completion_func, is_block);
    if (strchr(buffer, '\'') || strchr(buffer, '\"'))
    {
        ic_complete_filename(cenv, buffer, 0, NULL, NULL);
    }
}

static long match_string(void const *_s, long i)
{
    int quote = 0;
    char const *s = (char const *)_s + i;
    if (*s == '\'') { quote = '\''; }
    if (*s == '\"') { quote = '\"'; }
    if (quote)
    {
        for (++s; *s && *s != quote; ++s)
        {
            if (s[0] == '\\' && s[1] == quote) { ++s; }
        }
        if (*s == quote) { ++s; }
    }
    return (long)(s - (char const *)_s - i);
}

static long match_number(void const *_s, long i)
{
    char const *s = (char const *)_s + i;
    if (i && (isalnum(s[-1]) || s[-1] == '_')) { return 0; }
    if (s[0] == '0' && (s[1] == 'X' || s[1] == 'x'))
    {
        s += 2;
        for (; isxdigit(*s); ++s) {}
        if (*s == '.') { ++s; }
        for (; isxdigit(*s); ++s) {}
        if (*s == 'P' || *s == 'p')
        {
            ++s;
            if (*s == '+' || *s == '-') { ++s; }
            if (!isdigit(*s)) { return 0; }
        }
        for (; isdigit(*s); ++s) {}
    }
    else
    {
        for (; isdigit(*s); ++s) {}
        if (*s == '.') { ++s; }
        for (; isdigit(*s); ++s) {}
        if (*s == 'E' || *s == 'e')
        {
            ++s;
            if (*s == '+' || *s == '-') { ++s; }
            if (!isdigit(*s)) { return 0; }
        }
        for (; isdigit(*s); ++s) {}
    }
    return (long)(s - (char const *)_s - i);
}

static void highlighter(ic_highlight_env_t *henv, char const *input, void *arg)
{
    long len = (long)strlen(input);
    for (long i = 0; i < len;)
    {
        long tlen; // token length
        if (ic_starts_with(input + i, "--")) // line comment
        {
            for (tlen = 2; i + tlen < len && input[i + tlen] != '\n'; ++tlen) {}
            ic_highlight(henv, i, tlen, "comment");
            i += tlen;
        }
        else if ((tlen = ic_match_any_token(input, i, ic_char_is_idletter, keywords)) > 0)
        {
            ic_highlight(henv, i, tlen, "keyword");
            i += tlen;
        }
        else if ((tlen = match_string(input, i)) > 0)
        {
            ic_highlight(henv, i, tlen, "string");
            i += tlen;
        }
        else if ((tlen = match_number(input, i)) > 0)
        {
            ic_highlight(henv, i, tlen, "number");
            i += tlen;
        }
        else { ++i; }
    }
    (void)arg;
}

static void joinpath(void *buff, char const *path, char const *name)
{
    char *p = (char *)buff;
    for (; *path; ++path)
    {
        *p++ = (char)(*path != '\\' ? *path : '/');
    }
    if (p > (char *)buff && p[-1] != '/') { *p++ = '/'; }
    for (; *name; ++name)
    {
        *p++ = (char)(*name != '\\' ? *name : '/');
    }
    *p = 0;
}

static void loadhistory(char const *name)
{
#if defined(_WIN32)
    char path[260];
#else /* _WIN32 */
    char path[4096];
#endif /* _WIN32 */
    char const *home = getenv("HOME");
    if (!home)
    {
        home = getenv("USERPROFILE");
    }
    if (home)
    {
        joinpath(path, home, name);
        ic_set_history(path, -1);
    }
}

static void lua_initline(lua_State *L)
{
    ic_style_def("ic-bracematch", "teal");
    ic_set_default_completer(completer, L);
    ic_set_default_highlighter(highlighter, L);
    ic_set_prompt_marker("", "");
    ic_enable_brace_insertion(0);
    loadhistory(".lua_history");
}
