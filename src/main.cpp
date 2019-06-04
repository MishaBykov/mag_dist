#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

#include <IncidenceMatrix.h>
#include <Polyhedron.h>
#include <GenerationCombinations.h>
#include <Checker.h>
#include <Logs.h>
#include <GenerationPolyhedron.h>

//int main(){
//
//    auto test = Polyhedron::readFromFile("test.txt");
//    for (int i = 0; i < test.size(); ++i) {
//        test[i]->getMatrix()->sort();
//        test[i]->getMatrix()->transpose();
//        test[i]->getMatrix()->sort();
//        test[i]->getMatrix()->transpose();
//        test[i]->printToStream(std::cout);
//    }
//
//    return 0;
//}

int main() {
    setlocale(LC_ALL, "rus");

    std::string file_name_3d2sc = "re_src/3d2sc.txt";
    std::string file_name_3d = "re_src/3d.txt";

    auto v_2sc = Polyhedron::readFromFile(file_name_3d2sc);

    std::ofstream file_result("result.txt");
    GenerationPolyhedron generationPolyhedron = GenerationPolyhedron(*v_2sc[2], file_name_3d2sc, file_name_3d);
//    unsigned long init_combination[] = {6, 7, 8, 9, 14, 17, 23, 24, 30, 32};
//    std::vector<unsigned long> combination(init_combination, init_combination + sizeof(init_combination) / sizeof(unsigned long) );
//    generationPolyhedron.getGenerationCombinations().setCombination(combination);
    unsigned long count_polyhedron = 0;
    do {
        auto result = generationPolyhedron.getResult();
        if (!result->isInitialized()) {
            continue;
        }
        count_polyhedron++;
        if (Checker::isCompleteGraph(result)) {
            result->printToStream(file_result);
        }
        std::string log = "c:\n" + generationPolyhedron.getGenerationCombinations().printCombination()
                + "\ncount false:\n" + std::to_string(count_polyhedron) + '\n';
        Logs::print("log1", log);
        Logs::print("log2", log);
    } while (generationPolyhedron.next());
    file_result.close();
    return 0;
}
