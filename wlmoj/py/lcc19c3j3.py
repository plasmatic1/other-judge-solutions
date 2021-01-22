import sys
input = sys.stdin.readline

lines_num = int(input())
lines = [input().split() for x in range(lines_num)]
lines2 = sum(lines, [])
minecraft = []
legal_lines = 0

for _ in lines:
  minecraft = []
  mine = 0
  mine = False
  craft = False
  for i in _:
    if i == "mine":
      mine = True
      minecraft.append(i)
      mine += 1
    elif i == "craft":
      craft = True
      minecraft.append(i)
  if (mine and craft) and minecraft[0] == "mine":
    legal_lines+=1
    
ca = lines2.count('mine')
cb = lines2.count('craft')
wk = ca >= len(lines2) - ca - cb

if legal_lines == len(lines) and wk:
  print("PROFIT")
else:
  print("cri")