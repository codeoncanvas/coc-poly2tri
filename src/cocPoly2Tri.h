//
//  cocPoly2Tri.h
//  Created by Lukasz Karluk on 07/04/2016.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"

namespace coc {

//-----------------------------------------------------------------------
class p2tTriangle {
public:
    p2tTriangle() {
        points.push_back(&p0);
        points.push_back(&p1);
        points.push_back(&p2);
    }
    
    glm::vec2 p0;
    glm::vec2 p1;
    glm::vec2 p2;
    std::vector<glm::vec2 *> points;
};

//-----------------------------------------------------------------------
class Poly2Tri {
  
public:

    Poly2Tri();
    ~Poly2Tri();
    
    void setBounds(const std::vector<glm::vec2> & boundsPoly);
    
    void setPoints(const std::vector<glm::vec2> & meshPoints);
    void addPoint(const glm::vec2 & meshPoint);
    void clearPoints();
    
    void addHole(const std::vector<glm::vec2> & holePoly);
    void clearHoles();
    
    void update();
    const std::vector<p2tTriangle> & getTriangles() const;
    
protected:

    std::vector<glm::vec2> bounds;
    std::vector<glm::vec2> points;
    std::vector<std::vector<glm::vec2>> holes;
    std::vector<p2tTriangle> triangles;
};

};