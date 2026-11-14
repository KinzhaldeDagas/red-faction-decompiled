// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005962A0 rf_scene_point_pool_allocate_type0
// UNREALRED VERIFIED [transfer-scene-20261028]: Arguments position pointer followed by6 scalar floats. Scans50 records at0x1BC2160 stride140 for signed BYTE+0=-1; none returns-1. Copies3 floats position to+20; sets BYTE+60=1, scalar+64=arg3,+68=arg4, BYTE+0=0,+44=arg2,+32=arg5,+36=arg6,+40=arg7. Returns index. Does not initialize other fields or validate pointer/scalars. Scalar semantic units are not established by this routine.
int __cdecl rf_scene_point_pool_allocate_type0(
        float *source,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7)
{
  float copy_result[3]; // [esp+0h] [ebp-10h] BYREF
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < 50 && unk_1BC2160[140 * i] != -1; ++i )
    ;
  if ( i >= 50 )
    return -1;
  rf_vector_copy((float *)&unk_1BC2174 + 35 * i, copy_result, source);
  unk_1BC219C[140 * i] = 1;
  *((float *)&unk_1BC21A0 + 35 * i) = a3;
  unk_1BC21A4[35 * i] = a4;
  unk_1BC2160[140 * i] = 0;
  *((float *)&unk_1BC218C + 35 * i) = a2;
  *((float *)&unk_1BC2180 + 35 * i) = a5;
  *((float *)&unk_1BC2184 + 35 * i) = a6;
  *((float *)&unk_1BC2188 + 35 * i) = a7;
  return i;
}

