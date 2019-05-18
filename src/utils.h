#pragma once
#include <uv.h>
#include <napi.h>
#include "ThostFtdcUserApiStruct.h"
#include <map>
#define RETURN_PROMISE(x)                                            \
    Promise::Deferred deferred = Promise::Deferred::New(info.Env()); \
    promises.emplace(x, deferred);                                   \
    return deferred.Promise();

class CbRtnField
{
public:
    uv_work_t work;
    int eFlag;
    int nRequestID;
    int nReason;
    void *rtnField;
    CThostFtdcRspInfoField rspInfo;
    std::map<int, Napi::Promise::Deferred *> *promises;
    bool bIsLast;
    CbRtnField(CThostFtdcRspInfoField *_rspInfo, int nRequestID, bool bIsLast = false)
    {
        this->nRequestID = nRequestID;
        this->bIsLast = bIsLast;
        if (_rspInfo != nullptr)
        {
            memcpy(&rspInfo, _rspInfo, sizeof(CThostFtdcRspInfoField));
        }
        else
        {
            rspInfo.ErrorID = 0;
        }
        work.data = this;
    }
    ~CbRtnField()
    {
    }
    Napi::Error toErrorObject(Napi::Env env)
    {
        return Napi::Error::New(env, rspInfo.ErrorMsg);
    }
    virtual Napi::Value toJsObject(Napi::Env env)
    {
        return env.Undefined();
    }
};