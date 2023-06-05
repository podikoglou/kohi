#pragma once
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <zip.h>

#include "clazzfile.h"

class JarFile {
private:
  std::vector<char> data;

public:
  std::vector<ClassFile> classes;

public:
  JarFile(std::vector<char> data) : data(data) {}

  void analyze() {
    zip_source_t *source =
        zip_source_buffer_create(data.data(), data.size(), 0, nullptr);

    if (!source) {
      throw std::runtime_error("Failed to create ZIP source from data buffer");
    }

    zip_t *zip = zip_open_from_source(source, 0, nullptr);

    if (!zip) {
      zip_source_free(source);
      throw std::runtime_error("Failed to open ZIP archive from data buffer");
    }

    // read classes
    int files_amount = zip_get_num_entries(zip, 0);

    // if we can't, error
    if (files_amount < 0) {
      zip_close(zip);

      throw std::runtime_error(
          "Failed to get the number of files in the ZIP archive");
    }

    // iterate over all the files in the zip
    for (int i = 0; i < files_amount; ++i) {
      // get stat information of the file
      zip_stat_t file_info;

      // if we can't get it, error
      if (zip_stat_index(zip, i, 0, &file_info) < 0) {
        zip_close(zip);
        throw std::runtime_error("Failed to get the stat information of the "
                                 "file in the ZIP archive");
      }

      // check if the file is a class
      std::string file_name(file_info.name);
      std::string extension = file_name.substr(file_name.find_last_of(".") + 1);

      if (extension == "class") {
        // if the file IS a class, try to open the file
        zip_file_t *file = zip_fopen_index(zip, i, 0);

        // if we can't, error
        if (!file) {
          zip_close(zip);

          throw std::runtime_error(
              "Failed to open the file in the ZIP archive");
        }

        // read the contents of the file
        std::vector<char> contents;
        contents.resize(file_info.size);

        zip_fread(file, contents.data(), contents.size());

        // Close the file
        zip_fclose(file);

        printf("read class %s\n", file_info.name);

        ClassFile classfile(file_info.name, contents);
        classes.push_back(classfile);
      }
    }

    zip_close(zip);
    // commented cuz segfault
    // zip_source_free(source);
  }
};
