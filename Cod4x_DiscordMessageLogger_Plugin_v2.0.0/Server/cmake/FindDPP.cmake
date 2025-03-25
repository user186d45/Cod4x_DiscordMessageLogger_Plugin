message(STATUS "Searching for DPP in: ${DPP_ROOT_DIR}/lib /usr/local/lib")

find_path(DPP_INCLUDE_DIR NAMES dpp/dpp.h HINTS ${DPP_ROOT_DIR} /usr/local/include)

find_library(DPP_LIBRARIES NAMES dpp "libdpp.so" HINTS ${DPP_ROOT_DIR}/lib /usr/local/lib)
	 
include(FindPackageHandleStandardArgs)
	 
find_package_handle_standard_args(DPP DEFAULT_MSG DPP_LIBRARIES DPP_INCLUDE_DIR)
