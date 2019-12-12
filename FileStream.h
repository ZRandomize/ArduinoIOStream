#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class fstream
{
    friend fstream &endl(fstream &ost);
private:
    String reader(int blocks);
    bool blocker(int blocks, char chr);
public:
    File fu;
    char *fn;
    int readp, writep;
    fstream(int SD_S, char *fname);
    fstream &operator<<(fstream & (*op)(fstream &));
    const fstream &operator<<(const char *str);
    const fstream &operator<<(const String &str);
    const fstream &operator<<(const int &num);
    const fstream &operator<<(const char &chr);
    const fstream &operator<<(const float &num);
    const fstream &operator<<(const byte &b);

    const fstream &operator>>(String &str);
    const fstream &operator>>(int &str);
    const fstream &operator>>(char &chr);
    const fstream &operator>>(float &flt);
    const fstream &operator>>(byte &b) ;
    bool set_RP(int RP);
    bool set_WP(int WP);
    bool set_RL(int RL);
    bool set_WL(int WL);
};

fstream &endl(fstream &ost);