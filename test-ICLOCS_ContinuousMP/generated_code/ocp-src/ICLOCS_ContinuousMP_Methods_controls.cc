/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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

  real_type
  ICLOCS_ContinuousMP::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
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
    real_type t2   = XM__[17];
    real_type t3   = sin(t2);
    real_type t4   = P__[iP_u18];
    real_type t8   = XM__[57];
    real_type t9   = sin(t8);
    real_type t14  = XM__[18];
    real_type t15  = sin(t14);
    real_type t16  = P__[iP_u19];
    real_type t20  = XM__[58];
    real_type t21  = sin(t20);
    real_type t26  = XM__[40];
    real_type t27  = sin(t26);
    real_type t29  = P__[iP_u1];
    real_type t33  = XM__[0];
    real_type t34  = sin(t33);
    real_type t38  = XM__[41];
    real_type t39  = sin(t38);
    real_type t41  = P__[iP_u2];
    real_type t45  = XM__[1];
    real_type t46  = sin(t45);
    real_type t50  = XM__[42];
    real_type t51  = sin(t50);
    real_type t53  = P__[iP_u3];
    real_type t57  = XM__[2];
    real_type t58  = sin(t57);
    real_type t62  = XM__[43];
    real_type t63  = sin(t62);
    real_type t65  = P__[iP_u4];
    real_type t68  = (t3 + t4) * LM__[37] + (0.2e0 * t9 + t4) * LM__[77] + (t15 + t16) * LM__[38] + (0.2e0 * t21 + t16) * LM__[78] + (0.2e0 * t27 + t29) * LM__[60] + (t34 + t29) * LM__[20] + (0.2e0 * t39 + t41) * LM__[61] + (t46 + t41) * LM__[21] + (0.2e0 * t51 + t53) * LM__[62] + (t58 + t53) * LM__[22] + (0.2e0 * t63 + t65) * LM__[63];
    real_type t70  = XM__[3];
    real_type t71  = sin(t70);
    real_type t75  = XM__[44];
    real_type t76  = sin(t75);
    real_type t78  = P__[iP_u5];
    real_type t82  = XM__[4];
    real_type t83  = sin(t82);
    real_type t87  = XM__[45];
    real_type t88  = sin(t87);
    real_type t90  = P__[iP_u6];
    real_type t94  = XM__[5];
    real_type t95  = sin(t94);
    real_type t99  = XM__[46];
    real_type t100 = sin(t99);
    real_type t102 = P__[iP_u7];
    real_type t106 = XM__[6];
    real_type t107 = sin(t106);
    real_type t111 = XM__[47];
    real_type t112 = sin(t111);
    real_type t114 = P__[iP_u8];
    real_type t118 = XM__[7];
    real_type t119 = sin(t118);
    real_type t123 = XM__[48];
    real_type t124 = sin(t123);
    real_type t126 = P__[iP_u9];
    real_type t130 = XM__[8];
    real_type t131 = sin(t130);
    real_type t134 = (t71 + t65) * LM__[23] + (0.2e0 * t76 + t78) * LM__[64] + (t83 + t78) * LM__[24] + (0.2e0 * t88 + t90) * LM__[65] + (t95 + t90) * LM__[25] + (0.2e0 * t100 + t102) * LM__[66] + (t107 + t102) * LM__[26] + (0.2e0 * t112 + t114) * LM__[67] + (t119 + t114) * LM__[27] + (0.2e0 * t124 + t126) * LM__[68] + (t131 + t126) * LM__[28];
    real_type t137 = XM__[49];
    real_type t138 = sin(t137);
    real_type t140 = P__[iP_u10];
    real_type t144 = XM__[9];
    real_type t145 = sin(t144);
    real_type t149 = XM__[20];
    real_type t152 = XM__[21];
    real_type t155 = XM__[22];
    real_type t158 = XM__[23];
    real_type t161 = XM__[24];
    real_type t164 = XM__[25];
    real_type t167 = XM__[26];
    real_type t170 = XM__[27];
    real_type t173 = XM__[28];
    real_type t175 = (0.2e0 * t138 + t140) * LM__[69] + (t145 + t140) * LM__[29] + t149 * LM__[0] + t152 * LM__[1] + t155 * LM__[2] + t158 * LM__[3] + t161 * LM__[4] + t164 * LM__[5] + t167 * LM__[6] + t170 * LM__[7] + t173 * LM__[8];
    real_type t177 = XM__[29];
    real_type t180 = XM__[30];
    real_type t183 = XM__[31];
    real_type t186 = XM__[32];
    real_type t189 = XM__[33];
    real_type t192 = XM__[34];
    real_type t195 = XM__[35];
    real_type t198 = XM__[36];
    real_type t201 = XM__[37];
    real_type t204 = XM__[38];
    real_type t207 = XM__[39];
    real_type t210 = XM__[63];
    real_type t212 = QM__[0];
    real_type t214 = sin(t212 + 3);
    real_type t218 = t177 * LM__[9] + t180 * LM__[10] + t183 * LM__[11] + t186 * LM__[12] + t189 * LM__[13] + t192 * LM__[14] + t195 * LM__[15] + t198 * LM__[16] + t201 * LM__[17] + t204 * LM__[18] + t207 * LM__[19] + (0.12e1 * t210 + 0.1e0 * t214) * LM__[43];
    real_type t222 = XM__[64];
    real_type t225 = sin(t212 + 4);
    real_type t230 = XM__[65];
    real_type t233 = sin(t212 + 5);
    real_type t238 = XM__[66];
    real_type t241 = sin(t212 + 6);
    real_type t246 = XM__[67];
    real_type t249 = sin(t212 + 7);
    real_type t254 = XM__[68];
    real_type t257 = sin(t212 + 8);
    real_type t262 = XM__[69];
    real_type t265 = sin(t212 + 9);
    real_type t270 = XM__[70];
    real_type t273 = sin(t212 + 10);
    real_type t278 = XM__[71];
    real_type t281 = sin(t212 + 11);
    real_type t286 = XM__[19];
    real_type t287 = sin(t286);
    real_type t288 = P__[iP_u20];
    real_type t292 = XM__[59];
    real_type t293 = sin(t292);
    real_type t298 = XM__[60];
    real_type t300 = sin(t212);
    real_type t304 = (0.12e1 * t222 + 0.1e0 * t225) * LM__[44] + (0.12e1 * t230 + 0.1e0 * t233) * LM__[45] + (0.12e1 * t238 + 0.1e0 * t241) * LM__[46] + (0.12e1 * t246 + 0.1e0 * t249) * LM__[47] + (0.12e1 * t254 + 0.1e0 * t257) * LM__[48] + (0.12e1 * t262 + 0.1e0 * t265) * LM__[49] + (0.12e1 * t270 + 0.1e0 * t273) * LM__[50] + (0.12e1 * t278 + 0.1e0 * t281) * LM__[51] + (t287 + t288) * LM__[39] + (0.2e0 * t293 + t288) * LM__[79] + (0.12e1 * t298 + 0.1e0 * t300) * LM__[40];
    real_type t306 = XM__[61];
    real_type t309 = sin(t212 + 1);
    real_type t314 = XM__[50];
    real_type t315 = sin(t314);
    real_type t317 = P__[iP_u11];
    real_type t321 = XM__[10];
    real_type t322 = sin(t321);
    real_type t326 = XM__[51];
    real_type t327 = sin(t326);
    real_type t329 = P__[iP_u12];
    real_type t333 = XM__[11];
    real_type t334 = sin(t333);
    real_type t338 = XM__[52];
    real_type t339 = sin(t338);
    real_type t341 = P__[iP_u13];
    real_type t345 = XM__[12];
    real_type t346 = sin(t345);
    real_type t350 = XM__[53];
    real_type t351 = sin(t350);
    real_type t353 = P__[iP_u14];
    real_type t357 = XM__[13];
    real_type t358 = sin(t357);
    real_type t362 = XM__[14];
    real_type t363 = sin(t362);
    real_type t364 = P__[iP_u15];
    real_type t368 = XM__[54];
    real_type t369 = sin(t368);
    real_type t373 = (0.12e1 * t306 + 0.1e0 * t309) * LM__[41] + (0.2e0 * t315 + t317) * LM__[70] + (t322 + t317) * LM__[30] + (0.2e0 * t327 + t329) * LM__[71] + (t334 + t329) * LM__[31] + (0.2e0 * t339 + t341) * LM__[72] + (t346 + t341) * LM__[32] + (0.2e0 * t351 + t353) * LM__[73] + (t358 + t353) * LM__[33] + (t363 + t364) * LM__[34] + (0.2e0 * t369 + t364) * LM__[74];
    real_type t376 = XM__[15];
    real_type t377 = sin(t376);
    real_type t378 = P__[iP_u16];
    real_type t382 = XM__[55];
    real_type t383 = sin(t382);
    real_type t388 = XM__[16];
    real_type t389 = sin(t388);
    real_type t390 = P__[iP_u17];
    real_type t394 = XM__[56];
    real_type t395 = sin(t394);
    real_type t400 = XM__[73];
    real_type t403 = sin(t212 + 13);
    real_type t408 = XM__[74];
    real_type t411 = sin(t212 + 14);
    real_type t416 = XM__[75];
    real_type t419 = sin(t212 + 15);
    real_type t424 = XM__[76];
    real_type t427 = sin(t212 + 16);
    real_type t432 = XM__[62];
    real_type t435 = sin(t212 + 2);
    real_type t440 = XM__[77];
    real_type t443 = sin(t212 + 17);
    real_type t448 = XM__[78];
    real_type t451 = sin(t212 + 18);
    real_type t455 = (t377 + t378) * LM__[35] + (0.2e0 * t383 + t378) * LM__[75] + (t389 + t390) * LM__[36] + (0.2e0 * t395 + t390) * LM__[76] + (0.12e1 * t400 + 0.1e0 * t403) * LM__[53] + (0.12e1 * t408 + 0.1e0 * t411) * LM__[54] + (0.12e1 * t416 + 0.1e0 * t419) * LM__[55] + (0.12e1 * t424 + 0.1e0 * t427) * LM__[56] + (0.12e1 * t432 + 0.1e0 * t435) * LM__[42] + (0.12e1 * t440 + 0.1e0 * t443) * LM__[57] + (0.12e1 * t448 + 0.1e0 * t451) * LM__[58];
    real_type t457 = XM__[79];
    real_type t460 = sin(t212 + 19);
    real_type t465 = XM__[72];
    real_type t468 = sin(t212 + 12);
    real_type t472 = t167 * t167;
    real_type t474 = t170 * t170;
    real_type t476 = t173 * t173;
    real_type t478 = t177 * t177;
    real_type t480 = t180 * t180;
    real_type t482 = t183 * t183;
    real_type t484 = t14 * t14;
    real_type t486 = t286 * t286;
    real_type t487 = t149 * t149;
    real_type t489 = t152 * t152;
    real_type t491 = (0.12e1 * t457 + 0.1e0 * t460) * LM__[59] + (0.12e1 * t465 + 0.1e0 * t468) * LM__[52] + 14 * t472 + 13 * t474 + 12 * t476 + 11 * t478 + 10 * t480 + 9 * t482 + 2 * t484 + t486 + 20 * t487 + 19 * t489;
    real_type t495 = t321 * t321;
    real_type t497 = t333 * t333;
    real_type t499 = t345 * t345;
    real_type t501 = t357 * t357;
    real_type t503 = t362 * t362;
    real_type t505 = t376 * t376;
    real_type t507 = t388 * t388;
    real_type t509 = t155 * t155;
    real_type t511 = t158 * t158;
    real_type t513 = t161 * t161;
    real_type t515 = t164 * t164;
    real_type t517 = 10 * t495 + 9 * t497 + 8 * t499 + 7 * t501 + 6 * t503 + 5 * t505 + 4 * t507 + 18 * t509 + 17 * t511 + 16 * t513 + 15 * t515;
    real_type t518 = t2 * t2;
    real_type t520 = t57 * t57;
    real_type t522 = t70 * t70;
    real_type t524 = t82 * t82;
    real_type t526 = t94 * t94;
    real_type t528 = t106 * t106;
    real_type t530 = t118 * t118;
    real_type t532 = t130 * t130;
    real_type t534 = t144 * t144;
    real_type t536 = yy13Limitation(t465);
    real_type t537 = yy14Limitation(t400);
    real_type t538 = 3 * t518 + 18 * t520 + 17 * t522 + 16 * t524 + 15 * t526 + 14 * t528 + 13 * t530 + 12 * t532 + 11 * t534 + t536 + t537;
    real_type t540 = yy15Limitation(t408);
    real_type t541 = yy16Limitation(t416);
    real_type t542 = yy17Limitation(t424);
    real_type t543 = yy18Limitation(t440);
    real_type t544 = yy19Limitation(t448);
    real_type t545 = yy20Limitation(t457);
    real_type t546 = t33 * t33;
    real_type t548 = t45 * t45;
    real_type t550 = yy11Limitation(t270);
    real_type t551 = yy12Limitation(t278);
    real_type t552 = yy8Limitation(t246);
    real_type t553 = t540 + t541 + t542 + t543 + t544 + t545 + 20 * t546 + 19 * t548 + t550 + t551 + t552;
    real_type t554 = yy9Limitation(t254);
    real_type t555 = yy10Limitation(t262);
    real_type t556 = yy7Limitation(t238);
    real_type t557 = yy4Limitation(t210);
    real_type t558 = yy5Limitation(t222);
    real_type t559 = yy6Limitation(t230);
    real_type t560 = xx19Limitation(t20);
    real_type t561 = xx20Limitation(t292);
    real_type t562 = yy1Limitation(t298);
    real_type t563 = yy2Limitation(t306);
    real_type t564 = yy3Limitation(t432);
    real_type t565 = xx15Limitation(t368);
    real_type t566 = t554 + t555 + t556 + t557 + t558 + t559 + t560 + t561 + t562 + t563 + t564 + t565;
    real_type t569 = xx16Limitation(t382);
    real_type t570 = xx17Limitation(t394);
    real_type t571 = xx18Limitation(t8);
    real_type t572 = xx5Limitation(t75);
    real_type t573 = xx6Limitation(t87);
    real_type t574 = xx7Limitation(t99);
    real_type t575 = xx8Limitation(t111);
    real_type t576 = xx9Limitation(t123);
    real_type t577 = xx10Limitation(t137);
    real_type t578 = xx11Limitation(t314);
    real_type t579 = xx12Limitation(t326);
    real_type t580 = t569 + t570 + t571 + t572 + t573 + t574 + t575 + t576 + t577 + t578 + t579;
    real_type t581 = xx13Limitation(t338);
    real_type t582 = xx14Limitation(t350);
    real_type t583 = xx2Limitation(t38);
    real_type t584 = xx3Limitation(t50);
    real_type t585 = xx4Limitation(t62);
    real_type t586 = t204 * t204;
    real_type t588 = t207 * t207;
    real_type t589 = xx1Limitation(t26);
    real_type t590 = t192 * t192;
    real_type t592 = t195 * t195;
    real_type t594 = t198 * t198;
    real_type t596 = t581 + t582 + t583 + t584 + t585 + 2 * t586 + t588 + t589 + 6 * t590 + 5 * t592 + 4 * t594;
    real_type t598 = t201 * t201;
    real_type t600 = u13Limitation(t341);
    real_type t601 = u14Limitation(t353);
    real_type t602 = u15Limitation(t364);
    real_type t603 = u16Limitation(t378);
    real_type t604 = u17Limitation(t390);
    real_type t605 = u18Limitation(t4);
    real_type t606 = u19Limitation(t16);
    real_type t607 = u20Limitation(t288);
    real_type t608 = t186 * t186;
    real_type t610 = t189 * t189;
    real_type t612 = 3 * t598 + t600 + t601 + t602 + t603 + t604 + t605 + t606 + t607 + 8 * t608 + 7 * t610;
    real_type t613 = u4Limitation(t65);
    real_type t614 = u5Limitation(t78);
    real_type t615 = u6Limitation(t90);
    real_type t616 = u7Limitation(t102);
    real_type t617 = u8Limitation(t114);
    real_type t618 = u9Limitation(t126);
    real_type t619 = u10Limitation(t140);
    real_type t620 = u11Limitation(t317);
    real_type t621 = u12Limitation(t329);
    real_type t622 = u1Limitation(t29);
    real_type t623 = u2Limitation(t41);
    real_type t624 = u3Limitation(t53);
    real_type t625 = t613 + t614 + t615 + t616 + t617 + t618 + t619 + t620 + t621 + t622 + t623 + t624;
    real_type result__ = t68 + t134 + t175 + t218 + t304 + t373 + t455 + t491 + t517 + t538 + t553 + t566 + t580 + t596 + t612 + t625;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

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
    real_type t4   = pow(V__[19] - X__[iX_y20], 2);
    real_type t7   = sin(X__[iX_x1]);
    real_type t8   = P__[iP_u1];
    real_type t10  = pow(V__[20] - t7 - t8, 2);
    real_type t12  = X__[iX_xx1];
    real_type t13  = sin(t12);
    real_type t16  = pow(V__[60] - 0.2e0 * t13 - t8, 2);
    real_type t19  = sin(X__[iX_x2]);
    real_type t20  = P__[iP_u2];
    real_type t22  = pow(V__[21] - t19 - t20, 2);
    real_type t24  = X__[iX_xx2];
    real_type t25  = sin(t24);
    real_type t28  = pow(V__[61] - 0.2e0 * t25 - t20, 2);
    real_type t31  = sin(X__[iX_x3]);
    real_type t32  = P__[iP_u3];
    real_type t34  = pow(V__[22] - t31 - t32, 2);
    real_type t36  = X__[iX_xx3];
    real_type t37  = sin(t36);
    real_type t40  = pow(V__[62] - 0.2e0 * t37 - t32, 2);
    real_type t43  = sin(X__[iX_x4]);
    real_type t44  = P__[iP_u4];
    real_type t46  = pow(V__[23] - t43 - t44, 2);
    real_type t48  = X__[iX_xx4];
    real_type t49  = sin(t48);
    real_type t52  = pow(V__[63] - 0.2e0 * t49 - t44, 2);
    real_type t55  = sin(X__[iX_x5]);
    real_type t56  = P__[iP_u5];
    real_type t58  = pow(V__[24] - t55 - t56, 2);
    real_type t60  = X__[iX_xx5];
    real_type t61  = sin(t60);
    real_type t64  = pow(V__[64] - 0.2e0 * t61 - t56, 2);
    real_type t67  = sin(X__[iX_x6]);
    real_type t68  = P__[iP_u6];
    real_type t70  = pow(V__[25] - t67 - t68, 2);
    real_type t72  = X__[iX_xx6];
    real_type t73  = sin(t72);
    real_type t76  = pow(V__[65] - 0.2e0 * t73 - t68, 2);
    real_type t79  = sin(X__[iX_x7]);
    real_type t80  = P__[iP_u7];
    real_type t82  = pow(V__[26] - t79 - t80, 2);
    real_type t84  = X__[iX_xx7];
    real_type t85  = sin(t84);
    real_type t88  = pow(V__[66] - 0.2e0 * t85 - t80, 2);
    real_type t91  = sin(X__[iX_x8]);
    real_type t92  = P__[iP_u8];
    real_type t94  = pow(V__[27] - t91 - t92, 2);
    real_type t96  = X__[iX_xx8];
    real_type t97  = sin(t96);
    real_type t100 = pow(V__[67] - 0.2e0 * t97 - t92, 2);
    real_type t101 = t4 + t10 + t16 + t22 + t28 + t34 + t40 + t46 + t52 + t58 + t64 + t70 + t76 + t82 + t88 + t94 + t100;
    real_type t104 = sin(X__[iX_x9]);
    real_type t105 = P__[iP_u9];
    real_type t107 = pow(V__[28] - t104 - t105, 2);
    real_type t109 = X__[iX_xx9];
    real_type t110 = sin(t109);
    real_type t113 = pow(V__[68] - 0.2e0 * t110 - t105, 2);
    real_type t116 = sin(X__[iX_x10]);
    real_type t117 = P__[iP_u10];
    real_type t119 = pow(V__[29] - t116 - t117, 2);
    real_type t121 = X__[iX_xx10];
    real_type t122 = sin(t121);
    real_type t125 = pow(V__[69] - 0.2e0 * t122 - t117, 2);
    real_type t128 = sin(X__[iX_x11]);
    real_type t129 = P__[iP_u11];
    real_type t131 = pow(V__[30] - t128 - t129, 2);
    real_type t133 = X__[iX_xx11];
    real_type t134 = sin(t133);
    real_type t137 = pow(V__[70] - 0.2e0 * t134 - t129, 2);
    real_type t140 = sin(X__[iX_x12]);
    real_type t141 = P__[iP_u12];
    real_type t143 = pow(V__[31] - t140 - t141, 2);
    real_type t145 = X__[iX_xx12];
    real_type t146 = sin(t145);
    real_type t149 = pow(V__[71] - 0.2e0 * t146 - t141, 2);
    real_type t152 = sin(X__[iX_x13]);
    real_type t153 = P__[iP_u13];
    real_type t155 = pow(V__[32] - t152 - t153, 2);
    real_type t157 = X__[iX_xx13];
    real_type t158 = sin(t157);
    real_type t161 = pow(V__[72] - 0.2e0 * t158 - t153, 2);
    real_type t164 = sin(X__[iX_x14]);
    real_type t165 = P__[iP_u14];
    real_type t167 = pow(V__[33] - t164 - t165, 2);
    real_type t169 = X__[iX_xx14];
    real_type t170 = sin(t169);
    real_type t173 = pow(V__[73] - 0.2e0 * t170 - t165, 2);
    real_type t176 = sin(X__[iX_x15]);
    real_type t177 = P__[iP_u15];
    real_type t179 = pow(V__[34] - t176 - t177, 2);
    real_type t181 = X__[iX_xx15];
    real_type t182 = sin(t181);
    real_type t185 = pow(V__[74] - 0.2e0 * t182 - t177, 2);
    real_type t188 = sin(X__[iX_x16]);
    real_type t189 = P__[iP_u16];
    real_type t191 = pow(V__[35] - t188 - t189, 2);
    real_type t194 = sin(X__[iX_x19]);
    real_type t195 = P__[iP_u19];
    real_type t197 = pow(V__[38] - t194 - t195, 2);
    real_type t199 = X__[iX_xx19];
    real_type t200 = sin(t199);
    real_type t203 = pow(V__[78] - 0.2e0 * t200 - t195, 2);
    real_type t206 = sin(X__[iX_x20]);
    real_type t207 = P__[iP_u20];
    real_type t209 = pow(V__[39] - t206 - t207, 2);
    real_type t210 = t107 + t113 + t119 + t125 + t131 + t137 + t143 + t149 + t155 + t161 + t167 + t173 + t179 + t185 + t191 + t197 + t203 + t209;
    real_type t213 = X__[iX_xx20];
    real_type t214 = sin(t213);
    real_type t217 = pow(V__[79] - 0.2e0 * t214 - t207, 2);
    real_type t219 = X__[iX_yy1];
    real_type t221 = Q__[iQ_zeta];
    real_type t222 = sin(t221);
    real_type t225 = pow(V__[40] - 0.12e1 * t219 - 0.1e0 * t222, 2);
    real_type t227 = X__[iX_xx16];
    real_type t228 = sin(t227);
    real_type t231 = pow(V__[75] - 0.2e0 * t228 - t189, 2);
    real_type t234 = sin(X__[iX_x17]);
    real_type t235 = P__[iP_u17];
    real_type t237 = pow(V__[36] - t234 - t235, 2);
    real_type t239 = X__[iX_xx17];
    real_type t240 = sin(t239);
    real_type t243 = pow(V__[76] - 0.2e0 * t240 - t235, 2);
    real_type t246 = sin(X__[iX_x18]);
    real_type t247 = P__[iP_u18];
    real_type t249 = pow(V__[37] - t246 - t247, 2);
    real_type t251 = X__[iX_xx18];
    real_type t252 = sin(t251);
    real_type t255 = pow(V__[77] - 0.2e0 * t252 - t247, 2);
    real_type t259 = pow(V__[0] - X__[iX_y1], 2);
    real_type t263 = pow(V__[1] - X__[iX_y2], 2);
    real_type t267 = pow(V__[2] - X__[iX_y3], 2);
    real_type t271 = pow(V__[3] - X__[iX_y4], 2);
    real_type t275 = pow(V__[4] - X__[iX_y5], 2);
    real_type t279 = pow(V__[5] - X__[iX_y6], 2);
    real_type t283 = pow(V__[6] - X__[iX_y7], 2);
    real_type t287 = pow(V__[7] - X__[iX_y8], 2);
    real_type t291 = pow(V__[8] - X__[iX_y9], 2);
    real_type t295 = pow(V__[9] - X__[iX_y10], 2);
    real_type t296 = t217 + t225 + t231 + t237 + t243 + t249 + t255 + t259 + t263 + t267 + t271 + t275 + t279 + t283 + t287 + t291 + t295;
    real_type t300 = pow(V__[10] - X__[iX_y11], 2);
    real_type t304 = pow(V__[11] - X__[iX_y12], 2);
    real_type t308 = pow(V__[12] - X__[iX_y13], 2);
    real_type t312 = pow(V__[13] - X__[iX_y14], 2);
    real_type t316 = pow(V__[14] - X__[iX_y15], 2);
    real_type t320 = pow(V__[15] - X__[iX_y16], 2);
    real_type t324 = pow(V__[16] - X__[iX_y17], 2);
    real_type t328 = pow(V__[17] - X__[iX_y18], 2);
    real_type t332 = pow(V__[18] - X__[iX_y19], 2);
    real_type t334 = X__[iX_yy2];
    real_type t337 = sin(t221 + 1);
    real_type t340 = pow(V__[41] - 0.12e1 * t334 - 0.1e0 * t337, 2);
    real_type t342 = X__[iX_yy3];
    real_type t345 = sin(t221 + 2);
    real_type t348 = pow(V__[42] - 0.12e1 * t342 - 0.1e0 * t345, 2);
    real_type t350 = X__[iX_yy4];
    real_type t353 = sin(t221 + 3);
    real_type t356 = pow(V__[43] - 0.12e1 * t350 - 0.1e0 * t353, 2);
    real_type t358 = X__[iX_yy5];
    real_type t361 = sin(t221 + 4);
    real_type t364 = pow(V__[44] - 0.12e1 * t358 - 0.1e0 * t361, 2);
    real_type t366 = X__[iX_yy6];
    real_type t369 = sin(t221 + 5);
    real_type t372 = pow(V__[45] - 0.12e1 * t366 - 0.1e0 * t369, 2);
    real_type t374 = X__[iX_yy7];
    real_type t377 = sin(t221 + 6);
    real_type t380 = pow(V__[46] - 0.12e1 * t374 - 0.1e0 * t377, 2);
    real_type t382 = X__[iX_yy8];
    real_type t385 = sin(t221 + 7);
    real_type t388 = pow(V__[47] - 0.12e1 * t382 - 0.1e0 * t385, 2);
    real_type t390 = X__[iX_yy9];
    real_type t393 = sin(t221 + 8);
    real_type t396 = pow(V__[48] - 0.12e1 * t390 - 0.1e0 * t393, 2);
    real_type t398 = X__[iX_yy10];
    real_type t401 = sin(t221 + 9);
    real_type t404 = pow(V__[49] - 0.12e1 * t398 - 0.1e0 * t401, 2);
    real_type t405 = t300 + t304 + t308 + t312 + t316 + t320 + t324 + t328 + t332 + t340 + t348 + t356 + t364 + t372 + t380 + t388 + t396 + t404;
    real_type t409 = X__[iX_yy11];
    real_type t412 = sin(t221 + 10);
    real_type t415 = pow(V__[50] - 0.12e1 * t409 - 0.1e0 * t412, 2);
    real_type t417 = X__[iX_yy12];
    real_type t420 = sin(t221 + 11);
    real_type t423 = pow(V__[51] - 0.12e1 * t417 - 0.1e0 * t420, 2);
    real_type t425 = X__[iX_yy13];
    real_type t428 = sin(t221 + 12);
    real_type t431 = pow(V__[52] - 0.12e1 * t425 - 0.1e0 * t428, 2);
    real_type t433 = X__[iX_yy14];
    real_type t436 = sin(t221 + 13);
    real_type t439 = pow(V__[53] - 0.12e1 * t433 - 0.1e0 * t436, 2);
    real_type t441 = X__[iX_yy15];
    real_type t444 = sin(t221 + 14);
    real_type t447 = pow(V__[54] - 0.12e1 * t441 - 0.1e0 * t444, 2);
    real_type t449 = X__[iX_yy16];
    real_type t452 = sin(t221 + 15);
    real_type t455 = pow(V__[55] - 0.12e1 * t449 - 0.1e0 * t452, 2);
    real_type t457 = X__[iX_yy17];
    real_type t460 = sin(t221 + 16);
    real_type t463 = pow(V__[56] - 0.12e1 * t457 - 0.1e0 * t460, 2);
    real_type t465 = X__[iX_yy18];
    real_type t468 = sin(t221 + 17);
    real_type t471 = pow(V__[57] - 0.12e1 * t465 - 0.1e0 * t468, 2);
    real_type t473 = X__[iX_yy19];
    real_type t476 = sin(t221 + 18);
    real_type t479 = pow(V__[58] - 0.12e1 * t473 - 0.1e0 * t476, 2);
    real_type t481 = X__[iX_yy20];
    real_type t484 = sin(t221 + 19);
    real_type t487 = pow(V__[59] - 0.12e1 * t481 - 0.1e0 * t484, 2);
    real_type t488 = u1Limitation(t8);
    real_type t489 = u2Limitation(t20);
    real_type t490 = u3Limitation(t32);
    real_type t491 = u4Limitation(t44);
    real_type t492 = u5Limitation(t56);
    real_type t493 = u6Limitation(t68);
    real_type t494 = u7Limitation(t80);
    real_type t495 = t415 + t423 + t431 + t439 + t447 + t455 + t463 + t471 + t479 + t487 + t488 + t489 + t490 + t491 + t492 + t493 + t494;
    real_type t496 = u8Limitation(t92);
    real_type t497 = u9Limitation(t105);
    real_type t498 = u10Limitation(t117);
    real_type t499 = u11Limitation(t129);
    real_type t500 = u12Limitation(t141);
    real_type t501 = u13Limitation(t153);
    real_type t502 = u14Limitation(t165);
    real_type t503 = u15Limitation(t177);
    real_type t504 = u16Limitation(t189);
    real_type t505 = u17Limitation(t235);
    real_type t506 = u18Limitation(t247);
    real_type t507 = u19Limitation(t195);
    real_type t508 = u20Limitation(t207);
    real_type t509 = yy1Limitation(t219);
    real_type t510 = yy2Limitation(t334);
    real_type t511 = yy3Limitation(t342);
    real_type t512 = yy4Limitation(t350);
    real_type t513 = yy5Limitation(t358);
    real_type t514 = t496 + t497 + t498 + t499 + t500 + t501 + t502 + t503 + t504 + t505 + t506 + t507 + t508 + t509 + t510 + t511 + t512 + t513;
    real_type t516 = yy6Limitation(t366);
    real_type t517 = yy7Limitation(t374);
    real_type t518 = yy8Limitation(t382);
    real_type t519 = yy9Limitation(t390);
    real_type t520 = yy10Limitation(t398);
    real_type t521 = yy11Limitation(t409);
    real_type t522 = yy12Limitation(t417);
    real_type t523 = yy13Limitation(t425);
    real_type t524 = yy14Limitation(t433);
    real_type t525 = yy15Limitation(t441);
    real_type t526 = yy16Limitation(t449);
    real_type t527 = yy17Limitation(t457);
    real_type t528 = yy18Limitation(t465);
    real_type t529 = yy19Limitation(t473);
    real_type t530 = yy20Limitation(t481);
    real_type t531 = xx1Limitation(t12);
    real_type t532 = xx2Limitation(t24);
    real_type t533 = t516 + t517 + t518 + t519 + t520 + t521 + t522 + t523 + t524 + t525 + t526 + t527 + t528 + t529 + t530 + t531 + t532;
    real_type t534 = xx3Limitation(t36);
    real_type t535 = xx4Limitation(t48);
    real_type t536 = xx5Limitation(t60);
    real_type t537 = xx6Limitation(t72);
    real_type t538 = xx7Limitation(t84);
    real_type t539 = xx8Limitation(t96);
    real_type t540 = xx9Limitation(t109);
    real_type t541 = xx10Limitation(t121);
    real_type t542 = xx11Limitation(t133);
    real_type t543 = xx12Limitation(t145);
    real_type t544 = xx13Limitation(t157);
    real_type t545 = xx14Limitation(t169);
    real_type t546 = xx15Limitation(t181);
    real_type t547 = xx16Limitation(t227);
    real_type t548 = xx17Limitation(t239);
    real_type t549 = xx18Limitation(t251);
    real_type t550 = xx19Limitation(t199);
    real_type t551 = xx20Limitation(t213);
    real_type t552 = t534 + t535 + t536 + t537 + t538 + t539 + t540 + t541 + t542 + t543 + t544 + t545 + t546 + t547 + t548 + t549 + t550 + t551;
    real_type result__ = t101 + t210 + t296 + t405 + t495 + t514 + t533 + t552;
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
