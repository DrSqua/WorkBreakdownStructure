//
// Created by Robbe on 20/06/2022.
//

#ifndef WORKBREAKDOWNSTRUCTURE_WORKBREAKDOWNSTRUCTURE_H
#define WORKBREAKDOWNSTRUCTURE_WORKBREAKDOWNSTRUCTURE_H

#include "fstream"
#include "memory"
#include "iostream"
#include "algorithm"
#include "filesystem"
#include "numeric"

#include <type_traits>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <unordered_map>

namespace fs = std::filesystem;

static constexpr int MAX_NODES = 100;

class WorkBreakdownStructure;

/*!
 *
 *
 *
 *
 *
 */
class Node {
public:
    Node() = default;
    Node(int nodeID, std::string description, double time, std::vector<int> requirements);
    Node(int nodeID, std::string description, double time);
    Node(const std::vector<std::string>& inputVector, WorkBreakdownStructure& workBreakdownStructure);
    Node(const std::string& nodeID_str, std::string description, double time, const std::vector<std::string>& requirements_str, WorkBreakdownStructure& workBreakdownStructure);

    [[nodiscard]] int getNodeID() const {return nodeID;}
    [[nodiscard]] std::string getNodeDescription() const {return nodeDescription;}
    [[nodiscard]] double getNodeDuration() const {return duration;}
    [[nodiscard]] std::vector<int> getRequirements() const {return requirements;}

    friend std::ostream& operator<<(std::ostream& os, const Node& node);

private:
    int nodeID{};
    std::string nodeDescription{};
    double duration{};
    std::vector<int> requirements{};
};

/*!
 *
 *
 *
 *
 *
 */
class WBSGraph {
public:
    WBSGraph() = default;
    explicit WBSGraph(const std::vector<std::shared_ptr<Node>>& raw_nodeVector);

    //! Setters and Getters
    void setGraph(const std::vector<std::shared_ptr<Node>>& raw_nodeVector);
    void addConnection(int nodeID, const std::vector<int>& connections);
    void addNode(const Node& node);

    [[nodiscard]] std::vector<int> toposort() const;
    [[nodiscard]] std::vector<int> getStartNodes() const;
    std::vector<int>& getRightAdjacent(int nodeID);

    //! Print
    void printWBSGraph();

private:
    std::array<std::vector<int>, MAX_NODES> adjList;
    unsigned long long filledNodes{};
};

/*!
 *
 *
 *
 *
 *
 */
class WorkBreakdownStructure {
public:
    WorkBreakdownStructure() = default;

    //! Basic get and set
    std::vector<std::shared_ptr<Node>> &getNodeVectorPtr();

    unsigned long long getNodeVectorSize() const;

    void insertNode(const Node &node);

    //! Node passthrough
    [[nodiscard]] double getNodeDuration(int nodeID) const;
    [[nodiscard]] std::string getNodeName(int nodeID) const;
    [[nodiscard]] std::vector<std::string> getNodeName(const std::vector<int>& nodeIDs) const;
    [[nodiscard]] std::string getNodeDescription(int nodeID) const;

    //! Translation
    [[nodiscard]] int getNodeID(const std::string &nodeName);
    [[nodiscard]] std::vector<int> getNodeIDs(const std::vector<std::string>& nodeNames);

    std::vector<std::weak_ptr<Node>> getNodeFromNodeID(const std::vector<int> &nodeIDVector);

    //! Solving Problems
    std::pair<double, std::vector<int>> solveWbsStructrure();

    std::vector<int> getConnections(const std::shared_ptr<Node> &node);


    //! Print
    void printNodeList();

    void printSolvedWbsStructure(const std::pair<double, std::vector<int>> &wbsSolution) const;

private:
    std::vector<std::shared_ptr<Node>> nodeVector{};
    std::unordered_map<std::string, int> nodeIdMap;
    int nodeCount{};

    WBSGraph wbStree;
};

/*!
 *
 * @return
 */
std::pair<double, std::vector<int>> calculateLongestPath(WorkBreakdownStructure& workBreakdownStructure, WBSGraph& wbsTree);
bool isDAG(WorkBreakdownStructure& workBreakdownStructure, WBSGraph& wbsTree);

#endif //WORKBREAKDOWNSTRUCTURE_WORKBREAKDOWNSTRUCTURE_H
