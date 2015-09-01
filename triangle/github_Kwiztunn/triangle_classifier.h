// triangle_classifier.h

const long MIN = -1073741823;
const long MAX = 1073741823;
const long X1 = 0;
const long X2 = 2;
const long X3 = 4;
const long Y1 = 1;
const long Y2 = 3;
const long Y3 = 5;

long long line_length_sq(long p1_x, long p1_y, long p2_x, long p2_y);

long line_length(long p1_x, long p1_y, long p2_x, long p2_y);
long is_line(long* coords);
long is_right(long long* sides);
long is_acute(long long* sides);
long is_obtuse(long long* sides);
long is_equilateral(long long* sides);
long is_isosceles(long long* sides);
long is_scalene(long long* sides);