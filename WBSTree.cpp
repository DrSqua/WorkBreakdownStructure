//
// Created by Robbe on 26/06/2022.
//

#include "WorkBreakdownStructure.h"

WBSGraph::WBSGraph(const std::vector<std::shared_ptr<Node>>& raw_nodeVector) {
    setGraph(raw_nodeVector);
}

void WBSGraph::printWBSGraph() {
    int i{};
    for (auto& edge_vector : adjList) {
        if (filledNodes <= i) return;
        std::cout << "Node " << i++ << ": [";
        for (auto nodeID : edge_vector)
            std::cout << nodeID << ", ";
        std::cout << "] " << std::endl;
    }
}

void WBSGraph::addNode(const Node& node) {

}

void WBSGraph::addConnection(int nodeID, const std::vector<int>& connections) {
    if (filledNodes < nodeID) return;

    for (auto required_nodeID : connections) {
        if (filledNodes <= required_nodeID) return;

        adjList.at(required_nodeID).emplace_back(nodeID);
    }
}

void WBSGraph::setGraph(const std::vector<std::shared_ptr<Node>>& raw_nodeVector) {
    filledNodes = raw_nodeVector.size();
    for (auto& node : raw_nodeVector) {
        auto node_id = node->getNodeID();

        for (auto required_nodeID : node->getRequirements()) {
            adjList.at(required_nodeID).emplace_back(node_id); // For each of the required nodes, add the current node ID to their list
        }
    }
}

std::vector<int> &WBSGraph::getRightAdjacent(int nodeID) {
    return adjList.at(nodeID);
}

std::vector<int> WBSGraph::getStartNodes() const {
    std::vector<bool> hasConnectionVector(filledNodes);
    std::vector<int> startNodes{};

    for (auto& connectionsVector : adjList) {
        for (auto connectionID : connectionsVector) {
            if (connectionID > filledNodes) throw std::invalid_argument("WBSGraph::getStartNodes() bug");
            hasConnectionVector.at(connectionID) = true;
        }
    }

    for (int index=0; index < hasConnectionVector.size(); ++index) {
        if (!hasConnectionVector.at(index)) startNodes.emplace_back(index);
    }

    return startNodes;
}
/**
 * Function works in reverse order
 * @return
 */
std::vector<int> WBSGraph::toposort() const {
    std::vector<int> sortedVector{};
    std::vector<bool> visitedNodes(filledNodes);

    while (sortedVector.size() < filledNodes) {
        // While not sorted, loop through adjList (while size of sorted list is not equal to total node count)
        for (auto index=0; index<filledNodes; ++index) {
            auto vertices = adjList.at(index);

            // If node has already been sorted, continue with next loop
            if (visitedNodes.at(index)) continue;

            // If node is empty or all vertices lead to visited nodes, add it to sort
            if (vertices.empty() || std::all_of(vertices.begin(), vertices.end(), [visitedNodes](int connection){return visitedNodes.at(connection);})) {
                sortedVector.push_back(index);
                visitedNodes.at(index) = true;
            }

        }
    }

    // Reverse vector and return
    std::reverse(sortedVector.begin(), sortedVector.end());
    return sortedVector;
}
