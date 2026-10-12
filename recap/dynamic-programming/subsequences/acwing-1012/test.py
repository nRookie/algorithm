from pathlib import Path
import random
import subprocess

jar = Path(__file__).resolve().parent / '.build' / '1012.jar'

def baseline(pairs):
    best = 0
    for mask in range(1 << len(pairs)):
        chosen = [p for i, p in enumerate(pairs) if mask & (1 << i)]
        if all((a[0]-b[0]) * (a[1]-b[1]) > 0
               for i, a in enumerate(chosen) for b in chosen[:i]):
            best = max(best, len(chosen))
    return best

cases = [
    ([(3,2), (1,3), (4,4), (2,1)], 3),
    ([(0,10000)], 1),
    ([(1,3), (2,2), (3,1)], 1),
    ([(3,3), (1,1), (2,2)], 3),
    ([(i,i) for i in range(5000)], 5000),
]
rng = random.Random(1012)
for _ in range(20):
    n = rng.randint(1, 9)
    pairs = list(zip(rng.sample(range(30), n), rng.sample(range(30), n)))
    cases.append((pairs, baseline(pairs)))
for pairs, expected in cases:
    data = str(len(pairs)) + '\n' + '\n'.join(f'{a} {b}' for a, b in pairs)
    result = subprocess.run(['java', '-jar', str(jar)], input=data, text=True,
                            capture_output=True, check=True, timeout=30)
    assert result.stdout.strip() == str(expected), (pairs, expected, result.stdout)
print('Passed 5 fixed cases and 20 exhaustive-baseline comparisons.')
