//
// Created by Robbe on 28/06/2022.
//

#include "WorkBreakdownStructure.h"

int getLargestUnvisited(WorkBreakdownStructure& workBreakdownStructure, const std::vector<bool>& visitedVector)
{
    auto nodeVector = workBreakdownStructure.getNodeVectorPtr();

    auto largestUnvisitedNode = *std::max_element(nodeVector.begin(), nodeVector.end(), [visitedVector](const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs)
        {
        //! If one of nodes is visited, it is "lower" than the other
        if (visitedVector.at(lhs->getNodeID()) && visitedVector.at(!rhs->getNodeID())) {
            return true;
        }
        else if (!visitedVector.at(lhs->getNodeID()) && visitedVector.at(rhs->getNodeID())) {
            return false;
        }
        //! If both values are either visited or unvisited, compare durations
        return (lhs->getNodeDuration() < rhs->getNodeDuration());
        });

    return largestUnvisitedNode->getNodeID();
}

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

    std::vector<double> distanceVector(nodeCount, -1.0); // For each node (with access on index) stores the distance to starting node
    std::vector<int> previousNodeVector(nodeCount, -1.0); // For each node (with access on index) stores the previous Node to create longest path
    std::vector<bool> visitedVector(nodeCount); // For each node (with access on index) stores if it has been visited

    std::deque<int> nodeQueue;
    nodeQueue.push_back(*std::max_element(startNodeIDVector.begin(), startNodeIDVector.end()));
    for (auto startNodeID : startNodeIDVector) {
        distanceVector.at(startNodeID) = workBreakdownStructure.getNodeDuration(startNodeID);
    }

    // Loop
    while (!nodeQueue.empty())
    {
        // Get next node, remove it from queue and set it to visited
        auto currentNodeID = nodeQueue.front();
        nodeQueue.pop_front();
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
        // Check if all nodes are visited
        if (std::find(visitedVector.begin(), visitedVector.end(), false) != visitedVector.end()) {

            // Get next node to visit
            nodeQueue.push_back(getLargestUnvisited(workBreakdownStructure, visitedVector));
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