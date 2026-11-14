// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E5E0 rf_registry_write_float32_binary
// UNREALRED VERIFIED [registry-config-20261028]: Recovered previously unowned decoded code at0x59E5E0..0x59E5FD. Arguments optional section,value name,float value. Passes address of stack value to raw writer type3(REG_BINARY),4bytes,returns0/-1. Stores raw IEEE float bits without formatting or conversion; not REG_DWORD. No callers currently identified,so prototype follows fixed stack argument access rather than fabricated varargs.
int __cdecl rf_registry_write_float32_binary(const char *section, const char *value_name, float value)
{
  return rf_registry_write_raw_value((char *)section, value_name, 3u, (BYTE *)&value, 4u);
}

