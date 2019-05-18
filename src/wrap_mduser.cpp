#include "wrap_mduser.h"
#include "utils.h"

int MdReqID = 0;
FunctionReference Mduser::constructor;
Object Mduser::Init(Napi::Env env, Object exports)
{
    HandleScope scope(env);
    Function ctor = DefineClass(env, "Mduser",
                                {InstanceMethod("connect", &Mduser::Connect)});

    constructor = Persistent(ctor);
    constructor.SuppressDestruct();
    exports.Set("Mduser", ctor);
    return exports;
}
Mduser::Mduser(const CallbackInfo &info) : ObjectWrap<Mduser>(info), api(CThostFtdcMdApi::CreateFtdcMdApi(""))
{
}
Mduser::~Mduser(void)
{
}
Napi::Value Mduser::Connect(const CallbackInfo &info)
{
    char address[50];
    strcpy(address, info[0].As<String>().Utf8Value().c_str());
    api->RegisterSpi(this);
    api->RegisterFront(address);
    api->Init();
    auto deferred = new Promise::Deferred(info.Env());
    // promises.emplace(std::piecewise_construct, std::make_tuple(0), std::make_tuple((napi_env)info.Env()) );
    promises.emplace(0, deferred);
    return deferred->Promise();
}
void Mduser::OnFrontConnected()
{
    async(new CbRtnField(nullptr, 0));
}

void Mduser::OnFrontDisconnected(int nReason)
{
    CThostFtdcRspInfoField r;
    r.ErrorID = nReason;
    itoa(nReason, r.ErrorMsg, 16);
    async(new CbRtnField(&r, 0));
}

///心跳超时警告。当长时间未收到报文时，该方法被调用。
///@param nTimeLapse 距离上次接收报文的时间
void Mduser::OnHeartBeatWarning(int nTimeLapse) {}

///登录请求响应
void Mduser::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

///登出请求响应
void Mduser::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

///错误应答
void Mduser::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {}

///订阅行情应答
void Mduser::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                bool bIsLast) {}

///取消订阅行情应答
void Mduser::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                                  int nRequestID, bool bIsLast) {}

///订阅询价应答
void Mduser::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                 bool bIsLast) {}

///取消订阅询价应答
void Mduser::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                                   int nRequestID, bool bIsLast) {}

///深度行情通知
void Mduser::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {}

///询价通知
void Mduser::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {}