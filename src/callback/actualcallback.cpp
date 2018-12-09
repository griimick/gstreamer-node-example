#include <napi.h>

class ErrorAsyncWorker : public Napi::AsyncWorker
{
  public:
	ErrorAsyncWorker(
		const Napi::Function &callback,
		Napi::Error error) : Napi::AsyncWorker(callback), error(error)
	{
	}

  protected:
	void Execute() override
	{
		// Do nothing...?
	}

	void OnOK() override
	{
		Napi::Env env = Env();

		Callback().MakeCallback(
			Receiver().Value(),
			{error.Value(),
			 env.Undefined()});
	}

	void OnError(const Napi::Error &e) override
	{
		Napi::Env env = Env();

		Callback().MakeCallback(
			Receiver().Value(),
			{e.Value(),
			 env.Undefined()});
	}

  private:
	Napi::Error error;
};

class SumAsyncWorker : public Napi::AsyncWorker
{
  public:
	SumAsyncWorker(
		const Napi::Function &callback,
		const double arg0,
		const double arg1) : Napi::AsyncWorker(callback), arg0(arg0), arg1(arg1), sum(0)
	{
	}

  protected:
	void Execute() override
	{
		sum = arg0 + arg1;
	}

	void OnOK() override
	{
		Napi::Env env = Env();

		Callback().MakeCallback(
			Receiver().Value(),
			{env.Null(),
			 Napi::Number::New(env, sum)});
	}

	void OnError(const Napi::Error &e) override
	{
		Napi::Env env = Env();

		Callback().MakeCallback(
			Receiver().Value(),
			{e.Value(),
			 env.Undefined()});
	}

  private:
	double arg0;
	double arg1;
	double sum;
};
