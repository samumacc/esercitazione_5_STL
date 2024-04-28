#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;
    string fpath = "PolygonalMesh";

    if (!ImportMesh(fpath, mesh)) //mi assicuro di importare la mesh correttamente
    {
        cerr << "Errore nell'importare la mesh" << endl;
        return 1;
    }

    LunghezzaSegmenti(mesh);
    Area(mesh);

    cout << "Mesh importata correttamente" << endl;
    cout << "Il numero di vertici è: " << mesh.Cell0DId.size() << endl;
    cout << "Il numero di lati è: " << mesh.Cell1DId.size() << endl;
    cout << "Il numero di poligoni è: " << mesh.Cell2DId.size() << endl;

    return 0;
}

