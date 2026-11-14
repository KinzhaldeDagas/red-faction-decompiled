// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E020 rf_registry_read_raw_value
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,destination,capacity bytes. FIRST memset destination to0 for full capacity. Resolves root/subkey into1024-byte local,RegOpenKeyExA access1(KEY_QUERY_VALUE),then RegQueryValueExA with registry type output NULL and capacity local by reference. Returns0 query success,-1 open/query failure; closes nonnull opened handle. Does not return actual size/type,distinguish missing value from other errors,enforce string termination or reject mismatched registry types. Failed query can leave zero/partial destination. Diagnostic formatting is local only.
int __cdecl rf_registry_read_raw_value(char *String1, LPCSTR lpValueName, LPBYTE lpData, DWORD cbData)
{
  CHAR SubKey[1024]; // [esp+0h] [ebp-518h] BYREF
  LSTATUS v6; // [esp+400h] [ebp-118h]
  HKEY phkResult; // [esp+404h] [ebp-114h] BYREF
  char Buffer[260]; // [esp+408h] [ebp-110h] BYREF
  int v9; // [esp+510h] [ebp-8h]
  HKEY hKey; // [esp+514h] [ebp-4h]

  memset(lpData, 0, cbData);
  phkResult = nullptr;
  v9 = -1;
  hKey = (HKEY)rf_registry_resolve_root_and_subkey(SubKey, String1);
  v6 = RegOpenKeyExA(hKey, SubKey, 0, 1u, &phkResult);
  if ( v6 )
  {
    sprintf(Buffer, "Error opening registry key '%s'\n", SubKey);
  }
  else
  {
    v6 = RegQueryValueExA(phkResult, lpValueName, nullptr, nullptr, lpData, &cbData);
    if ( v6 )
      sprintf(Buffer, "Couldn't find registry key '%s', using default value.\n", lpValueName);
    else
      v9 = 0;
  }
  if ( phkResult )
    RegCloseKey(phkResult);
  return v9;
}

