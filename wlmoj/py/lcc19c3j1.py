import sys
# input = sys.stdin.readline
coord = {}
coord["x"],coord["y"] = map(int, input().split())
rotation = int(input())
if rotation == 90:
  print(-coord["y"],coord["x"])
elif rotation == 180:
  print(-coord["x"],-coord["y"])
elif rotation == 270:
  print(coord["y"], -coord["x"])
else:
  print(coord['x'], coord['y'])