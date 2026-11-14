// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0720 rf_binary_stream_write_float4
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,4-float pointer. Calls0x5A06D0 for components indices0,1,2,3 in order. No normalization,version field or early stop based on individual results; raw writer status may prevent later writes. Returns last helper incidental result.
int *__thiscall rf_binary_stream_write_float4(_DWORD *this, float *a2)
{
  rf_binary_stream_write_float32_host_order(this, *a2);
  rf_binary_stream_write_float32_host_order(this, a2[1]);
  rf_binary_stream_write_float32_host_order(this, a2[2]);
  return rf_binary_stream_write_float32_host_order(this, a2[3]);
}

