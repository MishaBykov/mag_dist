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

#include <test.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

    if(argc < 4)
    {
        std::cout << "Usage: " << argv[0]
                  << " [{unsigned int}source dimension] [{unsigned int}max_facet] [{unsigned int}count_vertex]"
                  << std::endl;
        return 1;
    }
    unsigned int source_dimension = 0;
    unsigned int max_facet = 0;
    unsigned int count_vertex = 0;
    try
    {
        source_dimension = std::stoul(argv[1]);
        max_facet = std::stoul(argv[2]);
        count_vertex = std::stoul(argv[3]);
    }
    catch(...)
    {
        std::cout << "Usage: " << argv[0]
                  << " [{unsigned int}source dimension] [{unsigned int}max_facet] [{unsigned int}count_vertex]"
                  << std::endl;
        return 1;
    }
    std::string input_name = "re_src/" + std::to_string(source_dimension) + "d2sc.txt";
    auto v_2sc = Polyhedron::readFromFile(input_name, max_facet, count_vertex, true);
    input_name = "re_src/" + std::to_string(source_dimension) + "d2n.txt";
    auto v_2n = Polyhedron::readFromFile(input_name, max_facet, count_vertex, false);

    std::string file_name_result = "result";
    file_name_result += "_f_max" + std::to_string(max_facet) + "_v" + std::to_string(count_vertex) + ".txt";
    std::string file_name_time = "full_time";
    file_name_time += "_f_max" + std::to_string(max_facet) + "_v" + std::to_string(count_vertex) + ".txt";
    Timer timer(file_name_time);
    std::ofstream file_result(file_name_result);
    for(int i = 0; i < v_2sc.size(); ++i)
    {
        GenerationPolyhedron generationPolyhedron = GenerationPolyhedron(max_facet, v_2sc[i], v_2sc, v_2n);
        unsigned long long count_polyhedron = 0;
        do
        {
            auto result = generationPolyhedron.getResult();
            if(!result->isInitialized())
            {
                continue;
            }
            count_polyhedron++;
            if(Checker::isCompleteGraph(result) && Checker::isFacetsPolyhedronInVector(result, v_2n))
            {
                result->printToStream(file_result);
            }
            if(count_polyhedron % 1000 == 0)
            {
                std::string log =
                        "ind_v_2sc:\n" + std::to_string(i) + " from " + std::to_string(v_2sc.size()) + " \nc:\n" +
                        generationPolyhedron.getGenerationCombinations().printCombination()
                        + "\ncount polyhedron:\n" + std::to_string(count_polyhedron) + '\n';
                if (count_polyhedron % 2 == 0)
                    Logs::print("log0", log);
                else
                    Logs::print("log1", log);
            }
        } while(generationPolyhedron.next());
    }
    file_result.close();
    return 0;
}
