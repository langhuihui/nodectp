{
    "targets": [
        {
            "target_name": "ctp",
            "sources": [
                "src/ctp.cc", "src/wrap_mduser.cpp","src/wrap_trader.cpp"
            ],
            "libraries": [
                "../20180109_ctp_windows/thostmduserapi.lib",
                "../20180109_ctp_windows/thosttraderapi.lib"
            ],
            'dependencies': [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "include_dirs": [
                "20180109_ctp_windows/",
                "src/",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': ['NAPI_CPP_EXCEPTIONS'
                        ],
            'cflags!': ['-fno-exceptions'
                        ],
            'cflags_cc!': ['-fno-exceptions'
                           ],
            'msvs_settings': {
                'VCCLCompilerTool': {'ExceptionHandling': 1},
            }
        }
    ]
}
