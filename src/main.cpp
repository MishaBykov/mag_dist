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

#include <generate_table.h>

int main(int argc, char *argv[]) {
    generate_table();
    return 0;


    setlocale(LC_ALL, "rus");

    if (argc < 4) {
        std::cout << "Usage: " << argv[0]
        << " [{unsigned int}source dimension] [{unsigned int}max_row] [{unsigned int}count_column]" << std::endl;
        return 1;
    }
    unsigned int source_dimension = 0;
    unsigned int max_row = 0;
    unsigned int count_column = 0;
    try {
        source_dimension = std::stoul(argv[1]);
        max_row = std::stoul(argv[2]);
        count_column = std::stoul(argv[3]);
    }
    catch (...) {
        std::cout << "Usage: " << argv[0]
        << " [{unsigned int}source dimension] [{unsigned int}max_row] [{unsigned int}max_column]" << std::endl;
        return 1;
    }
    std::string input_name = "re_src/" + std::to_string(source_dimension) + "d2sc.txt";
    auto v_2sc = Polyhedron::readFromFile(input_name, max_row, count_column, true);
    input_name = "re_src/" + std::to_string(source_dimension) + "d2n.txt";
    auto v_2n = Polyhedron::readFromFile(input_name, max_row, count_column, false);

    std::string file_name_result = "result";
    file_name_result += "_f_max" + std::to_string(max_row) + "_v" + std::to_string(count_column) + ".txt";
    std::string file_name_time = "full_time";
    file_name_time += "_f_max" + std::to_string(max_row) + "_v" + std::to_string(count_column) + ".txt";
    Timer timer(file_name_time);
    std::ofstream file_result(file_name_result);
    int count_generation = 0;
    for (int i = 0; i < v_2sc.size(); ++i) {
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
