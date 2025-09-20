/**
 * @file        drawingio.h
 * @description Declaration of methods used for file IO and drawing on PNG images
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#ifndef _DRAWINGIO_H_
#define _DRAWINGIO_H_

#include <string>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;
using namespace std;

/**
 * Draws a line connecting p1 and p2
 * Note that points are expected to be in image coordinates (e.g. top-left origin)
 * pixel is used only to contain colour information
**/
void DrawLine(PNG& im, RGBAPixel pixel, pair<double, double> p1, pair<double, double> p2);

/**
 * Draws a cross centred on p
 * bar length is 9 pixels
 * bar thickness is 3 pixels
 * pixel is used only to contain colour information
**/
void DrawPoint(PNG& im, RGBAPixel pixel, pair<double, double> p);

/**
 * Draws points passed in as a vector
 * pixel is used only to contain colour information
**/
void DrawPoints(PNG& im, RGBAPixel pixel, vector<pair<double, double>> v);

/**
 * Draws a polygon and its vertices
 * pixel is used only to contain colour information
 * v must contain the polygon's vertices in order along the boundary
**/
void DrawPolygon(PNG& im, RGBAPixel pixel, vector<pair<double, double>> v);

/**
 * Reads in a delimited file containing coordinate data
 * Each line in the file contains two integers separated by a space as
 * x y
**/
vector<pair<double, double>> ReadPointsFromFile(string filename);

#endif