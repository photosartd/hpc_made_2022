#include <vector>
#include <omp.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


double model_cpp(std::vector<double> &v) {
    int n = v.size();
    unsigned long sum = 0;

    omp_set_dynamic(0);
    omp_set_num_threads(8);
#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += std::pow(v[i], n - i);
    }
    return sum;
}


PYBIND11_MODULE(cpp_binding, m) {
    m.doc() = "pybind11 binding"; // optional module docstring

    m.def("model_cpp", &model_cpp, "A function that calculates model in parallel", py::arg("x"));
}
