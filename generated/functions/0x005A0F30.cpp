// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0F30 rf_binary_stream_serialize_string_object
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments RF string-object pointer,minimum version,fallback C string. READ0x59FD90 length-prefixed/versioned assignment. WRITE gets data through0x55F6F0 then calls0x5A08B0 with length-1,writing WORD length and bytes without NUL. Existing inferred std::exception pointer type comes from misleading accessor label; no exception/vtable operations in this body. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
unsigned __int16 __thiscall rf_binary_stream_serialize_string_object(
        int *this,
        std::exception *a2,
        int a3,
        char *Source)
{
  const char *v5; // eax

  if ( rf_vfile_test_mode_mask(this, 1) )
    return rf_binary_stream_read_string_object_versioned(this, a2, a3, Source);
  v5 = rf_string_object_c_str_or_empty(a2);
  return rf_binary_stream_write_u16_length_string(this, v5, -1);
}

