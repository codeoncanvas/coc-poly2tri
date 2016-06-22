/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#include "cocPoly2Tri.h"

using namespace std;

namespace coc {

//-----------------------------------------------------------------------
Poly2Tri::Poly2Tri() {
    cdt = NULL;
}

Poly2Tri::~Poly2Tri() {
    clearBounds();
    clearPoints();
    clearHoles();
    clearTriangles();
    clearCDT();
}

//-----------------------------------------------------------------------
void Poly2Tri::clearBounds() {
    for(int i=0; i<bounds.size(); i++) {
        delete bounds[i];
    }
    bounds.clear();
}

void Poly2Tri::clearPoints() {
    for(int i=0; i<points.size(); i++) {
        delete points[i];
    }
    points.clear();
}

void Poly2Tri::clearHoles() {
    for(int i=0; i<holes.size(); i++) {
        vector<p2t::Point *> & hole = holes[i];
        for(int j=0; j<hole.size(); j++) {
            delete hole[j];
        }
    }
    holes.clear();
}

void Poly2Tri::clearTriangles() {

    // when CDT is deleted,
    // it also deletes all the triangles its created which are stored internally.
    // so here we just need to clear the triangle vector only.

    triangles.clear();
}

void Poly2Tri::clearCDT() {
    if(cdt != NULL) {
        delete cdt;
        cdt = NULL;
    }
}

//-----------------------------------------------------------------------
void Poly2Tri::setBoundsRect(coc::Rect rect) {
    setBoundsRect(rect.getX(), rect.getY(), rect.getW(), rect.getH());
}

void Poly2Tri::setBoundsRect(glm::vec2 pos, glm::vec2 size) {
    setBoundsRect(pos.x, pos.y, size.x, size.y);
}

void Poly2Tri::setBoundsRect(float x, float y, float w, float h) {
    vector<glm::vec2> poly;
    poly.push_back(glm::vec2(x, y));
    poly.push_back(glm::vec2(x + w, y));
    poly.push_back(glm::vec2(x + w, y + h));
    poly.push_back(glm::vec2(x, y + h));
    setBoundsPoly(poly);
}

void Poly2Tri::setBoundsPoly(const std::vector<glm::vec2> & boundsPoly) {
    clearBounds();

    for(int i=0; i<boundsPoly.size(); i++) {
        bounds.push_back(new p2t::Point(boundsPoly[i].x, boundsPoly[i].y));
    }
}

//-----------------------------------------------------------------------
void Poly2Tri::setPoints(const std::vector<glm::vec2> & meshPoints) {
    clearPoints();

    for(int i=0; i<meshPoints.size(); i++) {
        addPoint(meshPoints[i]);
    }
}

void Poly2Tri::addPoint(const glm::vec2 & meshPoint) {
    points.push_back(new p2t::Point(meshPoint.x, meshPoint.y));
}

//-----------------------------------------------------------------------
void Poly2Tri::addHole(const std::vector<glm::vec2> & holePoly) {
    vector<p2t::Point *> hole;

    for(int i=0; i<holePoly.size(); i++) {
        hole.push_back(new p2t::Point(holePoly[i].x, holePoly[i].y));
    }

    holes.push_back(hole);
}

//-----------------------------------------------------------------------
void Poly2Tri::update() {

    clearTriangles();
    clearCDT();

    if(bounds.size() < 3) {
        return; // need at least 3 points to create a bounds.
    }

    if(points.size() == 0) {
        return; // no points to triangulate with.
    }

    cdt = new p2t::CDT(bounds);

    for(int i=0; i<points.size(); i++) {
        cdt->AddPoint(points[i]);
    }

    for(int i=0; i<holes.size(); i++) {
        cdt->AddHole(holes[i]);
    }

    cdt->Triangulate();

    triangles = cdt->GetTriangles();
}

//-----------------------------------------------------------------------
std::vector<p2t::Triangle *> Poly2Tri::getTriangles() const {
    return triangles;
}

};
