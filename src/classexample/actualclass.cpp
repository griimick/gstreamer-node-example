/* For signalling */
#include <libsoup/soup.h>
#include <json-glib/json-glib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "actualclass.h"

ActualClass::ActualClass(double value)
{
	this->dummy_opt = value;
	this->error = NULL;
	this->loop = NULL;
}

int ActualClass::init()
{
	GOptionContext *context;
	GError *error = NULL;

	context = g_option_context_new("- gstreamer webrtc sendrecv demo");
	g_option_context_add_group(context, gst_init_get_option_group());
	if (!g_option_context_parse(context, NULL, NULL, &error))
	{
		printf("Error initializing: %s\n", error->message);
		return -1;
	}
	this->context = context;

	/*
	char * env = getenv ("GST_PLUGIN_PATH");
	printf ("Env = %s\n", env);
	*/

	if (!this->check_plugins())
		return -1;

	return 0;
}

int ActualClass::start()
{
	this->loop = g_main_loop_new(NULL, FALSE);

	//connect_to_websocket_server_async ();

	this->start_pipeline();

	g_main_loop_run(this->loop);
	//g_main_loop_unref (this->loop);

	/*
	if (pipe1) {
		gst_element_set_state (GST_ELEMENT (pipe1), GST_STATE_NULL);
		g_print ("Pipeline stopped\n");
		gst_object_unref (pipe1);
	}
	*/

	return 0;
}

int ActualClass::start_pipeline(void)
{
	GstStateChangeReturn ret;
	GError *error = NULL;
	GstElement *pipe;

/*
	this->pipe1 =
		gst_parse_launch("webrtcbin bundle-policy=max-bundle name=sendrecv " STUN_SERVER
						 "videotestsrc is-live=true pattern=ball ! videoconvert ! queue ! vp8enc deadline=1 ! rtpvp8pay ! "
						 "queue ! " RTP_CAPS_VP8 "96 ! sendrecv. "
						 "audiotestsrc is-live=true wave=silence ! audioconvert ! audioresample ! queue ! opusenc ! rtpopuspay ! "
						 "queue ! " RTP_CAPS_OPUS "97 ! sendrecv. ",
						 &error);

*/
	this->pipe1 = gst_parse_launch("audiotestsrc ! audioconvert ! autoaudiosink", &error);
	if (error)
	{
		printf("Failed to parse launch: %s\n", error->message);
		g_error_free(error);
		printf("ERORR IN STARTING PIPELINE");
		return -2;
	}

	printf("Starting pipeline\n");

	ret = gst_element_set_state(GST_ELEMENT(this->pipe1), GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE)
		printf("ERORR IN STARTING PIPELINE: %s\n", ret);
		return -3;

	return 0;
}

int ActualClass::stop()
{
	g_main_loop_quit(this->loop);
	return 0;
}

double ActualClass::getValue()
{
	return this->dummy_opt;
}

double ActualClass::add(double toAdd)
{
	this->dummy_opt += toAdd;
	return this->dummy_opt;
}

gboolean ActualClass::check_plugins(void)
{
	int i;
	gboolean ret;
	GstPlugin *plugin;
	GstRegistry *registry;
	const gchar *needed[] = {"opus", "vpx", "nice", "webrtc", "dtls", "srtp",
							 "rtpmanager", "videotestsrc", "audiotestsrc", NULL};

	registry = gst_registry_get();
	ret = TRUE;
	for (i = 0; i < g_strv_length((gchar **)needed); i++)
	{
		plugin = gst_registry_find_plugin(registry, needed[i]);
		if (!plugin)
		{
			g_print("Required gstreamer plugin '%s' not found\n", needed[i]);
			ret = FALSE;
			continue;
		}
		gst_object_unref(plugin);
	}
	return ret;
}
