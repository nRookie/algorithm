def solve(N, K, balls):
    # Initialize variables to store the maximum total value and the last color seen
    max_total_value = 0
    
    # Iterate through all possible combinations of K balls to remove
    for i in range(N - K + 1):
        # Create a copy of the list of balls to work with
        remaining_balls = balls[:]
        
        # Remove the K balls starting from index i
        removed = remaining_balls[i:i+K]
        del remaining_balls[i:i+K]
        
        # Check if the remaining balls satisfy the condition of no two adjacent balls having the same color
        valid = True
        for j in range(len(remaining_balls) - 1):
            if remaining_balls[j][0] == remaining_balls[j+1][0]:
                valid = False
                break
        
        # Calculate the total value of the remaining balls if the condition is satisfied
        if valid:
            total_value = sum(val for _, val in remaining_balls)
            max_total_value = max(max_total_value, total_value)
    
    # If no valid arrangement is found, return -1
    if max_total_value == 0:
        return -1
    else:
        return max_total_value

# Read input
N, K = map(int, input().split())
balls = [tuple(map(int, input().split())) for _ in range(N)]

# Call the solve function and print the result
result = solve(N, K, balls)
print(result)
