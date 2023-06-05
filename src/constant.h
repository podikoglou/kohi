#pragma once

#include <cstdint>

namespace constant {
enum Tag {
  Clazz = 7,
  Fieldref = 9,
  Methodref = 10,
  InterfaceMethodref = 11,
  String = 8,
  Integer = 3,
  Float = 4,
  Long = 5,
  Double = 6,
  NameAndType = 12,
  Utf8 = 1,
  MethodHandle = 15,
  MethodType = 16,
  InvokeDynamic = 18
};

class Constant {
public:
  const Tag tag;

  Constant(Tag tag) : tag(tag) {}
  virtual ~Constant() {}
};
} // namespace constant

namespace constant::types {
class ConstantClass : public Constant {
public:
  uint16_t name_index;

  ConstantClass(uint16_t name_index)
      : Constant(Tag::Clazz), name_index(name_index) {}
};

class ConstantFieldref : public Constant {
public:
  uint16_t class_index;
  uint16_t name_and_type_index;

  ConstantFieldref(uint16_t class_index, uint16_t name_and_type_index)
      : Constant(Tag::Fieldref), class_index(class_index),
        name_and_type_index(name_and_type_index) {}
};
} // namespace constant::types
