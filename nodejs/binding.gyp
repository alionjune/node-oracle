{
  'targets': [
    {
      'target_name': 'oracle_client',
	  'include_dirs':[
	  '../oci',
	  '../un/include','../un/src/win32',
	  '../un/src/liunx'
	  ],
      'sources': ['src/QueryJob.cc','src/oracle_client.cc','src/Connection.cc','../third_party/CodingConv/encodeutil.cpp',
	 '../core/plateform_public.cpp','src/nodefunction.cc','../core/otlPool.cpp','src/QueryJob.cc','src/ConnctionPool.cc','../un/src/linux/thread.c'
	  ],
	'conditions':[
		["OS!='win'",{
			'libraries': [ '-lclntsh','-lpthread' ],
			'link_settings': {'libraries': [ '-L /home/zhs/oracle/product/10.2.0/db_2/lib/'] }
	
		}]
	],
	
	'cflags':['-fexceptions'],
	'cflags_cc':['-fexceptions'],
 	
	
	
	
    }
  ]

}
