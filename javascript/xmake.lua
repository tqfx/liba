---@diagnostic disable
-- option: liba-wasm
option("liba-wasm")
set_showmenu(true)
set_category("liba")
set_default(is_plat("wasm") or false)
set_description("Enable/Disable JavaScript WebAssembly")
option_end()

-- option: liba-wasm-async
option("liba-wasm-async")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable JavaScript Async")
option_end()

-- option: liba-wasm-bigint
option("liba-wasm-bigint")
set_default(false)
set_showmenu(true)
set_category("liba")
set_description("Enable/Disable JavaScript BigInt")
option_end()

if get_config("liba-wasm") and is_plat("wasm") then
    target("ajs")
    set_kind("binary")
    add_files("src/**.cc")
    if not has_config("liba-wasm") then
        add_ldflags("-sWASM=0")
    end
    if not has_config("liba-wasm-async") then
        add_ldflags("-sWASM_ASYNC_COMPILATION=0")
    end
    if has_config("liba-wasm-bigint") then
        add_ldflags("-sWASM_BIGINT")
        add_defines("WASM_BIGINT")
    end
    set_filename("liba.js")
    add_syslinks("embind")
    set_targetdir(".")
    add_deps("a")
    target_end()
end
