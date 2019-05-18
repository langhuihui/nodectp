#pragma once

#include "ThostFtdcTraderApi.h"
#include "promise.h"
using namespace Napi;
class Trader : public ObjectWrap<Trader>, public PromiseHelper
{
public:
  Trader(const Napi::CallbackInfo &info);
  ~Trader(void);
  static FunctionReference constructor;
  static Object Init(Napi::Env env, Object exports);
  CThostFtdcTraderApi *api;
  Napi::Value Connect(const CallbackInfo &info);
};