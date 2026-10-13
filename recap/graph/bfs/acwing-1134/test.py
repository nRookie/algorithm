from pathlib import Path
import subprocess

jar = Path(__file__).resolve().parent / '.build' / '1134.jar'
cases = [
    (5, [(1,2),(1,3),(2,4),(3,4),(4,5)], [1,1,1,2,2]),
    (1, [(1,1)], [1]),
    (3, [(1,2)], [1,1,0]),
    (3, [(1,2),(1,2),(2,2),(2,3)], [1,2,2]),
    (3, [(1,2),(2,3),(1,3)], [1,1,1]),
    (3, [(1,2)] * 100003 + [(2,3)], [1,0,0]),
    (21, [(u,u+1) for u in range(1,21) for _ in range(2)],
     [pow(2, i, 100003) for i in range(21)]),
]
for n, edges, expected in cases:
    data = f'{n} {len(edges)}\n' + '\n'.join(f'{a} {b}' for a,b in edges)
    result = subprocess.run(['java','-jar',str(jar)], input=data, text=True,
                            capture_output=True, check=True, timeout=30)
    actual = list(map(int, result.stdout.split()))
    assert actual == expected, (actual, expected)
print(f'Passed {len(cases)} console cases, including loops, parallel edges, and modulo wraparound.')
