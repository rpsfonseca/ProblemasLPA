#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>

#define N 20

using namespace std;

struct Point2D {
    int x;
    int y;
};

int n, m, lowest_ind;
Point2D point;
Point2D points[N], points_aux[N];
int points_not_in_convex_hull[N];
vector <Point2D> ordered_points(1);

double areaOfAnyPolygon(vector<Point2D> points, int num_points) {
    double area = 0.0;
    int j = num_points - 1;

    for (int i = 0; i < num_points; i++)
    {
        area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i;
    }

    return area/2.0;
}

float ccw(Point2D u1, Point2D u2, Point2D u3) {
    return (u2.x - u1.x)*(u3.y - u1.y) - (u2.y - u1.y)*(u3.x - u1.x);
}

double angle(Point2D reference, Point2D p) {
    return atan2(p.y - reference.y, p.x - reference.x);
}

void graham_scan(Point2D points[], Point2D points_aux[], int n) {

    int lowest = 1000000;

    if (n < 3) {
        return;
    }

    Point2D start;
    start.x = points[0].x;
    start.y = points[0].y;


    for (int j = 1; j < n; j++) {

        double angle1 = angle(start, points[j]);
        int i = 0;
        while (i != ordered_points.size() && angle(start, ordered_points[i]) < angle1) {
            i++;
        }
        ordered_points.insert(ordered_points.begin() + i, points[j]);

    }

    for (int k = 1; k < n; k++) {

        points[k].x = ordered_points[k].x;
        points[k].y = ordered_points[k].y;

    }

    m = 1;

    for (int i = 3; i < n; i++) {

        while (ccw(points[m-1], points[m], points[i]) <= 0) {
            if (m > 1) {
                m -= 1;
            } else if (i == n) {
                break;
            } else {
                points_not_in_convex_hull[i] = 1;
                i += 1;
            }
        }

        m += 1;

        point.x = points[m].x;
        point.y = points[m].y;
        points[m].x = points[i].x;
        points[m].y = points[i].y;
        points[i].x = point.x;
        points[i].y = point.y;

    }
    int count, num_of_areas = 0;
    for (int i1 = 1; i1 < n; i1++) {
        count = 0;
        for (int i = 0; i < m; i++) {
            if (points_aux[i1].x != points[i].x && points_aux[i1].y != points[i].y) {
                count++;
            } else if (points_aux[i1].x == points[i].x && points_aux[i1].y == points[i].y) {
                break;
            }
        }
        if (count == m) {
            bool still_not_in = true;
            int j = i1 + 1;
            while (still_not_in) {
                for (int k = 0; k < m; k++) {
                    if (points_aux[j].x == points[k].x && points_aux[j].y == points[k].y) {
                        k = m;
                        still_not_in = false;
                    }
                }
                if (still_not_in) {
                    j++;
                    if (j == n) {
                        j = 0;
                        i1 = 0;
                    }
                }
            }
            int offset = 0;
            vector <Point2D> area_points(j-i1);
            for (int l = j-i1-1; l < j+1; l++) {
                area_points[offset++].x = points_aux[l].x;
                area_points[offset++].y = points_aux[l].y;
            }
            double polygon_area = areaOfAnyPolygon(area_points, offset);
            if (polygon_area < 0) {
                polygon_area = -polygon_area;
            }
            printf("%d: %.1f\n",num_of_areas,polygon_area);
            num_of_areas++;
            i1 = j;
        }
    }
}

int main() {

    while (scanf("%d", &n) > 0) {

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &points[i].x, &points[i].y);
            points_aux[i].x = points[i].x;
            points_aux[i].y = points[i].y;
        }

        graham_scan(points, points_aux, n);
    }

    return 0;
}