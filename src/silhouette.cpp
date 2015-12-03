#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <fstream>
#include <map>

#include "gbufferedimage.h"
#include "gtypes.h"
#include "set.h"
#include "grid.h"
#include <set>

#include <queue>
#include <list>


using namespace std;

const int GRAY_COLOR = 3355443;     //  to determine is pixel black
const double LIMIT = 0.01;          //

//  storage for pixel coordinates
class sPoint {
    public :
        sPoint(){}
        sPoint(double x, double y) {
            this->x = x;
            this->y = y;
        }
        double getX() {
            return x;
        }
        double getY() {
            return y;
        }

    private:
        double x;
        double y;
};


typedef list< Vector<sPoint> > silhouettes;
typedef Vector<sPoint> silhouette;

/**
 * @brief       check point color
 * @param       image
 * @param x     coordinates
 * @param y     coordinates
 * @return true if point is black
 */
bool isBlack(GBufferedImage* image, double x, double y) {
    if (image->inBounds(x, y)) {
        return image->getRGB(x, y) < GRAY_COLOR;
    }

    return false;
}

/**
 * @brief               groupings nearest points in one set
 * @param p             point
 * @param setsOfPoints  store found sets of points
 * @param grid
 */
void checkPoint(sPoint p, silhouettes& setsOfPoints, Grid<bool>& grid ) {
    queue<sPoint> q;
    q.push(p);
    silhouette set;

    while (!q.empty()) {
        sPoint currentPoint = q.front();
        q.pop();
        //  detour around the current point
        for (int col = currentPoint.getX() - 1; col <= currentPoint.getX() + 1; col++) {
            for (int row = currentPoint.getY() - 1; row <= currentPoint.getY() + 1; row++) {
                if (grid.inBounds(row, col) && grid[row][col] == 1) {
                    sPoint newPoint(col, row);
                    q.push(newPoint);
                    grid[row][col] = 0;
                    set.push_back(newPoint);
                }
            }
        }
    }
    setsOfPoints.push_back(set);
}

/**
 * @brief processImage
 * @param gw        reference to GWindow object
 * @param fileName  the name of the image file
 * @return          a pointer to the GBufferedImage object
 */
GBufferedImage* processImage (GWindow& gw, string fileName) {
    GBufferedImage* image = new GBufferedImage;
    image->load(fileName);
    gw.setCanvasSize(image->getWidth(), image->getHeight());
    gw.add(image);

    return image;
}

/**
 * @brief filling a grid from image. black pixel is 1, white - 0
 * @param grid
 * @param image
 */
void fillGrid(Grid<bool>& grid, GBufferedImage* image) {
    for (double row = 0; row < image->getHeight(); ++row) {
        for (double col = 0; col < image->getWidth(); ++col) {
            if (isBlack(image, col, row)) {
                grid[row][col] = 1;
            }
        }
    }
}

/**
 * @brief bypassing all the points of the grid and union of points in sets
 * @param grid
 * @param setsOfPoints
 */
void groupPoints(Grid<bool>& grid, silhouettes& setsOfPoints) {
    for (double col = 0; col < grid.width(); ++col) {
        for (double row = 0; row < grid.height(); ++row) {
            if (grid[row][col] == 1) {
                sPoint p(col, row);
                checkPoint(p, setsOfPoints, grid);
            }
        }
    }
}

/**
 * @brief removal of sets of points which is less than the minimum value
 * @param setsOfPoints
 */
void filterSets(silhouettes& setsOfPoints) {
    double totalPoints = 0;
    for (silhouette item : setsOfPoints) {
        totalPoints += item.size();
    }
    double minSize = (totalPoints / setsOfPoints.size()) * LIMIT;

    setsOfPoints.remove_if([minSize](silhouette& p) { return  p.size() < minSize;});
}

int main() {
    GWindow gw;
    GBufferedImage* image = processImage(gw, "images/silhouette.jpg");

    Grid<bool> grid(image->getHeight(), image->getWidth(), 0);
    fillGrid(grid, image);

    silhouettes setsOfPoints;
    groupPoints(grid, setsOfPoints);

    filterSets(setsOfPoints);

    cout << "found silhouettes - " << setsOfPoints.size() << endl;

    delete image;
    return 0;
}
