//-- Copyright 2015 Intrig
//-- See https://github.com/intrig/xenon for license.
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ict/xddl_code.h>
#include <ict/command.h>

int main(int argc, char **argv)
{
    bool replace = false;
    bool decl = true;
    std::string filename;

    try {
        ict::command line("xml-pp", "Pretty print xml to stdout", "xml-pp [options] xmlfile...");
        line.add(ict::Option("nodecl", 'n', "don't print xml declaration", [&]{ decl = false; }));
        line.add(ict::Option("replace", 'r', "replace file instead", [&]{ replace = true; }));
        line.parse(argc, argv);

        if (line.targets.empty()) IT_THROW("no xml files specified");

        for (auto const & f : line.targets)
        {
            filename = f;
            ict::Xml xml(filename, decl);

            if (replace)
            {
                std::ostringstream oss;
                xml.str(oss);
                std::ofstream ofs(filename.c_str());
                ofs << oss.str();

            } else {
                xml.str(std::cout);
            }
        }

    } catch (ict::exception & e)
    {
        if (!filename.empty()) std::cerr << "file: " << filename << " ";
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
