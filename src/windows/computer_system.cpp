#include <hwinfo/platform.h>

#ifdef HWINFO_WINDOWS

#include <hwinfo/computer_system.h>
#include <hwinfo/utils/stringutils.h>
#include <hwinfo/utils/wmi_wrapper.h>

#include <string>

namespace hwinfo {

ComputerSystem::ComputerSystem() {
  utils::WMI::_WMI wmi;
  const std::wstring query_string(L"SELECT Manufacturer, Model FROM Win32_ComputerSystem");
  bool success = wmi.execute_query(query_string);
  if (!success) return;

  ULONG u_return = 0;
  IWbemClassObject* obj = nullptr;
  wmi.enumerator->Next(WBEM_INFINITE, 1, &obj, &u_return);
  if (!u_return) return;

  VARIANT vt_prop;
  HRESULT hr;
  hr = obj->Get(L"Manufacturer", 0, &vt_prop, nullptr, nullptr);
  if (SUCCEEDED(hr) && (V_VT(&vt_prop) == VT_BSTR)) {
    _manufacturer = utils::wstring_to_std_string(vt_prop.bstrVal);
  }
  hr = obj->Get(L"Model", 0, &vt_prop, nullptr, nullptr);
  if (SUCCEEDED(hr) && (V_VT(&vt_prop) == VT_BSTR)) {
    _model = utils::wstring_to_std_string(vt_prop.bstrVal);
  }
  VariantClear(&vt_prop);
  obj->Release();
}

}  // namespace hwinfo

#endif  // HWINFO_WINDOWS