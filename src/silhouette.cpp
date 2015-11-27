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


void printset(set< set<sPoint>* > silhouettes, GBufferedImage* image) {
    int i = 0;
    long colorset[4] = {0x0000ff, 0xFF0000, 0x00FF00, 0xffff00};
    for (set<sPoint>* set : silhouettes) {
        cout << "count = " << set->size() << endl;
        long color = colorset[i++ % 4];
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

void mergeSets(set< set<sPoint>* >& sets, set< set<sPoint>* >& mainset) {

    ////            cout << "mainset.size = " << mainset.size() << endl;
    ////            cout << "sets.size = " << sets.size() << endl;
    ////            pause(1000);
                set<sPoint>* sFirst = new set<sPoint>;
                for (set<sPoint>* s : sets) {
                    sFirst->insert(s->begin(), s->end());
//                    cout << "ms s.size = " << s->size() << endl;
//                    cout << "ms sFirst.size = " << sFirst->size() << endl;
                    mainset.erase(s);
                    delete s;
//                    image->setRGB(p.getX(), p.getY(), 0xffbb66);
                    cout << "--mainset.size = " << mainset.size() << endl;
                }
                mainset.insert(sFirst);
//                cout << "sFirst = " << sFirst << endl;
//                cout << "f mainset.size = " << mainset.size() << endl;
}

void checkPoint(sPoint p, set< set<sPoint>* >& mainset, Grid<bool>& grid, GBufferedImage* image ) {

    set< set<sPoint>* > sets;


//    cout << endl << "s mainset.size = " << mainset.size() << endl;
//    cout << "s sets.size = " << sets.size() << endl;

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

                for (set<sPoint>* sl : mainset) {
//                    cout << sl << endl;
                    cout << "sl size " << sl->size() << endl;
//                    cout << "for st sets.size = " << sets.size() << endl;
                    if (sl->find(pt) == sl->end()) {
//                        cout << "sl size" << sl->size() << endl;
                        if (sets.empty()) {
                            sl->insert(p);
                            sets.insert(sl);
                        } else {
                            if (sets.find(sl) == sets.end()) {
//                                image->setRGB(findX, findY, 0x00ff00);
                                sets.insert(sl);
                            }
                        }
//                        sl->insert(p);
//                        sets.insert(sl);
                    }
//                    cout << "for end sets.size = " << sets.size() << endl;
                }
//                pause(50);
                image->setRGB(p.getX(), p.getY(), 0xcccccc);
//                image->setRGB(findX, findY, 0xcccccc);
            }
        }
    }

    for ( set<sPoint>* s1 : sets) {
        cout << "s1 = " << s1 << endl;
    }

    cout << endl;
    cout << "mainset.size = " << mainset.size() << endl;
    cout << "sets.size = " << sets.size() << endl;
//    cout << "sets = " << sets << endl;

    if (!sets.empty()) {
        if (sets.size() > 1) {
            mergeSets(sets, mainset);
        }
    } else {
        set<sPoint>* silhouette = new set<sPoint>;
        image->setRGB(p.getX(), p.getY(), 0xff0000);
        silhouette->insert(p);
        mainset.insert(silhouette);
//        pause(50);
    }
}

int main() {
    GWindow gw;
    GBufferedImage* image = new GBufferedImage;
//    image->load("images/silhouette3.jpg");
    image->load("images/test1.jpg");
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

    set< set<sPoint>* > mainset;
    for (double col = 0; col < grid.width(); ++col) {
        for (double row = 0; row < grid.height(); ++row) {
            if (grid[row][col] == 1) {
                sPoint p(col, row);
                checkPoint(p, mainset, grid, image);
            }
        }
    }

//    set<sPoint>* set1 = mainset.first();
//    for (set<sPoint>* set : mainset) {
//        if (!(*set1 * *set)->isEmpty()) {
//            *set1 += *set;
//        }
//    }

//    printset(mainset, image);
    cout << "count = " << mainset.size() << endl;
    delete image;

    return 0;
}
