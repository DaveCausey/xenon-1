//-- Copyright 2015 Intrig
//-- See https://github.com/intrig/xenon for license.
#include "loadunit.h"

#include <ict/xenon.h>
#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;
using std::cout;

void load_unit::sanity() {
}

void load_all_xddl(const bf::path & dir, ict::spec_server & specs) {
    if (!exists(dir)) return;
    bf::directory_iterator end_itr;
    for (auto i = bf::directory_iterator(dir); i != end_itr; ++i) {
        if (bf::is_directory(i->path())) load_all_xddl(i->path(), specs);
        else if (bf::extension(i->path()) == ".xddl") {
            specs.add_spec(i->path().string());
        }
    }
}

void get_all_xddl(const bf::path & dir, std::vector<bf::path> & paths) {
    if (!exists(dir)) return;
    bf::directory_iterator end_itr;
    for (auto i = bf::directory_iterator(dir); i != end_itr; ++i) {
        if (bf::is_directory(i->path())) get_all_xddl(i->path(), paths);
        else if (bf::extension(i->path()) == ".xddl") {
            paths.push_back(i->path());
            //cout << i->path().string() << '\n';
        }
    }

}
void load_unit::load_all_specs() {
    auto root = ict::get_env_var("XDDLPATH");
    if (root.empty()) return;

    auto paths = std::vector<bf::path>();

    auto p = bf::path(root);
    try {
        load_all_xddl(p, specs);
      } catch (const bf::filesystem_error& ex) {
        IT_FORCE_ASSERT("filesystem error: " << ex.what());
      } catch (const ict::exception & ex) {
        IT_FORCE_ASSERT(ex.what());
      }
}


int main (int, char **) {
    load_unit test;
    ict::unit_test<load_unit> ut(&test);
    return ut.run();
}
