// Copyright 2021 Research Institute of Systems Planning, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vector>
#include <unordered_map>
#include <string>

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/functional.h"
#include "caret_analyze_cpp_impl/record.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

PYBIND11_MODULE(record_cpp_impl, m) {
  py::class_<RecordBase>(m, "RecordBase")
  .def(py::init())
  .def(
    py::init(
      [](const RecordBase & init) {
        return new RecordBase(init);
      })
  )
  .def(
    py::init(
      [](std::unordered_map<std::string, uint64_t> init) {
        return new RecordBase(init);
      })
  )
  .def("change_dict_key", &RecordBase::change_dict_key)
  .def("equals", &RecordBase::equals)
  .def("merge", &RecordBase::merge)
  .def("add", &RecordBase::add)
  .def("drop_columns", &RecordBase::drop_columns)
  .def("get", &RecordBase::get)
  .def("get_with_default", &RecordBase::get_with_default)
  .def_property_readonly("data", &RecordBase::get_data)
  .def_property_readonly("columns", &RecordBase::get_columns);

  py::class_<RecordsBase>(m, "RecordsBase")
  .def(py::init())
  .def(
    py::init(
      [](const RecordsBase & init) {
        return new RecordsBase(init);
      })
  )
  .def(
    py::init(
      [](std::vector<RecordBase> init, std::vector<std::string> columns) {
        return new RecordsBase(init, columns);
      })
  )
  .def("append", &RecordsBase::append)
  .def("append_column", &RecordsBase::append_column)
  .def("clone", &RecordsBase::clone)
  .def("equals", &RecordsBase::equals)
  .def("drop_columns", &RecordsBase::drop_columns)
  .def("rename_columns", &RecordsBase::rename_columns)
  .def("filter_if", &RecordsBase::filter_if)
  .def("reindex", &RecordsBase::reindex)
  .def("concat", &RecordsBase::concat)
  .def("sort", &RecordsBase::sort)
  .def("sort_column_order", &RecordsBase::sort_column_order)
  .def("merge", &RecordsBase::merge)
  .def("merge_sequencial", &RecordsBase::merge_sequencial)
  .def("bind_drop_as_delay", &RecordsBase::bind_drop_as_delay)
  .def(
    "merge_sequencial_for_addr_track",
    &RecordsBase::merge_sequencial_for_addr_track)
  .def_property_readonly("data", &RecordsBase::get_data)
  .def_property_readonly("columns", &RecordsBase::get_columns);

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}
