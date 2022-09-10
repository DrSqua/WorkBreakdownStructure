//
// Created by Robbe on 28/06/2022.
//

#include "WorkBreakdownStructure.h"

// TODO Eens kijken of ik het kan schrijven zonder de toposort vooraf
/**
 *
 * @param workBreakdownStructure
 * @param wbsTree
 * @param startNodeID
 * @return
 */
std::pair<double, std::vector<int>> calculateLongestPath(WorkBreakdownStructure& workBreakdownStructure, WBSGraph& wbsTree) {
    if (workBreakdownStructure.getNodeVectorSize() < 1) return {};

    // Establishing return values
    std::vector<int> path;
    double total_distance;

    // Establishing function variables
    const auto nodeCount = workBreakdownStructure.getNodeVectorSize();
    const auto startNodeIDVector = wbsTree.getStartNodes();
    const auto toposortedVector = wbsTree.toposort();

    std::vector<double> distanceVector(nodeCount, -1.0); // For each node (with access on index) stores the distance to starting node
    std::vector<int> previousNodeVector(nodeCount, -1.0); // For each node (with access on index) stores the previous Node to create longest path
    std::vector<bool> visitedVector(nodeCount); // For each node (with access on index) stores if it has been visited

    for (auto startNodeID : startNodeIDVector) {
        distanceVector.at(startNodeID) = workBreakdownStructure.getNodeDuration(startNodeID);
    }

    // Solving the WBS
    for (const auto currentNodeID : toposortedVector)
    {
        // Get next node, remove it from queue and set it to visited
        visitedVector.at(currentNodeID) = true;

        // Visit each connection
        double distance;
        for (auto connectedNodeID : wbsTree.getRightAdjacent(currentNodeID))
        {
            // Distance = distance_to_currentNode + length_of_connectedNode
            distance = distanceVector.at(currentNodeID) + workBreakdownStructure.getNodeDuration(connectedNodeID);

            if (distance > distanceVector.at(connectedNodeID))
            {
                distanceVector.at(connectedNodeID) = distance;
                previousNodeVector.at(connectedNodeID) = currentNodeID;
            }
        }
    }

    auto nodeID = std::max_element(distanceVector.begin(), distanceVector.end()) - distanceVector.begin();
    total_distance = distanceVector.at(nodeID);
    // Getting the path
    while (nodeID != -1)
    {
        path.push_back(static_cast<int>(nodeID));
        nodeID = previousNodeVector.at(nodeID);
    }
    std::reverse(path.begin(), path.end());

    return std::make_pair(total_distance, path);
}

bool isDAG(WorkBreakdownStructure &workBreakdownStructure, WBSGraph &wbsTree) {
    return false;
}
