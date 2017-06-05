# Arduino-mechanism

/magnetic_reed 
used the magnetic reed sensor 
when the sensor detect magnetic item, turn off the lock
use switch_PIN to control switch

/RFID
used the library form miguelbalboa/rfid on GitHub
include "rfid/src/MFRC522.h" and "rfid/src/MFRC522.cpp"
used whitelisting to open the door when the uid of card is in list
lock the door when the uid is not in list, so you can use the wrong card to reset  
when Debug_mode is True, you can get uid from serial message
you also have to change the ID_List value before using

