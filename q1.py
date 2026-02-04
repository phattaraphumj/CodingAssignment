s = input()
l = [int(x) for x in s.split()] #O(n) โดยที่ n คือจำนวนinput

l_max = l.copy() #O(n)
max_h = max(l) #O(n)

output = [""] * max_h # O(H) โดยที่ H คือ input ตัวที่มากที่สุด

current_h = max_h;
while current_h > 0:  #O(H)
    text = ""
    for i in range(len(l)):  # O(n)
        if l[i] == 0:
            text += " " * (l_max[i] * 2)  # O(H)
        else:
            padding = l_max[i] - l[i]
            text += " " * padding + "/" + " " * (l[i] * 2 - 2) + "\\" + " " * padding
            l[i] -= 1
    output[current_h - 1] = text
    current_h -= 1
#for loop(inner loop) : O(H*n)
#while loop : #O(H^2 * n)

for line in output: #O(H)
    print(line)

#Total time complexity O(H^2 * n)
