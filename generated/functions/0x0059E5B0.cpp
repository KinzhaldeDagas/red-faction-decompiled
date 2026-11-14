// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E5B0 rf_registry_read_float32_or_default
// UNREALRED VERIFIED [registry-config-20261028]: Recovered previously unowned decoded code at0x59E5B0..0x59E5E0. Arguments optional section,value name,float output,float fallback. Requests4 raw bytes without registry type/length validation; success0 returns0. Failure writes fallback through x87 FLD/FSTP and returns-1. Short successful values use zero-filled tail; no ASCII conversion or finite-value check.
int __cdecl rf_registry_read_float32_or_default(
        const char *section,
        const char *value_name,
        float *output,
        float fallback)
{
  if ( !rf_registry_read_raw_value((char *)section, value_name, (LPBYTE)output, 4u) )
    return 0;
  *output = fallback;
  return -1;
}

