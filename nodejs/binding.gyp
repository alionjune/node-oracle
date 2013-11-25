{
  'targets': [
    {
      'target_name': 'oracle_bindings',
      'sources': ['src/QueryJob.cc','src/oracle_bindings.cc','src/Connection.cc','../third_party/CodingConv/encodeutil.cpp',
	  '../core/OTLConn.cpp','../core/plateform_public.cpp','src/nodefunction.cc'
	  ],
	'conditions':[
		["OS!='win'",{
			'libraries': [ '-lclntsh' ],
			'link_settings': {'libraries': [ '-L /home/zhs/Desktop/oracle_oci/nodejs/lib/'] }
	
		}]
	],
	
	'cflags':['-fexceptions'],
	'cflags_cc':['-fexceptions'],
 	
	
	
	
    }
  ]

}
