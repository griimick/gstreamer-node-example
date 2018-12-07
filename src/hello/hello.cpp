#include "hello.h"

std::string hello::hello(){
	return "Hello World";
}

int hello::add(int a, int b){
	return a + b;
}

Napi::String hello::HelloWrapped(const Napi::CallbackInfo& info) 
{
	Napi::Env env = info.Env();
	Napi::String returnValue = Napi::String::New(env, hello::hello());

	return returnValue;
}

Napi::Number hello::AddWrapped(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
		Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
	}

	Napi::Number first = info[0].As<Napi::Number>();
	Napi::Number second = info[1].As<Napi::Number>();

	int returnValue = hello::add(first.Int32Value(), second.Int32Value());

	return Napi::Number::New(env, returnValue);
}

Napi::Object hello::Init(Napi::Env env, Napi::Object exports) 
{
	exports.Set("hello", Napi::Function::New(env, hello::HelloWrapped));
	exports.Set("add", Napi::Function::New(env, hello::AddWrapped));

	return exports;
}
