/**
 * @file convexhull.cpp
 * @description Implementation of methods used for computing convex hull using
 *              Graham scan algorithm
 *              https://en.wikipedia.org/wiki/Graham_scan
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE MUST BE SUBMITTED
 **/

#include "convexhull.h"
#include <algorithm>

/***************************************************
 * IF YOU WISH TO DEFINE YOUR OWN CUSTOM FUNCTIONS, *
 * ADD THEM HERE                                    *
 ***************************************************/

/**
 *
 */

bool straight(pair<double, double> piv, pair<double, double> p1, pair<double, double> p2)
{
    return (p1.second - piv.second) * (p2.first - p1.first) == (piv.first - p1.first) * (p2.second - p1.second);
}

bool between(pair<double, double> piv, pair<double, double> p1, pair<double, double> p2)
{
    return min(piv.first, p1, first) <= p2.first && p2.first <= max(piv.first, p2.first) &&
           min(piv.second, p1.second) <= p2.second &&
           p2.second <= max(piv.second, p1.second);
}

int distance(pair<double, double> p1, pair<double, double> p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

int polar(pair<double, double> piv, pair<double, double> p1, pair<double, double> p2)
{
    bool a = p1.first - piv.first >= 0;
    bool b = p2.first - piv.first >= 0;
    if (a && !b)
    {
        return -1;
    }
    if (!a && b)
    {
        return 1;
    }

    if (CCW(piv, p1, p2))
    {
        return -1;
    }
    if (CCW(piv, p2, p1))
    {
        return 1;
    }
    int distance1 = distance(piv, p1);
    int distance2 = distance(piv, p2);

    if (distance1 < distance2)
    {
        return -1;
    }
    else if (distance1 > distance2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
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
void SortByAngle(vector<pair<double, double>> &v)
{
    int min = 0;
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i].second < v[min].second || (v[i].second == v[min].second && v[i].first < v[min].first))
        {
            min = i;
        }
    }
    swap(v[0], v[min]);
    pair<double, double> piv = v[0];

    sort(v.begin() + 1, v.end(), [piv](pair<double, double> p1, pair<double, double> p2)
         { return polar(piv, p1, p2) < 0; });
}

/**
 * Determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
 **/
bool CCW(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3)
{
    int path = (p2.second - p1.second) * (p3.first - p2.first) - (p2.first - p1.first) * (p3.second - p2.second);
    return path > 0;
}

/**
 * Returns a vector of points representing the convex hull of v
 * if c is the vector representing the convex hull, then c[k], c[k+1]
 * is an edge in the convex hull, for all k in 0 to n-1, where n is the
 * number of points in the hull. c[n-1],c[0] is also an edge in the hull.
 * Note that only the endpoints of a colinear sequence will belong in the hull.
 * The returned vector should be a subset of v
 * Input: v - a vector of points in arbitrary order
 **/
vector<pair<double, double>> GetConvexHull(vector<pair<double, double>> &v)
{
    vector<pair<double, double>> hull;
    stack<pair<double, double>> stack;

    if (v.size() < 3)
    {
        return hull;
    }

    SortByAngle(v);
    stack.Push(v[0]);
    stack.Push(v[1]);

    for (int i = 2; i < v.size(); i++)
    {
        while (stack.Size() >= 2)
        {
            pair<double, double> a = stack.Peek();
            stack.Pop();
            pair<double, double> b = stack.Peek();

            if (CCW(a, b, v[i]))
            {
                stack.Push(b);
                break;
            }
        }
        stack.Push(v[i]);
    }

    while (!stack.IsEmpty())
    {

        hull.push_back(stack.Peek());
        stack.Pop();
    }
    reverse(hull.begin(), hull.end());
    return hull;
}
