import sys
input = sys.stdin.readline
lines_num = int(input())
teams = []
times = 0
for i in range(lines_num):
  input_1 = input().split()
  name = input_1[0]
  input_1.pop(0)
  teams.append((name,sum([int(x) for x in input_1])))

ll = sorted(teams,key=lambda x:(-x[1],x[0]))
for k,v in ll:
  if times < 2:
    print("{} {}".format(k,v))
    times += 1