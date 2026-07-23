module;

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

module model;

import geometry;

Model::Model(const std::string filename)
{
    std::ifstream ist{filename};
    if (!ist)
        throw std::runtime_error("Cannot open input file: " + filename);

    std::string line;
    while (std::getline(ist, line)) // All the line is consumed.
    {
        std::istringstream lineStream(line);
        std::string dataType;
        lineStream >> dataType;

        if (dataType == "v")
        {
            vec3 v;
            lineStream >> v.x >> v.y >> v.z;
            verts.push_back(v);
        }
        else if (dataType == "f")
        {
            int idx;
            while (lineStream >> idx)
                facet_vrt.push_back(idx);
        }
    }

    std::cout << "Loaded " << verts.size() << " vertices\n";
}