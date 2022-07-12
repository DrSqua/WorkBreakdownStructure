//
// Created by Robbe on 20/06/2022.
//

#ifndef WORKBREAKDOWNSTRUCTURE_WORKBREAKDOWNSTRUCTURE_H
#define WORKBREAKDOWNSTRUCTURE_WORKBREAKDOWNSTRUCTURE_H

#include "fstream"
#include "memory"
#include "iostream"
#include "algorithm"

#include "string"
#include "array"
#include "vector"
#include "deque"
#include "unordered_map"

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
    Node(int nodeID, std::string name, double time, std::vector<int> requirements);
    Node(const std::string& nodeID_str, std::string name, double time, const std::vector<std::string>& requirements_str, WorkBreakdownStructure& workBreakdownStructure);

    [[nodiscard]] int getNodeID() const {return nodeID;}
    [[nodiscard]] std::string getNodeName() const {return nodeName;}
    [[nodiscard]] double getNodeDuration() const {return duration;}
    [[nodiscard]] std::vector<int> getRequirements() const {return requirements;}

    friend std::ostream& operator<<(std::ostream& os, const Node& node);

private:
    int nodeID{};
    std::string nodeName{};
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
class WBSTree {
public:
    WBSTree() = default;
    explicit WBSTree(const std::vector<std::shared_ptr<Node>>& raw_nodeVector);

    //! Setters and Getters
    void setTree(const std::vector<std::shared_ptr<Node>>& raw_nodeVector);
    void addConnection(int nodeID, const std::vector<int>& connections);
    void addNode(const Node& node);

    std::vector<int> getStartNodes() const;
    std::vector<int>& getAdjacent(int nodeID);

    //! Print
    void printWBSTree();

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
    WorkBreakdownStructure()=default;
    explicit WorkBreakdownStructure(const std::string& filepath);

    //! Basic get and set
    std::vector<std::shared_ptr<Node>>& getNodeVectorPtr();
    unsigned long long getNodeVectorSize() const;
    void insertNode(const Node& node);

    //! Node passthrough
    [[nodiscard]] double getNodeDuration(int nodeID) const;

    //! Translation
    [[nodiscard]] int getNodeID(const std::string& ID_string);
    [[nodiscard]] std::string* getNodeIDstr(int nodeID) const;
    [[nodiscard]] std::string getNodeName(int nodeID) const;
    std::vector<std::shared_ptr<Node>> getNodeFromNodeID(const std::vector<int>& nodeIDVector);

    //! Solving WBS
    void doTheThing(); // Temp function


    //! Print
    void printNodeList();

private:
    std::vector<std::shared_ptr<Node>> nodeVector{};
    std::unordered_map<std::string, int> nodeIdMap;
    int nodeCount{};

    WBSTree wbStree;
};

/*!
 *
 * @return
 */
std::pair<double, std::vector<int>> calculateLongestPath(WorkBreakdownStructure& workBreakdownStructure, WBSTree& wbsTree);

#endif //WORKBREAKDOWNSTRUCTURE_WORKBREAKDOWNSTRUCTURE_H
