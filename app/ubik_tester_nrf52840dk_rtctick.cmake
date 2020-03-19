set_cache(UBINOS__UBIK__TICK_TYPE "RTC" STRING)
set_cache(UBINOS__UBIK__TICK_PER_SEC 1024 STRING)

set_cache(NRF5SDK__BSP_DEFINES_ONLY TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52840dk.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubik_test.cmake)

include(${PROJECT_LIBRARY_DIR}/nrf5sdk/config/nrf5sdk.cmake)

include(${PROJECT_UBINOS_DIR}/app/ubik_tester.cmake)

####

string(TOLOWER ${NRF5SDK__BOARD_NAME} _temp_board_name)

get_filename_component(_tmp_source_dir "${PROJECT_LIBRARY_DIR}/nrf5sdk/source/nRF5_SDK/examples/peripheral/rtc/" ABSOLUTE)

include_directories(${_tmp_source_dir}/${_temp_board_name}/blank/config)
include_directories(${_tmp_source_dir})

