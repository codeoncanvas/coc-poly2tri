//
//  cocPoly2Tri.h
//  Created by Lukasz Karluk on 07/04/2016.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"
#include "poly2tri.h"

namespace coc {

//-----------------------------------------------------------------------
class Poly2Tri {
  
public:

    Poly2Tri();
    ~Poly2Tri();
    
    void clearBounds();
    void clearPoints();
    void clearHoles();
    void clearTriangles();

    void setBoundsRect(coc::Rect rect);;
    void setBoundsRect(glm::vec2 pos, glm::vec2 size);
    void setBoundsRect(float x, float y, float w, float h);
    void setBoundsPoly(const std::vector<glm::vec2> & boundsPoly);
    
    void setPoints(const std::vector<glm::vec2> & meshPoints);
    void addPoint(const glm::vec2 & meshPoint);
    
    void addHole(const std::vector<glm::vec2> & holePoly);
    
    void update();
    
    const std::vector<p2t::Triangle *> & getTriangles() const;
    
protected:

    std::vector<p2t::Point *> bounds;
    std::vector<p2t::Point *> points;
    std::vector<std::vector<p2t::Point *>> holes;
    std::vector<p2t::Triangle *> triangles;
};

};