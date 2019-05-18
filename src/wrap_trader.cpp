#include "wrap_trader.h"
#include "utils.h"

FunctionReference Trader::constructor;
Object Trader::Init(Napi::Env env, Object exports)
{
    HandleScope scope(env);
    Function ctor = DefineClass(env, "Trader",
                                {InstanceMethod("connect", &Trader::Connect)});

    constructor = Persistent(ctor);
    constructor.SuppressDestruct();
    exports.Set("Trader", ctor);
    return exports;
}
Trader::Trader(const CallbackInfo &info) : ObjectWrap<Trader>(info), api(CThostFtdcTraderApi::CreateFtdcTraderApi(""))
{
}
Trader::~Trader(void)
{
}

Napi::Value Trader::Connect(const CallbackInfo &info)
{
    // char address[50];
    // strcpy(address, info[0].As<String>().Utf8Value().c_str());
    // api->RegisterSpi(this);
    // api->RegisterFront(address);
    // api->Init();
    auto deferred = new Promise::Deferred(info.Env());
    // promises.emplace(std::piecewise_construct, std::make_tuple(0), std::make_tuple((napi_env)info.Env()) );
    promises.emplace(0, deferred);
    return deferred->Promise();
}