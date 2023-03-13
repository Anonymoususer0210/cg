void y_x(int button, int state, int xx, int yy) {
    static vector<Point> polygon;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        drawPoint(xx, HEIGHT - yy);

        Point point(xx, yy);
        polygon.push_back(point);

        glFlush();
    } else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        drawPolygon(polygon, 1, 1, 1);
        glFlush();

        FColour background(0.0f, 0.0f, 0.0f);

        for(int y = 0; y <= HEIGHT; y++) {      // For each scan line
            vector<int> intersections;
            int n = polygon.size();

            for(int i = 0, j = 1; i < n; i++, j = (++j) % n) {      // For each edge
                int y1 = polygon[i].y;
                int y2 = polygon[j].y;

                if(y1 < y2) {
                    if(y >= y1 && y < y2) {
                        int x = (y - y1) * (polygon[j].x - polygon[i].x) / (y2 - y1) + polygon[i].x;
                        intersections.push_back(x);
                    }
                } else {
                    if (y >= y2 && y < y1) {
                        int x = (y - y1) * (polygon[j].x - polygon[i].x) / (y2 - y1) + polygon[i].x;
                        intersections.push_back(x);
                    }
                }
            }

            sort(intersections.begin(), intersections.end());
            int m = intersections.size();

            glColor3f(0, 1, 0);
            for(int i = 0; i < m; i += 2) {
                int x1 = intersections[i];
                int x2 = intersections[i + 1];
                glBegin(GL_LINES);
                    glVertex2i(x1, HEIGHT - y);
                    glVertex2i(x2, HEIGHT - y);
                glEnd();

                glFlush();
            }
        }
        glFlush();
    }
}
