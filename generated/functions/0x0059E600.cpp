// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E600 rf_registry_delete_key_or_value
// UNREALRED VERIFIED [registry-config-20261028]: Recovered previously unowned decoded code at0x59E600..0x59E764. Arguments optional section,optional value name. Resolves root/subkey. NULL value name calls RegDeleteKeyA directly (not recursive); failure diagnostic mistakenly passes NULL value-name argument to percent-s. Nonnull value name calls RegCreateKeyExA with KEY_ALL_ACCESS then RegDeleteValueA,so deleting missing value can CREATE the containing key. Returns0 success,-1 create/delete failure,closes nonnull created/opened handle. Does not use initialized marker or propagate raw Win32 status. No application registry operation is executed during this analysis; only original function behavior is described.
int __cdecl rf_registry_delete_key_or_value(const char *section, const char *value_name)
{
  DWORD dwDisposition; // [esp+0h] [ebp-51Ch] BYREF
  CHAR SubKey[1024]; // [esp+4h] [ebp-518h] BYREF
  LSTATUS v5; // [esp+404h] [ebp-118h]
  HKEY phkResult; // [esp+408h] [ebp-114h] BYREF
  char Buffer[260]; // [esp+40Ch] [ebp-110h] BYREF
  int v8; // [esp+514h] [ebp-8h]
  HKEY hKey; // [esp+518h] [ebp-4h]

  phkResult = nullptr;
  v8 = 0;
  hKey = (HKEY)rf_registry_resolve_root_and_subkey(SubKey, (char *)section);
  if ( value_name )
  {
    v5 = RegCreateKeyExA(hKey, SubKey, 0, &byte_642CFF, 0, 0xF003Fu, nullptr, &phkResult, &dwDisposition);
    if ( v5 )
    {
      sprintf(Buffer, "Error opening registry key '%s'\n", SubKey);
      v8 = -1;
    }
    else
    {
      v5 = RegDeleteValueA(phkResult, value_name);
      if ( v5 )
      {
        sprintf(Buffer, "Error removing registry value '%s'\n", value_name);
        v8 = -1;
      }
    }
  }
  else
  {
    v5 = RegDeleteKeyA(hKey, SubKey);
    if ( v5 )
    {
      sprintf(Buffer, "Error removing registry key '%s'\n", nullptr);
      v8 = -1;
    }
  }
  if ( phkResult )
    RegCloseKey(phkResult);
  return v8;
}

