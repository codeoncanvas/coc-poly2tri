//
//  cocPoly2Tri.cpp
//  Created by Lukasz Karluk on 07/04/2016.
//  http://codeoncanvas.cc
//

#include "cocPoly2Tri.h"
#include "poly2tri.h"

using namespace std;

namespace coc {

//-----------------------------------------------------------------------
Poly2Tri::Poly2Tri() {
    //
}

Poly2Tri::~Poly2Tri() {
    //
}

//-----------------------------------------------------------------------
void Poly2Tri::setBounds(const std::vector<glm::vec2> & boundsPoly) {
    bounds = boundsPoly;
}

void Poly2Tri::setPoints(const std::vector<glm::vec2> & meshPoints) {
    points = meshPoints;
}

void Poly2Tri::addPoint(const glm::vec2 & meshPoint) {
    points.push_back(meshPoint);
}

void Poly2Tri::clearPoints() {
    points.clear();
}

void Poly2Tri::addHole(const std::vector<glm::vec2> & holePoly) {
    holes.push_back(holePoly);
}

void Poly2Tri::clearHoles() {
    holes.clear();
}

//-----------------------------------------------------------------------
void Poly2Tri::update() {
    
    triangles.clear();
    
    if(bounds.size() < 3) {
        return; // need at least 3 points to create a bounds.
    }
    
    if(points.size() == 0) {
        return; // no points to triangulate with.
    }

    vector<p2t::Point *> p2tBounds;
    for(int i=0; i<bounds.size(); i++) {
        p2tBounds.push_back(new p2t::Point(bounds[i].x, bounds[i].y));
    }
    
    p2t::CDT cdt(p2tBounds);
    
    for(int i=0; i<points.size(); i++) {
        cdt.AddPoint(new p2t::Point(points[i].x, points[i].y));
    }
    
    for(int i=0; i<holes.size(); i++) {
        vector<p2t::Point *> p2tHole;
        
        for(int j=0; j<holes[i].size(); j++) {
            p2tHole.push_back(new p2t::Point(holes[i][j].x, holes[i][j].y));
        }
        
        cdt.AddHole(p2tHole);
    }
    
    cdt.Triangulate();
    
    std::vector<p2t::Triangle *> p2tTriangles = cdt.GetTriangles();
    for(int i=0; i<p2tTriangles.size(); i++){
        p2t::Triangle * triangleNew = p2tTriangles[i];
        
        triangles.push_back(p2tTriangle());
        p2tTriangle & triangle = triangles.back();
        
        for(int j=0; j<triangle.points.size(); j++) {
            triangle.points[j]->x = triangleNew->GetPoint(0)->x;
            triangle.points[j]->y = triangleNew->GetPoint(0)->y;
        }
    }
    
    for(int i=0; i<p2tBounds.size(); i++) {
        delete p2tBounds[i];
    }
    p2tBounds.clear();
}

//-----------------------------------------------------------------------
const std::vector<p2tTriangle> & Poly2Tri::getTriangles() const {
    return triangles;
}

};