#include <math.h>
#include <stdio.h>
#include "spectrum.h"
#include <errno.h>
double unified();
int Nmax();
double cutoff();
double dmax();
double dmin();
int imin();
double gffactor();

void balmer(hkap, model, wave)
atmosphere *model;
double hkap[];
double wave;
{
    static double w0[] = { 6562.813, 4861.328, 4340.463, 4101.733, 3970.070, 3889.047,
        3835.382, 3797.895, 3770.627, 3750.149, 3734.365, 3721.935,
        3711.968, 3703.849, 3697.148, 3691.551, 3686.828, 3682.804,
        3679.349, 3676.359, 3673.755, 3671.472, 3669.460, 3667.678,
        3666.092, 3664.673, 3663.400, 3662.252, 3661.215, 3660.274,
        3659.417, 3658.635, 3657.920, 3657.263, 3656.660, 3656.103,
        3655.589, 3655.113, 3654.672, 3654.262, 3653.880, 3653.524,
        3653.192, 3652.881, 3652.590, 3652.316, 3652.060, 3651.818,
        3651.591, 3651.377, 3651.175, 3650.984, 3650.803, 3650.632,
        3650.470, 3650.316, 3650.170, 3650.031, 3649.899, 3649.773,
        3649.654, 3649.539, 3649.431, 3649.326, 3649.227, 3649.132,
        3649.041, 3648.954, 3648.871, 3648.791, 3648.714, 3648.641,
        3648.570, 3648.502, 3648.437, 3648.374, 3648.314, 3648.256,
        3648.200, 3648.146, 3648.094, 3648.043, 3647.995, 3647.948,
        3647.903, 3647.860, 3647.817, 3647.777, 3647.737, 3647.699,
        3647.662, 3647.627, 3647.592, 3647.559, 3647.526, 3647.495,
        3647.464, 3647.434, 3647.406, 3647.378, 3647.351, 3647.324,
        3647.299, 3647.274, 3647.250, 3647.226, 3647.203, 3647.181,
        3647.159, 3647.138, 3647.118, 3647.098, 3647.078, 3647.060,
        3647.041, 3647.023, 3647.006, 3646.988, 3646.972, 3646.955,
        3646.940, 3646.924, 3646.909, 3646.894, 3646.880, 3646.866,
        3646.852, 3646.839, 3646.825, 3646.813, 3646.800, 3646.788,
        3646.776, 3646.764, 3646.753, 3646.741, 3646.730, 3646.720,
        3646.709, 3646.699, 3646.689, 3646.679, 3646.669, 3646.660,
        3646.650, 3646.641, 3646.632, 3646.624, 3646.615, 3646.607,
        3646.598, 3646.590, 3646.582, 3646.575, 3646.567, 3646.560,
        3646.552, 3646.545, 3646.538, 3646.531, 3646.524, 3646.518,
        3646.511, 3646.505, 3646.498, 3646.492, 3646.486, 3646.480,
        3646.474, 3646.468, 3646.463, 3646.457, 3646.452, 3646.446,
        3646.441, 3646.436, 3646.431, 3646.426, 3646.421, 3646.416,
        3646.411, 3646.406, 3646.402, 3646.397, 3646.392, 3646.388,
        3646.384, 3646.379, 3646.375, 3646.371, 3646.367, 3646.363,
        3646.359, 3646.355, 3646.351, 3646.347, 3646.344, 3646.340,
        3646.336, 3646.333, 3646.329, 3646.326, 3646.322, 3646.319,
        3646.316, 3646.312, 3646.309, 3646.306, 3646.303, 3646.300,
        3646.297, 3646.294, 3646.291, 3646.288, 3646.285, 3646.282,
        3646.279, 3646.277, 3646.274, 3646.271, 3646.269, 3646.266,
        3646.263, 3646.261, 3646.258, 3646.256, 3646.253, 3646.251,
        3646.249, 3646.246, 3646.244, 3646.242, 3646.239, 3646.237,
        3646.235, 3646.233, 3646.231, 3646.229, 3646.226, 3646.224,
        3646.222, 3646.220, 3646.218, 3646.216, 3646.214, 3646.212,
        3646.211, 3646.209, 3646.207
    };
    static double Ehigh[] = { 12.08516, 12.74607, 13.05198, 13.21815, 13.31834, 13.38338,
        13.42796, 13.45985, 13.48345, 13.50139, 13.51536, 13.52644,
        13.53538, 13.54270, 13.54877, 13.55385, 13.55815, 13.56182,
        13.56498, 13.56772, 13.57011, 13.57221, 13.57406, 13.57570,
        13.57716, 13.57847, 13.57964, 13.58070, 13.58166, 13.58253,
        13.58333, 13.58405, 13.58471, 13.58532, 13.58588, 13.58639,
        13.58687, 13.58731, 13.58772, 13.58810, 13.58846, 13.58879,
        13.58910, 13.58938, 13.58966, 13.58991, 13.59015, 13.59037,
        13.59058, 13.59078, 13.59097, 13.59115, 13.59132, 13.59147,
        13.59163, 13.59177, 13.59190, 13.59203, 13.59216, 13.59227,
        13.59238, 13.59249, 13.59259, 13.59269, 13.59278, 13.59287,
        13.59295, 13.59304, 13.59311, 13.59319, 13.59326, 13.59333,
        13.59339, 13.59346, 13.59352, 13.59358, 13.59363, 13.59369,
        13.59374, 13.59379, 13.59384, 13.59388, 13.59393, 13.59397,
        13.59401, 13.59405, 13.59409, 13.59413, 13.59417, 13.59420,
        13.59424, 13.59427, 13.59430, 13.59433, 13.59436, 13.59439,
        13.59442, 13.59445, 13.59448, 13.59450, 13.59453, 13.59455,
        13.59458, 13.59460, 13.59462, 13.59464, 13.59467, 13.59469,
        13.59471, 13.59473, 13.59475, 13.59476, 13.59478, 13.59480,
        13.59482, 13.59483, 13.59485, 13.59487, 13.59488, 13.59490,
        13.59491, 13.59493, 13.59494, 13.59495, 13.59497, 13.59498,
        13.59499, 13.59501, 13.59502, 13.59503, 13.59504, 13.59505,
        13.59506, 13.59507, 13.59509, 13.59510, 13.59511, 13.59512,
        13.59513, 13.59514, 13.59515, 13.59515, 13.59516, 13.59517,
        13.59518, 13.59519, 13.59520, 13.59521, 13.59521, 13.59522,
        13.59523, 13.59524, 13.59524, 13.59525, 13.59526, 13.59527,
        13.59527, 13.59528, 13.59529, 13.59529, 13.59530, 13.59530,
        13.59531, 13.59532, 13.59532, 13.59533, 13.59533, 13.59534,
        13.59534, 13.59535, 13.59536, 13.59536, 13.59537, 13.59537,
        13.59538, 13.59538, 13.59539, 13.59539, 13.59539, 13.59540,
        13.59540, 13.59541, 13.59541, 13.59542, 13.59542, 13.59543,
        13.59543, 13.59543, 13.59544, 13.59544, 13.59544, 13.59545,
        13.59545, 13.59546, 13.59546, 13.59546, 13.59547, 13.59547,
        13.59547, 13.59548, 13.59548, 13.59548, 13.59549, 13.59549,
        13.59549, 13.59550, 13.59550, 13.59550, 13.59550, 13.59551,
        13.59551, 13.59551, 13.59552, 13.59552, 13.59552, 13.59552,
        13.59553, 13.59553, 13.59553, 13.59553, 13.59554, 13.59554,
        13.59554, 13.59554, 13.59555, 13.59555, 13.59555, 13.59555,
        13.59556, 13.59556, 13.59556, 13.59556, 13.59556, 13.59557,
        13.59557, 13.59557, 13.59557, 13.59557, 13.59558, 13.59558,
        13.59558, 13.59558, 13.59558, 13.59559, 13.59559, 13.59559,
        13.59559, 13.59559
    };
    extern float **bkap;
    int i, j, m, ifcore;
    double *wave0, *Eh, s, s0s;
    float rad = 2000.0;
    double minrad = 0.01;
    double fac = 4.0;
    static double lambda[4] = { 3900.0, 3900.0, 3900.0, 3900.0 };
    static int nmax[NTAU];
    static double Cutoff[NTAU];
    static double gffac3[251];
    double *gffac;
    static int flag = 0;
    static int flag1 = 0;
    static double cut;
    double cutmax, cutmin;
    extern int Ntau;
    int NM = 250;
    extern memo reset;

    if (reset.balmer == 1) {
        flag = 0;
        reset.balmer = 0;
    }
    gffac = gffac3 - 3;
    ifcore = 0;
    wave0 = w0 - 3;
    Eh = Ehigh - 3;

    if (wave < 3646.0 || wave > 7000.0)
        return;
    if (flag1 == 0) {
        for (i = 0; i < Ntau; i++) {
            Cutoff[i] = cutoff(model->T[i], model->Ne[i], &NM);
            nmax[i] = NM;
        }
        for (m = 3; m < 251; m++)
            gffac[m] = gffactor(m);
        flag1 = 1;
    }

    for (m = 3; m < 251; m++) {
        if (fabs(wave - wave0[m]) < 5.0)
            ifcore = 1;
    }
    if (ifcore == 0 && flag == 0) {
        lambda[1] = floor(wave);
        lambda[0] = lambda[1] - 1.0;
        lambda[2] = lambda[1] + 1.0;
        lambda[3] = lambda[1] + 2.0;
        for (i = 0; i < Ntau; i++) {
            bkap[0][i] = bkap[1][i] = bkap[2][i] = bkap[3][i] = 0.0;
        }
        for (m = 3; m < 251; m++) {
            rad = fac * (wave0[m] - wave0[m + 1]);
            rad = dmin(2000.0, rad);
            if (rad < minrad)
                rad = minrad;
            if (fabs(wave - wave0[m]) < rad) {
                for (i = 0; i < Ntau; i++) {
                    if (m > nmax[i] || wave < Cutoff[i])
                        continue;
                    for (j = 0; j < 4; j++)
                        bkap[j][i] += gffac[m] * unified(2, m, i, 10.19855, Eh[m], model, lambda[j]);
                }
            }
        }
        flag = 1;
    }

    if (ifcore == 0 && wave >= lambda[2]) {
        for (j = 0; j < 4; j++)
            lambda[j] += 1.0;
        for (i = 0; i < Ntau; i++) {
            for (j = 0; j < 3; j++)
                bkap[j][i] = bkap[j + 1][i];
            bkap[3][i] = 0.0;
        }
        for (m = 3; m < 251; m++) {
            rad = fac * (wave0[m] - wave0[m + 1]);
            rad = dmin(2000.0, rad);
            if (rad < minrad)
                rad = minrad;
            if (fabs(wave - wave0[m]) < rad) {
                for (i = 0; i < Ntau; i++) {
                    if (m > nmax[i] || wave < Cutoff[i])
                        continue;
                    bkap[3][i] += gffac[m] * unified(2, m, i, 10.19855, Eh[m], model, lambda[3]);
                }
            }
        }
    }

    if (ifcore == 0) {
        for (i = 0; i < Ntau; i++) {
            hkap[i] = bkap[3][i] * ((wave - lambda[0]) *
                                    (wave - lambda[1]) * (wave -
                                                          lambda
                                                          [2])) /
                6.0 -
                bkap[0][i] * ((wave - lambda[1]) *
                              (wave - lambda[2]) * (wave -
                                                    lambda[3])) /
                6.0 +
                bkap[1][i] * ((wave - lambda[0]) *
                              (wave - lambda[2]) * (wave - lambda[3])) / 2.0 - bkap[2][i] * ((wave - lambda[0]) * (wave - lambda[1]) * (wave - lambda[3])) / 2.0;
        }
    }
    if (ifcore == 1) {
        for (i = 0; i < Ntau; i++)
            hkap[i] = 0.0;
        for (m = 3; m < 251; m++) {
            rad = fac * (wave0[m] - wave0[m + 1]);
            rad = dmin(2000.0, rad);
            if (rad < minrad)
                rad = minrad;
            if (fabs(wave - wave0[m]) < rad) {
                for (i = 0; i < Ntau; i++) {
                    if (m > nmax[i] || wave < Cutoff[i])
                        continue;
                    hkap[i] += gffac[m] * unified(2, m, i, 10.19855, Eh[m], model, wave);
                }
            }
        }
        flag = 0;
    }
}

