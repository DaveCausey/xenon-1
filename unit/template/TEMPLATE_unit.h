#pragma once
//-- Copyright 2015 Intrig
//-- see https://github.com/intrig/xenon for license

#include "../itunit.h"

class TEMPLATE_unit 
{
    public:
    void register_tests(IT::UnitTest<TEMPLATE_unit> & ut) 
    {
        ut.skip();
        ut.cont();
        ut.add(&TEMPLATE_unit::sanity);
    }

    void sanity();
};

#endif
