FQBN  ?=
PORT  ?=
TESTS ?=

$(info FQBN : $(FQBN))
$(info PORT : $(PORT))


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
	-rm -rf build/* cppcheck_reports build.ino.*elf.* ./-lm.res log.[0-9]*
	find . -name '*ctu-info' -exec \rm {} \;


arduino: clean
	cp -r config/arduinoLibraryTemplate/* build
	find src -name '*.[hc]*' -a \! -path '*mtb*' -a \! -name 'main*' -print -exec cp {} build \;
	rm -f build/n_* build/*.save


iic_ext_addr: arduino
	cp examples/framework/arduino/read_iic_a1b6_extended_addresses.ino build/build.ino


iic_c_style: arduino
	cp examples/framework/arduino/read_iic_sensor_c_style.ino build/build.ino
 

spi: arduino
	cp examples/framework/arduino/read_spi_sensor.ino build/build.ino
 

iic: arduino
	cp examples/framework/arduino/read_iic_sensor.ino build/build.ino

iic_with_wakeup: arduino
	cp examples/framework/arduino/read_iic_sensor_with_wakeup.ino build/build.ino


3iic: arduino
	cp examples/framework/arduino/read_3_different_iic_sensors.ino build/build.ino


3iic_equal: arduino
	cp examples/framework/arduino/read_3_equal_iic_sensors.ino build/build.ino


unity: arduino
	find ../../unity/Unity-master -name '*.[hc]' \( -path '*extras*' -a -path '*src*' -or -path '*src*' -a \! -path '*example*' \) -exec \cp {} build \;
	find test/unit/src -name '*.[hc]*' -a \! -path '*mtb*' -exec \cp {} build \;
	cp test/unit/src/framework/arduino/Test_main.ino build/build.ino



compile:
ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to compile Arduino sketches !")
else
	arduino-cli.exe compile --clean --log --warnings all --fqbn $(FQBN) \
	                        --build-property compiler.c.extra_flags="\"-DUNITY_INCLUDE_CONFIG_H=1\"" \
							--build-property compiler.cpp.extra_flags="$(TESTS)" \
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
	arduino-cli.exe upload -p $(PORT) --fqbn $(FQBN) build
endif


flash: compile upload


monitor:
ifeq ($(PORT),)
	$(error "Must set variable PORT (Windows port naming convention, ie COM16) in order to be able to flash Arduino sketches !")
endif
ifeq ($(FQBN),)
	$(error "Must set variable FQBN in order to be able to flash Arduino sketches !")
else
	arduino-cli.exe monitor -c baudrate=115200 -p $(PORT) --fqbn $(FQBN)
endif



# For WSL and Windows :
# download arduino-cli.exe from : https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip
prepare:
	arduino-cli.exe core update-index
	arduino-cli.exe core install Infineon:xmc
	arduino-cli.exe core update-index
	arduino-cli.exe core search Infineon
	arduino-cli.exe core list
	arduino-cli.exe board listall
	arduino-cli.exe board listall Infineon
