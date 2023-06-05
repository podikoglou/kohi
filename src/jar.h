#pragma once
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <zip.h>

#include "classfile.h"

class JarFile {
private:
  std::vector<char> data;

public:
  std::vector<ClassFile> classes;

public:
  JarFile(std::vector<char> data) : data(data) {}

  void analyze();
};
