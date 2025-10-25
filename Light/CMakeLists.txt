set(target ELight)

file(GLOB hdrs "*.h*" )
file(GLOB srcs "*.cpp")

#add_library(${target} STATIC ${srcs} ${hdrs})
add_executable(LLight ${srcs} ${hdrs})
target_link_libraries(LLight  ${MP2_LIBRARY})
