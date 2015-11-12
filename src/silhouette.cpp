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
            return (point.x < x) || (point.y < y);
        }
//        bool operator() (const sPoint* lhs, const sPoint* rhs) {
//            return (lhs->x == rhs->x) && (lhs->y == rhs->y) ;
//        }
//        ostream& operator<< (ostream& stream ) {
//          return stream << "[" << x << ", " << y << "]";
//        }
    private:
        double x;
        double y;
};


void printSet(Vector< Set<sPoint> > silhouettes, GBufferedImage* image) {
    int i = 0;
    long colorSet[3] = {0x0000ff, 0xFF0000, 0x00FF00};
    for (Set<sPoint> set : silhouettes) {
        cout << "count = " << set.size() << endl;
        long color = colorSet[i++ % 3];
        for (sPoint p : set) {
            image->setRGB(p.getX(), p.getY(), color);
        }
    }
    cout << endl;
}

bool isBlack(GBufferedImage* image, double x, double y) {
    if (image->inBounds(x, y)) {
//        cout << image->getRGBString(x, y) << endl;
//        cout << image->getRGB(x, y) << endl;
        return image->getRGB(x, y) < 3355443;
    }

    return false;
}

bool isInSet(Vector<sPoint> &set, sPoint pt) {
    if (set.isEmpty()) {
        return false;
    }

    for (sPoint var : set) {
        if (var.getX() == pt.getX() && var.getY() == pt.getY()) {
            return true;
        }
    }

    return false;
}

void checkPoint(sPoint p, Vector< Set<sPoint> >& silhouettes, GBufferedImage* image) {
//    printSet(silhouettes);
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

//            if (dx == 0 && dy == 0) {
//                continue;
//            }
            double findX = p.getX() + dx;
            double findY = p.getY() + dy;

            if (isBlack(image, findX, findY)) {
                sPoint pt(findX, findY);

                image->setRGB(findX, findY, 0xff0000);
//                pause(100);


//                Stack< Set<sPoint> > sets;
                for (Set<sPoint> &set : silhouettes) {

                    if (set.contains(pt)) {
                        set.add(p);
//                        sets.add(set);
                        image->setRGB(p.getX(), p.getY(), 0x0000ff);

//                        return;
                    }
                }

//                while (sets.size() > 1) {
//                    Set<sPoint> s1 = sets.pop();
//                    Set<sPoint> s2 = sets.pop();

//                    silhouettes.add(s1 + s2);

//                    s1.clear();
//                }
            }
        }
    }

    Set<sPoint> silhouette;
    image->setRGB(p.getX(), p.getY(), 0x00ff00);
    silhouette.add(p);
    silhouettes.add(silhouette);
}

int main() {
    GWindow gw;

    GBufferedImage* image = new GBufferedImage;
    image->load("images/silhouette1.jpg");

    gw.setCanvasSize(image->getWidth(), image->getHeight());
    gw.add(image);

    double count = 0;

//    Set<GPoint> silhouette;

    Vector< Set<sPoint> > silhouettes;

    Grid<bool> grid(image->getWidth(), image->getHeight(), 0);

    for (double h = 0; h < image->getHeight(); ++h) {
//        cout << h << endl;
        for (double w = 0; w < image->getWidth(); ++w) {
//            grid.set(h, w, (isBlack(image, w, h)) ? 1 : 0);
            if (isBlack(image, w, h)) {
                grid[w][h] = 1;

//                count++;

//                sPoint p(w, h);

//                checkPoint(p, silhouettes, image);

            }
//            image->setRGB(w, h, 0xffcc33);
//            pause(1);
        }
    }

    cout << grid.toString2D() ;

//    printSet(silhouettes, image);

//    cout << "count = " << silhouettes << endl;

//    cout << "count = " << silhouettes.size() << endl;

    delete image;

    return 0;
}
