{
    'conditions': [
      ['OS=="win"', {
        'targets': [
          {
            'target_name': 'oracle_client',
			 'include_dirs':[
	  '../oci',
	  '../un/include',
	  '../un/src/win32'
	  ],
      'sources': ['src/oracle_client.cc','src/Connection.cc','../third_party/CodingConv/encodeutil.cpp',
	 '../core/plateform_public.cpp','src/nodefunction.cc','../core/otlPool.cpp','src/ConnctionPool.cc',
	 	'../un/src/win32/thread.c','../un/src/win32/winapi.c'
	  ],
             
          },
        ],
      }],
	 ['OS=="linux"', {
        'targets': [
          {
            'target_name': 'oracle_client',
			 'include_dirs':[
	  '../oci',
	  '../un/include',
	  ],
      'sources': ['src/oracle_client.cc','src/Connection.cc','../third_party/CodingConv/encodeutil.cpp',
	 '../core/plateform_public.cpp','src/nodefunction.cc','../core/otlPool.cpp','src/ConnctionPool.cc',
	 	'../un/src/linux/thread.c'
	  ],
	  'libraries': [ '-lclntsh','-lpthread' ],
	'link_settings': {'libraries': [ '-L /home/zhs/oracle/product/10.2.0/db_2/lib/'] },
	'cflags':['-fexceptions'],
	'cflags_cc':['-fexceptions']
             
          },
        ],
      }]
     
	],
	
 	
}