// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FC30 rf_binary_stream_read_transposed12_floats_with_overwrites
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination,minimum version,default48-byte block. Version absent copies exactly48 bytes through0x43C8F0. Version present reads12 floats(minimum0/default0) into FLOAT INDEX ORDER0,3,6,1,4,7,2,5,8,9,10,11. THEN overwrites indices3,6,9 with0 and writes index12=1 (byte+48),so present path writes52 bytes and discards3 values just read. Does not initialize indices13..15. This is literal assembly behavior,not an assumed conventional4x4 layout or inverse of writer0x5A07C0. No bounds or aggregate status check; caller storage must cover the extra write.
void __thiscall rf_binary_stream_read_transposed12_floats_with_overwrites(int *this, float *a2, int a3, const void *a4)
{
  if ( rf_binary_stream_version_at_least(this, a3) )
  {
    *a2 = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[3] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[6] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[1] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[4] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[7] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[2] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[5] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[8] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[9] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[10] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[11] = rf_binary_stream_read_float_versioned(this, 0, 0.0);
    a2[3] = 0.0;
    a2[6] = 0.0;
    a2[9] = 0.0;
    a2[12] = 1.0;
  }
  else
  {
    rf_fixed_block48_copy(a2, a4);
  }
}

