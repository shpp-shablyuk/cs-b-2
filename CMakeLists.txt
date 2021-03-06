cmake_minimum_required(VERSION 3.3)
project(silhouette)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    lib/StanfordCPPLib/private/foreachpatch.h
    lib/StanfordCPPLib/private/main.h
    lib/StanfordCPPLib/private/randompatch.h
    lib/StanfordCPPLib/private/tokenpatch.h
    lib/StanfordCPPLib/private/tplatform.h
    lib/StanfordCPPLib/private/version.h
    lib/StanfordCPPLib/stacktrace/call_stack.h
    lib/StanfordCPPLib/stacktrace/call_stack_gcc.cpp
    lib/StanfordCPPLib/stacktrace/call_stack_windows.cpp
    lib/StanfordCPPLib/stacktrace/stack_exception.h
    lib/StanfordCPPLib/base64.cpp
    lib/StanfordCPPLib/base64.h
    lib/StanfordCPPLib/basicgraph.cpp
    lib/StanfordCPPLib/basicgraph.h
    lib/StanfordCPPLib/bitstream.cpp
    lib/StanfordCPPLib/bitstream.h
    lib/StanfordCPPLib/compare.h
    lib/StanfordCPPLib/console.cpp
    lib/StanfordCPPLib/console.h
    lib/StanfordCPPLib/dawglexicon.cpp
    lib/StanfordCPPLib/dawglexicon.h
    lib/StanfordCPPLib/deque.h
    lib/StanfordCPPLib/direction.cpp
    lib/StanfordCPPLib/direction.h
    lib/StanfordCPPLib/error.cpp
    lib/StanfordCPPLib/error.h
    lib/StanfordCPPLib/exceptions.cpp
    lib/StanfordCPPLib/exceptions.h
    lib/StanfordCPPLib/filelib.cpp
    lib/StanfordCPPLib/filelib.h
    lib/StanfordCPPLib/foreach.h
    lib/StanfordCPPLib/gbufferedimage.cpp
    lib/StanfordCPPLib/gbufferedimage.h
    lib/StanfordCPPLib/gevents.cpp
    lib/StanfordCPPLib/gevents.h
    lib/StanfordCPPLib/gfilechooser.cpp
    lib/StanfordCPPLib/gfilechooser.h
    lib/StanfordCPPLib/ginteractors.cpp
    lib/StanfordCPPLib/ginteractors.h
    lib/StanfordCPPLib/gmath.cpp
    lib/StanfordCPPLib/gmath.h
    lib/StanfordCPPLib/gobjects.cpp
    lib/StanfordCPPLib/gobjects.h
    lib/StanfordCPPLib/goptionpane.cpp
    lib/StanfordCPPLib/goptionpane.h
    lib/StanfordCPPLib/graph.h
    lib/StanfordCPPLib/grid.h
    lib/StanfordCPPLib/gtimer.cpp
    lib/StanfordCPPLib/gtimer.h
    lib/StanfordCPPLib/gtypes.cpp
    lib/StanfordCPPLib/gtypes.h
    lib/StanfordCPPLib/gwindow.cpp
    lib/StanfordCPPLib/gwindow.h
    lib/StanfordCPPLib/hashcode.cpp
    lib/StanfordCPPLib/hashcode.h
    lib/StanfordCPPLib/hashmap.h
    lib/StanfordCPPLib/hashset.h
    lib/StanfordCPPLib/lexicon.cpp
    lib/StanfordCPPLib/lexicon.h
    lib/StanfordCPPLib/linkedlist.h
    lib/StanfordCPPLib/main.cpp
    lib/StanfordCPPLib/map.h
    lib/StanfordCPPLib/observable.cpp
    lib/StanfordCPPLib/observable.h
    lib/StanfordCPPLib/platform.cpp
    lib/StanfordCPPLib/platform.h
    lib/StanfordCPPLib/point.cpp
    lib/StanfordCPPLib/point.h
    lib/StanfordCPPLib/pqueue.h
    lib/StanfordCPPLib/queue.h
    lib/StanfordCPPLib/random.cpp
    lib/StanfordCPPLib/random.h
    lib/StanfordCPPLib/regexpr.cpp
    lib/StanfordCPPLib/regexpr.h
    lib/StanfordCPPLib/set.h
    lib/StanfordCPPLib/shuffle.cpp
    lib/StanfordCPPLib/shuffle.h
    lib/StanfordCPPLib/simpio.cpp
    lib/StanfordCPPLib/simpio.h
    lib/StanfordCPPLib/sound.cpp
    lib/StanfordCPPLib/sound.h
    lib/StanfordCPPLib/sparsegrid.h
    lib/StanfordCPPLib/stack.h
    lib/StanfordCPPLib/startup.cpp
    lib/StanfordCPPLib/strlib.cpp
    lib/StanfordCPPLib/strlib.h
    lib/StanfordCPPLib/timer.cpp
    lib/StanfordCPPLib/timer.h
    lib/StanfordCPPLib/tokenscanner.cpp
    lib/StanfordCPPLib/tokenscanner.h
    lib/StanfordCPPLib/urlstream.cpp
    lib/StanfordCPPLib/urlstream.h
    lib/StanfordCPPLib/vector.h
    lib/StanfordCPPLib/version.cpp
    src/silhouette.cpp
    src/silhouette.h)

add_executable(silhouette ${SOURCE_FILES})