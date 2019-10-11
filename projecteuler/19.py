import datetime

a = datetime.datetime(1901, 1, 1)
b = datetime.datetime(2000, 12, 31)
plusDay = datetime.timedelta(days=1)
delta = b - a

cnt = 0
while a <= b:
    # print(a, a.weekday())
    cnt += a.weekday() == 6 and a.day == 1
    a += plusDay
print(cnt)