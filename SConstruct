base_env = Environment(CPPPATH=['#common/include'],
                       CXXFLAGS=['-g', '--std=c++14', '-Wall', '-Werror',
                       '-Wpedantic', '-fdiagnostics-color=auto',
                       '-DBOOST_LOG_DYN_LINK'],
                       LIBS=['pthread', 'boost_thread', 'boost_log'])

test_env = base_env.Clone()
test_env.AppendUnique(LIBS=['gtest'])

Export('base_env')
Export('test_env')

SConscript(['common/SConscript',
            'server/SConscript',
            'client/SConscript'], exports='base_env')

