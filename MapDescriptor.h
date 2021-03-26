#ifndef MAPDESCRIPTOR_H
#define MAPDESCRIPTOR_H

#include "wx/treelist.h"
#include <list>

#include <stdio.h>
#include "wx/string.h"

class MapDescriptor
{
    public:
        MapDescriptor();
        MapDescriptor(wxString server, wxString file, wxString name);
        virtual ~MapDescriptor();
        void SetFileLength(size_t length);

        wxString Name;
        size_t Length;

        wxString GetServer();
        wxString GetFile();
        int GetID();

        static bool Contain(int id, std::list<MapDescriptor> maps);
    protected:

    private:
        wxString server;
        wxString file;
        int id;
};

class IDGenerator
{
private:
    static int s_nextID;

public:
     static int getNextID();
};

#endif // MAPDESCRIPTOR_H
