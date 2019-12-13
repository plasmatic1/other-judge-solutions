def wa():
    print('REJECT')

def wam(x):
    # print(x)
    pass

def ac():
    print('HOTLINE')

PUNCS = list('!.?')
REQ = list(map(lambda x: x.lower(), ('I', 'he', 'she', 'they', 'it', 'this')))

s = input()

if len(s) == 0:
    wa()
else:
    words = s[:-1].split(' ')
    wwords = [word.lower() for word in words]

    if not s[0].isupper():
        wam('nuper')
        wa()
    elif sum([s.count(c) for c in PUNCS]) != 1:
        wam('puncs')
        wa()
    elif s[-1] not in PUNCS:
        wam('puncend')
        wa()
    elif len(words) <= 2:
        wam('wordc')
        wa()
    elif not any([word in wwords for word in REQ]):
        wam('reqword')
        wa()
    elif any([len(word) > 34 for word in words]):
        wam('wordlen')
        wa()
    else:
        ac()
