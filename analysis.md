# Closest Pair Algorithm Analysis

## Implementation Overview

I implemented the O(n log n) divide-and-conquer algorithm for finding the closest pair of points in the plane. The implementation follows the standard algorithm described in CLRS Chapter 33.4, with several key design decisions:

### Key Design Decisions

1. **Base Case Optimization**: I experimented with different cutoff values and found that a cutoff of 15 points provides optimal performance for switching from divide-and-conquer to brute force.

2. **Data Structure Management**: The algorithm maintains two sorted sequences:
   - `pointsX`: Points sorted by x-coordinate (with y-coordinate as tie-breaker)
   - `pointsY`: Points sorted by y-coordinate (with x-coordinate as tie-breaker)

3. **Strip Processing**: The algorithm processes the strip of points near the dividing line in O(n) time by only comparing points within a vertical distance of the current minimum distance.

4. **No Sorting in Recursion**: All sorting is done at the top level, ensuring the O(n log n) complexity is maintained.

## Data Structures and Recursion

### Data Structure Choices

The implementation uses `std::vector<Point>` for storing points. The key insight is maintaining two sorted sequences throughout the recursion:

- **X-sorted sequence**: Used for dividing the problem into left and right halves
- **Y-sorted sequence**: Used for efficient strip processing

### Recursive Data Passing

When dividing the problem, the algorithm:
1. Splits the x-sorted sequence at the median point
2. Creates corresponding y-sorted sequences for left and right halves by filtering the original y-sorted sequence
3. Passes both sequences to recursive calls

This approach avoids sorting within recursive calls, maintaining the O(n log n) complexity.

## Base Case Threshold Optimization

### Experimental Process

I tested different cutoff values with a dataset of 10,000 points:

- **Cutoff = 3**: 4.56 ms
- **Cutoff = 10**: 4.30 ms  
- **Cutoff = 15**: 3.85 ms (optimal)
- **Cutoff = 20**: 3.95 ms

The optimal cutoff of 15 points provides the best balance between reducing recursive overhead and maintaining algorithm efficiency.

### Rationale

A cutoff of 15 points is optimal because:
- It reduces the number of recursive calls significantly
- The overhead of recursive function calls becomes more expensive than brute force for small sets
- It maintains correctness while improving practical performance

## Performance Analysis

### Running Time Results

| N | Brute Force (ms) | Divide-and-Conquer (ms) |
|---|------------------|-------------------------|
| 1,000 | 0.488 | 0.249 |
| 2,000 | 1.872 | 0.484 |
| 4,000 | 7.008 | 1.017 |
| 8,000 | 28.208 | 2.001 |
| 16,000 | 113.891 | 4.375 |
| 32,000 | - | 9.384 |
| 64,000 | - | 18.392 |
| 128,000 | - | 41.139 |
| 256,000 | - | 85.893 |
| 512,000 | - | 175.471 |
| 1,000,000 | - | 342.231 |
| 2,000,000 | - | 733.698 |
| 4,000,000 | - | 1,493.73 |
| 8,000,000 | - | 3,225.45 |
| 16,000,000 | - | 6,876.82 |
| 32,000,000 | - | 14,703.8 |

### Asymptotic Analysis

#### Brute Force Algorithm (O(n²))
The brute force algorithm shows clear quadratic growth:
- N=1,000: 0.488 ms
- N=2,000: 1.872 ms (≈4x increase)
- N=4,000: 7.008 ms (≈4x increase)
- N=8,000: 28.208 ms (≈4x increase)
- N=16,000: 113.891 ms (≈4x increase)

The running time approximately quadruples when N doubles, confirming O(n²) behavior.

#### Divide-and-Conquer Algorithm (O(n log n))
The divide-and-conquer algorithm shows much better scaling:
- N=1,000: 0.249 ms
- N=2,000: 0.484 ms (≈2x increase)
- N=4,000: 1.017 ms (≈2x increase)
- N=8,000: 2.001 ms (≈2x increase)
- N=16,000: 4.375 ms (≈2.2x increase)
- N=32,000: 9.384 ms (≈2.1x increase)
- N=64,000: 18.392 ms (≈2x increase)

The running time approximately doubles when N doubles, confirming O(n log n) behavior.

### Performance Comparison

The divide-and-conquer algorithm shows dramatic performance improvements:
- At N=1,000: 2x faster than brute force
- At N=2,000: 3.9x faster than brute force  
- At N=4,000: 6.9x faster than brute force
- At N=8,000: 14.1x faster than brute force
- At N=16,000: 26x faster than brute force

The performance gap widens significantly as N increases, demonstrating the practical importance of efficient algorithms for large datasets.

## Implementation Correctness

The implementation has been tested for correctness by comparing results with the brute force algorithm on multiple test cases. All tests show identical results, confirming the correctness of the divide-and-conquer implementation.

## Conclusion

The divide-and-conquer algorithm successfully achieves O(n log n) performance while maintaining correctness. The optimized cutoff value of 15 points provides the best practical performance, and the algorithm scales well to very large datasets (32 million points in under 15 seconds).
