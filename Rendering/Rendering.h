//
// Created by Dirk on 13/07/2022.
//

#ifndef WORKBREAKDOWNSTRUCTURE_RENDERING_H
#define WORKBREAKDOWNSTRUCTURE_RENDERING_H

#include "memory"

#include "../WorkBreakdownStructure.h"

constexpr static int LINK_FORCE = 1;
constexpr static int REPEL_FORCE = 1;

class DisplayNode {
public:
    DisplayNode(std::shared_ptr<Node> wbs_node, std::vector<int>& connections, int n_xPos, int n_yPos);

    virtual int getWbsNodeID(); // TODO Inline maken?
    virtual void renderToSurface() {}
    virtual void applyMovement(const std::vector<std::unique_ptr<DisplayNode>>& displayNodeVector) {}

protected:
    std::shared_ptr<Node> wbsNode;
    std::vector<int>& connectedVertices;
    int xPos{};
    int yPos{};
};

class FreeDisplayNode : private DisplayNode {
public:
    FreeDisplayNode(std::shared_ptr<Node> wbs_node, std::vector<int>& connections, int n_xPos, int n_yPos);
    void renderToSurface() override;
    void applyMovement(const std::vector<std::unique_ptr<DisplayNode>>& displayNodeVector) override;

private:

};

class StaticDisplayNode : private DisplayNode {};

class WbsDisplayClass {
public:
    WbsDisplayClass(int n_screenWidth, int n_screenHeight, WorkBreakdownStructure& workBreakdownStructure);
    void updateDisplayNodes();
    void drawDisplayNodes();

private:
    // Objects
    std::vector<std::unique_ptr<DisplayNode>> displayNodeVector;

    // Surfaces
    int screenWidth{};
    int screenHeight{};
};

#endif //WORKBREAKDOWNSTRUCTURE_RENDERING_H
