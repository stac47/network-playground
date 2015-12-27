base_env = Environment(CPPPATH=['#common/include'],
                       CXXFLAGS=['-g', '--std=c++14', '-Wall', '-Werror',
                       '-Wpedantic', '-fdiagnostics-color=auto',
                       '-DBOOST_LOG_DYN_LINK'])
Export('base_env')

SConscript(['common/SConscript',
            'server/SConscript',
            'client/SConscript'], exports='base_env')

