from collections import Counter

def main():
    N = int(input())
    A = [int(input()) for _ in range(N)]
    freq = Counter(A)
    
    total = 0

    # Count triples for A_k = 1 separately
    if 1 in freq:
        total += freq[1] ** 3  # All three numbers are 1
    
    # Count triples for A_k != 1
    for Ak in freq:
        if Ak != 1:
            # Each A_k pairs with 1 (if present) to form valid triples
            if 1 in freq:
                total += freq[Ak] * freq[1] * (freq[1] - 1) * 2  # A_i or A_j is 1, the other is A_k
                total += freq[Ak] * (freq[Ak] - 1) * freq[1]  # Both A_i and A_j are A_k, paired with 1
                
    print(total)

if __name__ == "__main__":
    main()
