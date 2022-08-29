# ./punched-cards.yml

def gen(c):
    return list('+' + '-+' * c)

def genmid(c):
    return list('|' + '.|' * c)

for _ in range(int(input())):
    r, c = map(int, input().split())
    grid = [gen(c)]
    for i in range(r):
        grid.append(genmid(c))
        grid.append(gen(c))

    grid[0][0] = grid[0][1] = grid[1][0] = '.'

    print(f'Case #{_+1}:')
    for l in grid:
        print(''.join(l))


