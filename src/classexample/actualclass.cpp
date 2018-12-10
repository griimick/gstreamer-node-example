/* For signalling */
#include <libsoup/soup.h>
#include <json-glib/json-glib.h>

#include <string.h>


#include "actualclass.h"

ActualClass::ActualClass(double value){
	this->dummy_opt = value;
	this->error = NULL;
}

int ActualClass::init() {
	GOptionContext *context;
	GError *error = NULL;

	if (!check_plugins ())
		return -1;

	return 0;
}

int ActualClass::start () {
	this->loop = g_main_loop_new (NULL, FALSE);

	connect_to_websocket_server_async ();

	g_main_loop_run (this->loop);
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

int ActualClass::stop () {
	g_main_loop_quit (this->loop);
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
