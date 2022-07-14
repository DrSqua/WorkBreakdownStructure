//
// Created by Dirk on 13/07/2022.
//

#include "Rendering.h"

FreeDisplayNode::FreeDisplayNode(std::shared_ptr<Node> wbs_node, const std::vector<int>& connections, int n_xPos, int n_yPos) : DisplayNode(std::move(wbs_node), connections, n_xPos, n_yPos) {

}

void FreeDisplayNode::renderToSurface() {
    DisplayNode::renderToSurface();
}

void FreeDisplayNode::applyMovement(const std::vector<std::unique_ptr<DisplayNode>> &displayNodeVector) {
    for (const auto& node_ptr : displayNodeVector) {
        auto node = node_ptr.get();
        // Check if nodeID is in the connectedVertices nodeIDs
        if (std::any_of(connectedVertices.begin(), connectedVertices.end(), [node](int vertex){return vertex == node->getWbsNodeID();})) {
            // Do pulling thingy
        } else {
            // Do pushing thingy
        }
    }
}
