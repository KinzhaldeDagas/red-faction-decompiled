// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E140 rf_registry_set_default_software_path
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional company,optional application. Replaces256-byte base path0x1C0D1C8 with Software backslash,appends company when nonnull,then another backslash and application when nonnull. Sets DWORD initialized marker0x1C0D2C8=1,returns0. No bounds checks,registry access or validation; null company plus application leaves doubled separator. Readers/writers shown do not test marker.
int __cdecl rf_registry_set_default_software_path(const char *a1, const char *a2)
{
  strcpy(byte_1C0D1C8, "Software\\");
  if ( a1 )
    strcat(byte_1C0D1C8, a1);
  if ( a2 )
  {
    *(_WORD *)&byte_1C0D1C8[strlen(byte_1C0D1C8)] = 92;
    strcat(byte_1C0D1C8, a2);
  }
  unk_1C0D2C8 = 1;
  return 0;
}

