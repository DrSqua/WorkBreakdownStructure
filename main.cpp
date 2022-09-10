#include <iostream>

#include "WorkBreakdownStructure.h"
#include "Rendering/Rendering.h"
#include "WBSFilesystem/WBSFilesystem.h"

void insertTestCase2(WorkBreakdownStructure& workBreakdownStructure) {
    Node node_0({"A"}, "Contour uitzetten", 6, {}, workBreakdownStructure);
    Node node_1({"B"}, "Werfkeet Plaatsen", 4, {"A"}, workBreakdownStructure);
    Node node_2({"C"}, "Gereedschap aanvoeren", 7, {"B"}, workBreakdownStructure);
    Node node_3({"D"}, "Uitgraven", 2, {"A"}, workBreakdownStructure);
    Node node_4({"E"}, "Wapening en buizen plaatsen", 4, {"D"}, workBreakdownStructure);
    Node node_5({"F"}, "Gieten en uitharden beton", 10, {"E"}, workBreakdownStructure);
    Node node_6({"G"}, "sterfput plaatsen", 2, {}, workBreakdownStructure);
    Node node_7({"H"}, "ietsH", 10, {"G"}, workBreakdownStructure);
    Node node_8({"I"}, "ietsI", 6, {"H", "J"}, workBreakdownStructure);
    Node node_9({"J"}, "ietsJ", 13, {}, workBreakdownStructure);
    Node node_10({"K"}, "ietsK", 9, {"A"}, workBreakdownStructure);
    Node node_11({"L"}, "ietsL", 3, {"C", "K"}, workBreakdownStructure);
    Node node_12({"M"}, "ietsM", 5, {"I", "L"}, workBreakdownStructure);

    workBreakdownStructure.insertNode(node_0);
    workBreakdownStructure.insertNode(node_1);
    workBreakdownStructure.insertNode(node_2);
    workBreakdownStructure.insertNode(node_3);
    workBreakdownStructure.insertNode(node_4);
    workBreakdownStructure.insertNode(node_5);
    workBreakdownStructure.insertNode(node_6);
    workBreakdownStructure.insertNode(node_7);
    workBreakdownStructure.insertNode(node_8);
    workBreakdownStructure.insertNode(node_9);
    workBreakdownStructure.insertNode(node_10);
    workBreakdownStructure.insertNode(node_11);
    workBreakdownStructure.insertNode(node_12);
}

void insertTestCase1(WorkBreakdownStructure& workBreakdownStructure) {
    std::vector<Node> nodes {
        Node(0, "0", 6, {}),
        Node(1, "1", 4, {0}),
        Node(2, "2", 2, {0}),
        Node(3, "3", 3, {2}),
        Node(4, "4", 1, {1, 3}),
    };
    for (auto& node : nodes) {
        workBreakdownStructure.insertNode(node);
    }
}

int main() {

    int screenWidth = 600;
    int screenHeight = 400;

    std::string filename = "Construction";
    WorkBreakdownStructure workBreakdownStructureCSV = create_wbs(getCSVFilepathFromFilename(filename));

    workBreakdownStructureCSV.printNodeList();
    std::cout << std::endl;


    workBreakdownStructureCSV.printSolvedWbsStructure(workBreakdownStructureCSV.solveWbsStructrure());
    WbsDisplayClass wbsDisplayClass(screenWidth, screenHeight, workBreakdownStructureCSV);

    return 0;
}
