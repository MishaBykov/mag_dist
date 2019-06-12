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

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "rus");

    if (argc < 4) {
        std::cout << "Usage: " << argv[0]
        << " [{unsigned int}source dimension] [{unsigned int}max_row] [{unsigned int}max_column]" << std::endl;
        return 1;
    }
    unsigned int source_dimension = 0;
    unsigned int max_row = 0;
    unsigned int max_column = 0;
    try {
        source_dimension = std::stoul(argv[1]);
        max_row = std::stoul(argv[2]);
        max_column = std::stoul(argv[3]);
    }
    catch (...) {
        std::cout << "Usage: " << argv[0]
        << " [{unsigned int}source dimension] [{unsigned int}max_row] [{unsigned int}max_column]" << std::endl;
        return 1;
    }
    std::string input_name = "re_src/" + std::to_string(source_dimension) + "d2sc.txt";
    auto v_2sc = Polyhedron::readFromFile(input_name, max_row, max_column);
    input_name = "re_src/" + std::to_string(source_dimension) + "d2n.txt";
    auto v_2n = Polyhedron::readFromFile(input_name, max_row, max_column);

    std::string file_name_result = "result.txt";
    std::string file_name_time = "time";
    Timer timer("full_time");
    std::ofstream file_result(file_name_result);
    int count_generation = 0;
    for (int i = 0; i < v_2sc.size(); ++i) {
        Timer t(file_name_time + std::to_string(i));
        GenerationPolyhedron generationPolyhedron = GenerationPolyhedron(max_row, v_2sc[i], v_2sc, v_2n);
        unsigned long count_polyhedron = 0;
        do {
            auto result = generationPolyhedron.getResult();
            if (!result->isInitialized()) {
                continue;
            }
            count_polyhedron++;
            if (Checker::isCompleteGraph(result) && Checker::isFacetsPolyhedronInVector(result, v_2n)) {
                result->printToStream(file_result);
            }
            std::string log = "ind_v_2sc:\n" + std::to_string(i) + " from " + std::to_string(v_2sc.size()) + " \nc:\n" +
                              generationPolyhedron.getGenerationCombinations().printCombination()
                              + "\ncount polyhedron:\n" + std::to_string(count_polyhedron) + '\n';
            Logs::print("log1", log);
            Logs::print("log2", log);
        } while (generationPolyhedron.next());
    }
    file_result.close();
    return 0;
}
