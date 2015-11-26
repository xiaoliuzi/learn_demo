
local host, port = "127.0.0.1", 8880
local socket = require("socket")

--local server = assert(sokcet.bind("*", 8880))

--local ip, port = server:getsockname()
local tcp = assert(socket.tcp())

print("please telnet to localhost on port " .. port)
print("After connecting, you have 600s to enter a line to be echoed")

tcp:connect(host,port)
tcp:send("hello world\n")

while true do
        local s, status, partial = tcp:receive()
        print(s or partial)
        if status == "closed" then break end
end
tcp:close()

