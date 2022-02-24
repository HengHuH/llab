
local lgn = {}

function lgn.exe(name)
    local target = {}

    return target
end

local function gen_build_ninja(target)
    local content = "# This file is used to build llab."
    content = content .. "\n" .. "# It is generated by configure.lua."

    return content
end

local function write_file(path, content)
    local f = io.open(path, "w")
    f:write(content)
    f:close()
end

local function main()
    local llab = lgn.exe("llab")

    local content = gen_build_ninja(llab)
    write_file("./out/build.ninja", content)
end

main()