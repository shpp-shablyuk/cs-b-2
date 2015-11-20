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


using namespace std;



class sPoint {
    public :
        sPoint(){}
        sPoint(double x, double y) {
            this->x = x;
            this->y = y;
        }
        double getX() {
            return x;
        };
        double getY() {
            return y;
        }
        bool operator < (const sPoint &point) const {
            return (point.y < y) || (point.x < x) ;
        }
//        ~sPoint() {
//            delete this;
//        }

    private:
        double x;
        double y;
};


void printSet(Set< Set<sPoint>* > silhouettes, GBufferedImage* image) {
    int i = 0;
    long colorSet[4] = {0x0000ff, 0xFF0000, 0x00FF00, 0xffff00};
    for (Set<sPoint>* set : silhouettes) {
        cout << "count = " << set->size() << endl;
        long color = colorSet[i++ % 4];
        for (sPoint p : *set) {
            image->setRGB(p.getX(), p.getY(), color);
        }
        pause(200);
    }
    cout << endl;
}

bool isBlack(GBufferedImage* image, double x, double y) {
    if (image->inBounds(x, y)) {
        return image->getRGB(x, y) < 3355443;
    }

    return false;
}

void checkPoint(sPoint p, Set< Set<sPoint>* >& mainSet, Grid<bool>& grid, GBufferedImage* image ) {

    Set< Set<sPoint>* > sets;

    for (int dx = -1; dx < 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((dx == 0 && dy == 0) || (dx == 0 && dy == 1)) {
                continue;
            }
            double findX = p.getX() + dx;
            double findY = p.getY() + dy;

//            cout << findX << " - " << findY << endl;


            if (grid.inBounds(findY, findX) && grid[findY][findX] == 1) {
                sPoint pt(findX, findY);
//                cout << "x = " << findX << ", y = " << findY << endl;


//                image->setRGB(findX, findY, 0x00ff00);

                for (Set<sPoint>* set : mainSet) {
                    if (set->contains(pt)) {
                        if (sets.isEmpty()) {
                            set->add(p);
                            sets.add(set);
                        } else {
                            if (!sets.contains(set)) {
                                image->setRGB(findX, findY, 0x00ff00);
                                sets.add(set);
                            }
                        }
                    }
                }
//                pause(50);
                image->setRGB(p.getX(), p.getY(), 0xcccccc);
//                image->setRGB(findX, findY, 0xcccccc);
            }
        }
    }

//    cout << endl;

//    cout << "sets.size = " << sets.size() << endl;
//    cout << "sets = " << sets << endl;
//    cout << "mainSet.size = " << mainSet.size() << endl;

    if (!sets.isEmpty()) {
        if (sets.size() > 1) {
//            cout << "mainSet.size = " << mainSet.size() << endl;
//            cout << "sets.size = " << sets.size() << endl;
//            pause(1000);
            Set<sPoint>* sFirst;
            for (Set<sPoint>* s : sets) {
                if (sFirst == s) {
                    continue;
                }
                *sFirst += *s;
                mainSet.remove(s);
                image->setRGB(p.getX(), p.getY(), 0xffbb66);
            }
            mainSet.add(sFirst);
        }
    } else {
        Set<sPoint>* silhouette = new Set<sPoint>;
        image->setRGB(p.getX(), p.getY(), 0xff0000);
        silhouette->add(p);
        mainSet.add(silhouette);
    }
}

int main() {
    GWindow gw;
    GBufferedImage* image = new GBufferedImage;
    image->load("images/silhouette1.jpg");
    gw.setCanvasSize(image->getWidth(), image->getHeight());
    gw.add(image);

    Grid<bool> grid(image->getHeight(), image->getWidth(), 0);
    for (double row = 0; row < image->getHeight(); ++row) {
        for (double col = 0; col < image->getWidth(); ++col) {
            if (isBlack(image, col, row)) {
                grid[row][col] = 1;
            }
        }
    }

    Set< Set<sPoint>* > mainSet;
    for (double col = 0; col < grid.width(); ++col) {
        for (double row = 0; row < grid.height(); ++row) {
            if (grid[row][col] == 1) {
                sPoint p(col, row);
                checkPoint(p, mainSet, grid, image);
            }
        }
    }

//    Set<sPoint>* set1 = mainSet.first();
//    for (Set<sPoint>* set : mainSet) {
//        if (!(*set1 * *set)->isEmpty()) {
//            *set1 += *set;
//        }
//    }

    printSet(mainSet, image);
    cout << "count = " << mainSet.size() << endl;
    delete image;

    return 0;
}
