Library Installation
====================

The library can be installed in several ways, here are a few options:

* Arduino IDE library manager
* Arduino IDE import .zip-library
* Arduino IDE manual installation

These installation methods are conveniently described in the official `Arduino website <https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/>`_.

Library Manager
---------------

In order to install the library via the Arduino library manager open the Arduino IDE and open the library manager from the menu *Tools > Manage Libraries*. Enter the library name ``XENSIV 3D MAGNETIC SENSOR TLX493D`` and press the *INSTALL* button as soon as the tool found the library.

.ZIP Library Installation
-------------------------

If you prefer to install the library manually via a .zip-file go to the `release section <https://github.com/Infineon/arduino-xensiv-3d-magnetic-sensor-tlx493d/releases>`_ of the repository and get the .zip- or tar.gz-file from the desired release.
As soon as you downloaded the file you can go back to the Arduino IDE and choose *Sketch > Include Library > Add .ZIP library* from the menu.

.. warning:: 
    As a general recommendation, direct downloads from the master branch should be avoided. Even if it should not, it could contain incomplete or faulty code. So please stick to the releases.

Manual Installation
-------------------

If you prefer to install the library completely manual we would recommend the two following ways. The first way would be to use the .zip-file which you get from the steps mentioned in the ".ZIP Library Installation" part and unzip the downloaded folder. The unzipped folder has then to be copied to Arduino's library folder, which is usually ``C:\Users\USERNAME\Documents\Arduino\libraries`` in Windows. After you have copied the folder you should see the examples and library resources in the Arduino IDE.

The second and the preferable way if you want to develop something for the library is to clone the Github repository directly into the library folder of the Arduino IDE. This allows you to easily check changes you make to the library and to upstream them later on if you have finished the development.