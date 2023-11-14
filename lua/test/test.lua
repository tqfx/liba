local test = {}
function test:r(...)
    local io_write_cache = {}
    local function io_write(indent, ...)
        if io_write_cache[tostring(...)] then
            io.write(indent .. "*" .. tostring(...) .. "\n")
        else
            io_write_cache[tostring(...)] = true
            if type(...) == "table" then
                for pos, val in pairs(...) do
                    if type(val) == "table" then
                        io.write(indent .. "[" .. pos .. "] => " .. tostring(...) .. " {\n")
                        io_write(indent .. string.rep(" ", string.len(pos) + 8), val)
                        io.write(indent .. string.rep(" ", string.len(pos) + 6) .. "}\n")
                    elseif type(val) == "string" then
                        io.write(indent .. "[" .. pos .. '] => "' .. val .. '"\n')
                    else
                        io.write(indent .. "[" .. pos .. "] => " .. tostring(val) .. "\n")
                    end
                end
            else
                io.write(indent .. tostring(...) .. "\n")
            end
        end
    end
    if type(...) == "table" then
        io.write(tostring(...) .. " {\n")
        io_write("  ", ...)
        io.write("}\n")
    else
        io_write("  ", ...)
    end
end
function test:w(...)
    io.write(...)
    io.write('\n')
end
return test
