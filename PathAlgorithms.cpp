//
// Created by Robbe on 28/06/2022.
//

#include "WorkBreakdownStructure.h"

/**
 *
 * @param workBreakdownStructure
 * @param wbsTree
 * @param startNodeID
 * @return
 */
std::pair<double, std::vector<int>> calculateLongestPath(WorkBreakdownStructure& workBreakdownStructure, WBSTree& wbsTree) {
    // Establishing return values
    std::vector<int> path;

    // Establishing variables
    const auto nodeCount = workBreakdownStructure.getNodeVectorSize();
    const auto startNodeIDVector = wbsTree.getStartNodes();
    const auto toposortedVector = wbsTree.toposort();

    std::vector<double> distanceVector(nodeCount, -1.0); // For each node (with access on index) stores the distance to starting node
    std::vector<int> previousNodeVector(nodeCount, -1.0); // For each node (with access on index) stores the previous Node to create longest path
    std::vector<bool> visitedVector(nodeCount); // For each node (with access on index) stores if it has been visited

    for (auto startNodeID : startNodeIDVector) {
        distanceVector.at(startNodeID) = workBreakdownStructure.getNodeDuration(startNodeID);
    }

    // Loop
    for (const auto currentNodeID : toposortedVector)
    {
        // Get next node, remove it from queue and set it to visited
        visitedVector.at(currentNodeID) = true;

        // Visit each connection
        double distance;
        for (auto connectedNodeID : wbsTree.getAdjacent(currentNodeID))
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
    auto distance = distanceVector.at(nodeID);
    // Getting the path
    while (nodeID != -1)
    {
        path.push_back(static_cast<int>(nodeID));
        nodeID = previousNodeVector.at(nodeID);
    }
    std::reverse(path.begin(), path.end());

    return std::make_pair(distance, path);
}