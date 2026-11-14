// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A04F0 rf_binary_stream_read_packed4bytes_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,DWORD output,minimum version,DWORD fallback pointer. Allowed version initializes local through unknown_libname_28,then fills its four bytes sequentially with byte reader(minimum,default255),stores resulting DWORD to output. Below minimum copies fallback DWORD. Returns output pointer. No semantic channel conversion,byte-order swap or aggregate error return; failures of individual reads become255.
_DWORD *__thiscall rf_binary_stream_read_packed4bytes_versioned(int *this, _DWORD *a2, int a3, _DWORD *a4)
{
  int v6; // [esp+4h] [ebp-4h] BYREF

  if ( rf_binary_stream_version_at_least(this, a3) )
  {
    rf_rgba8_default_construct_noop(&v6);
    LOBYTE(v6) = rf_binary_stream_read_byte_versioned(this, a3, 255);
    BYTE1(v6) = rf_binary_stream_read_byte_versioned(this, a3, 255);
    BYTE2(v6) = rf_binary_stream_read_byte_versioned(this, a3, 255);
    HIBYTE(v6) = rf_binary_stream_read_byte_versioned(this, a3, 255);
    *a2 = v6;
  }
  else
  {
    *a2 = *a4;
  }
  return a2;
}

