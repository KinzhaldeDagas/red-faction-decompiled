// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059DF40 rf_registry_parse_predefined_root
// UNREALRED VERIFIED [registry-config-20261028]: Case-insensitive exact names HKEY_CLASSES_ROOT,HKEY_CURRENT_USER,HKEY_LOCAL_MACHINE,HKEY_USERS map0x80000000..3. Any other name formats Bogus HKEY_ string diagnostic and calls fatal0x5708E0 with original registry.cpp line183. That fatal routine exits1,so normal unknown-root fallback does not occur. No abbreviated aliases,null guard or user-defined handles.
int __cdecl rf_registry_parse_predefined_root(char *String1)
{
  char Buffer[260]; // [esp+0h] [ebp-108h] BYREF

  if ( !_stricmp(String1, "HKEY_CLASSES_ROOT") )
    return 0x80000000;
  if ( !_stricmp(String1, "HKEY_CURRENT_USER") )
    return -2147483647;
  if ( !_stricmp(String1, "HKEY_LOCAL_MACHINE") )
    return -2147483646;
  if ( _stricmp(String1, "HKEY_USERS") )
  {
    sprintf(Buffer, "Bogus HKEY_ string: %s", String1);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\os\\registry.cpp", 183, Buffer);
  }
  return -2147483645;
}

