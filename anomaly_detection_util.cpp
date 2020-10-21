/*
 * animaly_detection_util.cpp
 *
 * Author: write your ID and name here
 */

#include <math.h>
#include "anomaly_detection_util.h"

// returns the average of X
float avg(float *x, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += *(x + i);
    return size == 0 ? 0 : sum / (float) size;
}

// returns the variance of X
float var(float *x, int size) {
    float powSum = 0;
    for (int i = 0; i < size; ++i) {
        powSum += (*(x + i)) * (*(x + i));
    }
    float theAvg = avg(x, size);
    return size == 0 ? 0 : ((powSum / (float) size) - pow(theAvg, (float) 2));
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size) {
    float xAvg = avg(x, size);
    float yAvg = avg(y, size);
    float covSum = 0;
    for (int i = 0; i < size; ++i) {
        covSum += ((*(x + i) - xAvg) * (*(y + i) - yAvg));
    }
    return size == 0 ? 0 : covSum / (float) size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size) {
    float covResul = cov(x, y, size);
    float xVar = var(x, size);
    float yVar = var(y, size);
    return (xVar == 0 || yVar == 0) ? 0 : covResul / (sqrt(xVar) * sqrt(yVar));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; ++i) {
        x[i] = (*(points +i))->x;
        y[i] = (*(points + i))->y;
    }
    float covResul = cov(x, y, size);
    float varResul = var(x, size);
    float a;
    if (varResul == 0){
        a = 0;
    } else {
        a = covResul / varResul;
    }
    float b = avg(y, size) - (a * avg(x, size));
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {
    Line l1 = linear_reg(points, size);
    return dev(p, l1);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    float fx = (l.a*p.x) + l.b;
    return abs(fx - p.y);
}




