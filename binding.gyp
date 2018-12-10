{
	"targets": [{
		"target_name": "testaddon",
			"cflags!": [ "-fno-exceptions", "-O0", "-ggdb", "-Wall", "-fno-omit-frame-pointer",
			"-pthread",
			],
			"cflags_cc!": [ "-fno-exceptions", "-O0", "-ggdb", "-Wall", "-fno-omit-frame-pointer",
			"-pthread",
			],
			"sources": [
				"src/main.cpp",
				"src/hello/hello.cpp",
				"src/classexample/actualclass.cpp",
				"src/classexample/classexample.cpp",
				"src/gst-basic-example/basic-example.c"
			],
			'include_dirs': [
				"<!@(node -p \"require('node-addon-api').include\")",
				"/home/griimick/github/gst-build/subprojects/gstreamer/pkgconfig/../libs",
				"/home/griimick/github/gst-build/build/subprojects/gstreamer/pkgconfig/../libs",
				"/home/griimick/github/gst-build/subprojects/gstreamer/pkgconfig/..",
				"/home/griimick/github/gst-build/subprojects/gstreamer/pkgconfig/../libs",
				"/home/griimick/github/gst-build/build/subprojects/gstreamer/pkgconfig/..",
				"/home/griimick/github/gst-build/build/subprojects/gstreamer/pkgconfig/../libs",
				"/home/griimick/github/gst-build/subprojects/gst-plugins-bad/pkgconfig/../gst-libs",
				"/home/griimick/github/gst-build/build/subprojects/gst-plugins-bad/pkgconfig/../gst-libs",
				"/home/griimick/github/gst-build/subprojects/gst-plugins-base/pkgconfig/../gst-libs",
				"/home/griimick/github/gst-build/build/subprojects/gst-plugins-base/pkgconfig/../gst-libs",
				"/usr/include/json-glib-1.0",
				"/usr/include/libsoup-2.4",
				"/usr/include/libxml2",
				"/usr/include/glib-2.0",
				"/usr/lib/x86_64-linux-gnu/glib-2.0/include"
			],
			"library_dirs": [
				"/home/griimick/github/gst-build/build/subprojects/gstreamer/libs/gst/base",
				"/home/griimick/github/gst-build/build/subprojects/gstreamer/gst",
				"/home/griimick/github/gst-build/build/subprojects/gst-plugins-bad/gst-libs/gst/webrtc",
				"/home/griimick/github/gst-build/build/subprojects/gst-plugins-base/gst-libs/gst/sdp",
			],
			"libraries": [
				"-lgstsdp-1.0",
				"-lgstwebrtc-1.0",
				"-lgstbase-1.0",
				"-lgstreamer-1.0",
				"-ljson-glib-1.0",
				"-lsoup-2.4",
				"-lgio-2.0",
				"-lgobject-2.0",
				"-lglib-2.0"
			],
			'dependencies': [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
	}]
}
