/**
 * @file        convexhull.h
 * @description Declaration of methods used for computing convex hull using
 *              Graham scan algorithm
 *              https://en.wikipedia.org/wiki/Graham_scan
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 * 
 * THIS FILE WILL NOT BE SUBMITTED
**/

#ifndef _CONVEXHULL_H_
#define _CONVEXHULL_H_

#include <cmath>
#include <vector>
#include "stack.h"

using namespace std;

/**
 * Uses a sorting algorithm of your choice(must be fully implemented by you)
 * to sort the points in v to satisfy the following criteria:
 * 1. v[0] must contain the point with the smallest y-coordinate.
 *      If multiple points have the same smallest y-coordinate, v[0]
 *      must contain the one among those with the smallest x-coordinate.
 * 2. The remaining indices i contain the points, sorted in increasing order
 *      by the angle that the point forms with v[0] and the x-axis. THat is,
 * 	one of the legs of the angle is represened by the line through v[0] and
 *	v[i], and the other is the x-axis.
 * NOTE: "smallest" y-coordinate is actually closest to the TOP of a PNG image.
**/
void SortByAngle(vector<pair<double, double>>& v);

/**
 * Determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
**/
bool CCW(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3);

/**
 * Returns a vector of points representing the convex hull of v
 * if c is the vector representing the convex hull, then c[k], c[k+1]
 * is an edge in the convex hull, for all k in 0 to n-1, where n is the
 * number of points in the hull. c[n-1],c[0] is also an edge in the hull.
 * Note that only the endpoints of a colinear sequence will belong in the hull.
 * The returned vector should be a subset of v
 * Input: v - a vector of points in arbitrary order
**/
vector<pair<double, double>> GetConvexHull(vector<pair<double, double>>& v);

#endif
