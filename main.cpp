#include <iostream>
#include "DebugLog.h"
DebugLog Debug;
#include "GameBoy.h"
#include "TableGenerator.h"
#include <fstream>

uint8_t* GetFileBuffer(const std::string& file, size_t& FileSize)
{
    std::ifstream f(file.c_str(), std::ios::binary | std::ios::ate);
    if(!f.is_open())
    {
        FileSize = 0;
        return nullptr;
    }
    FileSize = f.tellg();
    f.seekg(0, std::ios::beg);

    uint8_t* buffer= new uint8_t[FileSize];
    f.read((char*)buffer, FileSize);
    return buffer;
}

std::ostream* CreateFileStream(const std::string& file)
{
    std::ofstream* returnv=new std::ofstream(file.c_str());
    if(!returnv)
        return nullptr;
    if(!returnv->is_open())
    {
        delete returnv;
        return nullptr;
    }
    return returnv;
}

int main()
{
    std::ofstream out;
    out.open("Table.csv", std::ostream::out | std::ostream::trunc);
    CSVDump(out);
    out.close();

    Debug.AddStream(&std::cout);
    Debug.AddManagedStream(CreateFileStream("Log.txt"));

    std::cout <<"Dump over.\nEnter file name.\n";
    size_t FileSize;
    std::string filename;
    getline(std::cin, filename);
    uint8_t* Buffer=GetFileBuffer(filename.c_str(), FileSize);
    if(!Buffer)
    {
        Debug.Log("Failed to open the file specified.", DebugLog::FatalError, "main.cpp");
        return 0;
    }
    GameBoy GB;
    sf::RenderWindow Window(sf::VideoMode(160/*32*8*/,144/*32*8*/), "Test");
    GB.GPU.FrameSkip = 0;
    if(!GB.Init(Buffer, FileSize, Window))
    {
        Debug.Log("Failed to initialize the gameboy emulator", DebugLog::FatalError, "main.cpp");
        return 0;
    }
    GB.Cartridge->Head.Dump(std::cout);
    GB.Run();
    return 0;
}