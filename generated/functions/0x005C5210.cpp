// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5210 rf_camera_frustum_outcode
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Verified enable behavior:if byte663F38==0 returns0;ANY nonzero byte enables ALL ordinary tests,not per-bit result mask. Side bits08 x>z,20 y>z,04 x<-z,10 y<-z. Perspective663F39 adds80 for z<=0 and02 for z>18CD370 when18CD369 enabled. Orthographic only side tests. Ordered strict side/far comparisons accept equality;zero Z sets80. No01/40,no special-plane test or vertex write. Distinct recovered581450 ignores enable gate and can add40.
// [UnrealRed retained room-view state 2026-11-12; full original-byte writer/callee closure] Clip-enable663F38 is a byte BOOLEAN (any nonzero), and581740 writesFF. Do not implement an older mask-bit claim. This is distinct from per-vertex outcodeBYTE24 and polygon clipping admission (which does not process0x80 camera-plane as a generic near plane).
char __cdecl rf_camera_frustum_outcode(float *a1)
{
  char v2; // [esp+3h] [ebp-1h]

  v2 = 0;
  if ( byte_663F38 )
  {
    if ( a1[2] < (double)*a1 )
      v2 = 8;
    if ( a1[2] < (double)a1[1] )
      v2 |= 0x20u;
    if ( *a1 < -a1[2] )
      v2 |= 4u;
    if ( a1[1] < -a1[2] )
      v2 |= 0x10u;
    if ( !byte_663F39 )
      return v2;
    if ( a1[2] <= 0.0 )
      v2 |= 0x80u;
    if ( byte_18CD369 )
    {
      if ( flt_18CD370 < (double)a1[2] )
        return v2 | 2;
    }
  }
  return v2;
}

