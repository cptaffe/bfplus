{
	'target_defaults': {
		'xcode_settings': {
			'OTHER_CFLAGS': [
				'--std=c++11',
			],
		},
		'cflags': [
			'--std=c++11',
		],
	},
	'targets': [
		{
			'target_name': 'libkai',
			'type': 'static_library',
			'dependencies': [],
			'sources': [
				'comp.cc',
				'jit.cc',
				'x86_64.cc',
			],
			'include_dirs': [],
		},
		{
			'target_name': 'test',
			'type': 'executable',
			'dependencies': [
				'libkai',
			],
			'defines': [],
			'include_dirs': [],
			'sources': [
				'main.cc',
			],
		},
	],
}
