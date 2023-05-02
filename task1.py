import itertools

def gen_perms(s, t):
    chars = ['1'] * s + ['2'] * t
    for p in itertools.permutations(chars):
        yield ''.join(p)

count = int(0)
for permutation in gen_perms(3, 2):
    print(permutation)
    count += 1

print(count)
