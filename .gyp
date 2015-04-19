{
	'target_defaults': {
		'xcode_settings': {
			'OTHER_CFLAGS': [
				'--std=c++11',
				'-g',
				'-static',
			],
		},
		'cflags': [
			'--std=c++11',
			'-g',
			'-static',
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
				'lex.cc',
				'x86_64.cc',
				'log.cc',
				'tok.cc',
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
