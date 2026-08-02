module;

#include <tuple>
#include <tuple>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.vbo;
import :structure.ebo;
import :model.loader.obj;
import :normal.calculator;

// ============================================================================
// Constants
// ============================================================================

constexpr bool DEBUG = false;

// ============================================================================
// Implementations
// ============================================================================

std::tuple<VBO, EBO> ObjModelLoader::load(
    const std::string &filename,
    const NormalCalculator &normalCalculator) const
{
    std::vector<VertexIn> vertices;
    std::vector<int> faces;

    std::ifstream ist{filename};
    if (!ist)
        throw std::runtime_error("Cannot open input file: " + filename);

    std::string line;
    while (std::getline(ist, line)) // All the line is consumed.
    {
        if (DEBUG)
            std::cout << "Line: " << line << '\n';

        std::istringstream lineStream(line);
        std::string dataType;
        lineStream >> dataType;

        if (dataType == "v") // Vertices.
        {
            VertexIn v;
            lineStream >> v.localPosition;
            vertices.push_back(v);
        }
        else if (dataType == "f") // Faces / Triangles.
        {
            std::string token;

            // Each token can have a form n, n/n, n//n, n/n/n.
            // Where n is a number.
            // At the moemnt, just the first n is of interest.
            while (lineStream >> token)
            {
                if (DEBUG)
                    std::cout << "Token: " << token << '\n';

                // Token stream creation so we are able to read from it.
                std::istringstream tokenStream(token);

                // Only the first number in each token is of interest.
                int idx;
                tokenStream >> idx; // It stops when finding a "/" or the end.

                if (DEBUG)
                    std::cout << idx << std::endl;

                // The vertices in .obj starts at 1, but the array starts at 0.
                // So we have to decrease one.
                faces.push_back(idx - 1);
            }
        }
    }

    if (DEBUG)
        std::cout << "Loaded " << vertices.size() << " vertices\n";

    normalCalculator.calculateNormals(vertices, faces);

    return {VBO{vertices}, EBO{faces}};
}

// ============================================================================
// EOF
// ============================================================================
