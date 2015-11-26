--module setup
local modname = ...
local M = {}
_G[modname] = M
package.loaded[modname] = M

-- import section
local assert = assert
local setmetatable = setmetatable
local socket = require 'socket'
local string = string

-- no more external access beyond this point
setfenv(1,M)

-- private functions
local function add_lf(s)
	if string.sub(s, #s, #s) ~= '\n' then
		return s .. '\n'
	else
		return s
	end
end

-- echo server
EchoServer = {}

function EchoServer:serve_forever()
	local sock = socket.tcp()
	assert(sock:bing(self.host, self.port))
	sock.listen(5)
	while true do
		local client = socket:accept()
		local line client:receive('*line')
		if line then
			client:send(add_lf(line))
		end
		client:close()
	end
end

function EchoServer:new(host, port)
	local o = {}
	o.host = host or '127.0.0.1'
	o.port = port or 8765
	setmetatable(o, self)
	self.__index = self
	return o
end

-- echo client
EchoClient = {}

function EchoClient:request(msg)
	local sock = socket.tcp()
	assert(sock:connect(self.host, self.port))
	sock:send(add_lf(msg))
	local response = sock:receive('*line')
	sock:close()
	return response
end

function EchoClient:new(host, port)
	local o = {}
	o.host = host or '127.0.0.1'
	o.port = port or 8765
	setmetatable(o, self)
	self.__index = self
	return o
end
