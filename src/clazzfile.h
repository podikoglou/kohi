#pragma once

#include "access.h"
#include <cstdint>
#include <string>

#include <vector>
class ClassFile {
public:
  std::string name;

private:
  std::string file_name;
  std::vector<char> data;

public:
  uint32_t magic;
  uint16_t minor_version;
  uint16_t major_version;
  uint16_t constant_pool_count;
  // TODO: define the cp_info class

  std::vector<AccessFlag> access_flags;
  uint16_t this_class;
  uint16_t super_class;
  // uint16_t interfaces_count;
  // std::vector<Interface> interfaces;
  // TODO: make interface class

  // uint16_t fields_count;
  // std::vector<Field> fields;
  // TODO: make field class

  // uint16_t methods_count;
  // std::vector<Method> methods;
  // TODO: make method class

  // uint16_t attributes_count;
  // std::vector<Attribute> attributes;
  // TODO: make attribute class

public:
  ClassFile(std::string name, std::vector<char> data)
      : name(name), data(data) {}

  void analyze() {}
};
