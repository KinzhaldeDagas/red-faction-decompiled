// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FD90 rf_binary_stream_read_string_object_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination string object,minimum version,optional fallback C string. Allowed version calls0x59F7D0 length-prefixed reader. Otherwise assigns supplied fallback,or empty literal0x642FEC when null,through string assignment0x55FFA0. Does not enforce maximum string length or translate reader errors. Forwards branch-specific helper result in EAX,including full string-object pointer on assignment paths. Existing unsigned-short return prototype is misleading; no normalized length/status.
unsigned __int16 __thiscall rf_binary_stream_read_string_object_versioned(int *this, _DWORD *a2, int a3, char *Source)
{
  if ( rf_binary_stream_version_at_least(this, a3) )
    return rf_binary_stream_read_string_object_u16_length(this, (int)a2);
  if ( Source )
    return (unsigned __int16)rf_string_assign_from_cstr(a2, Source);
  return (unsigned __int16)rf_string_assign_from_cstr(a2, (char *)&byte_642FEC);
}

