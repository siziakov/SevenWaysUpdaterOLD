#include "MapGroup.h"

MapGroup::MapGroup()
{
    //ctor
}

MapGroup::~MapGroup()
{
    //dtor
}

MapGroup::MapGroup(wxString name)
{
    this->Name = name;
}

void MapGroup::AddMaps(std::list<MapDescriptor> maps)
{
    MapDescriptors.clear();
    for (MapDescriptor map : maps)
    {
        MapDescriptors.push_back(map);
    }
}

int MapGroup::count()
{
	return MapDescriptors.size();
}
