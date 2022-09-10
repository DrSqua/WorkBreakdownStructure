//
// Created by Robbe on 20/06/2022.
//

#include "WorkBreakdownStructure.h"

Node::Node(const int nodeID, std::string description, double time, std::vector<int>  requirements) : nodeID(nodeID), nodeDescription(std::move(description)), duration(time), requirements(std::move(requirements)) {

}

Node::Node(int nodeID, std::string description, double time) : nodeID(nodeID), nodeDescription(std::move(description)), duration(time) {

}

Node::Node(const std::string& nodeID_str, std::string description, double time, const std::vector<std::string>& requirements_str, WorkBreakdownStructure& workBreakdownStructure) : nodeDescription(std::move(description)), duration(time) {
    nodeID = workBreakdownStructure.getNodeID(nodeID_str);

    for (auto& str_ID : requirements_str) {
        requirements.push_back(workBreakdownStructure.getNodeID(str_ID));
    }
}

Node::Node(const std::vector<std::string> &inputVector, WorkBreakdownStructure& workBreakdownStructure) {
    if (inputVector.size() < 3) throw std::invalid_argument("Node constructor requires inputVector of at least size == 3");

    nodeID = workBreakdownStructure.getNodeID(inputVector.at(0));
    nodeDescription = inputVector.at(1);
    duration = std::stod(inputVector.at(2));

    // Loop if size > 4 or not empty
    if (inputVector.size() < 4 || inputVector.at(3).empty()) return;

    requirements.reserve(inputVector.size()-3);
    for (auto& nodeIDStr : std::vector<std::string>(inputVector.begin()+3, inputVector.end())){
        requirements.emplace_back(workBreakdownStructure.getNodeID(nodeIDStr));
    }
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "Node " << node.getNodeID() << ": " << node.duration << ", " << node.getNodeDescription() << ", {";
    for (auto requirement : node.getRequirements()) {
        os << requirement << ", ";
    }
    os << "} ";

    return os;
}