int Nmax(E)
double E;
{
    static double energy[251] = { 0.0, 0.0, 82259.272,
        97492.229, 102823.836, 105291.608, 106632.126, 107440.416,
        107965.027,
        108324.699, 108581.970, 108772.322, 108917.100, 109029.771,
        109119.173,
        109191.297, 109250.325, 109299.247, 109340.243, 109374.939,
        109404.561,
        109430.053, 109452.149, 109471.426, 109488.343, 109503.272,
        109516.511,
        109528.307, 109538.862, 109548.343, 109556.893, 109564.628,
        109571.650,
        109578.043, 109583.880, 109589.224, 109594.129, 109598.642,
        109602.803,
        109606.648, 109610.209, 109613.512, 109616.582, 109619.440,
        109622.106,
        109624.596, 109626.925, 109629.107, 109631.154, 109633.078,
        109634.886,
        109636.590, 109638.196, 109639.713, 109641.145, 109642.501,
        109643.784,
        109645.000, 109646.154, 109647.250, 109648.292, 109649.282,
        109650.226,
        109651.124, 109651.981, 109652.799, 109653.579, 109654.325,
        109655.039,
        109655.721, 109656.375, 109657.001, 109657.601, 109658.177,
        109658.729,
        109659.260, 109659.769, 109660.259, 109660.731, 109661.184,
        109661.621,
        109662.041, 109662.446, 109662.837, 109663.214, 109663.578,
        109663.929,
        109664.267, 109664.595, 109664.911, 109665.217, 109665.513,
        109665.800,
        109666.077, 109666.345, 109666.605, 109666.857, 109667.101,
        109667.338,
        109667.567, 109667.790, 109668.006, 109668.216, 109668.420,
        109668.618,
        109668.810, 109668.997, 109669.178, 109669.355, 109669.527,
        109669.694,
        109669.856, 109670.014, 109670.169, 109670.319, 109670.465,
        109670.607,
        109670.746, 109670.881, 109671.013, 109671.141, 109671.267,
        109671.389,
        109671.508, 109671.625, 109671.739, 109671.850, 109671.958,
        109672.064,
        109672.167, 109672.268, 109672.367, 109672.463, 109672.558,
        109672.650,
        109672.740, 109672.828, 109672.914, 109672.999, 109673.081,
        109673.162,
        109673.241, 109673.319, 109673.394, 109673.469, 109673.541,
        109673.613,
        109673.682, 109673.751, 109673.818, 109673.883, 109673.948,
        109674.011,
        109674.073, 109674.133, 109674.193, 109674.251, 109674.308,
        109674.365,
        109674.420, 109674.474, 109674.527, 109674.579, 109674.630,
        109674.680,
        109674.729, 109674.778, 109674.825, 109674.872, 109674.918,
        109674.963,
        109675.007, 109675.051, 109675.093, 109675.135, 109675.177,
        109675.217,
        109675.257, 109675.296, 109675.335, 109675.373, 109675.410,
        109675.447,
        109675.483, 109675.518, 109675.553, 109675.588, 109675.622,
        109675.655,
        109675.688, 109675.720, 109675.752, 109675.783, 109675.814,
        109675.844,
        109675.874, 109675.903, 109675.932, 109675.960, 109675.988,
        109676.016,
        109676.043, 109676.070, 109676.096, 109676.123, 109676.148,
        109676.173,
        109676.198, 109676.223, 109676.247, 109676.271, 109676.294,
        109676.318,
        109676.341, 109676.363, 109676.385, 109676.407, 109676.429,
        109676.450,
        109676.471, 109676.492, 109676.512, 109676.533, 109676.552,
        109676.572,
        109676.592, 109676.611, 109676.630, 109676.648, 109676.667,
        109676.685,
        109676.703, 109676.720, 109676.738, 109676.755, 109676.772,
        109676.789,
        109676.805, 109676.822, 109676.838, 109676.854, 109676.870,
        109676.885,
        109676.901, 109676.916, 109676.931, 109676.946, 109676.960,
        109676.975,
        109676.989, 109677.003
    };
    int k;

    for (k = 1; k < 251; k++) {
        if (E <= energy[k])
            return (k - 1);
    }
    return (250);
}

