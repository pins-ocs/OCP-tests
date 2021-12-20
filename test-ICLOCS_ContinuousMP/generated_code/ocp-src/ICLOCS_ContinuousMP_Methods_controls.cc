/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Methods_controls.cc                        |
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
    real_type t2   = XM__[6];
    real_type t3   = sin(t2);
    real_type t4   = P__[iP_u7];
    real_type t8   = XM__[47];
    real_type t9   = sin(t8);
    real_type t11  = P__[iP_u8];
    real_type t15  = XM__[7];
    real_type t16  = sin(t15);
    real_type t20  = XM__[48];
    real_type t21  = sin(t20);
    real_type t23  = P__[iP_u9];
    real_type t27  = XM__[8];
    real_type t28  = sin(t27);
    real_type t32  = XM__[49];
    real_type t33  = sin(t32);
    real_type t35  = P__[iP_u10];
    real_type t39  = XM__[9];
    real_type t40  = sin(t39);
    real_type t44  = XM__[50];
    real_type t45  = sin(t44);
    real_type t47  = P__[iP_u11];
    real_type t51  = XM__[10];
    real_type t52  = sin(t51);
    real_type t56  = XM__[51];
    real_type t57  = sin(t56);
    real_type t59  = P__[iP_u12];
    real_type t63  = XM__[4];
    real_type t64  = sin(t63);
    real_type t65  = P__[iP_u5];
    real_type t68  = (t3 + t4) * LM__[26] + (0.2e0 * t9 + t11) * LM__[67] + (t16 + t11) * LM__[27] + (0.2e0 * t21 + t23) * LM__[68] + (t28 + t23) * LM__[28] + (0.2e0 * t33 + t35) * LM__[69] + (t40 + t35) * LM__[29] + (0.2e0 * t45 + t47) * LM__[70] + (t52 + t47) * LM__[30] + (0.2e0 * t57 + t59) * LM__[71] + (t64 + t65) * LM__[24];
    real_type t70  = XM__[45];
    real_type t71  = sin(t70);
    real_type t73  = P__[iP_u6];
    real_type t77  = XM__[5];
    real_type t78  = sin(t77);
    real_type t82  = XM__[40];
    real_type t83  = sin(t82);
    real_type t85  = P__[iP_u1];
    real_type t89  = XM__[0];
    real_type t90  = sin(t89);
    real_type t94  = XM__[41];
    real_type t95  = sin(t94);
    real_type t97  = P__[iP_u2];
    real_type t101 = XM__[1];
    real_type t102 = sin(t101);
    real_type t106 = XM__[42];
    real_type t107 = sin(t106);
    real_type t109 = P__[iP_u3];
    real_type t113 = XM__[2];
    real_type t114 = sin(t113);
    real_type t118 = XM__[43];
    real_type t119 = sin(t118);
    real_type t121 = P__[iP_u4];
    real_type t125 = XM__[3];
    real_type t126 = sin(t125);
    real_type t130 = XM__[44];
    real_type t131 = sin(t130);
    real_type t135 = (0.2e0 * t71 + t73) * LM__[65] + (t78 + t73) * LM__[25] + (0.2e0 * t83 + t85) * LM__[60] + (t90 + t85) * LM__[20] + (0.2e0 * t95 + t97) * LM__[61] + (t102 + t97) * LM__[21] + (0.2e0 * t107 + t109) * LM__[62] + (t114 + t109) * LM__[22] + (0.2e0 * t119 + t121) * LM__[63] + (t126 + t121) * LM__[23] + (0.2e0 * t131 + t65) * LM__[64];
    real_type t138 = XM__[20];
    real_type t141 = XM__[21];
    real_type t144 = XM__[22];
    real_type t147 = XM__[23];
    real_type t150 = XM__[24];
    real_type t153 = XM__[25];
    real_type t156 = XM__[26];
    real_type t159 = XM__[27];
    real_type t162 = XM__[28];
    real_type t165 = XM__[29];
    real_type t168 = XM__[30];
    real_type t170 = t138 * LM__[0] + t141 * LM__[1] + t144 * LM__[2] + t147 * LM__[3] + t150 * LM__[4] + t153 * LM__[5] + t156 * LM__[6] + t159 * LM__[7] + t162 * LM__[8] + t165 * LM__[9] + t168 * LM__[10];
    real_type t172 = XM__[31];
    real_type t175 = XM__[32];
    real_type t178 = XM__[33];
    real_type t181 = XM__[34];
    real_type t184 = XM__[35];
    real_type t187 = XM__[36];
    real_type t190 = XM__[37];
    real_type t193 = XM__[38];
    real_type t196 = XM__[39];
    real_type t199 = XM__[67];
    real_type t201 = QM__[0];
    real_type t203 = sin(t201 + 7);
    real_type t208 = XM__[68];
    real_type t211 = sin(t201 + 8);
    real_type t216 = XM__[69];
    real_type t219 = sin(t201 + 9);
    real_type t223 = t172 * LM__[11] + t175 * LM__[12] + t178 * LM__[13] + t181 * LM__[14] + t184 * LM__[15] + t187 * LM__[16] + t190 * LM__[17] + t193 * LM__[18] + t196 * LM__[19] + (0.12e1 * t199 + 0.1e0 * t203) * LM__[47] + (0.12e1 * t208 + 0.1e0 * t211) * LM__[48] + (0.12e1 * t216 + 0.1e0 * t219) * LM__[49];
    real_type t227 = XM__[15];
    real_type t228 = sin(t227);
    real_type t229 = P__[iP_u16];
    real_type t233 = XM__[56];
    real_type t234 = sin(t233);
    real_type t236 = P__[iP_u17];
    real_type t240 = XM__[16];
    real_type t241 = sin(t240);
    real_type t245 = XM__[57];
    real_type t246 = sin(t245);
    real_type t248 = P__[iP_u18];
    real_type t252 = XM__[17];
    real_type t253 = sin(t252);
    real_type t257 = XM__[58];
    real_type t258 = sin(t257);
    real_type t260 = P__[iP_u19];
    real_type t264 = XM__[18];
    real_type t265 = sin(t264);
    real_type t269 = XM__[59];
    real_type t270 = sin(t269);
    real_type t272 = P__[iP_u20];
    real_type t276 = XM__[19];
    real_type t277 = sin(t276);
    real_type t281 = XM__[70];
    real_type t284 = sin(t201 + 10);
    real_type t289 = XM__[71];
    real_type t292 = sin(t201 + 11);
    real_type t296 = (t228 + t229) * LM__[35] + (0.2e0 * t234 + t236) * LM__[76] + (t241 + t236) * LM__[36] + (0.2e0 * t246 + t248) * LM__[77] + (t253 + t248) * LM__[37] + (0.2e0 * t258 + t260) * LM__[78] + (t265 + t260) * LM__[38] + (0.2e0 * t270 + t272) * LM__[79] + (t277 + t272) * LM__[39] + (0.12e1 * t281 + 0.1e0 * t284) * LM__[50] + (0.12e1 * t289 + 0.1e0 * t292) * LM__[51];
    real_type t298 = XM__[72];
    real_type t301 = sin(t201 + 12);
    real_type t306 = XM__[73];
    real_type t309 = sin(t201 + 13);
    real_type t314 = XM__[74];
    real_type t317 = sin(t201 + 14);
    real_type t322 = XM__[75];
    real_type t325 = sin(t201 + 15);
    real_type t330 = XM__[11];
    real_type t331 = sin(t330);
    real_type t335 = XM__[52];
    real_type t336 = sin(t335);
    real_type t338 = P__[iP_u13];
    real_type t342 = XM__[12];
    real_type t343 = sin(t342);
    real_type t347 = XM__[53];
    real_type t348 = sin(t347);
    real_type t350 = P__[iP_u14];
    real_type t354 = XM__[13];
    real_type t355 = sin(t354);
    real_type t359 = XM__[54];
    real_type t360 = sin(t359);
    real_type t362 = P__[iP_u15];
    real_type t366 = XM__[14];
    real_type t367 = sin(t366);
    real_type t370 = (0.12e1 * t298 + 0.1e0 * t301) * LM__[52] + (0.12e1 * t306 + 0.1e0 * t309) * LM__[53] + (0.12e1 * t314 + 0.1e0 * t317) * LM__[54] + (0.12e1 * t322 + 0.1e0 * t325) * LM__[55] + (t331 + t59) * LM__[31] + (0.2e0 * t336 + t338) * LM__[72] + (t343 + t338) * LM__[32] + (0.2e0 * t348 + t350) * LM__[73] + (t355 + t350) * LM__[33] + (0.2e0 * t360 + t362) * LM__[74] + (t367 + t362) * LM__[34];
    real_type t373 = XM__[55];
    real_type t374 = sin(t373);
    real_type t379 = XM__[46];
    real_type t380 = sin(t379);
    real_type t385 = XM__[78];
    real_type t388 = sin(t201 + 18);
    real_type t393 = XM__[79];
    real_type t396 = sin(t201 + 19);
    real_type t401 = XM__[60];
    real_type t403 = sin(t201);
    real_type t408 = XM__[61];
    real_type t411 = sin(t201 + 1);
    real_type t416 = XM__[62];
    real_type t419 = sin(t201 + 2);
    real_type t424 = XM__[63];
    real_type t427 = sin(t201 + 3);
    real_type t432 = XM__[64];
    real_type t435 = sin(t201 + 4);
    real_type t440 = XM__[65];
    real_type t443 = sin(t201 + 5);
    real_type t448 = XM__[66];
    real_type t451 = sin(t201 + 6);
    real_type t455 = (0.2e0 * t374 + t229) * LM__[75] + (0.2e0 * t380 + t4) * LM__[66] + (0.12e1 * t385 + 0.1e0 * t388) * LM__[58] + (0.12e1 * t393 + 0.1e0 * t396) * LM__[59] + (0.12e1 * t401 + 0.1e0 * t403) * LM__[40] + (0.12e1 * t408 + 0.1e0 * t411) * LM__[41] + (0.12e1 * t416 + 0.1e0 * t419) * LM__[42] + (0.12e1 * t424 + 0.1e0 * t427) * LM__[43] + (0.12e1 * t432 + 0.1e0 * t435) * LM__[44] + (0.12e1 * t440 + 0.1e0 * t443) * LM__[45] + (0.12e1 * t448 + 0.1e0 * t451) * LM__[46];
    real_type t457 = XM__[76];
    real_type t460 = sin(t201 + 16);
    real_type t465 = XM__[77];
    real_type t468 = sin(t201 + 17);
    real_type t472 = xx9Limitation(t20);
    real_type t473 = xx10Limitation(t32);
    real_type t474 = xx11Limitation(t44);
    real_type t475 = xx12Limitation(t56);
    real_type t476 = t193 * t193;
    real_type t478 = t196 * t196;
    real_type t479 = xx1Limitation(t82);
    real_type t480 = xx2Limitation(t94);
    real_type t481 = xx3Limitation(t106);
    real_type t482 = xx4Limitation(t118);
    real_type t483 = (0.12e1 * t457 + 0.1e0 * t460) * LM__[56] + (0.12e1 * t465 + 0.1e0 * t468) * LM__[57] + t472 + t473 + t474 + t475 + 2 * t476 + t478 + t479 + t480 + t481 + t482;
    real_type t487 = xx5Limitation(t130);
    real_type t488 = xx6Limitation(t70);
    real_type t489 = xx7Limitation(t379);
    real_type t490 = xx8Limitation(t8);
    real_type t491 = t172 * t172;
    real_type t493 = t175 * t175;
    real_type t495 = t178 * t178;
    real_type t497 = t181 * t181;
    real_type t499 = t184 * t184;
    real_type t501 = t187 * t187;
    real_type t503 = t190 * t190;
    real_type t505 = t487 + t488 + t489 + t490 + 9 * t491 + 8 * t493 + 7 * t495 + 6 * t497 + 5 * t499 + 4 * t501 + 3 * t503;
    real_type t506 = t366 * t366;
    real_type t508 = t227 * t227;
    real_type t510 = t240 * t240;
    real_type t512 = t147 * t147;
    real_type t514 = t150 * t150;
    real_type t516 = t153 * t153;
    real_type t518 = t156 * t156;
    real_type t520 = t159 * t159;
    real_type t522 = t162 * t162;
    real_type t524 = t165 * t165;
    real_type t526 = t168 * t168;
    real_type t528 = 6 * t506 + 5 * t508 + 4 * t510 + 17 * t512 + 16 * t514 + 15 * t516 + 14 * t518 + 13 * t520 + 12 * t522 + 11 * t524 + 10 * t526;
    real_type t530 = t15 * t15;
    real_type t532 = t27 * t27;
    real_type t534 = t39 * t39;
    real_type t536 = t51 * t51;
    real_type t538 = t330 * t330;
    real_type t540 = t252 * t252;
    real_type t542 = t264 * t264;
    real_type t544 = t276 * t276;
    real_type t545 = t138 * t138;
    real_type t547 = t141 * t141;
    real_type t549 = t144 * t144;
    real_type t551 = 13 * t530 + 12 * t532 + 11 * t534 + 10 * t536 + 9 * t538 + 3 * t540 + 2 * t542 + t544 + 20 * t545 + 19 * t547 + 18 * t549;
    real_type t552 = t342 * t342;
    real_type t554 = t354 * t354;
    real_type t556 = yy19Limitation(t385);
    real_type t557 = yy20Limitation(t393);
    real_type t558 = t89 * t89;
    real_type t560 = t101 * t101;
    real_type t562 = t113 * t113;
    real_type t564 = t125 * t125;
    real_type t566 = t63 * t63;
    real_type t568 = t77 * t77;
    real_type t570 = t2 * t2;
    real_type t572 = yy10Limitation(t216);
    real_type t573 = 8 * t552 + 7 * t554 + t556 + t557 + 20 * t558 + 19 * t560 + 18 * t562 + 17 * t564 + 16 * t566 + 15 * t568 + 14 * t570 + t572;
    real_type t576 = yy11Limitation(t281);
    real_type t577 = yy12Limitation(t289);
    real_type t578 = yy13Limitation(t298);
    real_type t579 = yy14Limitation(t306);
    real_type t580 = yy15Limitation(t314);
    real_type t581 = yy16Limitation(t322);
    real_type t582 = yy17Limitation(t457);
    real_type t583 = yy18Limitation(t465);
    real_type t584 = xx20Limitation(t269);
    real_type t585 = yy1Limitation(t401);
    real_type t586 = yy2Limitation(t408);
    real_type t587 = t576 + t577 + t578 + t579 + t580 + t581 + t582 + t583 + t584 + t585 + t586;
    real_type t588 = yy3Limitation(t416);
    real_type t589 = yy4Limitation(t424);
    real_type t590 = yy5Limitation(t432);
    real_type t591 = yy6Limitation(t440);
    real_type t592 = yy7Limitation(t448);
    real_type t593 = yy8Limitation(t199);
    real_type t594 = yy9Limitation(t208);
    real_type t595 = u18Limitation(t248);
    real_type t596 = u19Limitation(t260);
    real_type t597 = u20Limitation(t272);
    real_type t598 = xx13Limitation(t335);
    real_type t599 = t588 + t589 + t590 + t591 + t592 + t593 + t594 + t595 + t596 + t597 + t598;
    real_type t601 = xx14Limitation(t347);
    real_type t602 = xx15Limitation(t359);
    real_type t603 = xx16Limitation(t373);
    real_type t604 = xx17Limitation(t233);
    real_type t605 = xx18Limitation(t245);
    real_type t606 = xx19Limitation(t257);
    real_type t607 = u9Limitation(t23);
    real_type t608 = u10Limitation(t35);
    real_type t609 = u11Limitation(t47);
    real_type t610 = u12Limitation(t59);
    real_type t611 = u13Limitation(t338);
    real_type t612 = t601 + t602 + t603 + t604 + t605 + t606 + t607 + t608 + t609 + t610 + t611;
    real_type t613 = u14Limitation(t350);
    real_type t614 = u15Limitation(t362);
    real_type t615 = u16Limitation(t229);
    real_type t616 = u17Limitation(t236);
    real_type t617 = u7Limitation(t4);
    real_type t618 = u8Limitation(t11);
    real_type t619 = u4Limitation(t121);
    real_type t620 = u5Limitation(t65);
    real_type t621 = u6Limitation(t73);
    real_type t622 = u1Limitation(t85);
    real_type t623 = u2Limitation(t97);
    real_type t624 = u3Limitation(t109);
    real_type t625 = t613 + t614 + t615 + t616 + t617 + t618 + t619 + t620 + t621 + t622 + t623 + t624;
    real_type result__ = t68 + t135 + t170 + t223 + t296 + t370 + t455 + t483 + t505 + t528 + t551 + t573 + t587 + t599 + t612 + t625;
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
    real_type t3   = sin(X__[iX_x10]);
    real_type t4   = P__[iP_u10];
    real_type t6   = pow(V__[29] - t3 - t4, 2);
    real_type t8   = X__[iX_xx10];
    real_type t9   = sin(t8);
    real_type t12  = pow(V__[69] - 0.2e0 * t9 - t4, 2);
    real_type t15  = sin(X__[iX_x11]);
    real_type t16  = P__[iP_u11];
    real_type t18  = pow(V__[30] - t15 - t16, 2);
    real_type t20  = X__[iX_yy20];
    real_type t22  = Q__[iQ_zeta];
    real_type t24  = sin(t22 + 19);
    real_type t27  = pow(V__[59] - 0.12e1 * t20 - 0.1e0 * t24, 2);
    real_type t29  = X__[iX_yy17];
    real_type t32  = sin(t22 + 16);
    real_type t35  = pow(V__[56] - 0.12e1 * t29 - 0.1e0 * t32, 2);
    real_type t37  = X__[iX_yy18];
    real_type t40  = sin(t22 + 17);
    real_type t43  = pow(V__[57] - 0.12e1 * t37 - 0.1e0 * t40, 2);
    real_type t45  = X__[iX_yy19];
    real_type t48  = sin(t22 + 18);
    real_type t51  = pow(V__[58] - 0.12e1 * t45 - 0.1e0 * t48, 2);
    real_type t53  = X__[iX_xx11];
    real_type t54  = sin(t53);
    real_type t57  = pow(V__[70] - 0.2e0 * t54 - t16, 2);
    real_type t60  = sin(X__[iX_x12]);
    real_type t61  = P__[iP_u12];
    real_type t63  = pow(V__[31] - t60 - t61, 2);
    real_type t65  = X__[iX_xx12];
    real_type t66  = sin(t65);
    real_type t69  = pow(V__[71] - 0.2e0 * t66 - t61, 2);
    real_type t72  = sin(X__[iX_x13]);
    real_type t73  = P__[iP_u13];
    real_type t75  = pow(V__[32] - t72 - t73, 2);
    real_type t77  = X__[iX_xx13];
    real_type t78  = sin(t77);
    real_type t81  = pow(V__[72] - 0.2e0 * t78 - t73, 2);
    real_type t84  = sin(X__[iX_x14]);
    real_type t85  = P__[iP_u14];
    real_type t87  = pow(V__[33] - t84 - t85, 2);
    real_type t89  = X__[iX_xx14];
    real_type t90  = sin(t89);
    real_type t93  = pow(V__[73] - 0.2e0 * t90 - t85, 2);
    real_type t96  = sin(X__[iX_x15]);
    real_type t97  = P__[iP_u15];
    real_type t99  = pow(V__[34] - t96 - t97, 2);
    real_type t101 = X__[iX_xx15];
    real_type t102 = sin(t101);
    real_type t105 = pow(V__[74] - 0.2e0 * t102 - t97, 2);
    real_type t108 = sin(X__[iX_x16]);
    real_type t109 = P__[iP_u16];
    real_type t111 = pow(V__[35] - t108 - t109, 2);
    real_type t112 = t6 + t12 + t18 + t27 + t35 + t43 + t51 + t57 + t63 + t69 + t75 + t81 + t87 + t93 + t99 + t105 + t111;
    real_type t114 = X__[iX_xx16];
    real_type t115 = sin(t114);
    real_type t118 = pow(V__[75] - 0.2e0 * t115 - t109, 2);
    real_type t121 = sin(X__[iX_x17]);
    real_type t122 = P__[iP_u17];
    real_type t124 = pow(V__[36] - t121 - t122, 2);
    real_type t126 = X__[iX_xx17];
    real_type t127 = sin(t126);
    real_type t130 = pow(V__[76] - 0.2e0 * t127 - t122, 2);
    real_type t133 = sin(X__[iX_x18]);
    real_type t134 = P__[iP_u18];
    real_type t136 = pow(V__[37] - t133 - t134, 2);
    real_type t138 = X__[iX_xx18];
    real_type t139 = sin(t138);
    real_type t142 = pow(V__[77] - 0.2e0 * t139 - t134, 2);
    real_type t145 = sin(X__[iX_x19]);
    real_type t146 = P__[iP_u19];
    real_type t148 = pow(V__[38] - t145 - t146, 2);
    real_type t150 = X__[iX_xx19];
    real_type t151 = sin(t150);
    real_type t154 = pow(V__[78] - 0.2e0 * t151 - t146, 2);
    real_type t157 = sin(X__[iX_x20]);
    real_type t158 = P__[iP_u20];
    real_type t160 = pow(V__[39] - t157 - t158, 2);
    real_type t162 = X__[iX_xx20];
    real_type t163 = sin(t162);
    real_type t166 = pow(V__[79] - 0.2e0 * t163 - t158, 2);
    real_type t168 = X__[iX_yy1];
    real_type t170 = sin(t22);
    real_type t173 = pow(V__[40] - 0.12e1 * t168 - 0.1e0 * t170, 2);
    real_type t175 = X__[iX_yy2];
    real_type t178 = sin(t22 + 1);
    real_type t181 = pow(V__[41] - 0.12e1 * t175 - 0.1e0 * t178, 2);
    real_type t183 = X__[iX_yy3];
    real_type t186 = sin(t22 + 2);
    real_type t189 = pow(V__[42] - 0.12e1 * t183 - 0.1e0 * t186, 2);
    real_type t191 = X__[iX_yy4];
    real_type t194 = sin(t22 + 3);
    real_type t197 = pow(V__[43] - 0.12e1 * t191 - 0.1e0 * t194, 2);
    real_type t199 = X__[iX_yy5];
    real_type t202 = sin(t22 + 4);
    real_type t205 = pow(V__[44] - 0.12e1 * t199 - 0.1e0 * t202, 2);
    real_type t207 = X__[iX_yy6];
    real_type t210 = sin(t22 + 5);
    real_type t213 = pow(V__[45] - 0.12e1 * t207 - 0.1e0 * t210, 2);
    real_type t215 = X__[iX_yy7];
    real_type t218 = sin(t22 + 6);
    real_type t221 = pow(V__[46] - 0.12e1 * t215 - 0.1e0 * t218, 2);
    real_type t223 = X__[iX_yy8];
    real_type t226 = sin(t22 + 7);
    real_type t229 = pow(V__[47] - 0.12e1 * t223 - 0.1e0 * t226, 2);
    real_type t231 = X__[iX_yy9];
    real_type t234 = sin(t22 + 8);
    real_type t237 = pow(V__[48] - 0.12e1 * t231 - 0.1e0 * t234, 2);
    real_type t238 = t118 + t124 + t130 + t136 + t142 + t148 + t154 + t160 + t166 + t173 + t181 + t189 + t197 + t205 + t213 + t221 + t229 + t237;
    real_type t241 = X__[iX_yy10];
    real_type t244 = sin(t22 + 9);
    real_type t247 = pow(V__[49] - 0.12e1 * t241 - 0.1e0 * t244, 2);
    real_type t249 = X__[iX_yy11];
    real_type t252 = sin(t22 + 10);
    real_type t255 = pow(V__[50] - 0.12e1 * t249 - 0.1e0 * t252, 2);
    real_type t257 = X__[iX_yy12];
    real_type t260 = sin(t22 + 11);
    real_type t263 = pow(V__[51] - 0.12e1 * t257 - 0.1e0 * t260, 2);
    real_type t265 = X__[iX_yy13];
    real_type t268 = sin(t22 + 12);
    real_type t271 = pow(V__[52] - 0.12e1 * t265 - 0.1e0 * t268, 2);
    real_type t273 = X__[iX_yy14];
    real_type t276 = sin(t22 + 13);
    real_type t279 = pow(V__[53] - 0.12e1 * t273 - 0.1e0 * t276, 2);
    real_type t281 = X__[iX_yy15];
    real_type t284 = sin(t22 + 14);
    real_type t287 = pow(V__[54] - 0.12e1 * t281 - 0.1e0 * t284, 2);
    real_type t289 = X__[iX_yy16];
    real_type t292 = sin(t22 + 15);
    real_type t295 = pow(V__[55] - 0.12e1 * t289 - 0.1e0 * t292, 2);
    real_type t296 = P__[iP_u1];
    real_type t297 = u1Limitation(t296);
    real_type t298 = P__[iP_u2];
    real_type t299 = u2Limitation(t298);
    real_type t300 = P__[iP_u3];
    real_type t301 = u3Limitation(t300);
    real_type t302 = P__[iP_u4];
    real_type t303 = u4Limitation(t302);
    real_type t304 = P__[iP_u5];
    real_type t305 = u5Limitation(t304);
    real_type t306 = P__[iP_u6];
    real_type t307 = u6Limitation(t306);
    real_type t308 = P__[iP_u7];
    real_type t309 = u7Limitation(t308);
    real_type t310 = P__[iP_u8];
    real_type t311 = u8Limitation(t310);
    real_type t312 = P__[iP_u9];
    real_type t313 = u9Limitation(t312);
    real_type t314 = u10Limitation(t4);
    real_type t315 = t247 + t255 + t263 + t271 + t279 + t287 + t295 + t297 + t299 + t301 + t303 + t305 + t307 + t309 + t311 + t313 + t314;
    real_type t316 = u11Limitation(t16);
    real_type t317 = u12Limitation(t61);
    real_type t318 = u13Limitation(t73);
    real_type t319 = u14Limitation(t85);
    real_type t320 = u15Limitation(t97);
    real_type t321 = u16Limitation(t109);
    real_type t322 = u17Limitation(t122);
    real_type t323 = u18Limitation(t134);
    real_type t324 = u19Limitation(t146);
    real_type t325 = u20Limitation(t158);
    real_type t326 = yy19Limitation(t45);
    real_type t327 = yy20Limitation(t20);
    real_type t328 = xx10Limitation(t8);
    real_type t329 = xx11Limitation(t53);
    real_type t330 = xx12Limitation(t65);
    real_type t331 = xx13Limitation(t77);
    real_type t332 = xx14Limitation(t89);
    real_type t333 = xx15Limitation(t101);
    real_type t334 = t316 + t317 + t318 + t319 + t320 + t321 + t322 + t323 + t324 + t325 + t326 + t327 + t328 + t329 + t330 + t331 + t332 + t333;
    real_type t337 = xx16Limitation(t114);
    real_type t338 = xx17Limitation(t126);
    real_type t339 = xx18Limitation(t138);
    real_type t340 = xx19Limitation(t150);
    real_type t341 = xx20Limitation(t162);
    real_type t342 = yy1Limitation(t168);
    real_type t343 = yy2Limitation(t175);
    real_type t344 = yy3Limitation(t183);
    real_type t345 = yy4Limitation(t191);
    real_type t346 = yy5Limitation(t199);
    real_type t347 = yy6Limitation(t207);
    real_type t348 = yy7Limitation(t215);
    real_type t349 = yy8Limitation(t223);
    real_type t350 = yy9Limitation(t231);
    real_type t351 = yy10Limitation(t241);
    real_type t352 = yy11Limitation(t249);
    real_type t353 = yy12Limitation(t257);
    real_type t354 = t337 + t338 + t339 + t340 + t341 + t342 + t343 + t344 + t345 + t346 + t347 + t348 + t349 + t350 + t351 + t352 + t353;
    real_type t355 = yy13Limitation(t265);
    real_type t356 = yy14Limitation(t273);
    real_type t357 = yy15Limitation(t281);
    real_type t358 = yy16Limitation(t289);
    real_type t359 = yy17Limitation(t29);
    real_type t360 = yy18Limitation(t37);
    real_type t361 = X__[iX_xx1];
    real_type t362 = xx1Limitation(t361);
    real_type t363 = X__[iX_xx2];
    real_type t364 = xx2Limitation(t363);
    real_type t365 = X__[iX_xx3];
    real_type t366 = xx3Limitation(t365);
    real_type t367 = X__[iX_xx4];
    real_type t368 = xx4Limitation(t367);
    real_type t369 = X__[iX_xx5];
    real_type t370 = xx5Limitation(t369);
    real_type t371 = X__[iX_xx6];
    real_type t372 = xx6Limitation(t371);
    real_type t373 = X__[iX_xx7];
    real_type t374 = xx7Limitation(t373);
    real_type t375 = X__[iX_xx8];
    real_type t376 = xx8Limitation(t375);
    real_type t377 = X__[iX_xx9];
    real_type t378 = xx9Limitation(t377);
    real_type t382 = pow(V__[0] - X__[iX_y1], 2);
    real_type t386 = pow(V__[1] - X__[iX_y2], 2);
    real_type t390 = pow(V__[2] - X__[iX_y3], 2);
    real_type t391 = t355 + t356 + t357 + t358 + t359 + t360 + t362 + t364 + t366 + t368 + t370 + t372 + t374 + t376 + t378 + t382 + t386 + t390;
    real_type t396 = pow(V__[3] - X__[iX_y4], 2);
    real_type t400 = pow(V__[4] - X__[iX_y5], 2);
    real_type t404 = pow(V__[5] - X__[iX_y6], 2);
    real_type t408 = pow(V__[6] - X__[iX_y7], 2);
    real_type t412 = pow(V__[7] - X__[iX_y8], 2);
    real_type t416 = pow(V__[8] - X__[iX_y9], 2);
    real_type t420 = pow(V__[9] - X__[iX_y10], 2);
    real_type t424 = pow(V__[10] - X__[iX_y11], 2);
    real_type t428 = pow(V__[11] - X__[iX_y12], 2);
    real_type t432 = pow(V__[12] - X__[iX_y13], 2);
    real_type t436 = pow(V__[13] - X__[iX_y14], 2);
    real_type t440 = pow(V__[14] - X__[iX_y15], 2);
    real_type t444 = pow(V__[15] - X__[iX_y16], 2);
    real_type t448 = pow(V__[16] - X__[iX_y17], 2);
    real_type t452 = pow(V__[17] - X__[iX_y18], 2);
    real_type t456 = pow(V__[18] - X__[iX_y19], 2);
    real_type t460 = pow(V__[19] - X__[iX_y20], 2);
    real_type t461 = t396 + t400 + t404 + t408 + t412 + t416 + t420 + t424 + t428 + t432 + t436 + t440 + t444 + t448 + t452 + t456 + t460;
    real_type t464 = sin(X__[iX_x1]);
    real_type t466 = pow(V__[20] - t464 - t296, 2);
    real_type t468 = sin(t361);
    real_type t471 = pow(V__[60] - 0.2e0 * t468 - t296, 2);
    real_type t474 = sin(X__[iX_x2]);
    real_type t476 = pow(V__[21] - t474 - t298, 2);
    real_type t478 = sin(t363);
    real_type t481 = pow(V__[61] - 0.2e0 * t478 - t298, 2);
    real_type t484 = sin(X__[iX_x3]);
    real_type t486 = pow(V__[22] - t484 - t300, 2);
    real_type t488 = sin(t365);
    real_type t491 = pow(V__[62] - 0.2e0 * t488 - t300, 2);
    real_type t494 = sin(X__[iX_x4]);
    real_type t496 = pow(V__[23] - t494 - t302, 2);
    real_type t498 = sin(t367);
    real_type t501 = pow(V__[63] - 0.2e0 * t498 - t302, 2);
    real_type t504 = sin(X__[iX_x5]);
    real_type t506 = pow(V__[24] - t504 - t304, 2);
    real_type t508 = sin(t369);
    real_type t511 = pow(V__[64] - 0.2e0 * t508 - t304, 2);
    real_type t514 = sin(X__[iX_x6]);
    real_type t516 = pow(V__[25] - t514 - t306, 2);
    real_type t518 = sin(t371);
    real_type t521 = pow(V__[65] - 0.2e0 * t518 - t306, 2);
    real_type t524 = sin(X__[iX_x7]);
    real_type t526 = pow(V__[26] - t524 - t308, 2);
    real_type t528 = sin(t373);
    real_type t531 = pow(V__[66] - 0.2e0 * t528 - t308, 2);
    real_type t534 = sin(X__[iX_x8]);
    real_type t536 = pow(V__[27] - t534 - t310, 2);
    real_type t538 = sin(t375);
    real_type t541 = pow(V__[67] - 0.2e0 * t538 - t310, 2);
    real_type t544 = sin(X__[iX_x9]);
    real_type t546 = pow(V__[28] - t544 - t312, 2);
    real_type t548 = sin(t377);
    real_type t551 = pow(V__[68] - 0.2e0 * t548 - t312, 2);
    real_type t552 = t466 + t471 + t476 + t481 + t486 + t491 + t496 + t501 + t506 + t511 + t516 + t521 + t526 + t531 + t536 + t541 + t546 + t551;
    real_type result__ = t112 + t238 + t315 + t334 + t354 + t391 + t461 + t552;
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
