local test = {}
function test:r(...)
  local print_r_cache = {}
  local function print_r(indent, ...)
    if print_r_cache[tostring(...)] then
      print(indent .. "*" .. tostring(...))
    else
      print_r_cache[tostring(...)] = true
      if type(...) == "table" then
        for pos, val in pairs(...) do
          if type(val) == "table" then
            print(indent .. "[" .. pos .. "] => " .. tostring(...) .. " {")
            print_r(indent .. string.rep(" ", string.len(pos) + 8), val)
            print(indent .. string.rep(" ", string.len(pos) + 6) .. "}")
          elseif type(val) == "string" then
            print(indent .. "[" .. pos .. '] => "' .. val .. '"')
          else
            print(indent .. "[" .. pos .. "] => " .. tostring(val))
          end
        end
      else
        print(indent .. tostring(...))
      end
    end
  end
  if type(...) == "table" then
    print(tostring(...) .. " {")
    print_r("  ", ...)
    print("}")
  else
    print_r("  ", ...)
  end
end
function test:p(...)
  print(...)
end
return test
