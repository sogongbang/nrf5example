set_cache(NRF5SDK__BOARD_NAME "PCA10040" STRING)
set_cache(NRF5SDK__BOARD_CONFIG_NAME "CLI" STRING)
set_cache(NRF5SDK__APP_TIMER_V2 TRUE BOOL)
set_cache(NRF5SDK__APP_TIMER_V2_RTC1_ENABLED TRUE BOOL)
set_cache(NRF5SDK__DEBUG TRUE BOOL)
set_cache(NRF5SDK__DEBUG_NRF TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52dk.cmake)

include(${PROJECT_LIBRARY_DIR}/nrf5sdk/config/nrf5sdk.cmake)

####

set(INCLUDE__APP TRUE)
set(APP__NAME "mycli2")

get_filename_component(_tmp_source_dir "${CMAKE_CURRENT_LIST_DIR}/mycli2" ABSOLUTE)

file(GLOB_RECURSE _tmp_sources
    "${_tmp_source_dir}/*.c"
    "${_tmp_source_dir}/*.cpp"
    "${_tmp_source_dir}/*.S"
    "${_tmp_source_dir}/*.s")

set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} ${_tmp_sources})

