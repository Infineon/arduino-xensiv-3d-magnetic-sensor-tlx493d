.. _api-ref:

API Reference
=============

TLx493D 3D Magnetic Sensor API
------------------------------

The following section shows you the API of the TLx493D base class.

.. doxygenclass:: ifx::tlx493d::TLx493DBase
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
   :members:
   :protected-members:
   :undoc-members:

TLx493D 3D Magnetic Sensor Arduino API
--------------------------------------

The following sections shows you the specific implementation of the Tlx493d classes for Arduino. The classes are inheriting most of their functionality from the Tlx493Base class, but also define the necessary interfaces (SPI, I2C) depending on the sensor.

.. doxygenfile:: TLx493D.hpp
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
   
Logger API
----------

The following section shows you all the available logger functions, which can be utilized for debugging or printing out important information of the sensors, for example the internal register map.

.. doxygenfunction:: logPrintRegisters
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logPrintDouble
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logPrint
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logPrintln
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library
.. doxygenfunction:: logFlush
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library

Communication Interface
-----------------------

The following section shows you the important high-level functions of the communication interface. The :code:`tlx493d_transfer()` function is implemented for every sensor depending on its available interface (I2C, SPI).

.. doxygenfile:: CommunicationInterface.h
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library

Kit2GoBoardSupport
------------------

The following section shows you how you can utilize the board support class for your applications. The Kit2GoBoardSupport class eases the usage of Kit2Go boards by giving the opportunity define for example power pins, which can be used to power up and power down the sensor. Or by defining chip select pins in case of a SPI interface.

.. doxygenfile:: Kit2GoBoardSupport.hpp
   :project: XENSIV™ 3D Magnetic Sensor TLx493D Arduino Library