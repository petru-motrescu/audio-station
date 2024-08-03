#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "asserts.hpp"
#include "project.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_project_tests() {

    test("Empty project", [] {
        Project project;
        for (int i = 0; i < 100; i++) {
            assert_equal(0, project.render());
        }
    });
    
}
