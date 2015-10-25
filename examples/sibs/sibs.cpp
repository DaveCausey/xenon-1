#include <iostream>
#include <ict/xenon.h>

using std::cout;
using std::cerr;

int main(int argc, char ** argv) {
    try {
        ict::spec doc("icd.xddl");

        auto msg = ict::parse(doc, "020008a7ae1f7f61fd041694e494700fa39251e20660b30000000000000000000001");

        cout << ict::to_text(msg);

        auto c = ict::find(msg.root(), "//SIB-Data-variable");
        if (c==msg.end()) IT_THROW("can't find SIB-Data-variable");

        cout << c->name() << " " << c->bits << "\n";
        cout << "bits: " << ict::to_bin_string(c->bits) << "\n";

        auto start = ict::get_record(doc, "3GPP/TS-25.331.xddl#SysInfoType19");

        auto inner = ict::parse(start, c->bits);

        cout << inner.text("nlvhFLs", false);
    }

    catch (std::exception & e) {
        cerr << e.what() << "\n";
    }
}
