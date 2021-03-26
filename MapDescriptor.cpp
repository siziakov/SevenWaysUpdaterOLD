#include "MapDescriptor.h"

int IDGenerator::s_nextID = 1;
int IDGenerator::getNextID() { return s_nextID++; }

MapDescriptor::MapDescriptor(wxString server, wxString file, wxString name)
{
    this->server = server;
    this->file= file;
    this->Name = name;
    Length = 0;
    id = IDGenerator::getNextID();
}

void MapDescriptor::SetFileLength(size_t length)
{
    this->Length = length;
}

MapDescriptor::MapDescriptor()
{
    //ctor
}

MapDescriptor::~MapDescriptor()
{
    //dtor
}

wxString MapDescriptor::GetServer()
{
	return server;
}

wxString MapDescriptor::GetFile()
{
	return file;
}

int MapDescriptor::GetID()
{
    return id;
}

bool MapDescriptor::Contain(int id, std::list<MapDescriptor> maps)
{
    for (MapDescriptor currentMap: maps)
        if (currentMap.GetID() == id) return true;
    return false;
}
