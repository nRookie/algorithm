import subprocess

cases = [
    ("4 4\n1 2 10\n1 3 1\n2 4 1\n3 2 1\n", "3"),
    ("3 3\n1 2 5\n1 3 2\n2 3 -7\n", "-2"),
    ("3 1\n2 3 -5\n", "impossible"),
    ("1 1\n1 1 0\n", "0"),
    ("3 4\n1 2 8\n1 2 2\n2 2 0\n2 3 -1\n", "1"),
    ("3 3\n1 2 2\n2 3 -1\n3 2 1\n", "1"),
]
for data, expected in cases:
    result = subprocess.run(["java", "-jar", ".build/851.jar"],
                            input=data, text=True, capture_output=True,
                            check=True, timeout=10)
    assert result.stdout.strip() == expected, (data, result.stdout, expected)
print(f"{len(cases)} checks passed")
