--[[
a = {}
for i=1,10 do
a[i] = io.read()
print(a[i])
end
--]]
i = 10;
j = "10";
k = "+10";
a = {}
a[i] = "one value"
a[j] = "another value"
a[k] = "yet another value"
print(a[j])
print(a[k])
print(a[tonumber(j)])
print(a[tonumber(k)])
