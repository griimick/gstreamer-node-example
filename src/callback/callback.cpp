#include <napi.h>
#include "actualcallback.cpp"

void SumAsyncCallback(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();

	//
	// Account for known potential issues that MUST be handled by
	// synchronously throwing an `Error`
	//
	if (info.Length() < 3)
	{
		Napi::TypeError::New(env, "Invalid argument count").ThrowAsJavaScriptException();
		return;
	}

	if (!info[2].IsFunction())
	{
		Napi::TypeError::New(env, "Invalid argument types").ThrowAsJavaScriptException();
		return;
	}

	//
	// Handle all other potential issues asynchronously via the provided callback
	//

	Napi::Function cb = info[2].As<Napi::Function>();

	if (info.Length() != 3)
	{
		(new ErrorAsyncWorker(cb, Napi::TypeError::New(env, "Invalid argument count")))->Queue();
	}
	else if (!info[0].IsNumber() || !info[1].IsNumber())
	{
		(new ErrorAsyncWorker(cb, Napi::TypeError::New(env, "Invalid argument types")))->Queue();
	}
	else
	{
		double arg0 = info[0].As<Napi::Number>().DoubleValue();
		double arg1 = info[1].As<Napi::Number>().DoubleValue();

		(new SumAsyncWorker(cb, arg0, arg1))->Queue();
	}

	return;
}