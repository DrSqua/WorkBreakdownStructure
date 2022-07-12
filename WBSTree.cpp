//
// Created by Robbe on 26/06/2022.
//

#include "WorkBreakdownStructure.h"

WBSTree::WBSTree(const std::vector<std::shared_ptr<Node>>& raw_nodeVector) {
    setTree(raw_nodeVector);
}

void WBSTree::printWBSTree() {
    int i{};
    for (auto& edge_vector : adjList) {
        if (filledNodes <= i) return;
        std::cout << "Node " << i++ << ": [";
        for (auto nodeID : edge_vector)
            std::cout << nodeID << ", ";
        std::cout << "] " << std::endl;
    }
}

void WBSTree::addNode(const Node& node) {

}

void WBSTree::addConnection(int nodeID, const std::vector<int>& connections) {
    if (filledNodes < nodeID) return;

    for (auto required_nodeID : connections) {
        if (filledNodes <= required_nodeID) return;

        adjList.at(required_nodeID).emplace_back(nodeID);
    }
}

void WBSTree::setTree(const std::vector<std::shared_ptr<Node>>& raw_nodeVector) {
    filledNodes = raw_nodeVector.size();
    for (auto& node : raw_nodeVector) {
        auto node_id = node->getNodeID();

        for (auto required_nodeID : node->getRequirements()) {
            adjList.at(required_nodeID).emplace_back(node_id); // For each of the required nodes, add the current node ID to their list
        }
    }
}

std::vector<int> &WBSTree::getAdjacent(int nodeID) {
    return adjList.at(nodeID);
}

std::vector<int> WBSTree::getStartNodes() const {
    std::vector<bool> hasConnectionVector(filledNodes);
    std::vector<int> startNodes{};

    for (auto& connectionsVector : adjList) {
        for (auto connectionID : connectionsVector) {
            hasConnectionVector.at(connectionID) = true;
        }
    }

    for (int index=0; index < hasConnectionVector.size(); ++index) {
        if (!hasConnectionVector.at(index)) startNodes.emplace_back(index);
    }

    return startNodes;
}
