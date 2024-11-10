
set(PYTHON "/home/ubuntu/.espressif/python_env/idf5.2_py3.12_env/bin/python")
set(__BUILD_PROPERTIES "PYTHON;__BUILD_PROPERTIES;IDF_PATH;__PREFIX;__CHECK_PYTHON;IDF_COMPONENT_MANAGER;COMPILE_DEFINITIONS;COMPILE_OPTIONS;C_COMPILE_OPTIONS;CXX_COMPILE_OPTIONS;__COMPONENT_TARGETS;BUILD_COMPONENT_DIRS;BUILD_COMPONENT_TARGETS;__COMPONENT_REQUIRES_COMMON;IDF_VER;__ROOT_KCONFIG;__ROOT_SDKCONFIG_RENAME;__OUTPUT_SDKCONFIG;EXTRA_CMAKE_ARGS;__COMPONENT_MANAGER_INTERFACE_VERSION;BOOTLOADER_BUILD;IDF_TOOLCHAIN;IDF_TARGET;IDF_TARGET_ARCH;PROJECT_DIR;PROJECT_NAME;PROJECT_VER;BUILD_DIR;SDKCONFIG;SDKCONFIG_DEFAULTS")
set(IDF_PATH "/home/ubuntu/esp/esp-idf")
set(__PREFIX "idf")
set(__CHECK_PYTHON "0")
set(IDF_COMPONENT_MANAGER "1")
set(COMPILE_DEFINITIONS "_GLIBCXX_USE_POSIX_SEMAPHORE;_GLIBCXX_HAVE_POSIX_SEMAPHORE;_GNU_SOURCE;IDF_VER="v5.2.3"")
set(COMPILE_OPTIONS "-ffunction-sections;-fdata-sections;-Wall;-Werror=all;-Wno-error=unused-function;-Wno-error=unused-variable;-Wno-error=unused-but-set-variable;-Wno-error=deprecated-declarations;-Wextra;-Wno-unused-parameter;-Wno-sign-compare;-Wno-enum-conversion;-gdwarf-4;-ggdb")
set(C_COMPILE_OPTIONS "-std=gnu17")
set(CXX_COMPILE_OPTIONS "-std=gnu++2b")
set(__COMPONENT_TARGETS "___idf_app_trace;___idf_app_update;___idf_bootloader;___idf_bootloader_support;___idf_bt;___idf_cmock;___idf_console;___idf_cxx;___idf_driver;___idf_efuse;___idf_esp-tls;___idf_esp_adc;___idf_esp_app_format;___idf_esp_bootloader_format;___idf_esp_coex;___idf_esp_common;___idf_esp_eth;___idf_esp_event;___idf_esp_gdbstub;___idf_esp_hid;___idf_esp_http_client;___idf_esp_http_server;___idf_esp_https_ota;___idf_esp_https_server;___idf_esp_hw_support;___idf_esp_lcd;___idf_esp_local_ctrl;___idf_esp_mm;___idf_esp_netif;___idf_esp_netif_stack;___idf_esp_partition;___idf_esp_phy;___idf_esp_pm;___idf_esp_psram;___idf_esp_ringbuf;___idf_esp_rom;___idf_esp_system;___idf_esp_timer;___idf_esp_wifi;___idf_espcoredump;___idf_esptool_py;___idf_fatfs;___idf_freertos;___idf_hal;___idf_heap;___idf_http_parser;___idf_idf_test;___idf_ieee802154;___idf_json;___idf_linux;___idf_log;___idf_lwip;___idf_mbedtls;___idf_mqtt;___idf_newlib;___idf_nvs_flash;___idf_nvs_sec_provider;___idf_openthread;___idf_partition_table;___idf_perfmon;___idf_protobuf-c;___idf_protocomm;___idf_pthread;___idf_riscv;___idf_sdmmc;___idf_soc;___idf_spi_flash;___idf_spiffs;___idf_tcp_transport;___idf_touch_element;___idf_ulp;___idf_unity;___idf_usb;___idf_vfs;___idf_wear_levelling;___idf_wifi_provisioning;___idf_wpa_supplicant;___idf_xtensa;___idf_main")
set(BUILD_COMPONENT_DIRS "/home/ubuntu/esp/esp-idf/components/app_trace;/home/ubuntu/esp/esp-idf/components/app_update;/home/ubuntu/esp/esp-idf/components/bootloader;/home/ubuntu/esp/esp-idf/components/bootloader_support;/home/ubuntu/esp/esp-idf/components/bt;/home/ubuntu/esp/esp-idf/components/cmock;/home/ubuntu/esp/esp-idf/components/console;/home/ubuntu/esp/esp-idf/components/cxx;/home/ubuntu/esp/esp-idf/components/driver;/home/ubuntu/esp/esp-idf/components/efuse;/home/ubuntu/esp/esp-idf/components/esp-tls;/home/ubuntu/esp/esp-idf/components/esp_adc;/home/ubuntu/esp/esp-idf/components/esp_app_format;/home/ubuntu/esp/esp-idf/components/esp_bootloader_format;/home/ubuntu/esp/esp-idf/components/esp_coex;/home/ubuntu/esp/esp-idf/components/esp_common;/home/ubuntu/esp/esp-idf/components/esp_eth;/home/ubuntu/esp/esp-idf/components/esp_event;/home/ubuntu/esp/esp-idf/components/esp_gdbstub;/home/ubuntu/esp/esp-idf/components/esp_hid;/home/ubuntu/esp/esp-idf/components/esp_http_client;/home/ubuntu/esp/esp-idf/components/esp_http_server;/home/ubuntu/esp/esp-idf/components/esp_https_ota;/home/ubuntu/esp/esp-idf/components/esp_https_server;/home/ubuntu/esp/esp-idf/components/esp_hw_support;/home/ubuntu/esp/esp-idf/components/esp_lcd;/home/ubuntu/esp/esp-idf/components/esp_local_ctrl;/home/ubuntu/esp/esp-idf/components/esp_mm;/home/ubuntu/esp/esp-idf/components/esp_netif;/home/ubuntu/esp/esp-idf/components/esp_netif_stack;/home/ubuntu/esp/esp-idf/components/esp_partition;/home/ubuntu/esp/esp-idf/components/esp_phy;/home/ubuntu/esp/esp-idf/components/esp_pm;/home/ubuntu/esp/esp-idf/components/esp_psram;/home/ubuntu/esp/esp-idf/components/esp_ringbuf;/home/ubuntu/esp/esp-idf/components/esp_rom;/home/ubuntu/esp/esp-idf/components/esp_system;/home/ubuntu/esp/esp-idf/components/esp_timer;/home/ubuntu/esp/esp-idf/components/esp_wifi;/home/ubuntu/esp/esp-idf/components/espcoredump;/home/ubuntu/esp/esp-idf/components/esptool_py;/home/ubuntu/esp/esp-idf/components/fatfs;/home/ubuntu/esp/esp-idf/components/freertos;/home/ubuntu/esp/esp-idf/components/hal;/home/ubuntu/esp/esp-idf/components/heap;/home/ubuntu/esp/esp-idf/components/http_parser;/home/ubuntu/esp/esp-idf/components/idf_test;/home/ubuntu/esp/esp-idf/components/ieee802154;/home/ubuntu/esp/esp-idf/components/json;/home/ubuntu/esp/esp-idf/components/linux;/home/ubuntu/esp/esp-idf/components/log;/home/ubuntu/esp/esp-idf/components/lwip;/home/ubuntu/esp/esp-idf/components/mbedtls;/home/ubuntu/esp/esp-idf/components/mqtt;/home/ubuntu/esp/esp-idf/components/newlib;/home/ubuntu/esp/esp-idf/components/nvs_flash;/home/ubuntu/esp/esp-idf/components/nvs_sec_provider;/home/ubuntu/esp/esp-idf/components/openthread;/home/ubuntu/esp/esp-idf/components/partition_table;/home/ubuntu/esp/esp-idf/components/perfmon;/home/ubuntu/esp/esp-idf/components/protobuf-c;/home/ubuntu/esp/esp-idf/components/protocomm;/home/ubuntu/esp/esp-idf/components/pthread;/home/ubuntu/esp/esp-idf/components/riscv;/home/ubuntu/esp/esp-idf/components/sdmmc;/home/ubuntu/esp/esp-idf/components/soc;/home/ubuntu/esp/esp-idf/components/spi_flash;/home/ubuntu/esp/esp-idf/components/spiffs;/home/ubuntu/esp/esp-idf/components/tcp_transport;/home/ubuntu/esp/esp-idf/components/touch_element;/home/ubuntu/esp/esp-idf/components/ulp;/home/ubuntu/esp/esp-idf/components/unity;/home/ubuntu/esp/esp-idf/components/usb;/home/ubuntu/esp/esp-idf/components/vfs;/home/ubuntu/esp/esp-idf/components/wear_levelling;/home/ubuntu/esp/esp-idf/components/wifi_provisioning;/home/ubuntu/esp/esp-idf/components/wpa_supplicant;/home/ubuntu/esp/esp-idf/components/xtensa;/home/ubuntu/CLionProjects/Display_Test/main")
set(BUILD_COMPONENT_TARGETS "___idf_app_trace;___idf_app_update;___idf_bootloader;___idf_bootloader_support;___idf_bt;___idf_cmock;___idf_console;___idf_cxx;___idf_driver;___idf_efuse;___idf_esp-tls;___idf_esp_adc;___idf_esp_app_format;___idf_esp_bootloader_format;___idf_esp_coex;___idf_esp_common;___idf_esp_eth;___idf_esp_event;___idf_esp_gdbstub;___idf_esp_hid;___idf_esp_http_client;___idf_esp_http_server;___idf_esp_https_ota;___idf_esp_https_server;___idf_esp_hw_support;___idf_esp_lcd;___idf_esp_local_ctrl;___idf_esp_mm;___idf_esp_netif;___idf_esp_netif_stack;___idf_esp_partition;___idf_esp_phy;___idf_esp_pm;___idf_esp_psram;___idf_esp_ringbuf;___idf_esp_rom;___idf_esp_system;___idf_esp_timer;___idf_esp_wifi;___idf_espcoredump;___idf_esptool_py;___idf_fatfs;___idf_freertos;___idf_hal;___idf_heap;___idf_http_parser;___idf_idf_test;___idf_ieee802154;___idf_json;___idf_linux;___idf_log;___idf_lwip;___idf_mbedtls;___idf_mqtt;___idf_newlib;___idf_nvs_flash;___idf_nvs_sec_provider;___idf_openthread;___idf_partition_table;___idf_perfmon;___idf_protobuf-c;___idf_protocomm;___idf_pthread;___idf_riscv;___idf_sdmmc;___idf_soc;___idf_spi_flash;___idf_spiffs;___idf_tcp_transport;___idf_touch_element;___idf_ulp;___idf_unity;___idf_usb;___idf_vfs;___idf_wear_levelling;___idf_wifi_provisioning;___idf_wpa_supplicant;___idf_xtensa;___idf_main")
set(__COMPONENT_REQUIRES_COMMON "cxx;newlib;freertos;esp_hw_support;heap;log;soc;hal;esp_rom;esp_common;esp_system;xtensa")
set(IDF_VER "v5.2.3")
set(__ROOT_KCONFIG "/home/ubuntu/esp/esp-idf/Kconfig")
set(__ROOT_SDKCONFIG_RENAME "/home/ubuntu/esp/esp-idf/sdkconfig.rename")
set(__OUTPUT_SDKCONFIG "1")
set(EXTRA_CMAKE_ARGS "")
set(__COMPONENT_MANAGER_INTERFACE_VERSION "2")
set(BOOTLOADER_BUILD "")
set(IDF_TOOLCHAIN "gcc")
set(IDF_TARGET "esp32")
set(IDF_TARGET_ARCH "xtensa")
set(PROJECT_DIR "/home/ubuntu/CLionProjects/Display_Test")
set(PROJECT_NAME "main")
set(PROJECT_VER "1")
set(BUILD_DIR "/home/ubuntu/CLionProjects/Display_Test/build")
set(SDKCONFIG "/home/ubuntu/CLionProjects/Display_Test/sdkconfig")
set(SDKCONFIG_DEFAULTS "")