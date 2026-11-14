// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FBC0 rf_binary_stream_read_matrix3_vectors_201_versioned
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination36-byte matrix,minimum version,default matrix. Version allowed reads three12-byte vectors in FILE ORDER destination+24,then+0,then+12,using vector helper minimum0 and global default0x1C8FBDC. Stream is ECX even when caller pseudocode hides it. Version absent calls matrix3 copy with default. No row/column transposition beyond stated vector ordering,normalization or aggregate status return. Return is last helper result,not read count.
int __thiscall rf_binary_stream_read_matrix3_vectors_201_versioned(_DWORD *this, float *a2, int a3, float *a4)
{
  if ( !rf_binary_stream_version_at_least(this, a3) )
    return rf_matrix3_copy(a2, a4);
  rf_binary_stream_read_vector3_versioned(this, a2 + 6, 0, unk_1C8FBDC);
  rf_binary_stream_read_vector3_versioned(this, a2, 0, unk_1C8FBDC);
  return rf_binary_stream_read_vector3_versioned(this, a2 + 3, 0, unk_1C8FBDC);
}

