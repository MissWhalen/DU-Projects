if(EXISTS "C:/Users/Briana/CLionProjects/COMP4370Ass2MergFib/cmake-build-debug/tests/unit_tests[1]_tests.cmake")
  include("C:/Users/Briana/CLionProjects/COMP4370Ass2MergFib/cmake-build-debug/tests/unit_tests[1]_tests.cmake")
else()
  add_test(unit_tests_NOT_BUILT unit_tests_NOT_BUILT)
endif()