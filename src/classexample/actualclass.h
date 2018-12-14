#include <gst/gst.h>
#include <gst/sdp/sdp.h>

#define GST_USE_UNSTABLE_API
#include <gst/webrtc/webrtc.h>

#include <napi.h>

class ActualClass {
	public:
		ActualClass(double value); //constructor
		double getValue(); //getter for the value
		double add(double toAdd); //adds the toAdd value to the value_
		int init();
		int start();
		int stop();
		gboolean check_plugins();
		int start_pipeline();
		void set_function(Napi::Function& cb);
		void call_function();
	private: 
		GOptionContext *context;
		double dummy_opt;
		GError * error;
		GMainLoop * loop;
		GstElement *pipe1;
		Napi::FunctionReference callback;
};
