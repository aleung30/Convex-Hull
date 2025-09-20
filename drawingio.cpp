/**
 * @file        drawingio.cpp
 * @description Implementation of methods used for file IO and drawing on PNG images
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#include <cmath>
#include <iostream>
#include <fstream>

#include "drawingio.h"

/**
 * Draws a line connecting p1 and p2
 * Note that points are expected to be in image coordinates (e.g. top-left origin)
 * pixel is used only to contain colour information
**/
void DrawLine(PNG& im, RGBAPixel pixel, pair<double, double> p1, pair<double, double> p2)
{
    RGBAPixel* px;

    // cases: vertical line, horizontal line, slope > 1, slope < 1
    // case 1: vertical line
    if (p1.first == p2.first) // typically, don't use == for double types
    {
        unsigned int y1, y2;
        if (p1.second > p2.second)
        {
            y1 = (unsigned int)p2.second;
            y2 = (unsigned int)p1.second;
        }
        else
        {
            y1 = (unsigned int)p1.second;
            y2 = (unsigned int)p2.second;
        }
        for (unsigned int yc = y1; yc < y2; yc++)
        {
            px = im.getPixel((unsigned int)p1.first, yc);
            *px = pixel;
        }
    }
    // case 2: horizontal line
    else if (p1.second == p2.second)
    {
        unsigned int x1, x2;
        if (p1.first > p2.first)
        {
            x1 = (unsigned int)p2.first;
            x2 = (unsigned int)p1.first;
        }
        else
        {
            x1 = (unsigned int)p1.first;
            x2 = (unsigned int)p2.first;
        }
        for (unsigned int xc = x1; xc < x2; xc++)
        {
            px = im.getPixel(xc, (unsigned int)p1.second);
            *px = pixel;
        }
    }
    else
    {
        double slope = (p2.second - p1.second) / (p2.first - p1.first);
        double icept = p1.second - (slope * p1.first);
        // case 3: shallow slope
        // iterate over x-coordinate
        if (-1 <= slope && slope <= 1)
        {
            pair<double, double> pleft, pright;
            if (p1.first < p2.first)
            {
                pleft = p1;
                pright = p2;
            }
            else
            {
                pleft = p2;
                pright = p1;
            }
            for (double xc = pleft.first; xc <= pright.first; xc++)
            {
                // calculate the y-coordinate
                double yc = (slope * xc) + icept;
                px = im.getPixel((unsigned int)xc, (unsigned int)yc);
                *px = pixel;
            }
        }
        // case 4: steep slope
        // iterate over y-coordinate
        else
        {
            pair<double, double> pbottom, ptop;
            if (p1.second < p2.second)
            {
                pbottom = p1;
                ptop = p2;
            }
            else
            {
                pbottom = p2;
                ptop = p1;
            }
            for (double yc = pbottom.second; yc <= ptop.second; yc++)
            {
                // calculate the y-coordinate
                double xc = ((double)yc - icept) / slope;
                px = im.getPixel((unsigned int)xc, (unsigned int)yc);
                *px = pixel;
            }
        }
    }
}

/**
 * Draws a cross centred on p
 * bar length is 9 pixels
 * bar thickness is 3 pixels
 * pixel is used only to contain colour information
**/
void DrawPoint(PNG& im, RGBAPixel pixel, pair<double, double> p)
{
    int row, column;
    RGBAPixel* px;
    // draw horizontal bar
    for (row = (int)p.second - 1; row <= (int)p.second + 1; row++)
    {
        for (column = (int)p.first - 4; column <= (int)p.first + 4; column++)
        {
            // draw the pixel if it is within the image boundaries
            if (0 <= row && (unsigned int)row < im.height() && 0 <= column && (unsigned int)column < im.width())
            {
                px = im.getPixel(column, row);
                *px = pixel;
            }
        }
    }
    // draw vertical bar
    for (row = (int)p.second - 4; row <= (int)p.second + 4; row++)
    {
        for (column = (int)p.first - 1; column <= (int)p.first + 1; column++)
        {
            // draw the pixel if it is within the image boundaries
            if (0 <= row && (unsigned int)row < im.height() && 0 <= column && (unsigned int)column < im.width())
            {
                px = im.getPixel(column, row);
                *px = pixel;
            }
        }
    }
}

/**
 * Draws points passed in as a vector
 * pixel is used only to contain colour information
**/
void DrawPoints(PNG& im, RGBAPixel pixel, vector<pair<double, double>> v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        DrawPoint(im, pixel, v[i]);
    }
}

/**
 * Draws a polygon and its vertices
 * pixel is used only to contain colour information
 * v must contain the polygon's vertices in order along the boundary
**/
void DrawPolygon(PNG& im, RGBAPixel pixel, vector<pair<double, double>> v)
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        DrawPoint(im, pixel, v[i]);
        DrawLine(im, pixel, v[i], v[(i + 1) % v.size()]);
    }
}

/**
 * Reads in a delimited file containing coordinate data
 * Each line in the file contains two integers separated by a space as
 * x y
**/
vector<pair<double, double>> ReadPointsFromFile(string filename)
{
    vector<pair<double, double>> v;
    string line;
    double x, y;
    ifstream infile(filename);

    while (infile >> x >> y)
    {
        v.push_back(pair<double, double>(x, y));
    }

    infile.close();
    return v;
}