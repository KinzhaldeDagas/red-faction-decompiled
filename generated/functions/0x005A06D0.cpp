// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A06D0 rf_binary_stream_write_float32_host_order
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,float stack value. Passes address,count4 to0x5A0990,writing raw native IEEE float bytes without promotion,text conversion,endian swap or finite-value check. Returns lower helper incidental result.
int *__thiscall rf_binary_stream_write_float32_host_order(_DWORD *this, float Buffer)
{
  return rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 4u);
}

