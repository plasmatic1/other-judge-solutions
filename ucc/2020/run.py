import sys
from subprocess import Popen, PIPE

prob = int(sys.argv[1]) if len(sys.argv) > 1 else 4
lang = 'py'
cc = 4

def runpy(path, caseno):
    p = Popen(['python', path], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    with open(f'ucc/{prob}-{caseno}-in') as f:
        inp = f.read()
    return p.communicate(bytes(inp, 'ascii'), 2)


path = f'ucc/{prob}.{lang}'
run = runpy
for i in range(cc):
    o, e = map(lambda x: str(x, 'utf8'), run(path, i))
    print(f'Case #{i}: {o}, Err: {e}')
