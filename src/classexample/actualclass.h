#include <gst/gst.h>
#include <gst/sdp/sdp.h>

#define GST_USE_UNSTABLE_API
#include <gst/webrtc/webrtc.h>

class ActualClass {
	public:
		ActualClass(double value); //constructor
		double getValue(); //getter for the value
		double add(double toAdd); //adds the toAdd value to the value_
	private:
		double value_;
		GError * error;
		GMainLoop * loop;
};
