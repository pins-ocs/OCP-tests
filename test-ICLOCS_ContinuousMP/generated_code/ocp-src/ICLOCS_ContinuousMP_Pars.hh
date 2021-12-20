/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Pars.hh                                    |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef ICLOCS_CONTINUOUSMPPARS_DOT_HH
#define ICLOCS_CONTINUOUSMPPARS_DOT_HH

#define numBc                    80
#define numModelPars             4
#define numConstraint1D          60
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 80
#define numLvars                 80
#define numUvars                 0
#define numOMEGAvars             80
#define numQvars                 1
#define numPvars                 20
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1           0
#define iX_x2           1
#define iX_x3           2
#define iX_x4           3
#define iX_x5           4
#define iX_x6           5
#define iX_x7           6
#define iX_x8           7
#define iX_x9           8
#define iX_x10          9
#define iX_x11          10
#define iX_x12          11
#define iX_x13          12
#define iX_x14          13
#define iX_x15          14
#define iX_x16          15
#define iX_x17          16
#define iX_x18          17
#define iX_x19          18
#define iX_x20          19
#define iX_y1           20
#define iX_y2           21
#define iX_y3           22
#define iX_y4           23
#define iX_y5           24
#define iX_y6           25
#define iX_y7           26
#define iX_y8           27
#define iX_y9           28
#define iX_y10          29
#define iX_y11          30
#define iX_y12          31
#define iX_y13          32
#define iX_y14          33
#define iX_y15          34
#define iX_y16          35
#define iX_y17          36
#define iX_y18          37
#define iX_y19          38
#define iX_y20          39
#define iX_xx1          40
#define iX_xx2          41
#define iX_xx3          42
#define iX_xx4          43
#define iX_xx5          44
#define iX_xx6          45
#define iX_xx7          46
#define iX_xx8          47
#define iX_xx9          48
#define iX_xx10         49
#define iX_xx11         50
#define iX_xx12         51
#define iX_xx13         52
#define iX_xx14         53
#define iX_xx15         54
#define iX_xx16         55
#define iX_xx17         56
#define iX_xx18         57
#define iX_xx19         58
#define iX_xx20         59
#define iX_yy1          60
#define iX_yy2          61
#define iX_yy3          62
#define iX_yy4          63
#define iX_yy5          64
#define iX_yy6          65
#define iX_yy7          66
#define iX_yy8          67
#define iX_yy9          68
#define iX_yy10         69
#define iX_yy11         70
#define iX_yy12         71
#define iX_yy13         72
#define iX_yy14         73
#define iX_yy15         74
#define iX_yy16         75
#define iX_yy17         76
#define iX_yy18         77
#define iX_yy19         78
#define iX_yy20         79

// Lvars
#define iL_lambda1__xo  0
#define iL_lambda2__xo  1
#define iL_lambda3__xo  2
#define iL_lambda4__xo  3
#define iL_lambda5__xo  4
#define iL_lambda6__xo  5
#define iL_lambda7__xo  6
#define iL_lambda8__xo  7
#define iL_lambda9__xo  8
#define iL_lambda10__xo 9
#define iL_lambda11__xo 10
#define iL_lambda12__xo 11
#define iL_lambda13__xo 12
#define iL_lambda14__xo 13
#define iL_lambda15__xo 14
#define iL_lambda16__xo 15
#define iL_lambda17__xo 16
#define iL_lambda18__xo 17
#define iL_lambda19__xo 18
#define iL_lambda20__xo 19
#define iL_lambda21__xo 20
#define iL_lambda22__xo 21
#define iL_lambda23__xo 22
#define iL_lambda24__xo 23
#define iL_lambda25__xo 24
#define iL_lambda26__xo 25
#define iL_lambda27__xo 26
#define iL_lambda28__xo 27
#define iL_lambda29__xo 28
#define iL_lambda30__xo 29
#define iL_lambda31__xo 30
#define iL_lambda32__xo 31
#define iL_lambda33__xo 32
#define iL_lambda34__xo 33
#define iL_lambda35__xo 34
#define iL_lambda36__xo 35
#define iL_lambda37__xo 36
#define iL_lambda38__xo 37
#define iL_lambda39__xo 38
#define iL_lambda40__xo 39
#define iL_lambda41__xo 40
#define iL_lambda42__xo 41
#define iL_lambda43__xo 42
#define iL_lambda44__xo 43
#define iL_lambda45__xo 44
#define iL_lambda46__xo 45
#define iL_lambda47__xo 46
#define iL_lambda48__xo 47
#define iL_lambda49__xo 48
#define iL_lambda50__xo 49
#define iL_lambda51__xo 50
#define iL_lambda52__xo 51
#define iL_lambda53__xo 52
#define iL_lambda54__xo 53
#define iL_lambda55__xo 54
#define iL_lambda56__xo 55
#define iL_lambda57__xo 56
#define iL_lambda58__xo 57
#define iL_lambda59__xo 58
#define iL_lambda60__xo 59
#define iL_lambda61__xo 60
#define iL_lambda62__xo 61
#define iL_lambda63__xo 62
#define iL_lambda64__xo 63
#define iL_lambda65__xo 64
#define iL_lambda66__xo 65
#define iL_lambda67__xo 66
#define iL_lambda68__xo 67
#define iL_lambda69__xo 68
#define iL_lambda70__xo 69
#define iL_lambda71__xo 70
#define iL_lambda72__xo 71
#define iL_lambda73__xo 72
#define iL_lambda74__xo 73
#define iL_lambda75__xo 74
#define iL_lambda76__xo 75
#define iL_lambda77__xo 76
#define iL_lambda78__xo 77
#define iL_lambda79__xo 78
#define iL_lambda80__xo 79

// Uvars

// Qvars
#define iQ_zeta         0

// Pvars
#define iP_u1           0
#define iP_u2           1
#define iP_u3           2
#define iP_u4           3
#define iP_u5           4
#define iP_u6           5
#define iP_u7           6
#define iP_u8           7
#define iP_u9           8
#define iP_u10          9
#define iP_u11          10
#define iP_u12          11
#define iP_u13          12
#define iP_u14          13
#define iP_u15          14
#define iP_u16          15
#define iP_u17          16
#define iP_u18          17
#define iP_u19          18
#define iP_u20          19

// ModelPars Maps
#define iM_xy_eps0      0
#define iM_xy_eps1      1
#define iM_xy_tol0      2
#define iM_xy_tol1      3

#endif

// EOF: ICLOCS_ContinuousMP_Pars.hh
