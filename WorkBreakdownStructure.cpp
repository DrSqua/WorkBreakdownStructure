//
// Created by Robbe on 20/06/2022.
//

#include "WorkBreakdownStructure.h"

void WorkBreakdownStructure::insertNode(const Node &node) {
    nodeVector.push_back(std::make_shared<Node>(node));
}

int WorkBreakdownStructure::getNodeID(const std::string& nodeName) {
    if (nodeName.empty()) throw std::invalid_argument("getNodeID() nodeName is empty");

    std::cout << nodeName;

    auto iterator = nodeIdMap.find(nodeName);
    if(iterator != nodeIdMap.end()) {
        /**
         *  Returns the uint_u that was binded to the given ID
         */
        return iterator->second;
    }
    /**
     *  Else
     *  Insert a new node into the map and return the ID
     */
    nodeIdMap.insert(std::make_pair(nodeName, nodeCount));

    //! Returns Node and updates it after
    return nodeCount++;
}

void WorkBreakdownStructure::printNodeList() {
    for (const auto& node : nodeVector) {
        std::cout << *node << std::endl;
    }
    std::cout << '\n';
}

std::pair<double, std::vector<int>> WorkBreakdownStructure::solveWbsStructrure() {
    wbStree.setGraph(nodeVector);
    wbStree.printWBSGraph();

    auto [time, path] = calculateLongestPath(*this, wbStree);

    return std::make_pair(time, path);
}

double WorkBreakdownStructure::getNodeDuration(int nodeID) const {
    if (nodeVector.size() <= nodeID) return 0;
    return nodeVector.at(nodeID)->getNodeDuration();
}

std::vector<std::shared_ptr<Node>>& WorkBreakdownStructure::getNodeVectorPtr() {
    return nodeVector;
}

std::vector<std::weak_ptr<Node>> WorkBreakdownStructure::getNodeFromNodeID(const std::vector<int> &nodeIDVector) {
    std::vector<std::weak_ptr<Node>> result_vector{};

    result_vector.reserve(nodeIDVector.size());
    for (auto nodeID : nodeIDVector) {
        if (nodeIDVector.size() <= nodeID) continue; // Checks if ID is within bounds (if the node exists)
        result_vector.push_back(nodeVector.at(nodeID)); // Pushes back a copy of the shared_ptr into result vector
    }

    // Return result
    return result_vector;
}

unsigned long long WorkBreakdownStructure::getNodeVectorSize() const {
    return nodeVector.size();
}

std::string WorkBreakdownStructure::getNodeDescription(int nodeID) const {
    if (nodeID > nodeVector.size()) return {"Could not find Node with nodeID " + std::to_string(nodeID)};
    return nodeVector.at(nodeID)->getNodeDescription();
}

std::string WorkBreakdownStructure::getNodeName(int nodeID) const {

    //! If nodeStr can't be found return empty str
    return {};
}

std::vector<int> WorkBreakdownStructure::getConnections(const std::shared_ptr<Node>& node) {
    std::vector<int> connections = wbStree.getRightAdjacent(node->getNodeID());

    for (const auto& curNode : nodeVector) {

    }

    return connections;
}

void WorkBreakdownStructure::printSolvedWbsStructure(const std::pair<double, std::vector<int>>& wbsSolution) const {
    auto [time, path] = wbsSolution;
    std::cout << std::endl << "Time: " << time << std::endl;
    std::cout << "Path taken:" << std::endl;
    std::cout << "  NodeID:    {";
    for (auto nodeID : path) {
        std::cout << nodeID << ", ";}
    std::cout << "}" << std::endl << "  Node Name: {";
    for (auto nodeID : path) {
        std::cout << getNodeDescription(nodeID) << ", ";}
    std::cout << "}" << std::endl;
}

std::vector<std::string> WorkBreakdownStructure::getNodeName(const std::vector<int> &nodeIDs) const {
    std::vector<std::string> nodeNames;

    nodeNames.reserve(nodeIDs.size());
    for (auto nodeID : nodeIDs) {
        nodeNames.emplace_back(getNodeName(nodeID));
    }

    return nodeNames;
}

std::vector<int> WorkBreakdownStructure::getNodeIDs(const std::vector<std::string>& nodeNames) {
    std::vector<int> nodeIDs{};

    nodeIDs.reserve(nodeNames.size());
    for (const auto& nodeName : nodeNames) {
        nodeIDs.emplace_back(getNodeID(nodeName));
    }

    return nodeIDs;
}
