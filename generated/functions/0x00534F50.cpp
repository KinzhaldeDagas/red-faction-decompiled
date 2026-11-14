// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00534F50 rf_geomod_face_split_for_corner_limit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Cdecl solid,sourceFace,outA,outB, caller pops16. Choose projected axes from source plane; traverse ring once, compute F32 2D determinant(next-prev,current-prev). A corner is near-collinear only on ORDERED inclusive [-double(float0.0001),+double(float0.0001)]; NaN rejects. Track longest LINEAR consecutive near-collinear run, recording best only on extension to length>=2; equal lengths keep first, and head/tail runs are NOT merged. With best length L>0,start S,countN choose indices(S+L/2)%N and(S+L+(N-L)/2)%N using signed truncating halves; otherwise0,N/2. Locate exact corner pointers, make two24-byte intersection records with shared vertex at0 and other-endpoint4=0; remaining record payload is
// uninitialized/no-op constructed. Invoke split(sourceFace,solid,0,1,recordPointers,outA,outB). If source metadata40 has200000, collect nonnull output faces unequal to source (no dedup) and, if count>0, reclip source decal polygons onto them. Outputs carry fragments; EAX residue is NOT normalized success or a stable fragment pointer. No empty-ring/NULL selected-corner guard, no recursive >16 check or source destruction here. Caller52ACE0 calls only for count>16 then separately removes/destroys source.
int *__cdecl rf_geomod_face_split_for_corner_limit(void *a1, int a2, int *a3, int *a4)
{
  int *result; // eax
  int *v5; // [esp+8h] [ebp-BCh]
  bool v6; // [esp+Ch] [ebp-B8h]
  float v7; // [esp+10h] [ebp-B4h]
  float v8; // [esp+14h] [ebp-B0h]
  float v9; // [esp+18h] [ebp-ACh]
  float v10; // [esp+1Ch] [ebp-A8h]
  int *v11; // [esp+20h] [ebp-A4h]
  int v12; // [esp+24h] [ebp-A0h]
  _DWORD v13[3]; // [esp+28h] [ebp-9Ch] BYREF
  bool v14; // [esp+37h] [ebp-8Dh]
  float v15[2]; // [esp+38h] [ebp-8Ch] BYREF
  float v16; // [esp+40h] [ebp-84h]
  float v17[2]; // [esp+44h] [ebp-80h] BYREF
  int v18; // [esp+4Ch] [ebp-78h]
  int v19; // [esp+50h] [ebp-74h]
  int v20; // [esp+54h] [ebp-70h]
  int v21; // [esp+58h] [ebp-6Ch]
  int v22; // [esp+5Ch] [ebp-68h]
  int v23; // [esp+60h] [ebp-64h] BYREF
  int *i; // [esp+64h] [ebp-60h]
  int v25; // [esp+68h] [ebp-5Ch] BYREF
  int v26; // [esp+6Ch] [ebp-58h]
  int v27; // [esp+70h] [ebp-54h] BYREF
  _DWORD *v28; // [esp+74h] [ebp-50h]
  _DWORD v29[2]; // [esp+78h] [ebp-4Ch] BYREF
  int v30; // [esp+80h] [ebp-44h]
  _DWORD *v31; // [esp+84h] [ebp-40h]
  int v32; // [esp+88h] [ebp-3Ch]
  _DWORD v33[6]; // [esp+8Ch] [ebp-38h] BYREF
  _DWORD v34[6]; // [esp+A4h] [ebp-20h] BYREF
  int v35; // [esp+BCh] [ebp-8h]
  int v36; // [esp+C0h] [ebp-4h]

  rf_face_projection_axes_select((float *)a2, &v27, &v23, &v25);
  v32 = 0;
  v35 = -1;
  v26 = -1;
  v21 = -1;
  v36 = -1;
  for ( i = *(int **)(a2 + 64); i; i = v11 )
  {
    v19 = *(_DWORD *)i[6];
    v20 = *i;
    v18 = *(_DWORD *)i[5];
    v10 = *(float *)(v18 + 4 * v25) - *(float *)(v19 + 4 * v25);
    v9 = *(float *)(v18 + 4 * v23) - *(float *)(v19 + 4 * v23);
    rf_vector2_assign_components(v17, v9, v10);
    v8 = *(float *)(v20 + 4 * v25) - *(float *)(v19 + 4 * v25);
    v7 = *(float *)(v20 + 4 * v23) - *(float *)(v19 + 4 * v23);
    rf_vector2_assign_components(v15, v7, v8);
    v16 = v17[0] * v15[1] - v15[0] * v17[1];
    v6 = v16 >= -0.00009999999747378752 && v16 <= 0.00009999999747378752;
    v14 = v6;
    if ( v6 )
    {
      if ( v21 >= 0 )
      {
        if ( ++v36 > v26 )
        {
          v35 = v21;
          v26 = v36;
        }
      }
      else
      {
        v21 = v32;
        v36 = 1;
      }
    }
    else if ( v21 > -1 )
    {
      v21 = -1;
    }
    ++v32;
    if ( i[5] == *(_DWORD *)(a2 + 64) )
      v11 = nullptr;
    else
      v11 = (int *)i[5];
  }
  if ( v26 <= 0 )
  {
    v30 = 0;
    v22 = v32 / 2;
  }
  else
  {
    v30 = (v35 + v26 / 2) % v32;
    v13[2] = v32 - v26;
    v22 = (v26 + v35 + (v32 - v26) / 2) % v32;
  }
  v31 = nullptr;
  v28 = nullptr;
  v32 = 0;
  for ( i = *(int **)(a2 + 64); i; i = v5 )
  {
    if ( v30 == v32 )
      v31 = i;
    if ( v22 == v32 )
      v28 = i;
    ++v32;
    if ( i[5] == *(_DWORD *)(a2 + 64) )
      v5 = nullptr;
    else
      v5 = (int *)i[5];
  }
  rf_vector_construct_no_unwind(
    (char *)v33,
    0x18u,
    2,
    (void *(__thiscall *)(void *))rf_geomod_intersection24_construct_noop);
  v29[0] = v33;
  v29[1] = v34;
  v33[0] = *v31;
  v33[1] = 0;
  v34[0] = *v28;
  v34[1] = 0;
  rf_geomod_face_split_between_intersection_vertices(a2, a1, 0, 1, (int)v29, a3, a4);
  result = (int *)(*(_DWORD *)(a2 + 40) & 0x200000);
  if ( result )
  {
    v12 = 0;
    if ( *a3 )
    {
      result = (int *)*a3;
      if ( *a3 != a2 )
      {
        result = (int *)*a3;
        v13[0] = *a3;
        v12 = 1;
      }
    }
    if ( *a4 )
    {
      result = a4;
      if ( *a4 != a2 )
      {
        result = a4;
        v13[v12++] = *a4;
      }
    }
    if ( v12 > 0 )
      return rf_geomod_face_decal_polygons_replace_after_split((_DWORD *)a2, (int)v13, v12);
  }
  return result;
}

