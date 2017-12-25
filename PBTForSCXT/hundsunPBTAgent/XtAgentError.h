#ifndef __GWTEWAY_ERROR_H__
#define __GWTEWAY_ERROR_H__

namespace agent
{
    // 网关错误号定义
    enum
    {
        GW_SUCCESS                  = 0,

        GW_ERR_PARAM                = 10000,
        GW_ERR_SESSION_NOT_FOUND,
        GW_ERR_DISCONNECTED,
        GW_ERR_REQUEST_FAILED,
        GW_ERR_SEND_DATA,
        GW_ERR_RECV_EMPTY_DATA,
        GW_ERR_NO_SUCH_FUNCNO,

        GW_ERR_OTHERS               = 11000,
    };

}

#endif