double cutoff(T, Ne, nm)
double Ne, T;
int *nm;
{
    double Eion = 109678.758;
    double E250 = 109677.003;
    double dE;
    double Cutoff;
    double fac = 1.0;

    /* Calculate lowering of ionization potential using Unsold Approx */
    /* fac = sqrt(10000.0/T); */

    dE = 5.61e-03 * fac * pow(Ne, 1.0 / 3.0);
    *nm = Nmax(Eion - dE);
    dE = dmax(dE, Eion - E250);

    Cutoff = 1.0e+08 / (27419.486 - dE) - 1.066;
    return (Cutoff);
}

/* 
   double cutoff(T,Ne,nm) double Ne,T; int *nm; { double Eion = 109678.758;
   double E250 = 109677.003; double dE; double Cutoff; double pd; double fac = 
   1.0;

   /* Calculate lowering of ionization potential using Debye Approx */

/* pd = 6.895*sqrt(T/(2.0*Ne)); dE = 1.16e-03*fac/pd; *nm = Nmax(Eion - dE);
   dE = dmax(dE,Eion-E250);

   Cutoff = 5.0 + 1.0e+08/(27419.486 - dE) - 1.066; return(Cutoff); } */

/* 

   double cutoff(T,Ne,nm) double T,Ne; int *nm; { static double energy[41] =
   {0.0,0.0,82259.272,97492.342,102823.904,
   105291.652,106632.157,107440.439,107965.045,108324.714,108581.98,
   108772.33,108917.11,109029.78,109119.18,109191.30,109250.33,109299.25,
   109340.25,109374.94,109404.57,109430.06,109452.15,109471.428,
   109488.346,109503.274,109516.513,109528.309,109538.863,109548.345,
   109556.894,109564.629,109571.651,109578.044,109583.881,109589.225,
   109594.130,109598.643,109602.804,109606.649,109610.210}; double Eion =
   109678.758; double E40 = 109610.210; double dE,Cutoff;

   *nm = 2+(int)pow(10.0,3.09-0.133*log10(Ne)); *nm = imin(40,*nm); dE = Eion
   - energy[*nm]; Cutoff = 1.0e+08/(27419.851 - dE) - 1.05; return(Cutoff); }

 */

double gffactor(m)
int m;
{
    /* This routine introduces a "factor" <= 1.0 into the computation of the
       gf value for the various Balmer lines.  The purpose is to bring the
       Balmer convergence into accord with observations.  Without the
       following factors, the synthetic spectrum shows a large dip between
       about 3660 and 3670 A, which is not supported by observations.  The
       below approximate factors were calculated on Jan 29, 1995 by comparison 
       with the spectrum of HD 221741 from the stellar spectrum library of
       Jacoby et al, using a Kurucz model with Teff = 8500 K and logg = 3.8.
       The resulting fit is good.  This "fudge" is entirely empirical and has
       no theoretical basis.  To erase it, simply remove the comments from the 
       first line "return(1.0)".  */

    /* return(1.0) */
    if (m < 14)
        return (1.0);
    else if (m == 14)
        return (0.9);
    else if (m == 15)
        return (0.8);
    else if (m == 16)
        return (0.7);
    else
        return (0.6);
}
