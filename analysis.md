# Closest Pair Algorithm Analysis

## Implementation Overview

We implemented the **O(n log n) divide-and-conquer algorithm** for finding the closest pair of points in the plane.  
Our work follows the method described in CLRS (Chapter 33.4), with a few choices made to balance clarity and efficiency.

### Main Design Choices
1. **Base Case Cutoff**  
   We experimented with different cutoff values for switching to brute force. A cutoff of **15 points** gave the best performance in our tests.

2. **Sorted Sequences**  
   - `pointsX`: points sorted by x-coordinate (y used as tie-breaker)  
   - `pointsY`: points sorted by y-coordinate (x used as tie-breaker)  
   These are maintained across recursive calls, so we only sort once at the top level.

3. **Strip Handling**  
   In the middle strip near the dividing line, we compare only points within the current minimum distance, and because the list is y-sorted we only check a few neighbors for each point.

4. **No Sorting Inside Recursion**  
   By sorting once at the top, each recursive level only does linear work, which keeps the overall runtime O(n log n).

---

## Data Structures and Recursion

We used `std::vector<Point>` to hold our data.  
At each recursion step:
1. Split the x-sorted list into left and right halves.  
2. Partition the y-sorted list into left and right (linear scan).  
3. Recurse on both halves, then check the strip for any closer pair.  

This design avoids unnecessary re-sorting and keeps the algorithm efficient.

---

## Base Case Threshold

### Testing
We tried different cutoff values on 10,000 points:
- 3 → 4.56 ms  
- 10 → 4.30 ms  
- **15 → 3.85 ms (best)**  
- 20 → 3.95 ms  

### Why 15 Works Best
- Reduces recursive overhead for small sets  
- Brute force is faster once sets are small enough  
- Keeps results correct while improving speed  

---

## Performance Results

We compared brute force and divide-and-conquer.  
We stopped reporting brute force once runtimes exceeded ~20 seconds.

| N          | Brute Force (ms) | Divide & Conquer (ms) |
|------------|------------------|------------------------|
| 1,000      | 0.488            | 0.249                 |
| 2,000      | 1.872            | 0.484                 |
| 4,000      | 7.008            | 1.017                 |
| 8,000      | 28.208           | 2.001                 |
| 16,000     | 113.891          | 4.375                 |
| 32,000     | —                | 9.384                 |
| 64,000     | —                | 18.392                |
| 128,000    | —                | 41.139                |
| 256,000    | —                | 85.893                |
| 512,000    | —                | 175.471               |
| 1,000,000  | —                | 342.231               |
| 2,000,000  | —                | 733.698               |
| 4,000,000  | —                | 1,493.73              |
| 8,000,000  | —                | 3,225.45              |
| 16,000,000 | —                | 6,876.82              |
| 32,000,000 | —                | 14,703.8              |

---

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

## Correctness

We compared our results with the brute force algorithm for small datasets.  
Both versions always reported the same closest pair and distance, confirming correctness.

---

## Conclusion

- Our divide-and-conquer algorithm is **correct** and runs in **O(n log n)** time.  
- Using a cutoff of **15 points** gave the best practical performance.  
- Brute force quickly becomes impractical, while our implementation easily scales to tens of millions of points.
