#pragma once
#include "utils.h"
class PromiseHelper
{
public:
    std::map<int, Napi::Promise::Deferred *> promises;
    uv_async_t async_t;
    PromiseHelper()
    {
        uv_async_init(uv_default_loop(), &async_t, NULL);
    }
    ~PromiseHelper()
    {
        uv_close((uv_handle_t *)&async_t, NULL);
    }
    static void _on_async(uv_work_t *work)
    {
        //do nothing
    }
    static void _on_completed(uv_work_t *work, int)
    {
        auto data = (CbRtnField *)work->data;
        auto promises = *data->promises;
        auto it = promises.find(data->nRequestID);
        if (it != promises.end())
        {
            auto deferred = *it->second;
            auto env = deferred.Env();
            Napi::HandleScope scope(env);
            if (data->rspInfo.ErrorID != 0)
                deferred.Reject(data->toErrorObject(env).Value());
            else
                deferred.Resolve(data->toJsObject(env));
            delete it->second;
            promises.erase(it->first);
        }
        delete work->data;
    }
    void async(CbRtnField *field)
    {
        field->promises = &promises;
        uv_queue_work(uv_default_loop(), &field->work, _on_async, _on_completed);
    }
};