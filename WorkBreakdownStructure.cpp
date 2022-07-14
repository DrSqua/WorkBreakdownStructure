//
// Created by Robbe on 20/06/2022.
//

#include "WorkBreakdownStructure.h"

WorkBreakdownStructure::WorkBreakdownStructure(const std::string& filepath) {
    std::string raw_line; // Lijn die wordt gelezen (dus de rij van een csv)

    // Create connection
    std::ifstream data(filepath);
    if (!data.is_open())
    {
        std::exit(EXIT_FAILURE);  // RAISE IF FILE OPENING DOESN'T WORK
    }

    // Processing
    std::getline(data, raw_line); // skip the first line
    while (std::getline(data, raw_line))  // Loop through next lines
    {

    }
}

void WorkBreakdownStructure::insertNode(const Node &node) {
    nodeVector.push_back(std::make_shared<Node>(node));
}

int WorkBreakdownStructure::getNodeID(const std::string &ID_string) {
    auto iterator = nodeIdMap.find(ID_string);
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
    nodeIdMap.insert(std::make_pair(ID_string, nodeCount));

    //! Returns Node and updates it after
    return nodeCount++;
}

void WorkBreakdownStructure::printNodeList() {
    for (const auto& node : nodeVector) {
        std::cout << *node << std::endl;
    }
}

void WorkBreakdownStructure::doTheThing() {
    wbStree.setTree(nodeVector);
    wbStree.printWBSTree();

    auto [time, path] = calculateLongestPath(*this, wbStree);
    std::cout << std::endl << "Time: " << time << std::endl;
    std::cout << "Path taken:" << std::endl;
    std::cout << "  NodeID:    {";
    for (auto nodeID : path) {
        std::cout << nodeID << ", ";}
    std::cout << "}" << std::endl << "  Node Name: {";
    for (auto nodeID : path) {
        std::cout << getNodeName(nodeID) << ", ";}
    std::cout << "}" << std::endl;
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

std::string WorkBreakdownStructure::getNodeName(int nodeID) const {
    if (nodeID > nodeVector.size()) return {"Could not find Node with nodeID " + std::to_string(nodeID)};
    return nodeVector.at(nodeID)->getNodeName();
}

std::string *WorkBreakdownStructure::getNodeIDstr(int nodeID) const {

    return nullptr;
}

std::vector<int> WorkBreakdownStructure::getConnections(const std::shared_ptr<Node>& node) {
    std::vector<int> connections;

    for (const auto& curNode : nodeVector) {

    }

    return connections;
}
