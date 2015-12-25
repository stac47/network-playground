base_env = Environment(CPPPATH=['#common/include'],
                       CXXFLAGS='-g --std=c++11')
Export('base_env')

SConscript(['common/SConscript',
            'server/SConscript',
            'client/SConscript'], exports='base_env')

