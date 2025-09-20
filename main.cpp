/**
 * @file        main.cpp
 * @description Partial test of PA2 classes
 *              Reads Point data from external files
 *              Produces PNG images of the point sets
 *              and their convex hulls and intersections
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "stack.h"
#include "convexhull.h"
#include "convexintersection.h"
#include "drawingio.h"

using namespace cs221util;
using namespace std;

// Declaration of testing support functions

/**
 * Tests basic Stack functions
**/
void TestStackBasic();

/**
 * Returns a point representing 20 pixels more than
 * the maximum x and y coordinates found in the provided vector
 * Used for determining output PNG dimensions
**/
pair<double, double> GetDimension(vector<pair<double, double>>& v);

/**
 * Manages the convex hull generation
 * @param infilename input file with point data in space-delimited format as x y
 * @param outfilename name of output PNG
**/
void ConvexHullFromFile(string infilename, string outfilename);

/**
 * Manages multiple convex hull and intersection generation
 * @param infile1 input file with point data, set 1
 * @param infile2 input file with point data, set 2
 * @param outfilename name of output PNG
**/
void IntersectionFromFile(string infile1, string infile2, string outfilename);

/**
 * Initializes a PNG to all white pixels
**/
void InitializePNG(PNG& im);

int main()
{
    cout << "Testing basic stack functions... " << endl;
    TestStackBasic();
    cout << "Stack test complete." << endl;

    ConvexHullFromFile("points1.txt", "images-output/out-hull_1.png");
    ConvexHullFromFile("points2.txt", "images-output/out-hull_2.png");
    ConvexHullFromFile("points3.txt", "images-output/out-hull_3.png");

    cout << "Convex hulls produced." << endl;

    IntersectionFromFile("dept_1a.txt", "dept_1b.txt", "images-output/out-intersection_1.png");
    IntersectionFromFile("dept_2a.txt", "dept_2b.txt", "images-output/out-intersection_2.png");
    IntersectionFromFile("dept_3a.txt", "dept_3b.txt", "images-output/out-intersection_3.png");

    cout << "Convex intersections produced." << endl;

    return 0;
}

/**
 * Tests basic Stack functions
**/
void TestStackBasic() {
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;

    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.Push(i);
    }

    while (!intStack.IsEmpty()) {
        result.push_back(intStack.Pop());
    }

    bool vecmatch = (result == expected);
    if (vecmatch) {
        cout << "Stack basic functions passed." << endl;
    }
    else {
        cout << "Stack basic functions failed." << endl;
    }
}

/**
 * Returns a point representing 20 pixels more than
 * the maximum x and y coordinates found in the provided vector
 * Used for determining output PNG dimensions
**/
pair<double, double> GetDimension(vector<pair<double, double>>& v)
{
    double maxx = 0;
    double maxy = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i].first > maxx)
            maxx = v[i].first;
        if (v[i].second > maxy)
            maxy = v[i].second;
    }
    return pair<double, double>(maxx + 20, maxy + 20);
}

/**
 * Manages the convex hull generation
 * @param infilename input file with point data in space-delimited format as x y
 * @param outfilename name of output PNG
**/
void ConvexHullFromFile(string infilename, string outfilename)
{
    vector<pair<double, double>> v = ReadPointsFromFile(infilename);
    pair<double, double> dims = GetDimension(v);
    unsigned int dimx = (unsigned int)dims.first;
    unsigned int dimy = (unsigned int)dims.second;
    // Create a blank white PNG
    PNG base(dimx, dimy);
    InitializePNG(base);

    // draw the original points
    DrawPoints(base, RGBAPixel(0, 0, 0, 1), v);

    // get the convex hull
    vector<pair<double, double>> v_hull = GetConvexHull(v);
    // draw the convex hull
    DrawPolygon(base, RGBAPixel(255, 0, 0, 1), v_hull);

    base.writeToFile(outfilename);
}

/**
 * Manages multiple convex hull and intersection generation
 * @param infile1 input file with point data, set 1
 * @param infile2 input file with point data, set 2
 * @param outfilename name of output PNG
**/
void IntersectionFromFile(string infile1, string infile2, string outfilename)
{
    vector<pair<double, double>> v1 = ReadPointsFromFile(infile1);
    pair<double, double> dims1 = GetDimension(v1);
    vector<pair<double, double>> v2 = ReadPointsFromFile(infile2);
    pair<double, double> dims2 = GetDimension(v2);
    unsigned int dimx = (unsigned int)max(dims1.first, dims2.first);
    unsigned int dimy = (unsigned int)max(dims1.second, dims2.second);
    // Create a blank white PNG
    PNG base(dimx, dimy);
    InitializePNG(base);

    // draw the original points
    DrawPoints(base, RGBAPixel(127, 0, 0, 1), v1);
    DrawPoints(base, RGBAPixel(0, 0, 127, 1), v2);

    // get the convex hull
    vector<pair<double, double>> v_hull_1 = GetConvexHull(v1);
    vector<pair<double, double>> v_hull_2 = GetConvexHull(v2);
    // draw the convex hull
    DrawPolygon(base, RGBAPixel(255, 0, 0, 1), v_hull_1);
    DrawPolygon(base, RGBAPixel(0, 0, 255, 1), v_hull_2);

    // get the intersection
    vector<pair<double, double>> hull_intersection = GetConvexIntersection(v_hull_1, v_hull_2);
    // draw the intersection
    DrawPolygon(base, RGBAPixel(0, 255, 0, 1), hull_intersection);

    base.writeToFile(outfilename);
}

/**
 * Initializes a PNG to all white pixels
**/
void InitializePNG(PNG& im)
{
    RGBAPixel* px;
    for (unsigned int x = 0; x < im.width(); x++)
    {
        for (unsigned int y = 0; y < im.height(); y++)
        {
            px = im.getPixel(x, y);
            px->r = 255;
            px->g = 255;
            px->b = 255;
            px->a = 1;
        }
    }
}