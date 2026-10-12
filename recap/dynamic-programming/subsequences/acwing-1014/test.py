from pathlib import Path
import subprocess

jar = Path(__file__).resolve().parent / '.build' / '1014.jar'
cases = [
    ([186, 186, 150, 200, 160, 130, 197, 220], 4),
    ([1, 2, 3, 4], 4),
    ([4, 3, 2, 1], 4),
    ([5, 5, 5], 1),
    ([1, 4, 2, 5, 3], 4),
    ([1, 3, 2], 3),
    ([1, 2], 2),
    ([2, 1, 2], 2),
    (list(range(1000)), 1000),
]
for heights, expected in cases:
    data = f'{len(heights)}\n' + ' '.join(map(str, heights)) + '\n'
    result = subprocess.run(['java', '-jar', str(jar)], input=data,
                            text=True, capture_output=True, check=True, timeout=30)
    assert result.stdout.strip() == str(expected), (heights, expected, result.stdout)
print(f'Passed {len(cases)} console cases.')
