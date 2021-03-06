/* cppsrc/Samples/classexample.cpp */

#include "classexample.h"

Napi::FunctionReference ClassExample::constructor;

Napi::Object ClassExample::Init(Napi::Env env, Napi::Object exports)
{
	Napi::HandleScope scope(env);

	Napi::Function func = DefineClass(env, "ClassExample", {
															   InstanceMethod("add", &ClassExample::Add),
															   InstanceMethod("getValue", &ClassExample::GetValue),
															   InstanceMethod("init", &ClassExample::Initialize),
															   InstanceMethod("startPipeline", &ClassExample::StartPipeline),
															   InstanceMethod("start", &ClassExample::Start),
															   InstanceMethod("setFunction", &ClassExample::setFunction),
															   InstanceMethod("callFunction", &ClassExample::callFunction),
														   });

	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();

	exports.Set("ClassExample", func);
	return exports;
}

ClassExample::ClassExample(const Napi::CallbackInfo &info) : Napi::ObjectWrap<ClassExample>(info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	int length = info.Length();
	if (length != 1 || !info[0].IsNumber())
	{
		Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
	}

	Napi::Number value = info[0].As<Napi::Number>();
	this->actualClass_ = new ActualClass(value.DoubleValue());
}

Napi::Value ClassExample::GetValue(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	double num = this->actualClass_->getValue();
	return Napi::Number::New(env, num);
}

Napi::Value ClassExample::Add(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if (info.Length() != 1 || !info[0].IsNumber())
	{
		Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
	}

	Napi::Number toAdd = info[0].As<Napi::Number>();
	double answer = this->actualClass_->add(toAdd.DoubleValue());

	return Napi::Number::New(info.Env(), answer);
}

Napi::Value ClassExample::Initialize(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	int num = this->actualClass_->init();
	return Napi::Number::New(env, num);
}

Napi::Value ClassExample::setFunction(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if (info.Length() != 1 || !info[0].IsFunction())
	{
		Napi::TypeError::New(env, "Invalid argument types").ThrowAsJavaScriptException();
	}

	Napi::Function cb = info[0].As<Napi::Function>();
	this->actualClass_->set_function(cb);

	int num = 123;
	return Napi::Number::New(env, num);
}

Napi::Value ClassExample::callFunction(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	this->actualClass_->call_function();

	int num = 321;
	return Napi::Number::New(env, num);
}

Napi::Value ClassExample::Start(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	int num = this->actualClass_->start();
	return Napi::Number::New(env, num);
}

Napi::Value ClassExample::StartPipeline(const Napi::CallbackInfo &info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	int num = this->actualClass_->start_pipeline();
	return Napi::Number::New(env, num);
}
