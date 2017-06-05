# Arduino-mechanism

<b>/magnetic_reed</b><br>
used the magnetic reed sensor <br>
when the sensor detect magnetic item, turn off the lock<br>
use switch_PIN to control switch

<b>/RFID</b><br>
used the library form miguelbalboa/rfid on GitHub<br>
include "rfid/src/MFRC522.h" and "rfid/src/MFRC522.cpp"<br>
used whitelisting to open the door when the uid of card is in list<br>
lock the door when the uid is not in list, so you can use the wrong card to reset  <br>
when Debug_mode is True, you can get uid from serial message<br>
you also have to change the ID_List value before using<br>

