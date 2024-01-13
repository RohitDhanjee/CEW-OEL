# CMake generated Testfile for 
# Source directory: /workspaces/CEW-OEL/cJSON
# Build directory: /workspaces/CEW-OEL/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/workspaces/CEW-OEL/build/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/CEW-OEL/cJSON/CMakeLists.txt;252;add_test;/workspaces/CEW-OEL/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
