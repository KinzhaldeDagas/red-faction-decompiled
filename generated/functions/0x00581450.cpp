// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581450 rf_camera_outcode_with_special_plane_unmasked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl XYZ pointer,returns byte. Ordered side tests set08 x>z,20 y>z,04 x<-z,10 y<-z. Perspective byte663F39 additionally sets80 for z<=0,02 when far enabled18CD369 and z>scaledFar18CD370,40 when flag18CD384 and special-plane rejection581380 true. Orthographic returns only side bits. Does NOT consult663F38 enable gate,does not emit01,does not modify vertex or apply matrix. Special-plane helper uses supplied XYZ directly with its stored point/normal;no coordinate conversion inserted. Distinct from backend5C5210,which has gate and omits40.
unsigned __int8 __cdecl rf_camera_outcode_with_special_plane_unmasked(const float *a1)
{
  unsigned __int8 v2; // [esp+3h] [ebp-1h]

  v2 = 0;
  if ( a1[2] < (double)*a1 )
    v2 = 8;
  if ( a1[2] < (double)a1[1] )
    v2 |= 0x20u;
  if ( *a1 < -a1[2] )
    v2 |= 4u;
  if ( a1[1] < -a1[2] )
    v2 |= 0x10u;
  if ( byte_663F39 )
  {
    if ( a1[2] <= 0.0 )
      v2 |= 0x80u;
    if ( byte_18CD369 && flt_18CD370 < (double)a1[2] )
      v2 |= 2u;
    if ( dword_18CD384 && rf_clip_special_plane_reject_point((float *)a1) )
      v2 |= 0x40u;
  }
  return v2;
}

