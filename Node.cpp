//
// Created by Robbe on 20/06/2022.
//

#include "WorkBreakdownStructure.h"

Node::Node(const int nodeID, std::string name, double time, std::vector<int>  requirements) : nodeID(nodeID), nodeName(std::move(name)), duration(time), requirements(std::move(requirements)) {

}

Node::Node(const std::string& nodeID_str, std::string name, double time, const std::vector<std::string>& requirements_str, WorkBreakdownStructure& workBreakdownStructure) : nodeName(std::move(name)), duration(time) {
    nodeID = workBreakdownStructure.getNodeID(nodeID_str);

    for (auto& str_ID : requirements_str) {
        requirements.push_back(workBreakdownStructure.getNodeID(str_ID));
    }
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "Node " << node.getNodeID() << ": " << node.getNodeName() << ", {";
    for (auto requirement : node.getRequirements()) {
        os << requirement << ", ";
    }
    os << "} ";

    return os;
}
