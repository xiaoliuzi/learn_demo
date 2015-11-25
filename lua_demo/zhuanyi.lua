print("one line\nnext line\n\"in quotes\", 'in quotes'")
print('a backslash inside quotes: \'\\\'')
print("a simpler way: '\\'")

line = io.read()
n = tonumber(line)
if n == nil then
	error(line .. " is not a valid number")
	else
	print(n*2)
	end
