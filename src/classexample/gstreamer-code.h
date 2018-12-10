#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <gst/gst.h>
#include <gst/sdp/sdp.h>

static gboolean
check_plugins(void)
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

#endif