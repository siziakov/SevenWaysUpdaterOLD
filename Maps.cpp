#include "wx/filefn.h"

#include "Maps.h"
#include "MapGroup.h"

Maps::Maps()
{
    //ctor
    init_maps();
}

Maps::~Maps()
{
    //dtor
}

int Maps::count()
{
    int count = 0;
    for (MapGroup group: Groups)
    {
        count += group.count();
    }
    return count;
}

wxString GetFilename(wxString name, int extSymbolsCount)
{
    return wxFileNameFromPath(name.Remove(name.length() - extSymbolsCount)).Lower();
}

bool Maps::Find(wxString filename, MapDescriptor &mapDescriptor)
{
    wxString fileToSearch = GetFilename(filename, 3);
    if (fileToSearch.Cmp(wxString("russia")) == 0) fileToSearch = wxString("russia_adm");
    for (MapGroup group: Groups)
    {
        for (MapDescriptor descriptor: group.MapDescriptors)
        {
            wxString filenameOnServer = descriptor.GetFile();
            filenameOnServer = GetFilename(filenameOnServer, 4);
            if (fileToSearch.Cmp(filenameOnServer) == 0)
            {
                mapDescriptor = descriptor;
                return true;
            }
        }
    }
    return false;
}

bool Maps::Find(int id, MapDescriptor& mapDescriptor)
{
    for (MapGroup group: Groups)
    {
        for (MapDescriptor descriptor: group.MapDescriptors)
        {
            if (descriptor.GetID() == id)
            {
                mapDescriptor = descriptor;
                return true;
            }
        }
    }
    return false;
}

bool Maps::Contain(wxString filename, MapDescriptor descriptor)
{
    wxString fileToSearch = GetFilename(filename, 4);
    if (fileToSearch.Cmp(wxString("russia")) == 0) fileToSearch = wxString("russia_adm");
    wxString filenameOnServer = descriptor.GetFile();
    filenameOnServer = GetFilename(filenameOnServer, 4);
    if (fileToSearch.Cmp(filenameOnServer) == 0)
    {
        return true;
    }
    return false;
}

bool Maps::Find(wxString filename, std::list<MapDescriptor> maps)
{
    for (MapDescriptor descriptor: maps)
    {
        bool result = Contain(filename, descriptor);
        if (result)
            return true;
    }
    return false;
}

