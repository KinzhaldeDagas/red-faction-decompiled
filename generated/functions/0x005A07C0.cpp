// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A07C0 rf_binary_stream_write_transposed12_floats
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,source12-float block. Writes12 floats in INDEX ORDER0,3,6,1,4,7,2,5,8,9,10,11,via float32 writer. No padding fields,homogeneous constants,version header or aggregate status check. Reader0x59FC30 consumes this order but then overwrites indices3,6,9 and writes extra index12,so it is not a literal round-trip of all12 stored values. Returns last helper incidental result.
int *__thiscall rf_binary_stream_write_transposed12_floats(_DWORD *this, float *a2)
{
  rf_binary_stream_write_float32_host_order(this, *a2);
  rf_binary_stream_write_float32_host_order(this, a2[3]);
  rf_binary_stream_write_float32_host_order(this, a2[6]);
  rf_binary_stream_write_float32_host_order(this, a2[1]);
  rf_binary_stream_write_float32_host_order(this, a2[4]);
  rf_binary_stream_write_float32_host_order(this, a2[7]);
  rf_binary_stream_write_float32_host_order(this, a2[2]);
  rf_binary_stream_write_float32_host_order(this, a2[5]);
  rf_binary_stream_write_float32_host_order(this, a2[8]);
  rf_binary_stream_write_float32_host_order(this, a2[9]);
  rf_binary_stream_write_float32_host_order(this, a2[10]);
  return rf_binary_stream_write_float32_host_order(this, a2[11]);
}

