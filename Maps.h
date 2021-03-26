#ifndef MAPS_H
#define MAPS_H

#include <list>

#include "MapGroup.h"

class Maps
{
    public:
        Maps();
        virtual ~Maps();

        std::list<MapGroup> Groups;

        int count();
        bool Find(wxString filename, MapDescriptor &mapDescriptor);
        bool Find(wxString filename, std::list<MapDescriptor> maps);
        bool Contain(wxString filename, MapDescriptor descriptor);

        bool Find(int id, MapDescriptor &mapDescriptor);
    protected:

    private:

        void init_maps();
};

#endif // MAPS_H
