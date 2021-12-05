/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 10/12/2021                                       |
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


#include "ICLOCS_ContinuousMP.hh"
#include "ICLOCS_ContinuousMP_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wunused-macros"
#elif defined(__llvm__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-macros"
#elif defined(_MSC_VER)
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#endif

// map user defined functions and objects with macros
#define ALIAS_yy20Limitation_DD(__t1) yy20Limitation.DD( __t1)
#define ALIAS_yy20Limitation_D(__t1) yy20Limitation.D( __t1)
#define ALIAS_xx20Limitation_DD(__t1) xx20Limitation.DD( __t1)
#define ALIAS_xx20Limitation_D(__t1) xx20Limitation.D( __t1)
#define ALIAS_yy19Limitation_DD(__t1) yy19Limitation.DD( __t1)
#define ALIAS_yy19Limitation_D(__t1) yy19Limitation.D( __t1)
#define ALIAS_xx19Limitation_DD(__t1) xx19Limitation.DD( __t1)
#define ALIAS_xx19Limitation_D(__t1) xx19Limitation.D( __t1)
#define ALIAS_yy18Limitation_DD(__t1) yy18Limitation.DD( __t1)
#define ALIAS_yy18Limitation_D(__t1) yy18Limitation.D( __t1)
#define ALIAS_xx18Limitation_DD(__t1) xx18Limitation.DD( __t1)
#define ALIAS_xx18Limitation_D(__t1) xx18Limitation.D( __t1)
#define ALIAS_yy17Limitation_DD(__t1) yy17Limitation.DD( __t1)
#define ALIAS_yy17Limitation_D(__t1) yy17Limitation.D( __t1)
#define ALIAS_xx17Limitation_DD(__t1) xx17Limitation.DD( __t1)
#define ALIAS_xx17Limitation_D(__t1) xx17Limitation.D( __t1)
#define ALIAS_yy16Limitation_DD(__t1) yy16Limitation.DD( __t1)
#define ALIAS_yy16Limitation_D(__t1) yy16Limitation.D( __t1)
#define ALIAS_xx16Limitation_DD(__t1) xx16Limitation.DD( __t1)
#define ALIAS_xx16Limitation_D(__t1) xx16Limitation.D( __t1)
#define ALIAS_yy15Limitation_DD(__t1) yy15Limitation.DD( __t1)
#define ALIAS_yy15Limitation_D(__t1) yy15Limitation.D( __t1)
#define ALIAS_xx15Limitation_DD(__t1) xx15Limitation.DD( __t1)
#define ALIAS_xx15Limitation_D(__t1) xx15Limitation.D( __t1)
#define ALIAS_yy14Limitation_DD(__t1) yy14Limitation.DD( __t1)
#define ALIAS_yy14Limitation_D(__t1) yy14Limitation.D( __t1)
#define ALIAS_xx14Limitation_DD(__t1) xx14Limitation.DD( __t1)
#define ALIAS_xx14Limitation_D(__t1) xx14Limitation.D( __t1)
#define ALIAS_yy13Limitation_DD(__t1) yy13Limitation.DD( __t1)
#define ALIAS_yy13Limitation_D(__t1) yy13Limitation.D( __t1)
#define ALIAS_xx13Limitation_DD(__t1) xx13Limitation.DD( __t1)
#define ALIAS_xx13Limitation_D(__t1) xx13Limitation.D( __t1)
#define ALIAS_yy12Limitation_DD(__t1) yy12Limitation.DD( __t1)
#define ALIAS_yy12Limitation_D(__t1) yy12Limitation.D( __t1)
#define ALIAS_xx12Limitation_DD(__t1) xx12Limitation.DD( __t1)
#define ALIAS_xx12Limitation_D(__t1) xx12Limitation.D( __t1)
#define ALIAS_yy11Limitation_DD(__t1) yy11Limitation.DD( __t1)
#define ALIAS_yy11Limitation_D(__t1) yy11Limitation.D( __t1)
#define ALIAS_xx11Limitation_DD(__t1) xx11Limitation.DD( __t1)
#define ALIAS_xx11Limitation_D(__t1) xx11Limitation.D( __t1)
#define ALIAS_yy10Limitation_DD(__t1) yy10Limitation.DD( __t1)
#define ALIAS_yy10Limitation_D(__t1) yy10Limitation.D( __t1)
#define ALIAS_xx10Limitation_DD(__t1) xx10Limitation.DD( __t1)
#define ALIAS_xx10Limitation_D(__t1) xx10Limitation.D( __t1)
#define ALIAS_yy9Limitation_DD(__t1) yy9Limitation.DD( __t1)
#define ALIAS_yy9Limitation_D(__t1) yy9Limitation.D( __t1)
#define ALIAS_xx9Limitation_DD(__t1) xx9Limitation.DD( __t1)
#define ALIAS_xx9Limitation_D(__t1) xx9Limitation.D( __t1)
#define ALIAS_yy8Limitation_DD(__t1) yy8Limitation.DD( __t1)
#define ALIAS_yy8Limitation_D(__t1) yy8Limitation.D( __t1)
#define ALIAS_xx8Limitation_DD(__t1) xx8Limitation.DD( __t1)
#define ALIAS_xx8Limitation_D(__t1) xx8Limitation.D( __t1)
#define ALIAS_yy7Limitation_DD(__t1) yy7Limitation.DD( __t1)
#define ALIAS_yy7Limitation_D(__t1) yy7Limitation.D( __t1)
#define ALIAS_xx7Limitation_DD(__t1) xx7Limitation.DD( __t1)
#define ALIAS_xx7Limitation_D(__t1) xx7Limitation.D( __t1)
#define ALIAS_yy6Limitation_DD(__t1) yy6Limitation.DD( __t1)
#define ALIAS_yy6Limitation_D(__t1) yy6Limitation.D( __t1)
#define ALIAS_xx6Limitation_DD(__t1) xx6Limitation.DD( __t1)
#define ALIAS_xx6Limitation_D(__t1) xx6Limitation.D( __t1)
#define ALIAS_yy5Limitation_DD(__t1) yy5Limitation.DD( __t1)
#define ALIAS_yy5Limitation_D(__t1) yy5Limitation.D( __t1)
#define ALIAS_xx5Limitation_DD(__t1) xx5Limitation.DD( __t1)
#define ALIAS_xx5Limitation_D(__t1) xx5Limitation.D( __t1)
#define ALIAS_yy4Limitation_DD(__t1) yy4Limitation.DD( __t1)
#define ALIAS_yy4Limitation_D(__t1) yy4Limitation.D( __t1)
#define ALIAS_xx4Limitation_DD(__t1) xx4Limitation.DD( __t1)
#define ALIAS_xx4Limitation_D(__t1) xx4Limitation.D( __t1)
#define ALIAS_yy3Limitation_DD(__t1) yy3Limitation.DD( __t1)
#define ALIAS_yy3Limitation_D(__t1) yy3Limitation.D( __t1)
#define ALIAS_xx3Limitation_DD(__t1) xx3Limitation.DD( __t1)
#define ALIAS_xx3Limitation_D(__t1) xx3Limitation.D( __t1)
#define ALIAS_yy2Limitation_DD(__t1) yy2Limitation.DD( __t1)
#define ALIAS_yy2Limitation_D(__t1) yy2Limitation.D( __t1)
#define ALIAS_xx2Limitation_DD(__t1) xx2Limitation.DD( __t1)
#define ALIAS_xx2Limitation_D(__t1) xx2Limitation.D( __t1)
#define ALIAS_yy1Limitation_DD(__t1) yy1Limitation.DD( __t1)
#define ALIAS_yy1Limitation_D(__t1) yy1Limitation.D( __t1)
#define ALIAS_xx1Limitation_DD(__t1) xx1Limitation.DD( __t1)
#define ALIAS_xx1Limitation_D(__t1) xx1Limitation.D( __t1)
#define ALIAS_u20Limitation_DD(__t1) u20Limitation.DD( __t1)
#define ALIAS_u20Limitation_D(__t1) u20Limitation.D( __t1)
#define ALIAS_u19Limitation_DD(__t1) u19Limitation.DD( __t1)
#define ALIAS_u19Limitation_D(__t1) u19Limitation.D( __t1)
#define ALIAS_u18Limitation_DD(__t1) u18Limitation.DD( __t1)
#define ALIAS_u18Limitation_D(__t1) u18Limitation.D( __t1)
#define ALIAS_u17Limitation_DD(__t1) u17Limitation.DD( __t1)
#define ALIAS_u17Limitation_D(__t1) u17Limitation.D( __t1)
#define ALIAS_u16Limitation_DD(__t1) u16Limitation.DD( __t1)
#define ALIAS_u16Limitation_D(__t1) u16Limitation.D( __t1)
#define ALIAS_u15Limitation_DD(__t1) u15Limitation.DD( __t1)
#define ALIAS_u15Limitation_D(__t1) u15Limitation.D( __t1)
#define ALIAS_u14Limitation_DD(__t1) u14Limitation.DD( __t1)
#define ALIAS_u14Limitation_D(__t1) u14Limitation.D( __t1)
#define ALIAS_u13Limitation_DD(__t1) u13Limitation.DD( __t1)
#define ALIAS_u13Limitation_D(__t1) u13Limitation.D( __t1)
#define ALIAS_u12Limitation_DD(__t1) u12Limitation.DD( __t1)
#define ALIAS_u12Limitation_D(__t1) u12Limitation.D( __t1)
#define ALIAS_u11Limitation_DD(__t1) u11Limitation.DD( __t1)
#define ALIAS_u11Limitation_D(__t1) u11Limitation.D( __t1)
#define ALIAS_u10Limitation_DD(__t1) u10Limitation.DD( __t1)
#define ALIAS_u10Limitation_D(__t1) u10Limitation.D( __t1)
#define ALIAS_u9Limitation_DD(__t1) u9Limitation.DD( __t1)
#define ALIAS_u9Limitation_D(__t1) u9Limitation.D( __t1)
#define ALIAS_u8Limitation_DD(__t1) u8Limitation.DD( __t1)
#define ALIAS_u8Limitation_D(__t1) u8Limitation.D( __t1)
#define ALIAS_u7Limitation_DD(__t1) u7Limitation.DD( __t1)
#define ALIAS_u7Limitation_D(__t1) u7Limitation.D( __t1)
#define ALIAS_u6Limitation_DD(__t1) u6Limitation.DD( __t1)
#define ALIAS_u6Limitation_D(__t1) u6Limitation.D( __t1)
#define ALIAS_u5Limitation_DD(__t1) u5Limitation.DD( __t1)
#define ALIAS_u5Limitation_D(__t1) u5Limitation.D( __t1)
#define ALIAS_u4Limitation_DD(__t1) u4Limitation.DD( __t1)
#define ALIAS_u4Limitation_D(__t1) u4Limitation.D( __t1)
#define ALIAS_u3Limitation_DD(__t1) u3Limitation.DD( __t1)
#define ALIAS_u3Limitation_D(__t1) u3Limitation.D( __t1)
#define ALIAS_u2Limitation_DD(__t1) u2Limitation.DD( __t1)
#define ALIAS_u2Limitation_D(__t1) u2Limitation.D( __t1)
#define ALIAS_u1Limitation_DD(__t1) u1Limitation.DD( __t1)
#define ALIAS_u1Limitation_D(__t1) u1Limitation.D( __t1)


