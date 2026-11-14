// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005307A0 rf_geomod_face_area
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall face, plainRET x87 float-rounded SIGNED projected area. Anchor first corner64, iterate fan triangles(anchor,current,next) from second corner until next returns anchor. Compute F32 vectors current-anchor and next-anchor, cross, accumulate each component with F32 stores; dot accumulated cross-sum with stored face normalXYZ0, roundF32, divide by double2 then roundF32/reloadST0. NO abs or normal normalization; magnitude scales with supplied normal and winding can produce negative/cancelled area. Does not sum absolute triangle areas or reject a degenerate first triangle. Empty/one-corner rings dereference missing corners during fan setup; two-corner ring produces zero. No
// geometry mutation or coplanarity test.
double __thiscall rf_geomod_face_area(float *this)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  int v7; // [esp+14h] [ebp-78h]
  int v8; // [esp+18h] [ebp-74h]
  float v10[3]; // [esp+20h] [ebp-6Ch] BYREF
  float v11[3]; // [esp+2Ch] [ebp-60h] BYREF
  float v12[3]; // [esp+38h] [ebp-54h] BYREF
  float copy_result[3]; // [esp+44h] [ebp-48h] BYREF
  float out_vector[3]; // [esp+50h] [ebp-3Ch] BYREF
  float v15[3]; // [esp+5Ch] [ebp-30h] BYREF
  float destination[3]; // [esp+68h] [ebp-24h] BYREF
  float v17; // [esp+74h] [ebp-18h]
  int i; // [esp+78h] [ebp-14h]
  float v19[3]; // [esp+7Ch] [ebp-10h] BYREF
  int v20; // [esp+88h] [ebp-4h]

  rf_vector3_set_components_return_destination(v19, 0.0, 0.0, 0.0);
  v20 = *((_DWORD *)this + 16);
  if ( *(_DWORD *)(v20 + 20) == *((_DWORD *)this + 16) )
    v8 = 0;
  else
    v8 = *(_DWORD *)(v20 + 20);
  for ( i = v8; *(_DWORD *)(i + 20) == *((_DWORD *)this + 16) ? 0 : *(_DWORD *)(i + 20); i = v7 )
  {
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v15);
    v1 = rf_vector_subtract(*(const float **)i, out_vector, *(const float **)v20);
    rf_vector_copy(destination, copy_result, v1);
    v2 = rf_vector_subtract(**(const float ***)(i + 20), v12, *(const float **)v20);
    rf_vector_copy(v15, v11, v2);
    v3 = rf_vector_cross(destination, v10, v15);
    rf_vector_accumulate(v19, v3);
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)this + 16) )
      v7 = 0;
    else
      v7 = *(_DWORD *)(i + 20);
  }
  v17 = rf_vector_dot(this, v19);
  return (float)(v17 / 2.0);
}

