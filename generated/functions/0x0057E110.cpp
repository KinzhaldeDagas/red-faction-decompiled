// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E110 rf_binary_stream_read_orientation
// UNREALRED VERIFIED [mission-mover-geometry-20261013] Serialized orientation reads first vector into matrix row +0x18, second into +0x00, third into +0x0C. Thus serialized forward/right/up becomes runtime right/up/forward rows. Together with row-vector multiplication at 0x559540, solid-local X follows right, Y follows up, Z follows forward. For UE coordinates (x,-z,y), conjugated pose axes are converted right, negative converted forward, converted up. A character-facing rotator is not a solid-local basis.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Adapter mode0 forwards output,minversion,defaultmatrix to file matrix reader. Memory older-version branch copies supplied3x3 default without consuming. Accepted branch calls vector reader three times, destinations matrix+24,+0,+12, with min0/global vector default; no aggregate36-byte bounds check or rollback. Return is final vector-reader register, not necessarily matrix base. Preserves existing verified orientation-layout comment; this is a file-or-memory adapter, not a raw stream object.
float *__thiscall rf_binary_stream_read_orientation(void *this, float *a2, int a3, const float *a4)
{
  if ( !*(_DWORD *)this )
    return (float *)rf_binary_stream_read_matrix3_vectors_201_versioned((char *)a2, a3, (int)a4);
  if ( *((_DWORD *)this + 20) < a3 )
    return (float *)rf_matrix3_copy(a2, a4);
  rf_stream_adapter_read_vector3_versioned(this, a2 + 6, 0, unk_1C8FBDC);
  rf_stream_adapter_read_vector3_versioned(this, a2, 0, unk_1C8FBDC);
  return rf_stream_adapter_read_vector3_versioned(this, a2 + 3, 0, unk_1C8FBDC);
}

