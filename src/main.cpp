#include "jar.h"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <jar>\n";
    return 1;
  }

  std::string jar_path = argv[1];

  std::ifstream jar_file(jar_path, std::ios::binary);
  if (!jar_file) {
    std::cout << "Failed to open the JAR file: " << jar_path << "\n";
    return 1;
  }

  jar_file.seekg(0, std::ios::end);
  std::streampos file_size = jar_file.tellg();
  jar_file.seekg(0, std::ios::beg);

  // create a vector to store the bytes
  std::vector<char> buffer(file_size);

  // read the bytes into the vector
  jar_file.read(buffer.data(), file_size);

  // Close the JAR file
  jar_file.close();

  // create instance of JarFile class
  JarFile jar = JarFile(buffer);
  jar.analyze();

  return 0;
}
