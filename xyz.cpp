bool inside(Point p, Edge e) {
    switch(e) {
        case Left:
            if(p.x < wMin.x) {
                return false;
            }
            break;
        case Right:
            if(p.x > wMax.x) {
                return false;
            }
            break;
        case Bottom:
            if(p.y < wMin.y) {
                return false;
            }
            break;
        case Top:
            if(p.y > wMax.y) {
                return false;
            }
            break;
    }

    return true;
}

bool cross(Point p1, Point p2, Edge e) {
    if(inside(p1, e) == inside(p2, e)) {
        return false;
    } else {
        return true;
    }
}

Point intersect(Point p1, Point p2, Edge e) {
    Point intersection;
    float m;

    if(p1.x != p2.x) {
        m = (p2.y - p1.y) / (p2.x - p1.x);
    }

    switch(e) {
        case Left:
            intersection.x = wMin.x;
            intersection.y = p2.y + (wMin.x - p2.x) * m;
            break;
        case Right:
            intersection.x = wMax.x;
            intersection.y = p2.y + (wMax.x - p2.x) * m;
            break;
        case Bottom:
            intersection.y = wMin.y;
            if(p1.x != p2.x) {
                intersection.x = p2.x + (wMin.y - p2.y) / m;
            } else {
                intersection.x = p2.x;
            }
            break;
        case Top:
            intersection.y = wMax.y;
            if(p1.x != p2.x) {
                intersection.x = p2.x + (wMax.y - p2.y) / m;
            } else {
                intersection.x = p2.x;
            }
            break;
    }

    return intersection;
}

vector<Point> clip(vector<Point> polygon, Edge e, vector<Point> &out) {
    vector<Point> clipped;
    int n = polygon.size();

    for(int i = 0, j = 1; i < n; i++, j = (++j) % n) {
        if(cross(polygon[i], polygon[j], e)) {
            Point intersection = intersect(polygon[i], polygon[j], e);
            if(inside(polygon[i], e)) {      // Inside -> Outside
                clipped.push_back(intersection);
                out.push_back(intersection);
                out.push_back(polygon[j]);
            } else {                         // Outside -> Inside
                clipped.push_back(intersection);
                clipped.push_back(polygon[j]);
                out.push_back(intersection);
            }
        } else {
            if(inside(polygon[i], e)) {     // Inside -> Inside
                clipped.push_back(polygon[j]);
            } else {                        // Outside -> Outside
                out.push_back(polygon[j]);
            }
        }
    }

    return clipped;
}

void sutherlandHodgeman(int button, int state, int xx, int yy) {
    static vector<Point> polygon;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        drawPoint(xx, HEIGHT - yy);

        Point point(xx, yy);
        polygon.push_back(point);

        glFlush();
    } else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        vector<Point> clipped;
        vector<Point> out;

        clipped = clip(polygon, Left, out);
        clipped = clip(clipped, Right, out);
        clipped = clip(clipped, Bottom, out);
        clipped = clip(clipped, Top, out);

        // drawPolygon(out, 1, 0, 0);
        drawPolygon(clipped, 0, 1, 0);

        glFlush();
        polygon.clear();
    }
}
