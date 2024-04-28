#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
namespace PolygonalLibrary

{
bool ImportMesh(const string& fpath, PolygonalMesh& mesh)
{
    if (!ImportCell0Ds(fpath + "/Cell0Ds.csv", mesh) ||
        !ImportCell1Ds(fpath + "/Cell1Ds.csv", mesh) ||
        !ImportCell2Ds(fpath + "/Cell2Ds.csv", mesh))  //verifico corretta importazione dati dai file

    {
        cerr << "Errore nell'importazione dati della mesh" << endl;
        return false;
    }
    return true;
}


bool ImportCell0Ds(const string &fname, PolygonalMesh& mesh)
{
    ifstream file(fname);
    if (!file) //controllo sull'apertura del file
    {
        cerr << "Errore nell'apertura del file " << fname << endl;
        return false;
    }
    string line;
    getline(file, line); //per saltare intestazione!!
    while (getline(file, line))
    {
        istringstream iss(line);
        unsigned int id;
        unsigned int marker;
        double x, y;
        char delim;

        if (!(iss >> id >> delim >> marker >> delim >> x >> delim >> y)) //mi assicuro lettura corretta dei numeri in ogni riga
        {
            cerr << "Errore in " << fname << " sulla linea: " << line << endl;
            continue;
        }

        mesh.Cell0DId.push_back(id); //ID del vertice
        mesh.Cell0DCoordinates.push_back(Vector2d(x, y)); // coordinate
        mesh.Cell0DMarkers[marker].push_back(id); //puntatore associato all'ID
    }
    file.close();
    return true;
}

bool ImportCell1Ds(const string &fname, PolygonalMesh& mesh)
{
    ifstream file(fname);
    if (!file)
    {
        cerr << "Errore nell'apertura del file " << fname << endl;
        return false;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        istringstream iss(line);
        unsigned int id, marker, origin, end;
        char delim;

        if (!(iss >> id >> delim >> marker >> delim >> origin >> delim >> end))
        {
            cerr << "Errore in " << fname << " sulla linea: " << line << endl;
            continue;
        }

        mesh.Cell1DId.push_back(id); //ID del lato
        mesh.Cell1DVertices.push_back(Vector2i(origin, end)); //vertici origine e fine
        mesh.Cell1DMarkers[marker].push_back(id);
    }
    file.close();
    return true;
}

bool ImportCell2Ds(const string &fname, PolygonalMesh& mesh)
{
    ifstream file(fname);
    if (!file)
    {
        cerr << "Errore nell'apertura del file " << fname << endl;
        return false;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        istringstream iss(line);
        unsigned int id, marker, numVertices, numEdges;
        char delim;
        vector<unsigned int> vertices, edges;

        iss >> id >> delim >> marker >> delim >> numVertices;
        for (unsigned int i = 0; i < numVertices; ++i)
        {
            unsigned int vertex;
            iss >> delim >> vertex;
            vertices.push_back(vertex);
        }

        iss >> delim >> numEdges;
        for (unsigned int i = 0; i < numEdges; ++i)
        {
            unsigned int edge;
            iss >> delim >> edge;
            edges.push_back(edge);
        }

        mesh.Cell2DId.push_back(id);
        mesh.Cell2DVertices.push_back(vertices); //vertici poligono
        mesh.Cell2DEdges.push_back(edges);
    }
    file.close();
    return true;
}


//se aree non nulle:
void Area(const PolygonalMesh& mesh)
{
    for (const auto& vertices : mesh.Cell2DVertices)
    {
        double area = 0;
        int n = vertices.size();

        if (n >= 3) //area nulla per forza se non ha almeno 3 vertici
        {
            for (int i = 0; i < n; ++i) //uso formula di Gauss
            {
                Vector2d current = mesh.Cell0DCoordinates[vertices[i]];
                Vector2d prox = mesh.Cell0DCoordinates[vertices[(i + 1) % n]];
                area += current[0] * prox[1] - prox[0] * current[1];
            }
            area = 0.5 * abs(area);

            if (area == 0)
            {
                cerr << "Il poligono di vertici: ";
                for (int i = 0; i < n; ++i) { cerr << vertices[i] << " "; }
                cerr << "ha area nulla" << endl;
            }
        }
    }
}

//se lati di lunghezza non nulla:
void LunghezzaSegmenti(const PolygonalMesh& mesh)
{
    for (const auto& vertices : mesh.Cell1DVertices)
    {
        Vector2d start = mesh.Cell0DCoordinates[vertices(0)]; //inizio lato
        Vector2d end = mesh.Cell0DCoordinates[vertices(1)]; //fine lato
        double length = (end - start).norm();  //lunghezza

        if (length == 0)
        {
            cerr << "Segmento di vertici " << vertices(0) << " e " << vertices(1) << " ha lunghezza nulla" << endl;
        }
    }
}

}
