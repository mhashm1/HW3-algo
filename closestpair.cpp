#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
using namespace std;

// For convenience, we provide a brute-force implementation that can be applied
// to any portion of a larger sequence by providing start and stop iterators.
template <typename IT>
Outcome bruteUtility(IT start, IT stop) {
    IT second = start;
    ++second;
    Outcome best(*start, *second, distSquared(*start, *second));
    for (IT k=start; k != stop; ++k)
        for (IT j=start; j != k; ++j) {
            long long temp = distSquared(*j, *k);
            if (temp < best.dsq) {
                best = Outcome(*j, *k, temp);
            }
        }
    return best;
}

// The public facing brute-force function that takes a vector as input
Outcome brute(const vector<Point>& data) {
    return bruteUtility(data.begin(), data.end());
}


/*------------------------------------------------------------
| Here we define a cutoff value at which the divide-and-conquer
| approach should resort to a base-case in which brute-force is applied.
| You are free to change this cutoff to optimize, but please make sure
| that the logic of your implementation rely on this defined CUTOFF constant.
--------------------------------------------------------------*/
#define CUTOFF 15         // you may change this, but please 


// Helper function for the divide-and-conquer algorithm
Outcome closestPairRecursive(vector<Point>& pointsX, vector<Point>& pointsY) {
    int n = pointsX.size();
    
    // Base case: use brute force for small sets
    if (n <= CUTOFF) {
        return bruteUtility(pointsX.begin(), pointsX.end());
    }
    
    // Divide: split points by x-coordinate
    int mid = n / 2;
    Point midPoint = pointsX[mid];
    
    // Create left and right halves for x-sorted points
    vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
    vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
    
    // Create y-sorted sequences for left and right halves
    vector<Point> leftY, rightY;
    for (const Point& p : pointsY) {
        if (compareByX(p, midPoint) || (p.x == midPoint.x && p.y == midPoint.y)) {
            leftY.push_back(p);
        } else {
            rightY.push_back(p);
        }
    }
    
    // Recursively find closest pairs in left and right halves
    Outcome leftResult = closestPairRecursive(leftX, leftY);
    Outcome rightResult = closestPairRecursive(rightX, rightY);
    
    // Find the minimum distance from both sides
    Outcome minResult = (leftResult.dsq < rightResult.dsq) ? leftResult : rightResult;
    long long minDistSq = minResult.dsq;
    
    // Create strip of points close to the dividing line
    vector<Point> strip;
    for (const Point& p : pointsY) {
        long long dx = p.x - midPoint.x;
        if (dx * dx < minDistSq) {
            strip.push_back(p);
        }
    }
    
    // Check for closer pairs in the strip
    for (int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < minDistSq; ++j) {
            long long distSq = distSquared(strip[i], strip[j]);
            if (distSq < minDistSq) {
                minDistSq = distSq;
                minResult = Outcome(strip[i], strip[j], distSq);
            }
        }
    }
    
    return minResult;
}

// The student's implementation of the O(n log n) divide-and-conquer approach
Outcome efficient(const vector<Point>& data) {
    if (data.size() < 2) {
        return Outcome();
    }
    
    // Create copies for sorting
    vector<Point> pointsX = data;
    vector<Point> pointsY = data;
    
    // Sort by x-coordinate and y-coordinate
    sort(pointsX.begin(), pointsX.end(), compareByX);
    sort(pointsY.begin(), pointsY.end(), compareByY);
    
    return closestPairRecursive(pointsX, pointsY);
}

// An extra credit algorithm
Outcome extra(const vector<Point>& data) {
    srand(time(NULL));  // re-seeding random number generator
    return Outcome();
}
