// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B11F0 rf_segment_bounds_build
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Cdecl four pointers(outMin,outMax,endpointA,endpointB),16-byte caller cleanup. For X thenY thenZ compares B vsA; ordered B>A stores A toMin thenB toMax,otherwise stores B toMin thenA toMax. Equality uses B/A branch. Raw x87 TEST AH,41h/JNZ also sends UNORDERED to B/A branch; no NaN rejection or IEEE fmin/fmax special handling. Each output store occurs BEFORE subsequent source read for corresponding maximum: NOT universally safe when outputs alias endpoint buffers. No temp snapshot,pointer/size/overlap guard. Stored float* return is incidental EAX: finalZ B/A branch returns endpointB pointer,ordered B>A branch returns outMax. No uniform returned-bounds contract.
float *__cdecl rf_segment_bounds_build(float *a1, float *a2, float *a3, float *a4)
{
  if ( *a4 <= (double)*a3 )
  {
    *a1 = *a4;
    *a2 = *a3;
  }
  else
  {
    *a1 = *a3;
    *a2 = *a4;
  }
  if ( a4[1] <= (double)a3[1] )
  {
    a1[1] = a4[1];
    a2[1] = a3[1];
  }
  else
  {
    a1[1] = a3[1];
    a2[1] = a4[1];
  }
  if ( a4[2] <= (double)a3[2] )
  {
    a1[2] = a4[2];
    a2[2] = a3[2];
    return a4;
  }
  else
  {
    a1[2] = a3[2];
    a2[2] = a4[2];
    return a2;
  }
}

