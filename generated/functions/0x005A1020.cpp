// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A1020 rf_binary_stream_serialize_packed4bytes
// UNREALRED VERIFIED [stream-serializers-20261029]: Recovered code0x5A1020..0x5A1066. Arguments DWORD value pointer,minimum version,DWORD fallback pointer. READ calls0x5A04F0 into local DWORD then stores it at value pointer. WRITE0x5A0B80 emits four bytes in order. No color-channel permutation or numeric conversion. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
void __thiscall rf_binary_stream_serialize_packed4bytes(
        void *stream,
        unsigned int *value,
        int minimum_version,
        const unsigned int *fallback)
{
  int v5; // [esp+4h] [ebp-4h] BYREF

  if ( rf_vfile_test_mode_mask(stream, 1) )
    *value = *rf_binary_stream_read_packed4bytes_versioned((int *)stream, &v5, minimum_version, fallback);
  else
    rf_binary_stream_write_packed4bytes(stream, (char *)value);
}

