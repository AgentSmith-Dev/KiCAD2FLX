# CMake generated Testfile for 
# Source directory: /work/test
# Build directory: /work/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SmokeConvert "/work/KiCAD2FLX" "/work/test/../CurrentSensor-top.pos" "/work/test/CurrentSensor-top.flx.pos" "/work/test/../KiCADPackage2FLX.txt")
set_tests_properties(SmokeConvert PROPERTIES  _BACKTRACE_TRIPLES "/work/test/CMakeLists.txt;1;add_test;/work/test/CMakeLists.txt;0;")
add_test(CompareAgainstExpected "/usr/bin/cmake" "-E" "compare_files" "/work/test/CurrentSensor-top.flx.pos" "/work/test/../CurrentSensor-top.flx.pos.expected")
set_tests_properties(CompareAgainstExpected PROPERTIES  _BACKTRACE_TRIPLES "/work/test/CMakeLists.txt;9;add_test;/work/test/CMakeLists.txt;0;")
