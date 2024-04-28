#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary //libreria mesh polygonal
{

struct PolygonalMesh
{
    vector<unsigned int> Cell0DId; //vertici
    vector<Vector2d> Cell0DCoordinates;
    map<unsigned int, list<unsigned int>> Cell0DMarkers;

    vector<unsigned int> Cell1DId; //lati
    vector<Vector2i> Cell1DVertices;
    map<unsigned int, list<unsigned int>> Cell1DMarkers;

    vector<unsigned int> Cell2DId; //poligoni
    vector<vector<unsigned int>> Cell2DVertices;
    vector<vector<unsigned int>> Cell2DEdges;
};

}
