// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059DB40 rf_registry_write_raw_value
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section/key string,value name,registry type,data pointer,byte count. Resolves root/subkey through0x59DC60,RegCreateKeyExA options0/access0xF003F(KEY_ALL_ACCESS),then RegSetValueExA with supplied type/data/count. Returns0 success,-1 create/set error. Closes nonnull opened handle regardless result. Errors are formatted only into local diagnostic; does not validate input data,type,count,initialization flag or string capacity. Creates missing key hierarchy; not an atomic multi-value update.
int __cdecl rf_registry_write_raw_value(char *String1, LPCSTR lpValueName, DWORD dwType, BYTE *lpData, DWORD cbData)
{
  CHAR SubKey[1024]; // [esp+0h] [ebp-518h] BYREF
  LSTATUS v7; // [esp+400h] [ebp-118h]
  HKEY phkResult; // [esp+404h] [ebp-114h] BYREF
  char Buffer[256]; // [esp+408h] [ebp-110h] BYREF
  DWORD dwDisposition; // [esp+50Ch] [ebp-Ch] BYREF
  HKEY hKey; // [esp+510h] [ebp-8h]
  int v12; // [esp+514h] [ebp-4h]

  v12 = 0;
  phkResult = nullptr;
  hKey = (HKEY)rf_registry_resolve_root_and_subkey(SubKey, String1);
  v7 = RegCreateKeyExA(hKey, SubKey, 0, (LPSTR)&Class, 0, 0xF003Fu, nullptr, &phkResult, &dwDisposition);
  if ( v7 )
  {
    sprintf(Buffer, "Error opening registry key '%s'\n", SubKey);
    v12 = -1;
  }
  else
  {
    v7 = RegSetValueExA(phkResult, lpValueName, 0, dwType, lpData, cbData);
    if ( v7 )
    {
      sprintf(Buffer, "Error writing registry key '%s'\n", lpValueName);
      v12 = -1;
    }
  }
  if ( phkResult )
    RegCloseKey(phkResult);
  return v12;
}

