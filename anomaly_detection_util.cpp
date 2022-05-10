/*
 * animaly_detection_util.cpp
 *
 * Author: Itamar Twersky 
 */

#include <math.h>
#include "anomaly_detection_util.h"

// returns the average of X
float avg(float *x, int size) {
    float sum = 0;
    //sum x
    for (int i = 0; i < size; i++)
        sum += *(x + i);
    //if x's size isn't 0 - compute & return its average
    //otherwise, return 0.
    return size == 0 ? 0 : sum / (float) size;
}

// returns the variance of X
float var(float *x, int size) {
    float powSum = 0;
    //sum every number in x powered by 2
    for (int i = 0; i < size; ++i) {
        powSum += (*(x + i)) * (*(x + i));
    }
    //calculate x's average
    float theAvg = avg(x, size);
    //if x's size isn't 0 - compute & return its variance
    //otherwise, return 0.
    return size == 0 ? 0 : ((powSum / (float) size) - pow(theAvg, (float) 2));
}

// returns the covariance of X and Y
float cov(float *x, float *y, int size) {
    //save the average of x & y.
    float xAvg = avg(x, size);
    float yAvg = avg(y, size);
    float covSum = 0;
    //save in covSum the sum of (x - xAvg) * (y - yAvg) for every x and y in *x and *y
    for (int i = 0; i < size; ++i) {
        covSum += ((*(x + i) - xAvg) * (*(y + i) - yAvg));
    }
    //if size isn't 0 - compute & return the covariance
    //otherwise, return 0.
    return size == 0 ? 0 : covSum / (float) size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size) {
    //compute & save the covariance for x,y.
    float covResul = cov(x, y, size);
    //compute & save the variance for x,y.
    float xVar = var(x, size);
    float yVar = var(y, size);
    //if xVar & yVar isn't 0 - compute & Pearson correlation coefficient of X and Y
    //otherwise, return 0.
    return (xVar == 0 || yVar == 0) ? 0 : covResul / (sqrt(xVar) * sqrt(yVar));
}

// performs a linear regression and returns the line equation
Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    //save all the x & y points' parameters in x & y arrays.
    for (int i = 0; i < size; ++i) {
        x[i] = (*(points +i))->x;
        y[i] = (*(points + i))->y;
    }
    //compute & save the variance for x
    // and the covariance for x,y.
    float covResul = cov(x, y, size);
    float varResul = var(x, size);
    //craete variable to save the a of f(x) = ax + b.
    float a;
    // if variance for x a = 0
    //else - calculate 'a' with linear regression
    if (varResul == 0){
        a = 0;
    } else {
        a = covResul / varResul;
    }
    //calculate 'b' with linear regression
    float b = avg(y, size) - (a * avg(x, size));
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size) {
    //create a line using linear regression
    Line l1 = linear_reg(points, size);
    // calculate the deviation with line based dev function.
    return dev(p, l1);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    //calculate the f(x) parameter on the line for the point's x.
    float fx = l.f(p.x);
    //return the distance between the fx and point's y.
    return fabs(fx - p.y);
}




