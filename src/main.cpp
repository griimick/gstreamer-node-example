/* cppsrc/main.cpp */
#include <napi.h>
#include "hello/hello.h"
#include "classexample/classexample.h"
#include "callback/callback.cpp"

Napi::Object InitAll (Napi::Env env, Napi::Object exports) {
	hello::Init(env, exports);
	ClassExample::Init(env, exports);
	exports.Set(
		Napi::String::New(env, "addCallback"),
		Napi::Function::New(env, SumAsyncCallback)
	);
	return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