namespace ICLOCS_ContinuousMPDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  ICLOCS_ContinuousMP::g_numEqns() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[80], LM__[80];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    XM__[8] = (XL__[8]+XR__[8])/2;
    XM__[9] = (XL__[9]+XR__[9])/2;
    XM__[10] = (XL__[10]+XR__[10])/2;
    XM__[11] = (XL__[11]+XR__[11])/2;
    XM__[12] = (XL__[12]+XR__[12])/2;
    XM__[13] = (XL__[13]+XR__[13])/2;
    XM__[14] = (XL__[14]+XR__[14])/2;
    XM__[15] = (XL__[15]+XR__[15])/2;
    XM__[16] = (XL__[16]+XR__[16])/2;
    XM__[17] = (XL__[17]+XR__[17])/2;
    XM__[18] = (XL__[18]+XR__[18])/2;
    XM__[19] = (XL__[19]+XR__[19])/2;
    XM__[20] = (XL__[20]+XR__[20])/2;
    XM__[21] = (XL__[21]+XR__[21])/2;
    XM__[22] = (XL__[22]+XR__[22])/2;
    XM__[23] = (XL__[23]+XR__[23])/2;
    XM__[24] = (XL__[24]+XR__[24])/2;
    XM__[25] = (XL__[25]+XR__[25])/2;
    XM__[26] = (XL__[26]+XR__[26])/2;
    XM__[27] = (XL__[27]+XR__[27])/2;
    XM__[28] = (XL__[28]+XR__[28])/2;
    XM__[29] = (XL__[29]+XR__[29])/2;
    XM__[30] = (XL__[30]+XR__[30])/2;
    XM__[31] = (XL__[31]+XR__[31])/2;
    XM__[32] = (XL__[32]+XR__[32])/2;
    XM__[33] = (XL__[33]+XR__[33])/2;
    XM__[34] = (XL__[34]+XR__[34])/2;
    XM__[35] = (XL__[35]+XR__[35])/2;
    XM__[36] = (XL__[36]+XR__[36])/2;
    XM__[37] = (XL__[37]+XR__[37])/2;
    XM__[38] = (XL__[38]+XR__[38])/2;
    XM__[39] = (XL__[39]+XR__[39])/2;
    XM__[40] = (XL__[40]+XR__[40])/2;
    XM__[41] = (XL__[41]+XR__[41])/2;
    XM__[42] = (XL__[42]+XR__[42])/2;
    XM__[43] = (XL__[43]+XR__[43])/2;
    XM__[44] = (XL__[44]+XR__[44])/2;
    XM__[45] = (XL__[45]+XR__[45])/2;
    XM__[46] = (XL__[46]+XR__[46])/2;
    XM__[47] = (XL__[47]+XR__[47])/2;
    XM__[48] = (XL__[48]+XR__[48])/2;
    XM__[49] = (XL__[49]+XR__[49])/2;
    XM__[50] = (XL__[50]+XR__[50])/2;
    XM__[51] = (XL__[51]+XR__[51])/2;
    XM__[52] = (XL__[52]+XR__[52])/2;
    XM__[53] = (XL__[53]+XR__[53])/2;
    XM__[54] = (XL__[54]+XR__[54])/2;
    XM__[55] = (XL__[55]+XR__[55])/2;
    XM__[56] = (XL__[56]+XR__[56])/2;
    XM__[57] = (XL__[57]+XR__[57])/2;
    XM__[58] = (XL__[58]+XR__[58])/2;
    XM__[59] = (XL__[59]+XR__[59])/2;
    XM__[60] = (XL__[60]+XR__[60])/2;
    XM__[61] = (XL__[61]+XR__[61])/2;
    XM__[62] = (XL__[62]+XR__[62])/2;
    XM__[63] = (XL__[63]+XR__[63])/2;
    XM__[64] = (XL__[64]+XR__[64])/2;
    XM__[65] = (XL__[65]+XR__[65])/2;
    XM__[66] = (XL__[66]+XR__[66])/2;
    XM__[67] = (XL__[67]+XR__[67])/2;
    XM__[68] = (XL__[68]+XR__[68])/2;
    XM__[69] = (XL__[69]+XR__[69])/2;
    XM__[70] = (XL__[70]+XR__[70])/2;
    XM__[71] = (XL__[71]+XR__[71])/2;
    XM__[72] = (XL__[72]+XR__[72])/2;
    XM__[73] = (XL__[73]+XR__[73])/2;
    XM__[74] = (XL__[74]+XR__[74])/2;
    XM__[75] = (XL__[75]+XR__[75])/2;
    XM__[76] = (XL__[76]+XR__[76])/2;
    XM__[77] = (XL__[77]+XR__[77])/2;
    XM__[78] = (XL__[78]+XR__[78])/2;
    XM__[79] = (XL__[79]+XR__[79])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
    LM__[8] = (LL__[8]+LR__[8])/2;
    LM__[9] = (LL__[9]+LR__[9])/2;
    LM__[10] = (LL__[10]+LR__[10])/2;
    LM__[11] = (LL__[11]+LR__[11])/2;
    LM__[12] = (LL__[12]+LR__[12])/2;
    LM__[13] = (LL__[13]+LR__[13])/2;
    LM__[14] = (LL__[14]+LR__[14])/2;
    LM__[15] = (LL__[15]+LR__[15])/2;
    LM__[16] = (LL__[16]+LR__[16])/2;
    LM__[17] = (LL__[17]+LR__[17])/2;
    LM__[18] = (LL__[18]+LR__[18])/2;
    LM__[19] = (LL__[19]+LR__[19])/2;
    LM__[20] = (LL__[20]+LR__[20])/2;
    LM__[21] = (LL__[21]+LR__[21])/2;
    LM__[22] = (LL__[22]+LR__[22])/2;
    LM__[23] = (LL__[23]+LR__[23])/2;
    LM__[24] = (LL__[24]+LR__[24])/2;
    LM__[25] = (LL__[25]+LR__[25])/2;
    LM__[26] = (LL__[26]+LR__[26])/2;
    LM__[27] = (LL__[27]+LR__[27])/2;
    LM__[28] = (LL__[28]+LR__[28])/2;
    LM__[29] = (LL__[29]+LR__[29])/2;
    LM__[30] = (LL__[30]+LR__[30])/2;
    LM__[31] = (LL__[31]+LR__[31])/2;
    LM__[32] = (LL__[32]+LR__[32])/2;
    LM__[33] = (LL__[33]+LR__[33])/2;
    LM__[34] = (LL__[34]+LR__[34])/2;
    LM__[35] = (LL__[35]+LR__[35])/2;
    LM__[36] = (LL__[36]+LR__[36])/2;
    LM__[37] = (LL__[37]+LR__[37])/2;
    LM__[38] = (LL__[38]+LR__[38])/2;
    LM__[39] = (LL__[39]+LR__[39])/2;
    LM__[40] = (LL__[40]+LR__[40])/2;
    LM__[41] = (LL__[41]+LR__[41])/2;
    LM__[42] = (LL__[42]+LR__[42])/2;
    LM__[43] = (LL__[43]+LR__[43])/2;
    LM__[44] = (LL__[44]+LR__[44])/2;
    LM__[45] = (LL__[45]+LR__[45])/2;
    LM__[46] = (LL__[46]+LR__[46])/2;
    LM__[47] = (LL__[47]+LR__[47])/2;
    LM__[48] = (LL__[48]+LR__[48])/2;
    LM__[49] = (LL__[49]+LR__[49])/2;
    LM__[50] = (LL__[50]+LR__[50])/2;
    LM__[51] = (LL__[51]+LR__[51])/2;
    LM__[52] = (LL__[52]+LR__[52])/2;
    LM__[53] = (LL__[53]+LR__[53])/2;
    LM__[54] = (LL__[54]+LR__[54])/2;
    LM__[55] = (LL__[55]+LR__[55])/2;
    LM__[56] = (LL__[56]+LR__[56])/2;
    LM__[57] = (LL__[57]+LR__[57])/2;
    LM__[58] = (LL__[58]+LR__[58])/2;
    LM__[59] = (LL__[59]+LR__[59])/2;
    LM__[60] = (LL__[60]+LR__[60])/2;
    LM__[61] = (LL__[61]+LR__[61])/2;
    LM__[62] = (LL__[62]+LR__[62])/2;
    LM__[63] = (LL__[63]+LR__[63])/2;
    LM__[64] = (LL__[64]+LR__[64])/2;
    LM__[65] = (LL__[65]+LR__[65])/2;
    LM__[66] = (LL__[66]+LR__[66])/2;
    LM__[67] = (LL__[67]+LR__[67])/2;
    LM__[68] = (LL__[68]+LR__[68])/2;
    LM__[69] = (LL__[69]+LR__[69])/2;
    LM__[70] = (LL__[70]+LR__[70])/2;
    LM__[71] = (LL__[71]+LR__[71])/2;
    LM__[72] = (LL__[72]+LR__[72])/2;
    LM__[73] = (LL__[73]+LR__[73])/2;
    LM__[74] = (LL__[74]+LR__[74])/2;
    LM__[75] = (LL__[75]+LR__[75])/2;
    LM__[76] = (LL__[76]+LR__[76])/2;
    LM__[77] = (LL__[77]+LR__[77])/2;
    LM__[78] = (LL__[78]+LR__[78])/2;
    LM__[79] = (LL__[79]+LR__[79])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DgDxlxlp_numRows() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DgDxlxlp_numCols() const
  { return 340; }

  integer
  ICLOCS_ContinuousMP::DgDxlxlp_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DgDu_numRows() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DgDu_numCols() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DgDu_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  ICLOCS_ContinuousMP::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    // no controls to compute
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    // no controls to compute
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  ICLOCS_ContinuousMP::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = pow(V__[16] - X__[iX_y17], 2);
    real_type t8   = pow(V__[17] - X__[iX_y18], 2);
    real_type t12  = pow(V__[18] - X__[iX_y19], 2);
    real_type t16  = pow(V__[19] - X__[iX_y20], 2);
    real_type t20  = pow(V__[12] - X__[iX_y13], 2);
    real_type t24  = pow(V__[13] - X__[iX_y14], 2);
    real_type t28  = pow(V__[14] - X__[iX_y15], 2);
    real_type t32  = pow(V__[15] - X__[iX_y16], 2);
    real_type t36  = pow(V__[8] - X__[iX_y9], 2);
    real_type t40  = pow(V__[9] - X__[iX_y10], 2);
    real_type t44  = pow(V__[10] - X__[iX_y11], 2);
    real_type t48  = pow(V__[11] - X__[iX_y12], 2);
    real_type t52  = pow(V__[5] - X__[iX_y6], 2);
    real_type t56  = pow(V__[6] - X__[iX_y7], 2);
    real_type t60  = pow(V__[7] - X__[iX_y8], 2);
    real_type t64  = pow(V__[1] - X__[iX_y2], 2);
    real_type t68  = pow(V__[2] - X__[iX_y3], 2);
    real_type t69  = t4 + t8 + t12 + t16 + t20 + t24 + t28 + t32 + t36 + t40 + t44 + t48 + t52 + t56 + t60 + t64 + t68;
    real_type t73  = pow(V__[3] - X__[iX_y4], 2);
    real_type t77  = pow(V__[4] - X__[iX_y5], 2);
    real_type t80  = sin(X__[iX_x18]);
    real_type t81  = P__[iP_u18];
    real_type t83  = pow(V__[37] - t80 - t81, 2);
    real_type t85  = X__[iX_xx18];
    real_type t86  = sin(t85);
    real_type t89  = pow(V__[77] - 0.2e0 * t86 - t81, 2);
    real_type t93  = pow(V__[0] - X__[iX_y1], 2);
    real_type t95  = X__[iX_xx16];
    real_type t96  = sin(t95);
    real_type t98  = P__[iP_u16];
    real_type t100 = pow(V__[75] - 0.2e0 * t96 - t98, 2);
    real_type t103 = sin(X__[iX_x17]);
    real_type t104 = P__[iP_u17];
    real_type t106 = pow(V__[36] - t103 - t104, 2);
    real_type t108 = X__[iX_xx17];
    real_type t109 = sin(t108);
    real_type t112 = pow(V__[76] - 0.2e0 * t109 - t104, 2);
    real_type t115 = sin(X__[iX_x15]);
    real_type t116 = P__[iP_u15];
    real_type t118 = pow(V__[34] - t115 - t116, 2);
    real_type t120 = X__[iX_xx15];
    real_type t121 = sin(t120);
    real_type t124 = pow(V__[74] - 0.2e0 * t121 - t116, 2);
    real_type t127 = sin(X__[iX_x16]);
    real_type t129 = pow(V__[35] - t127 - t98, 2);
    real_type t131 = X__[iX_xx13];
    real_type t132 = sin(t131);
    real_type t134 = P__[iP_u13];
    real_type t136 = pow(V__[72] - 0.2e0 * t132 - t134, 2);
    real_type t139 = sin(X__[iX_x14]);
    real_type t140 = P__[iP_u14];
    real_type t142 = pow(V__[33] - t139 - t140, 2);
    real_type t144 = X__[iX_xx14];
    real_type t145 = sin(t144);
    real_type t148 = pow(V__[73] - 0.2e0 * t145 - t140, 2);
    real_type t151 = sin(X__[iX_x12]);
    real_type t152 = P__[iP_u12];
    real_type t154 = pow(V__[31] - t151 - t152, 2);
    real_type t156 = X__[iX_xx12];
    real_type t157 = sin(t156);
    real_type t160 = pow(V__[71] - 0.2e0 * t157 - t152, 2);
    real_type t163 = sin(X__[iX_x13]);
    real_type t165 = pow(V__[32] - t163 - t134, 2);
    real_type t168 = sin(X__[iX_x10]);
    real_type t169 = P__[iP_u10];
    real_type t171 = pow(V__[29] - t168 - t169, 2);
    real_type t172 = t73 + t77 + t83 + t89 + t93 + t100 + t106 + t112 + t118 + t124 + t129 + t136 + t142 + t148 + t154 + t160 + t165 + t171;
    real_type t175 = X__[iX_xx11];
    real_type t176 = sin(t175);
    real_type t178 = P__[iP_u11];
    real_type t180 = pow(V__[70] - 0.2e0 * t176 - t178, 2);
    real_type t183 = sin(X__[iX_x11]);
    real_type t185 = pow(V__[30] - t183 - t178, 2);
    real_type t187 = X__[iX_xx9];
    real_type t188 = sin(t187);
    real_type t190 = P__[iP_u9];
    real_type t192 = pow(V__[68] - 0.2e0 * t188 - t190, 2);
    real_type t195 = sin(X__[iX_x9]);
    real_type t197 = pow(V__[28] - t195 - t190, 2);
    real_type t199 = X__[iX_xx10];
    real_type t200 = sin(t199);
    real_type t203 = pow(V__[69] - 0.2e0 * t200 - t169, 2);
    real_type t205 = X__[iX_xx8];
    real_type t206 = sin(t205);
    real_type t208 = P__[iP_u8];
    real_type t210 = pow(V__[67] - 0.2e0 * t206 - t208, 2);
    real_type t213 = sin(X__[iX_x8]);
    real_type t215 = pow(V__[27] - t213 - t208, 2);
    real_type t218 = sin(X__[iX_x7]);
    real_type t219 = P__[iP_u7];
    real_type t221 = pow(V__[26] - t218 - t219, 2);
    real_type t223 = X__[iX_xx7];
    real_type t224 = sin(t223);
    real_type t227 = pow(V__[66] - 0.2e0 * t224 - t219, 2);
    real_type t229 = X__[iX_xx6];
    real_type t230 = sin(t229);
    real_type t232 = P__[iP_u6];
    real_type t234 = pow(V__[65] - 0.2e0 * t230 - t232, 2);
    real_type t237 = sin(X__[iX_x6]);
    real_type t239 = pow(V__[25] - t237 - t232, 2);
    real_type t242 = sin(X__[iX_x4]);
    real_type t243 = P__[iP_u4];
    real_type t245 = pow(V__[23] - t242 - t243, 2);
    real_type t247 = X__[iX_xx5];
    real_type t248 = sin(t247);
    real_type t250 = P__[iP_u5];
    real_type t252 = pow(V__[64] - 0.2e0 * t248 - t250, 2);
    real_type t255 = sin(X__[iX_x5]);
    real_type t257 = pow(V__[24] - t255 - t250, 2);
    real_type t259 = X__[iX_xx3];
    real_type t260 = sin(t259);
    real_type t262 = P__[iP_u3];
    real_type t264 = pow(V__[62] - 0.2e0 * t260 - t262, 2);
    real_type t267 = sin(X__[iX_x3]);
    real_type t269 = pow(V__[22] - t267 - t262, 2);
    real_type t271 = X__[iX_xx4];
    real_type t272 = sin(t271);
    real_type t275 = pow(V__[63] - 0.2e0 * t272 - t243, 2);
    real_type t276 = t180 + t185 + t192 + t197 + t203 + t210 + t215 + t221 + t227 + t234 + t239 + t245 + t252 + t257 + t264 + t269 + t275;
    real_type t279 = sin(X__[iX_x1]);
    real_type t280 = P__[iP_u1];
    real_type t282 = pow(V__[20] - t279 - t280, 2);
    real_type t284 = X__[iX_xx2];
    real_type t285 = sin(t284);
    real_type t287 = P__[iP_u2];
    real_type t289 = pow(V__[61] - 0.2e0 * t285 - t287, 2);
    real_type t292 = sin(X__[iX_x2]);
    real_type t294 = pow(V__[21] - t292 - t287, 2);
    real_type t296 = X__[iX_xx1];
    real_type t297 = sin(t296);
    real_type t300 = pow(V__[60] - 0.2e0 * t297 - t280, 2);
    real_type t302 = X__[iX_yy19];
    real_type t304 = Q__[iQ_zeta];
    real_type t306 = sin(t304 + 18);
    real_type t309 = pow(V__[58] - 0.12e1 * t302 - 0.1e0 * t306, 2);
    real_type t311 = X__[iX_yy20];
    real_type t314 = sin(t304 + 19);
    real_type t317 = pow(V__[59] - 0.12e1 * t311 - 0.1e0 * t314, 2);
    real_type t319 = X__[iX_yy16];
    real_type t322 = sin(t304 + 15);
    real_type t325 = pow(V__[55] - 0.12e1 * t319 - 0.1e0 * t322, 2);
    real_type t327 = X__[iX_yy17];
    real_type t330 = sin(t304 + 16);
    real_type t333 = pow(V__[56] - 0.12e1 * t327 - 0.1e0 * t330, 2);
    real_type t335 = X__[iX_yy18];
    real_type t338 = sin(t304 + 17);
    real_type t341 = pow(V__[57] - 0.12e1 * t335 - 0.1e0 * t338, 2);
    real_type t343 = X__[iX_yy13];
    real_type t346 = sin(t304 + 12);
    real_type t349 = pow(V__[52] - 0.12e1 * t343 - 0.1e0 * t346, 2);
    real_type t351 = X__[iX_yy14];
    real_type t354 = sin(t304 + 13);
    real_type t357 = pow(V__[53] - 0.12e1 * t351 - 0.1e0 * t354, 2);
    real_type t359 = X__[iX_yy15];
    real_type t362 = sin(t304 + 14);
    real_type t365 = pow(V__[54] - 0.12e1 * t359 - 0.1e0 * t362, 2);
    real_type t367 = X__[iX_yy11];
    real_type t370 = sin(t304 + 10);
    real_type t373 = pow(V__[50] - 0.12e1 * t367 - 0.1e0 * t370, 2);
    real_type t375 = X__[iX_yy12];
    real_type t378 = sin(t304 + 11);
    real_type t381 = pow(V__[51] - 0.12e1 * t375 - 0.1e0 * t378, 2);
    real_type t383 = X__[iX_yy8];
    real_type t386 = sin(t304 + 7);
    real_type t389 = pow(V__[47] - 0.12e1 * t383 - 0.1e0 * t386, 2);
    real_type t391 = X__[iX_yy9];
    real_type t394 = sin(t304 + 8);
    real_type t397 = pow(V__[48] - 0.12e1 * t391 - 0.1e0 * t394, 2);
    real_type t399 = X__[iX_yy10];
    real_type t402 = sin(t304 + 9);
    real_type t405 = pow(V__[49] - 0.12e1 * t399 - 0.1e0 * t402, 2);
    real_type t407 = X__[iX_yy5];
    real_type t410 = sin(t304 + 4);
    real_type t413 = pow(V__[44] - 0.12e1 * t407 - 0.1e0 * t410, 2);
    real_type t414 = t282 + t289 + t294 + t300 + t309 + t317 + t325 + t333 + t341 + t349 + t357 + t365 + t373 + t381 + t389 + t397 + t405 + t413;
    real_type t418 = X__[iX_yy6];
    real_type t421 = sin(t304 + 5);
    real_type t424 = pow(V__[45] - 0.12e1 * t418 - 0.1e0 * t421, 2);
    real_type t426 = X__[iX_yy7];
    real_type t429 = sin(t304 + 6);
    real_type t432 = pow(V__[46] - 0.12e1 * t426 - 0.1e0 * t429, 2);
    real_type t434 = X__[iX_yy2];
    real_type t437 = sin(t304 + 1);
    real_type t440 = pow(V__[41] - 0.12e1 * t434 - 0.1e0 * t437, 2);
    real_type t442 = X__[iX_yy3];
    real_type t445 = sin(t304 + 2);
    real_type t448 = pow(V__[42] - 0.12e1 * t442 - 0.1e0 * t445, 2);
    real_type t450 = X__[iX_yy4];
    real_type t453 = sin(t304 + 3);
    real_type t456 = pow(V__[43] - 0.12e1 * t450 - 0.1e0 * t453, 2);
    real_type t458 = X__[iX_xx20];
    real_type t459 = sin(t458);
    real_type t461 = P__[iP_u20];
    real_type t463 = pow(V__[79] - 0.2e0 * t459 - t461, 2);
    real_type t465 = X__[iX_yy1];
    real_type t467 = sin(t304);
    real_type t470 = pow(V__[40] - 0.12e1 * t465 - 0.1e0 * t467, 2);
    real_type t471 = yy20Limitation(t311);
    real_type t474 = sin(X__[iX_x19]);
    real_type t475 = P__[iP_u19];
    real_type t477 = pow(V__[38] - t474 - t475, 2);
    real_type t479 = X__[iX_xx19];
    real_type t480 = sin(t479);
    real_type t483 = pow(V__[78] - 0.2e0 * t480 - t475, 2);
    real_type t486 = sin(X__[iX_x20]);
    real_type t488 = pow(V__[39] - t486 - t461, 2);
    real_type t489 = yy13Limitation(t343);
    real_type t490 = yy14Limitation(t351);
    real_type t491 = yy15Limitation(t359);
    real_type t492 = yy16Limitation(t319);
    real_type t493 = yy17Limitation(t327);
    real_type t494 = yy18Limitation(t335);
    real_type t495 = t424 + t432 + t440 + t448 + t456 + t463 + t470 + t471 + t477 + t483 + t488 + t489 + t490 + t491 + t492 + t493 + t494;
    real_type t496 = yy19Limitation(t302);
    real_type t497 = yy6Limitation(t418);
    real_type t498 = yy7Limitation(t426);
    real_type t499 = yy8Limitation(t383);
    real_type t500 = yy9Limitation(t391);
    real_type t501 = yy10Limitation(t399);
    real_type t502 = yy11Limitation(t367);
    real_type t503 = yy12Limitation(t375);
    real_type t504 = xx19Limitation(t479);
    real_type t505 = xx20Limitation(t458);
    real_type t506 = yy1Limitation(t465);
    real_type t507 = yy2Limitation(t434);
    real_type t508 = yy3Limitation(t442);
    real_type t509 = yy4Limitation(t450);
    real_type t510 = yy5Limitation(t407);
    real_type t511 = xx13Limitation(t131);
    real_type t512 = xx14Limitation(t144);
    real_type t513 = xx15Limitation(t120);
    real_type t514 = t496 + t497 + t498 + t499 + t500 + t501 + t502 + t503 + t504 + t505 + t506 + t507 + t508 + t509 + t510 + t511 + t512 + t513;
    real_type t516 = xx16Limitation(t95);
    real_type t517 = xx17Limitation(t108);
    real_type t518 = xx18Limitation(t85);
    real_type t519 = xx6Limitation(t229);
    real_type t520 = xx7Limitation(t223);
    real_type t521 = xx8Limitation(t205);
    real_type t522 = xx9Limitation(t187);
    real_type t523 = xx10Limitation(t199);
    real_type t524 = xx11Limitation(t175);
    real_type t525 = xx12Limitation(t156);
    real_type t526 = u20Limitation(t461);
    real_type t527 = xx1Limitation(t296);
    real_type t528 = xx2Limitation(t284);
    real_type t529 = xx3Limitation(t259);
    real_type t530 = xx4Limitation(t271);
    real_type t531 = xx5Limitation(t247);
    real_type t532 = u13Limitation(t134);
    real_type t533 = t516 + t517 + t518 + t519 + t520 + t521 + t522 + t523 + t524 + t525 + t526 + t527 + t528 + t529 + t530 + t531 + t532;
    real_type t534 = u14Limitation(t140);
    real_type t535 = u15Limitation(t116);
    real_type t536 = u16Limitation(t98);
    real_type t537 = u17Limitation(t104);
    real_type t538 = u18Limitation(t81);
    real_type t539 = u19Limitation(t475);
    real_type t540 = u6Limitation(t232);
    real_type t541 = u7Limitation(t219);
    real_type t542 = u8Limitation(t208);
    real_type t543 = u9Limitation(t190);
    real_type t544 = u10Limitation(t169);
    real_type t545 = u11Limitation(t178);
    real_type t546 = u12Limitation(t152);
    real_type t547 = u1Limitation(t280);
    real_type t548 = u2Limitation(t287);
    real_type t549 = u3Limitation(t262);
    real_type t550 = u4Limitation(t243);
    real_type t551 = u5Limitation(t250);
    real_type t552 = t534 + t535 + t536 + t537 + t538 + t539 + t540 + t541 + t542 + t543 + t544 + t545 + t546 + t547 + t548 + t549 + t550 + t551;
    real_type result__ = t69 + t172 + t276 + t414 + t495 + t514 + t533 + t552;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DmDu_numEqns() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ContinuousMP::DmDuu_numRows() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DmDuu_numCols() const
  { return 0; }

  integer
  ICLOCS_ContinuousMP::DmDuu_nnz() const
  { return 0; }

  void
  ICLOCS_ContinuousMP::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ContinuousMP::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ContinuousMP_Methods_controls.cc
