set(requires esp-tls nvs_flash esp_netif esp_http_server esp_driver_ledc)
idf_build_get_property(target IDF_TARGET)

if(${target} STREQUAL "linux")
    list(APPEND requires esp_stubs protocol_examples_common)
else()
    list(APPEND requires esp_wifi esp_eth)
endif()

idf_component_register(SRCS "main.c" "led/led_ctrl.c"
                    INCLUDE_DIRS "." "led"
                    PRIV_REQUIRES ${requires})
