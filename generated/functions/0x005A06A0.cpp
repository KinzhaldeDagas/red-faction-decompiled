// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A06A0 rf_binary_stream_write_uint32_host_order
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,32-bit stack value. Passes address of argument,count4 to0x5A0990. Equivalent-width implementation to0x5A0670; no endian conversion or status check. Returns lower helper incidental result,not guaranteed4.
int *__thiscall rf_binary_stream_write_uint32_host_order(_DWORD *this, int Buffer)
{
  return rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 4u);
}

