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

//std::string combToRow(unsigned int n, const std::vector<unsigned long>& combination){
//    std::string result(n, '0');
//    for( auto item : combination){
//        result[item - 1] = '1';
//    }
//    return result;
//}

int main() {
    setlocale(LC_ALL, "rus");

    std::string file_name_3d2sc = "re_src/3d2sc.txt";
    std::string file_name_3d = "re_src/3d.txt";

    auto v_2sc = Polyhedron::readFromFile(file_name_3d2sc);

    std::ofstream file_result("result.txt");
    GenerationPolyhedron generationPolyhedron = GenerationPolyhedron(*v_2sc[1], file_name_3d2sc, file_name_3d);
    unsigned int count_false = 0;
    do {
        Logs print_log("log.txt");
        Logs::print("c:\n" + generationPolyhedron.getGenerationCombinations().printCombination());
        Logs::print("\ncount false:\n" + std::to_string(count_false) + '\n');
        auto result = generationPolyhedron.getResult();
        if (!result->isInitialized()) {
            continue;
        }
        if (Checker::is2neighborly(result)) {
            result->printToStream(file_result);
        } else {
            count_false++;
        }

    } while (generationPolyhedron.next());
    file_result.close();
    return 0;
}

