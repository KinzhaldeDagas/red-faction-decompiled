// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005337E0 rf_geomod_face_contains_projected_point
// UNREALRED VERIFIED [combat-native-planes-20261104]: Ordered projected odd-even test has half-open vertical edge admission and strict horizontal comparison. It does not automatically admit near-boundary points. The separate positive-distance boundary check in535BF0 can request a retry only after nearest-candidate and finite-containment admission.
bool __thiscall rf_geomod_face_contains_projected_point(float *this, char *a2)
{
  int v3; // [esp+0h] [ebp-34h]
  float v5; // [esp+8h] [ebp-2Ch]
  float v6; // [esp+Ch] [ebp-28h]
  int v7; // [esp+10h] [ebp-24h] BYREF
  bool v8; // [esp+17h] [ebp-1Dh]
  int v9; // [esp+18h] [ebp-1Ch]
  int v10; // [esp+1Ch] [ebp-18h] BYREF
  int v11; // [esp+20h] [ebp-14h] BYREF
  float v12; // [esp+24h] [ebp-10h]
  float v13; // [esp+28h] [ebp-Ch]
  float v14; // [esp+2Ch] [ebp-8h]
  float v15; // [esp+30h] [ebp-4h]

  rf_face_projection_axes_select(this, &v11, &v7, &v10);
  v14 = *(float *)rf_vector_component_address_unchecked(a2, v7);
  v15 = *(float *)rf_vector_component_address_unchecked(a2, v10);
  v8 = 0;
  v9 = *((_DWORD *)this + 16);
  v12 = *(float *)rf_vector_component_address_unchecked(**(char ***)(v9 + 24), v7);
  v13 = *(float *)rf_vector_component_address_unchecked(**(char ***)(v9 + 24), v10);
  while ( v9 )
  {
    v5 = *(float *)rf_vector_component_address_unchecked(*(char **)v9, v7);
    v6 = *(float *)rf_vector_component_address_unchecked(*(char **)v9, v10);
    if ( (v15 >= (double)v6 && v13 > (double)v15 || v15 >= (double)v13 && v6 > (double)v15)
      && v14 < (v12 - v5) * (v15 - v6) / (v13 - v6) + v5 )
    {
      v8 = !v8;
    }
    v12 = v5;
    v13 = v6;
    if ( *(_DWORD *)(v9 + 20) == *((_DWORD *)this + 16) )
      v3 = 0;
    else
      v3 = *(_DWORD *)(v9 + 20);
    v9 = v3;
  }
  return v8;
}

