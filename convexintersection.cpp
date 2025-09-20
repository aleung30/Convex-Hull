/**
 * @file        convexintersection.cpp
 * @description Implementation of methods used for computing convex intersection using
 *              Sutherland-Hodgman algorithm
 *              https://en.wikipedia.org/wiki/Sutherland�Hodgman_algorithm
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE MUST BE SUBMITTED
 **/

#include "convexintersection.h"

/***************************************************
 * IF YOU WISH TO DEFINE YOUR OWN CUSTOM FUNCTIONS, *
 * ADD THEM HERE                                    *
 ***************************************************/

double cross(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3)
{
    return (p2.first - p1.first) * (p3.second - p1.second) * (p2.second - p1.second) * (p3.first - p1.first);
}

double Slope(pair<double, double> p1, pair<double, double> p2)
{
    return (p2.second - p1.second) / (p2.first - p1.first);
}

/**
 * Determines whether a point p1 is inside or outside
 * of a line segment defined by sp1 and sp2
 * sp1 and sp2 should be consistently provided
 * from the convex hull algorithm such that the edges
 * are listed in a CCW direction
 * p1 belongs to the subject polygon
 * sp1 and sp2 belong to the clipping polygon
 **/
bool Inside(pair<double, double> p1, pair<double, double> sp1, pair<double, double> sp2)
{
    return cross(sp1, sp2, p1) > 0;
}

/**
 * computes the point of intersection between the line segment
 * defined by s1 and s2, and the infinite line defined by
 * i1 and i2.
 * Assume that this will only be called when the intersection exists.
 **/
pair<double, double> ComputeIntersection(pair<double, double> s1, pair<double, double> s2, pair<double, double> i1, pair<double, double> i2)
{
    pair<double, double> intersect;
    if (s2.first == s1.first)
    {
        // Case I: line s1-s2 is vertical
        intersect.first = s1.first;
        double mi = Slope(i1, i2);
        double bi = i1.second - (mi * i1.first);
        intersect.second = mi * intersect.first + bi;
    }
    else if (i2.first == i1.first)
    {
        // Case II: line i1-i2 is vertical
        intersect.first = i1.first;
        double ms = Slope(s1, s2);
        double bs = s1.second - (ms * s1.first);
        intersect.second = ms * intersect.first + bs;
    }
    else
    {
        // Case III: both lines are not vertical
        double ms = Slope(s1, s2);
        double bs = s1.second - (ms * s1.first);
        double mi = Slope(i1, i2);
        double bi = i1.second - (mi * i1.first);

        intersect.first = (bi - bs) / (ms - mi);
        intersect.second = ms * intersect.first + bs;
    }
    return intersect;
}

/**
 * Returns a vector containing a sequence of points defining
 * the intersection of two convex polygons poly1 and poly2
 * Inputs: poly1 and poly2 - sequences of points defining the
 *                           borders of convex polygons
 **/
vector<pair<double, double>> GetConvexIntersection(vector<pair<double, double>> &poly1, vector<pair<double, double>> &poly2)
{
    vector<pair<double, double>> isect;

    /* Add your code below */

    return isect;
}
