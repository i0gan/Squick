#ifndef SQUICK_MSG_DEFINE_H
#define SQUICK_MSG_DEFINE_H

#include <squick/core/platform.h>
#include <squick/core/i_record_manager.h>
#include <squick/core/i_property_manager.h>
#include <squick/core/list.h>
#include "limit.h"
#include "define.pb.h"
#include "msg_base.pb.h"
#include "msg_pre_game.pb.h"
#include "msg_share.pb.h"
#include "protocol_define.h"

#ifdef _MSC_VER
#pragma warning(default: 4244 4267)
#endif
// -------------------------------------------------------------------------
#pragma pack(push,1)

enum E_CHECK_TYPE
{
    ECT_SAVE        = 0, 
    ECT_PRIVATE     = 1, 
    ECT_PUBLIC      = 2, 
};
#pragma pack(pop)
#endif