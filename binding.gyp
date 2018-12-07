{
	"targets": [{
		"target_name": "testaddon",
			"cflags!": [ "-fno-exceptions" ],
			"cflags_cc!": [ "-fno-exceptions" ],
			"sources": [
				"src/main.cpp",
				"src/hello/hello.cpp",
				"src/classexample/actualclass.cpp",
				"src/classexample/classexample.cpp"
			],
			'include_dirs': [
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			'libraries': [],
			'dependencies': [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
	}]
}
