#include <math.h>
#include <errno.h>
#include <stdio.h>
double H1tab();
void dlocate();

double voigt(a, v)
double a, v;
{
    double H;
    double pi = 3.14159265358979323846;
    double sqrtpi = 1.77245385090552;
    double sqrt2 = 1.41421356237310;
    double v2, v4, H0, H1, H2, h0, h1, h2, h3, h4, Psi, u, a2, a4, u2, u4, hs;

    v = fabs(v);

    v2 = v * v;
    v4 = v2 * v2;
    a2 = a * a;
    a4 = a2 * a2;

    if (a == 0.0)
        return (exp(-v2) / sqrtpi);

    if (a <= 0.2 && v >= 5.0) {
        H = a * (1.0 + 3.0 / (2.0 * v2) + 15.0 / (4.0 * v4)) / (sqrtpi * v2);
        return (H / sqrtpi);
    }

    if ((a <= 0.2 && v < 5.0) || (a >= 0.2 && a <= 1.4 && a + v <= 3.2)) {
        H0 = exp(-v2);
        H1 = H1tab(v);
        H2 = (1.0 - 2.0 * v2) * H0;
        H = (((H2 * a) + H1) * a + H0);
        if (a <= 0.2 && v < 5.0)
            return (H / sqrtpi);
        if (a >= 0.2 && a <= 1.4 && a + v <= 3.2) {
            h0 = H0;
            h1 = H1 + 2.0 * h0 / sqrtpi;
            h2 = H2 - h0 + 2.0 * h1 / sqrtpi;
            h3 = 2.0 * (1.0 - H2) / (3.0 * sqrtpi) - 2.0 * v2 * h1 / 3.0 + 2.0 * h2 / sqrtpi;
            h4 = 2.0 * v4 * h0 / 3.0 - 2.0 * h1 / (3.0 * sqrtpi) + 2.0 * h3 / sqrtpi;
            Psi = ((-0.122727278 * a + 0.532770573) * a - 0.962846325) * a + 0.979895023;
            hs = h4 * a4 + h3 * a2 * a + h2 * a2 + h1 * a + h0;
            return (Psi * hs / sqrtpi);
        }
    }

    if (a > 1.4 || (a >= 0.2 && a + v > 3.2)) {
        u = sqrt2 * (a2 + v2);
        u2 = u * u;
        u4 = u2 * u2;
        return ((sqrt2 * a / (pi * u)) * (1.0 + (3.0 * v2 - a2) / u2 + (15.0 * v4 - 30.0 * a2 * v2 + 3.0 * a4) / u4));
    } else
        return (0.0);

}

double H1tab(v)
double v;
{
    int i, j;
    double h1;
    static double vtab[] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
        1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,
        2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9,
        3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9,
        4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8,
        6.0, 6.2, 6.4, 6.6, 6.8, 7.0, 7.2, 7.4, 7.6, 7.8,
        8.0, 8.2, 8.4, 8.6, 8.8, 9.0, 9.2, 9.4, 9.6, 9.8,
        10.0, 10.2, 10.4, 10.6, 10.8, 11.0, 11.2, 11.4, 11.6, 11.8,
        12.0
    };
    static double H1[] = { -1.12838, -1.10596, -1.04048, -0.93703, -0.80346, -0.64945,
        -0.48552, -0.32192, -0.16772, -0.03012, 0.08594, 0.17789,
        0.24537, 0.28981, 0.31394, 0.32130, 0.31573, 0.30094,
        0.28027, 0.25648, 0.231726, 0.207528, 0.184882, 0.164341,
        0.146128, 0.130236, 0.116515, 0.104739, 0.094653, 0.086005,
        0.078565, 0.072129, 0.066526, 0.061615, 0.057281, 0.053430,
        0.049988, 0.046894, 0.044098, 0.041561, 0.039250, 0.035195,
        0.031762, 0.028824, 0.026288, 0.024081, 0.022146, 0.020411,
        0.018929, 0.017582, 0.016375, 0.015291, 0.014312, 0.013426,
        0.012620, 0.0118860, 0.0112145, 0.0105990, 0.0100332, 0.0095119,
        0.0090306, 0.0085852, 0.0081722, 0.0077885, 0.0074314,
        0.0070985,
        0.0067875, 0.0064967, 0.0062243, 0.0059688, 0.0057287,
        0.0055030,
        0.0052903, 0.0050898, 0.0049006, 0.0047217, 0.0045526,
        0.0043924,
        0.0042405, 0.0040964, 0.0039595
    };

    if (v > 12)
        return (0.56419 / (v * v) + 0.846 / (v * v * v * v));
    if (v == 0.0)
        return (-1.12838);

    i = 0;
    dlocate(vtab, 80, v, &i, 0, 80);
    h1 = H1[i - 1] + (H1[i] - H1[i - 1]) * (v - vtab[i - 1]) / (vtab[i] - vtab[i - 1]);
    return (h1);
}