void Maps::init_maps()
{
    MapGroup *russia = new MapGroup(_("RUSSIA"));
    MapDescriptor *adm = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/russia_adm.zip"), _("ADM"));
    std::list<MapDescriptor> mapsADM;
    mapsADM.push_back(*adm);
    russia->AddMaps(mapsADM);

    MapGroup *cfo = new MapGroup(_("CFO"));
    MapDescriptor *bel = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-BEL.zip"), _("BEL"));
    MapDescriptor *bry = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-BRY.zip"), _("BRY"));
    MapDescriptor *vla = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-VLA.zip"), _("VLA"));
    MapDescriptor *vor = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-VOR.zip"), _("VOR"));
    MapDescriptor *iva = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-IVA.zip"), _("IVA"));
    MapDescriptor *klu = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KLU.zip"), _("KLU"));
    MapDescriptor *kos = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KOS.zip"), _("KOS"));
    MapDescriptor *krs = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KRS.zip"), _("KRS"));
    MapDescriptor *lip = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-LIP.zip"), _("LIP"));
    MapDescriptor *mow = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-MOW.zip"), _("MOW"));
    MapDescriptor *mos = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-MOS.zip"), _("MOS"));
    MapDescriptor *orl = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ORL.zip"), _("ORL"));
    MapDescriptor *rya = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-RYA.zip"), _("RYA"));
    MapDescriptor *smo = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SMO.zip"), _("SMO"));
    MapDescriptor *tam = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TAM.zip"), _("TAM"));
    MapDescriptor *tve = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TVE.zip"), _("TVE"));
    MapDescriptor *tul = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TUL.zip"), _("TUL"));
    MapDescriptor *yar = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-YAR.zip"), _("YAR"));
    std::list<MapDescriptor> mapsCFO;
    mapsCFO.push_back(*bel);
    mapsCFO.push_back(*bry);
    mapsCFO.push_back(*vla);
    mapsCFO.push_back(*vor);
    mapsCFO.push_back(*iva);
    mapsCFO.push_back(*klu);
    mapsCFO.push_back(*kos);
    mapsCFO.push_back(*krs);
    mapsCFO.push_back(*lip);
    mapsCFO.push_back(*mow);
    mapsCFO.push_back(*mos);
    mapsCFO.push_back(*orl);
    mapsCFO.push_back(*rya);
    mapsCFO.push_back(*smo);
    mapsCFO.push_back(*tam);
    mapsCFO.push_back(*tve);
    mapsCFO.push_back(*tul);
    mapsCFO.push_back(*yar);
    cfo->AddMaps(mapsCFO);

    MapGroup *szfo = new MapGroup(_("SZFO"));
    MapDescriptor *kr = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KR.zip"), _("KR"));
    MapDescriptor *ko = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KO.zip"), _("KO"));
    MapDescriptor *ark = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ARK.zip"), _("ARK"));
    MapDescriptor *vlg = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-VLG.zip"), _("VLG"));
    MapDescriptor *kgd = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KGD.zip"), _("KGD"));
    MapDescriptor *len = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-LEN.zip"), _("LEN"));
    MapDescriptor *mur = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-MUR.zip"), _("MUR"));
    MapDescriptor *ngr = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-NGR.zip"), _("NGR"));
    MapDescriptor *psk = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-PSK.zip"), _("PSK"));
    MapDescriptor *spe = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SPE.zip"), _("SPE"));
    MapDescriptor *nen = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-NEN.zip"), _("NEN"));
    std::list<MapDescriptor> mapsSZFO;
    mapsSZFO.push_back(*kr);
    mapsSZFO.push_back(*ko);
    mapsSZFO.push_back(*ark);
    mapsSZFO.push_back(*vlg);
    mapsSZFO.push_back(*kgd);
    mapsSZFO.push_back(*len);
    mapsSZFO.push_back(*mur);
    mapsSZFO.push_back(*ngr);
    mapsSZFO.push_back(*psk);
    mapsSZFO.push_back(*spe);
    mapsSZFO.push_back(*nen);
    szfo->AddMaps(mapsSZFO);

    MapGroup *ufo = new MapGroup(_("UFO"));
    MapDescriptor *ad = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-AD.zip"), _("AD"));
    MapDescriptor *kl = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KL.zip"), _("KL"));
    MapDescriptor *krm = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KRM.zip"), _("KRM"));
    MapDescriptor *kda = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KDA.zip"), _("KDA"));
    MapDescriptor *ast = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-AST.zip"), _("AST"));
    MapDescriptor *vgg = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-VGG.zip"), _("VGG"));
    MapDescriptor *ros = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ROS.zip"), _("ROS"));
    MapDescriptor *sev = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SEV.zip"), _("SEV"));
    std::list<MapDescriptor> mapsUFO;
    mapsUFO.push_back(*ad);
    mapsUFO.push_back(*kl);
    mapsUFO.push_back(*krm);
    mapsUFO.push_back(*kda);
    mapsUFO.push_back(*ast);
    mapsUFO.push_back(*vgg);
    mapsUFO.push_back(*ros);
    mapsUFO.push_back(*sev);
    ufo->AddMaps(mapsUFO);

    MapGroup *skfo = new MapGroup(_("SKFO"));
    MapDescriptor *da = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-DA.zip"), _("DA"));
    MapDescriptor *in = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-IN.zip"), _("IN"));
    MapDescriptor *kb = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KB.zip"), _("KB"));
    MapDescriptor *kc = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KC.zip"), _("KC"));
    MapDescriptor *se = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SE.zip"), _("SE"));
    MapDescriptor *ce = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-CE.zip"), _("CE"));
    MapDescriptor *sta = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-STA.zip"), _("STA"));
    std::list<MapDescriptor> mapsSKFO;
    mapsSKFO.push_back(*da);
    mapsSKFO.push_back(*in);
    mapsSKFO.push_back(*kb);
    mapsSKFO.push_back(*kc);
    mapsSKFO.push_back(*se);
    mapsSKFO.push_back(*ce);
    mapsSKFO.push_back(*sta);
    skfo->AddMaps(mapsSKFO);

    MapGroup *pfo = new MapGroup(_("PFO"));
    MapDescriptor *ba = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-BA.zip"), _("BA"));
    MapDescriptor *me = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ME.zip"), _("ME"));
    MapDescriptor *mo = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-MO.zip"), _("MO"));
    MapDescriptor *ta = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TA.zip"), _("TA"));
    MapDescriptor *ud = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-UD.zip"), _("UD"));
    MapDescriptor *cu = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-CU.zip"), _("CU"));
    MapDescriptor *per = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-PER.zip"), _("PER"));
    MapDescriptor *kir = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KIR.zip"), _("KIR"));
    MapDescriptor *niz = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-NIZ.zip"), _("NIZ"));
    MapDescriptor *ore = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ORE.zip"), _("ORE"));
    MapDescriptor *pnz = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-PNZ.zip"), _("PNZ"));
    MapDescriptor *sam = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SAM.zip"), _("SAM"));
    MapDescriptor *sar = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SAR.zip"), _("SAR"));
    MapDescriptor *uly = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ULY.zip"), _("ULY"));
    std::list<MapDescriptor> mapsPFO;
    mapsPFO.push_back(*ba);
    mapsPFO.push_back(*me);
    mapsPFO.push_back(*mo);
    mapsPFO.push_back(*ta);
    mapsPFO.push_back(*ud);
    mapsPFO.push_back(*cu);
    mapsPFO.push_back(*per);
    mapsPFO.push_back(*kir);
    mapsPFO.push_back(*niz);
    mapsPFO.push_back(*ore);
    mapsPFO.push_back(*pnz);
    mapsPFO.push_back(*sam);
    mapsPFO.push_back(*sar);
    mapsPFO.push_back(*uly);
    pfo->AddMaps(mapsPFO);

    MapGroup *urfo = new MapGroup(_("URFO"));
    MapDescriptor *kgn = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KGN.zip"), _("KGN"));
    MapDescriptor *sve = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SVE.zip"), _("SVE"));
    MapDescriptor *tyu = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TYU.zip"), _("TYU"));
    MapDescriptor *che = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-CHE.zip"), _("CHE"));
    MapDescriptor *khm = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KHM.zip"), _("KHM"));
    MapDescriptor *yan = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-YAN.zip"), _("YAN"));
    std::list<MapDescriptor> mapsURFO;
    mapsURFO.push_back(*kgn);
    mapsURFO.push_back(*sve);
    mapsURFO.push_back(*tyu);
    mapsURFO.push_back(*che);
    mapsURFO.push_back(*khm);
    mapsURFO.push_back(*yan);
    urfo->AddMaps(mapsURFO);

    MapGroup *sfo = new MapGroup(_("SFO"));
    MapDescriptor *al = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-AL.zip"), _("AL"));
    MapDescriptor *ty = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TY.zip"), _("TY"));
    MapDescriptor *kk = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KK.zip"), _("KK"));
    MapDescriptor *alt = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ALT.zip"), _("ALT"));
    MapDescriptor *kya = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KYA.zip"), _("KYA"));
    MapDescriptor *irk = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-IRK.zip"), _("IRK"));
    MapDescriptor *kem = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KEM.zip"), _("KEM"));
    MapDescriptor *nvs = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-NVS.zip"), _("NVS"));
    MapDescriptor *oms = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-OMS.zip"), _("OMS"));
    MapDescriptor *tom = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-TOM.zip"), _("TOM"));
    std::list<MapDescriptor> mapsSFO;
    mapsSFO.push_back(*al);
    mapsSFO.push_back(*ty);
    mapsSFO.push_back(*kk);
    mapsSFO.push_back(*alt);
    mapsSFO.push_back(*kya);
    mapsSFO.push_back(*irk);
    mapsSFO.push_back(*kem);
    mapsSFO.push_back(*nvs);
    mapsSFO.push_back(*oms);
    mapsSFO.push_back(*tom);
    sfo->AddMaps(mapsSFO);

    MapGroup *dfo = new MapGroup(_("DFO"));
    MapDescriptor *bu = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-BU.zip"), _("BU"));
    MapDescriptor *sa = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SA.zip"), _("SA"));
    MapDescriptor *zab = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-ZAB.zip"), _("ZAB"));
    MapDescriptor *kam = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KAM.zip"), _("KAM"));
    MapDescriptor *pri = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-PRI.zip"), _("PRI"));
    MapDescriptor *kha = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-KHA.zip"), _("KHA"));
    MapDescriptor *amu = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-AMU.zip"), _("AMU"));
    MapDescriptor *mag = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-MAG.zip"), _("MAG"));
    MapDescriptor *sak = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-SAK.zip"), _("SAK"));
    MapDescriptor *yev = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-YEV.zip"), _("YEV"));
    MapDescriptor *chu = new MapDescriptor(wxT("megamaps.org"), wxT("/store/navikey/russia/RU-CHU.zip"), _("CHU"));
    std::list<MapDescriptor> mapsDFO;
    mapsDFO.push_back(*bu);
    mapsDFO.push_back(*sa);
    mapsDFO.push_back(*zab);
    mapsDFO.push_back(*kam);
    mapsDFO.push_back(*pri);
    mapsDFO.push_back(*kha);
    mapsDFO.push_back(*amu);
    mapsDFO.push_back(*mag);
    mapsDFO.push_back(*sak);
    mapsDFO.push_back(*yev);
    mapsDFO.push_back(*chu);
    dfo->AddMaps(mapsDFO);

    Groups.push_back(*russia);
    Groups.push_back(*cfo);
    Groups.push_back(*szfo);
    Groups.push_back(*ufo);
    Groups.push_back(*skfo);
    Groups.push_back(*pfo);
    Groups.push_back(*urfo);
    Groups.push_back(*sfo);
    Groups.push_back(*dfo);
}
