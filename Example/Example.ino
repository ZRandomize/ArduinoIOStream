#include <SerialStream.h>
#include <FileStream.h>

//HardwareSerial only(Serial,Serial1,Serial2...)
stream cio(&Serial);

//FileStream (SD_Select_Pin,File_Name)
//DO NOT use SD.begin() when using a FileStream
fstream fio(4,"NEW.TXT");

void setup() {
  Serial.begin(9600);
  
  /*
   * These type are supported:
   * String
   * int
   * float
   * char
   * char* (output only)
   * byte (output 0xXX)
   * 
   * FileStream FUNCTION:
   * bool set_WP(int)
   *  set the write pointer to a position,
   *  return true if succeeded.
   * bool set_RP(int)
   *  set the read pointer to a position,
   *  return true if succeeded.
   * bool set_WL(int)
   *  set the write pointer to the start of the giving line,
   *  this would CREATE new empty line if 
   *  giving line does NOT exists,
   *  return true if succeeded.
   * bool set_RL(int)
   *  set the read pointer to the start of the giving line,
   *  return false if the line not found.
   */
  String test[5];
  float a,b;
  cio>>b;
  cio<<fio.set_WL(100)<<endl;
  fio<<b<<endl;
  fio.set_RL(100);
  fio>>a;

  fio.set_RL(0);
  fio>>test[0]>>test[1]>>test[2]>>test[3]>>test[4];
  cio<<"done."<<endl<<a<<endl<<test[0]<<endl<<test[1]<<endl<<test[2]<<endl<<test[3]<<endl<<test[4]<<endl;
  
}
void loop() {

}
