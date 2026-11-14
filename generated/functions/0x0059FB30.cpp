// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FB30 rf_binary_stream_read_float4_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination4-float array,minimum version,default4-float pointer. Version allowed reads4 floats sequentially with minimum0/default0 and stores offsets0,4,8,12; returns destination. Version absent copies4 floats from default via0x566BC0. No destination validation,normalization or aggregate error return; field readers substitute zero after status error.
float *__thiscall rf_binary_stream_read_float4_versioned(int *this, float *a2, int a3, float *a4)
{
  double float_versioned; // st7

  if ( !rf_binary_stream_version_at_least(this, a3) )
    return rf_float4_copy_return_destination(a2, a4);
  *a2 = rf_binary_stream_read_float_versioned(this, 0, 0.0);
  a2[1] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
  a2[2] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
  float_versioned = rf_binary_stream_read_float_versioned(this, 0, 0.0);
  a2[3] = float_versioned;
  return a2;
}

