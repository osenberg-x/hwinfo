#pragma once
#ifndef HWINFO_COMPUTER_SYSTEM_H_
#define HWINFO_COMPUTER_SYSTEM_H_

#include <hwinfo/platform.h>
#include <string>

namespace hwinfo {

class HWINFO_API ComputerSystem {
 friend std::string get_dmi_by_name(const std::string& name);

 public:
  ComputerSystem();
  ~ComputerSystem() = default;

  HWI_NODISCARD const std::string& manufacturer() const;
  HWI_NODISCARD const std::string& model() const;

 private:
  std::string _manufacturer;
  std::string _model;
};

}

#endif  // HWINFO_COMPUTER_SYSTEM_H_
