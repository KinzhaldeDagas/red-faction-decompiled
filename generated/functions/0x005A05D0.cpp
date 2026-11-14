// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A05D0 rf_binary_stream_write_char8_host_order
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,8-bit stack value. Passes address of argument and count1 to0x5A0990. No encoding conversion,numeric parsing or result normalization. Parallel unsigned byte writer0x5A05F0 has same-width raw behavior.
int *__thiscall rf_binary_stream_write_char8_host_order(_DWORD *this, char Buffer)
{
  return rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 1u);
}

