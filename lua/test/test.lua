local m = {}
m.indent = "    "
function m.dir(...)
    local io_write_cache = {}
    local function io_write(indent, x)
        local str = tostring(x)
        if io_write_cache[str] then
            io.write(indent, "*", str, "\n")
        else
            io_write_cache[str] = true
            if type(x) == "table" then
                for idx, val in pairs(x) do
                    if type(idx) ~= "string" then
                        idx = "[" .. tostring(idx) .. "]"
                    elseif idx:find('"') then
                        idx = '["' .. idx:gsub('"', '\\"') .. '"]'
                    end
                    if type(val) == "table" then
                        io.write(indent, idx, " = ", str, "\n")
                        io.write(indent, "{\n")
                        io_write(indent .. m.indent, val)
                        io.write(indent, "}\n")
                    else
                        if type(val) ~= "string" then
                            val = tostring(val)
                        else
                            val = '"' .. val:gsub('"', '\\"') .. '"'
                        end
                        io.write(indent, idx, " = ", val, ",\n")
                    end
                end
            else
                io.write(indent, str, "\n")
            end
        end
    end
    for _, x in ipairs({ ... }) do
        if type(x) == "table" then
            io.write(tostring(x), "\n")
            io.write("{\n")
            io_write(m.indent, x)
            io.write("}\n")
        else
            io_write("", x)
        end
    end
end

function m.log(...)
    for i, v in ipairs({ ... }) do
        if i > 1 then
            io.write(" ")
        end
        io.write(tostring(v))
    end
    io.write("\n")
end

function m.fmt(...)
    io.write(string.format(...), "\n")
end

return m
