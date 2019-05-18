#include <napi.h>
#include "wrap_trader.h"
#include "wrap_mduser.h"
using namespace Napi;

Object Init(Env env,Object exports){
    Mduser::Init(env,exports);
    Trader::Init(env,exports);
    return exports;
}
NODE_API_MODULE(NODE_GYP_MODULE_NAME,Init)