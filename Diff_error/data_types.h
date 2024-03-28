
#ifndef D_TYPE_PARAM
#define D_TYPE_PARAM


#include "ac_fixed.h"

#define DATA_WIDTH 8
#define COEF_WIDTH 16

#define HEAD_ROOM_WIDTH 6

typedef ac_fixed<DATA_WIDTH,DATA_WIDTH,false,AC_RND_INF,AC_SAT> d_type;
typedef ac_fixed< 4, 4, false> ca_type;

typedef ac_fixed<COEF_WIDTH, 5, true, AC_RND_INF, AC_SAT>     coef_type;
// typedef ac_fixed<DATA_WIDTH+COEF_WIDTH+HEAD_ROOM_WIDTH+4, DATA_WIDTH+HEAD_ROOM_WIDTH, true> acc_type;
typedef ac_fixed<DATA_WIDTH+COEF_WIDTH+HEAD_ROOM_WIDTH+1, DATA_WIDTH+HEAD_ROOM_WIDTH, true> acc_type;
// typedef ac_fixed<34, 8, true> acc_type;

#endif