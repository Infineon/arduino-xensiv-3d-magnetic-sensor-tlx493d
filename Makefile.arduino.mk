FQBN  ?=
PORT  ?=
TESTS ?=
UNITY_PATH ?=

# These vars are used for example-tests:
SENSOR_TYPE ?= 
BOARD_TYPE ?=

$(info FQBN  : $(FQBN))
$(info PORT  : $(PORT))
$(info TESTS : $(TESTS))
$(info UNITY_PATH : $(UNITY_PATH))
$(info SENSOR_TYPE  : $(SENSOR_TYPE))
$(info BOARD_TYPE  : $(BOARD_TYPE))


TESTS_NEEDS_SENSOR=-DTEST_TLx493D_A1B6_NEEDS_SENSOR \
				   -DTEST_TLx493D_A2B6_NEEDS_SENSOR \
				   -DTEST_TLx493D_A2BW_NEEDS_SENSOR \
				   -DTEST_TLx493D_P2B6_NEEDS_SENSOR \
				   -DTEST_TLx493D_W2B6_NEEDS_SENSOR \
				   -DTEST_TLx493D_W2BW_NEEDS_SENSOR \
				   -DTEST_TLx493D_P3B6_NEEDS_SENSOR \
				   -DTEST_TLx493D_P3I8_NEEDS_SENSOR


TESTS_NO_SENSOR=-DTEST_TLx493D_A1B6 \
				-DTEST_TLx493D_A2B6 \
				-DTEST_TLx493D_A2BW \
				-DTEST_TLx493D_P2B6 \
				-DTEST_TLx493D_W2B6 \
			 	-DTEST_TLx493D_W2BW \
				-DTEST_TLx493D_P3B6 \
				-DTEST_TLx493D_P3I8

				

A1B6_needsSensor: TESTS=-DTEST_TLx493D_A1B6 -DTEST_TLx493D_A1B6_NEEDS_SENSOR
A1B6: TESTS=-DTEST_TLx493D_A1B6

A2B6_needsSensor: TESTS=-DTEST_TLx493D_A2B6 -DTEST_TLx493D_A2B6_NEEDS_SENSOR
A2B6: TESTS=-DTEST_TLx493D_A2B6

A2BW_needsSensor: TESTS=-DTEST_TLx493D_A2BW -DTEST_TLx493D_A2BW_NEEDS_SENSOR
A2BW: TESTS=-DTEST_TLx493D_A2BW

P2B6_needsSensor: TESTS=-DTEST_TLx493D_P2B6 -DTEST_TLx493D_P2B6_NEEDS_SENSOR
P2B6: TESTS=-DTEST_TLx493D_P2B6

W2B6_needsSensor: TESTS=-DTEST_TLx493D_W2B6 -DTEST_TLx493D_W2B6_NEEDS_SENSOR
W2B6: TESTS=-DTEST_TLx493D_W2B6

W2BW_needsSensor: TESTS=-DTEST_TLx493D_W2BW -DTEST_TLx493D_W2BW_NEEDS_SENSOR
W2BW: TESTS=-DTEST_TLx493D_W2BW

P3B6_needsSensor: TESTS=-DTEST_TLx493D_P3B6 -DTEST_TLx493D_P3B6_NEEDS_SENSOR
P3B6: TESTS=-DTEST_TLx493D_P3B6

P3I8_needsSensor: TESTS=-DTEST_TLx493D_P3I8 -DTEST_TLx493D_P3I8_NEEDS_SENSOR
P3I8: TESTS=-DTEST_TLx493D_P3I8

A1B6_needsSensor A1B6 \
A2B6_needsSensor A2B6 \
A2BW_needsSensor A2BW \
P2B6_needsSensor P2B6 \
W2B6_needsSensor W2B6 \
W2BW_needsSensor W2BW \
P3B6_needsSensor P3B6 \
P3I8_needsSensor P3I8: unity flash


test_all: TESTS=$(TESTS_NEEDS_SENSOR) $(TESTS_NO_SENSOR)
test_needsSensor: TESTS=$(TESTS_NEEDS_SENSOR) $(TEST_COMMON_NEEDS_SENSOR)
test: TESTS=$(TESTS_NO_SENSOR)

test_all \
test_needsSensor \
test: unity flash


EXAMPLES = iic_c_style iic iic_with_wakeup 3iic 3iic_equal iic_ext_addr spi

# $(EXAMPLES): arduino compile


### Arduino targets
clean:
	-rm -rf build/


arduino: clean
	-mkdir build
	find src -name '*.[hc]*' -print -exec cp {} build \;


iic_ext_addr: arduino
	cp examples/read_iic_a1b6_extended_addresses/read_iic_a1b6_extended_addresses.ino build/build.ino


iic_c_style: arduino
	cp examples/read_iic_sensor_c_style/read_iic_sensor_c_style.ino build/build.ino
 

spi: arduino
	cp examples/read_spi_sensor/read_spi_sensor.ino build/build.ino
 

iic: arduino
	cp examples/read_iic_sensor/read_iic_sensor.ino build/build.ino

iic_with_wakeup: arduino
	cp examples/read_iic_sensor_with_wakeup/read_iic_sensor_with_wakeup.ino build/build.ino


3iic: arduino
	cp examples/read_3_different_iic_sensors/read_3_different_iic_sensors.ino build/build.ino


3iic_equal: arduino
	cp examples/read_3_equal_iic_sensors/read_3_equal_iic_sensors.ino build/build.ino


unity: arduino
	find $(UNITY_PATH) -name '*.[hc]' \( -path '*extras*' -a -path '*src*' -or -path '*src*' -a \! -path '*example*' \) -exec \cp {} build \;
	find test/unit/src -name '*.[hc]*' -a \! -path '*mtb*' -exec \cp {} build \;
	cp test/unit/src/framework/arduino/Test_main.ino build/build.ino


.ONESHELL:
compile:
ifneq ($(SENSOR_TYPE),)
	$(eval SENSOR_TYPE=-DSENSOR_TYPE=$(SENSOR_TYPE))
endif
ifneq ($(BOARD_TYPE),)
	$(eval BOARD_TYPE=-DBOARD_TYPE=$(BOARD_TYPE))
endif

	echo "$(SENSOR_TYPEV) $(BOARD_TYPEV)"

ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to compile Arduino sketches !")
else
	arduino-cli compile --clean --log --warnings all --fqbn $(FQBN) \
	                        --build-property compiler.c.extra_flags="\"-DUNITY_INCLUDE_CONFIG_H=1\"" \
							--build-property compiler.cpp.extra_flags="$(TESTS) $(SENSOR_TYPE) $(BOARD_TYPE)" \
			        build

# 	                        --build-property compiler.c.extra_flags="\"-DUNITY_INCLUDE_CONFIG_H=1\"" \
					
endif


upload:	
ifeq ($(PORT),)
	$(error "Must set variable PORT (Windows port naming convention, ie COM16) in order to be able to flash Arduino sketches !")
endif
ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to flash Arduino sketches !")
else
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) build
endif


flash: compile upload


monitor:
ifeq ($(PORT),)
	$(error "Must set variable PORT (Windows port naming convention, ie COM16) in order to be able to flash Arduino sketches !")
endif
	arduino-cli monitor -c baudrate=115200 -p $(PORT) --fqbn $(FQBN)



# For WSL and Windows :
# download arduino-cli from : https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip
prepare:
	arduino-cli core update-index
	arduino-cli core install Infineon:xmc
	arduino-cli core update-index
	arduino-cli core search Infineon
	arduino-cli core list
	arduino-cli board listall
	arduino-cli board listall Infineon
