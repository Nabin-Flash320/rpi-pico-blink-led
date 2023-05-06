# BLINK LED EXAMPLE FOR RASPBERRY-PI PICO

## CMAKE EXPLAINED
1. Build function for pico sdk is included first.
```cmake
   include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
```
2. Then path to FreeRTOSConfig.h and freertos source directory is provided.
```cmake
   set(FREERTOS_CFG_DIRECTORY "<path to FreeRTOSConfig.h>")
   set(FREERTOS_SRC_DIRECTORY "<path to freertos source directory>")
```
3. Initialize pico sdk. This will create a pico-sdk subdirectory in our project for the libraries.
```cmake
   pico_sdk_init()
```
4. Add freeRTOS as a library.
```cmake
   add_library(FreeRTOS STATIC
      ${FREERTOS_SRC_DIRECTORY}/event_groups.c
      ${FREERTOS_SRC_DIRECTORY}/list.c
      ${FREERTOS_SRC_DIRECTORY}/queue.c
      ${FREERTOS_SRC_DIRECTORY}/stream_buffer.c
      ${FREERTOS_SRC_DIRECTORY}/tasks.c
      ${FREERTOS_SRC_DIRECTORY}/timers.c
      ${FREERTOS_SRC_DIRECTORY}/portable/MemMang/heap_3.c
      ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0/port.c
   )
```
5. Build freeRTOS
```cmake
   target_include_directories(FreeRTOS PUBLIC
      ${FREERTOS_CFG_DIRECTORY}/
      ${FREERTOS_SRC_DIRECTORY}/include
      ${FREERTOS_SRC_DIRECTORY}/portable/GCC/ARM_CM0
   )
```
6. Since .uf2 file is used rather than binary file, all (map/bin/hex/uf2) files should be generated.
```cmake
   pico_add_extra_outputs(${PROJECT_NAME})
```
7. Link pico_stdlib and freeRTOS to the project.
```cmake
   target_link_libraries(${PROJECT_NAME}
            pico_stdlib
            FreeRTOS
   )
```
8. To monitor through serial port disable UART communication and enable USB communication for the given project as below.
```cmake
   pico_enable_stdio_usb(${PROJECT_NAME} 1)
   pico_enable_stdio_uart(${PROJECT_NAME} 0)
```
## CODE EXPLAINED
1. Include standard library for RPI-pico and stdio.(including freertos is not mandatory for this project so can be skipped.)
```c
   #include "pico/stdlib.h"
   #include "FreeRTOS.h"
   #include "stdio.h"
```
2. Initialize stdio functionalities for RPI-pico
```c
   stdio_init_all();
```
3. Select the pin for LED output. In this example default onboard led is used.
```c
   const uint LED_PIN = PICO_DEFAULT_LED_PIN;
```
4. Initialize the GPIO for I/O operation and set the GPIO direction as output.
```c
   gpio_init(LED_PIN);
   gpio_set_dir(LED_PIN, GPIO_OUT);
```
5. Within an infinite while loop, the gpio are toogled between on and off.
```c
   while (true) {
      gpio_put(LED_PIN, 1);
      sleep_ms(250);
      printf("ON\n");
      gpio_put(LED_PIN, 0);
      sleep_ms(250);
      printf("OFF\n");
   }
```
## COMPILING AND FLASHING 
1. Create a build direcotry in the project folder and cd into it.
```bash
   mkdir build && cd build
```
2. Execute cmake and run make command
```bash
   cmake ..
   make
```
3. After that connect the RPI-pico to the computer. 
   - If it is very first flashing direction connection to the computer will work.
   - If another firmware is already running, push **BOOTSEL** button and then plug the USB to the computer.
5. The RPI-pico is conneced to the computer as a drive named **RPI-RP2**. Copy the .uf2 file within in the build directory and paste it in **RPI-RP2**. Then the RPI-pico will automatically reboot and LED starts blinking.
6. For monitoring through serial interface, any program or software that has serial monitro functionality will work. For linux following command will work as well:
```bash
   cat /dev/<port name it RPI-pico is connected>
```

## THANK YOU