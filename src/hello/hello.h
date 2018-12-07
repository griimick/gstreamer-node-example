#include <napi.h>
namespace hello {
  std::string hello();
  int add(int a, int b);
  Napi::String HelloWrapped(const Napi::CallbackInfo& info);
  Napi::Number AddWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
}
