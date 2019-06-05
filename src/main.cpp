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
#include <Timer.h>

int main() {
    setlocale(LC_ALL, "rus");

    auto v_2sc = Polyhedron::readFromFile("re_src/3d2sc.txt");
    auto v_2n = Polyhedron::readFromFile("re_src/3d.txt");
    unsigned int max_add_row = 5;

    std::string file_name_result = "result";
    std::string file_name_time = "time";
    for (int i = 0; i < v_2sc.size(); ++i) {
        std::ofstream file_result(file_name_result + std::to_string(i));
        Timer timer(file_name_time + std::to_string(i) );
        GenerationPolyhedron generationPolyhedron = GenerationPolyhedron(max_add_row, *v_2sc[i], v_2sc, v_2n);
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
            std::string log = "ind_v_2sc:\n" + std::to_string(i) + "\nc:\n" + generationPolyhedron.getGenerationCombinations().printCombination()
                              + "\ncount polyhedron:\n" + std::to_string(count_polyhedron) + '\n';
            Logs::print("log1", log);
            Logs::print("log2", log);
        } while (generationPolyhedron.next());
        file_result.close();
    }
    return 0;
}
