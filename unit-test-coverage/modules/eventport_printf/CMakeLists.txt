########################################################
# PSP Module: Unit test for eventport_printf
########################################################

# Create the unit test executable
add_executable(coverage-eventport_printf-testrunner
    coveragetest-eventport_printf.c
    ${PSP_UT_SHARED_COVERAGE_SRCS}
    $<TARGET_OBJECTS:ut_coverage_support>
)

target_link_libraries(coverage-eventport_printf-testrunner PUBLIC
    ${UT_COVERAGE_LINK_FLAGS}
    psp_module_api
    ut_assert
)

add_test(coverage-eventport_printf-testrunner coverage-eventport_printf-testrunner)

# Install the executables to a staging area for test in cross environments
if (INSTALL_TARGET_LIST)
    foreach(TGT ${INSTALL_TARGET_LIST})
        install(TARGETS coverage-eventport_printf-testrunner DESTINATION ${TGT}/${UT_INSTALL_SUBDIR})
    endforeach()
endif()