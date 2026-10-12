"""Exercise the actual console program, including Scanner and output."""
from pathlib import Path
import subprocess

jar = Path(__file__).resolve().parent / '.build' / '104.jar'
cases = [
    ('Official sample', '4\n6 2 9 1\n', 12),
    ('Singleton', '1\n40000\n', 0),
    ('Duplicates', '4\n7 7 7 7\n', 0),
    ('Odd count', '3\n100 1 2\n', 99),
    ('Whitespace', '4\n\n6\t2\n9   1', 12),
    ('Maximum distance', '100000\n' + '0 ' * 50000 + '40000 ' * 50000, 2000000000),
]
for name, data, expected in cases:
    result = subprocess.run(
        ['java', '-jar', str(jar)], input=data, text=True,
        capture_output=True, timeout=30, check=True,
    )
    assert result.stdout.strip() == str(expected), (name, result.stdout, expected)
    print(f'PASS: {name}')
print(f'{len(cases)}/{len(cases)} cases passed.')
