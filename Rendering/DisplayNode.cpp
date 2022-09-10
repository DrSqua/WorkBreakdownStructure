//
// Created by Dirk on 13/07/2022.
//

#include "Rendering.h"

DisplayNode::DisplayNode(std::shared_ptr<Node> wbs_node, std::vector<int> &connections, int n_xPos, int n_yPos) : wbsNode(std::move(wbs_node)), connectedVertices(connections), xPos(n_xPos), yPos(n_yPos) {

}

int DisplayNode::getWbsNodeID() {
    return wbsNode->getNodeID();
}
