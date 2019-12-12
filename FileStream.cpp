#include "FileStream.h"

fstream::fstream(int SD_S, char *fname)
{
    if(!SD.begin(SD_S))
    {
        Serial.println("SD card initialize failed!");
        while(1);
    }
    fu = SD.open(fname, O_READ | O_WRITE | O_CREAT | O_SYNC);
    if(!fu)
    {
        Serial.println("Open File Failed!");
        while(1);
    }
    fn = fname;
    readp = 0;
    writep = fu.size();
}
fstream &fstream::operator<<(fstream & (*op)(fstream &))
{
    return (*op)(*this);
}
const fstream &fstream::operator<<(const char *str)
{
    fu.seek(writep);
    fu.print(str);
    writep += strlen(str);
    return *this;
}
const fstream &fstream::operator<<(const String &str)
{
    fu.seek(writep);
    fu.print(str);
    writep += str.length();
    return *this;
}
const fstream &fstream::operator<<(const int &num)
{
    return (*this) << String(num);
}
const fstream &fstream::operator<<(const char &chr)
{
    return (*this) << String(chr);
}
const fstream &fstream::operator<<(const float &num)
{
    return (*this) << String(num);
}
const fstream &fstream::operator<<(const byte &b)
{
    fu.seek(writep);
    fu.print("0x");
    fu.print(b, HEX);
    writep += 4;
    return *this;
}

fstream &endl(fstream &ost)
{
    ost << "\n";
    ++ost.writep;
    return ost;
}


String fstream::reader(int blocks)
{
    fu.seek(readp);
    String buf = "";
    char chr;
    if (fu.available())
    {
        chr = (char)fu.read();
        ++readp;
    }
    else
    {
        return "";
    }
    while (blocker(blocks, chr))
    {
        buf += chr;
        if (fu.available())
        {
            chr = (char)fu.read();
            ++readp;
        }
        else
        {
            break;
        }
    }
    return buf;
}
bool fstream::blocker(int blocks, char chr)
{
    char ablocks[] = {'\n', ',', ' '};
    for(int i = 0; i < blocks; i++)
    {
        if(ablocks[i] == chr)
        {
            return false;
        }
    }
    return true;
}
const fstream &fstream::operator>>(String &str)
{
    str = reader(1);
    return *this;
}
const fstream &fstream::operator>>(int &str)
{
    str = reader(3).toInt();
    return *this;
}
const fstream &fstream::operator>>(float &flt)
{
    flt = reader(3).toFloat();
    return *this;
}
const fstream &fstream::operator>>(byte &b)
{
    fu.seek(readp);
    if(fu.available())
    {
        b = (byte)fu.read();
        readp++;
    }
    else
    {
        b = 0;
    }
    return *this;
}
const fstream &fstream::operator>>(char &chr)
{
    fu.seek(readp);
    if(fu.available())
    {
        chr = (char)fu.read();
        readp++;
    }
    else
    {
        chr = 0;
    }
    return *this;
}
bool fstream::set_RL(int RL)
{
    int CC = 0;
    int CL = 0;
    fu.seek(0);
    for(; fu.available() && CL < RL;)
    {
        CC++;
        if(fu.read() == '\n')
        {
            CL++;
        }
    }
    if(CL == RL)
    {
        readp = CC;
        return true;
    }
    return false;
}
bool fstream::set_WL(int WL)
{
    int CC = 0;
    int CL = 0;
    fu.seek(0);
    for(; fu.available() && CL < WL;)
    {
        CC++;
        if(fu.read() == '\n')
        {
            CL++;
        }
    }
    if(CL == WL)
    {
        writep = CC;
        return true;
    }
    else
    {
        for(int i = 0; i < WL - CL; i++)
            (*this) << "\n";
        writep = fu.size();
        return true;
    }
    return false;
}
bool fstream::set_RP(int RP)
{
    if(RP < fu.size())
    {
        readp = RP;
        return true;
    }
    return false;
}
bool fstream::set_WP(int WP)
{
    if(WP < fu.size())
    {
        writep = WP;
        return true;
    }
    return false;
}