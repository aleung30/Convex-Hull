/**
 * @file        convexintersection.h
 * @description Declaration of methods used for computing convex intersection using
 *              Sutherland-Hodgman algorithm
 *              https://en.wikipedia.org/wiki/Sutherland–Hodgman_algorithm
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#ifndef _CONVEXINTERSECTION_H_
#define _CONVEXINTERSECTION_H_

#include <cmath>
#include <vector>

using namespace std;

/**
 * Determines whether a point p1 is inside or outside
 * of a line segment defined by sp1 and sp2
 * sp1 and sp2 should be consistently provided
 * from the convex hull algorithm such that the edges
 * are listed in a CCW direction
 * p1 belongs to the subject polygon
 * sp1 and sp2 belong to the clipping polygon
**/
bool Inside(pair<double, double> p1, pair<double, double> sp1, pair<double, double> sp2);

/**
 * computes the point of intersection between the line segment
 * defined by s1 and s2, and the infinite line defined by
 * i1 and i2.
 * Assume that this will only be called when the intersection exists.
**/
pair<double, double> ComputeIntersection(pair<double, double> s1, pair<double, double> s2, pair<double, double> i1, pair<double, double> i2);

/**
 * Returns a vector containing a sequence of points defining
 * the intersection of two convex polygons poly1 and poly2
 * Inputs: poly1 and poly2 - sequences of points defining the
 *                           borders of convex polygons
**/
vector<pair<double, double>> GetConvexIntersection(vector<pair<double, double>>& poly1, vector<pair<double, double>>& poly2);

#endif