//
// Created by Dirk on 13/07/2022.
//

#include "Rendering.h"

WbsDisplayClass::WbsDisplayClass(int n_screenWidth, int n_screenHeight, WorkBreakdownStructure &workBreakdownStructure) {
    if (workBreakdownStructure.getNodeVectorSize() < 1) return;

    const int nodeYpos{screenHeight/2};
    int nodeXpos{16};
    const int xIncrease = (screenWidth-32)/static_cast<int>(workBreakdownStructure.getNodeVectorSize());

    // Initializing DisplayNodes
    for (const auto& node : workBreakdownStructure.getNodeVectorPtr()) {
        auto connections = workBreakdownStructure.getConnections(node);
        DisplayNode displayNode(node, connections, nodeXpos, nodeYpos);
        displayNodeVector.emplace_back(std::make_unique<DisplayNode>(displayNode));
        nodeXpos += xIncrease;
    }
}

void WbsDisplayClass::updateDisplayNodes() {
    for (const auto& displayNode : displayNodeVector) {
        displayNode->applyMovement(displayNodeVector);
    }
}

void WbsDisplayClass::drawDisplayNodes() {
    // Do drawing
}
