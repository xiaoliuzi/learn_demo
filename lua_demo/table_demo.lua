a = {}  -- an empty table
for i=1,1000 do a[i] = i*2 end
print(a[9])   -->18
a["x"] = 10
print(a["x"]) -->10
print(a["y"]) --> nil
