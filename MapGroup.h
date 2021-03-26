#ifndef MAPGROUP_H
#define MAPGROUP_H

#include <list>
//#include "wx/list.h"
#include "MapDescriptor.h"
//#include "wx/listimpl.cpp"

//WX_DECLARE_LIST(MapDescriptor, MapsList);
//WX_DEFINE_LIST(MapsList);

class MapGroup
{
    public:
        MapGroup();
        MapGroup(wxString name);
        virtual ~MapGroup();
        void AddMaps(std::list<MapDescriptor> maps);

        wxString Name;
        std::list<MapDescriptor> MapDescriptors;

        int count();
    protected:

    private:
};

#endif // MAPGROUP_H
