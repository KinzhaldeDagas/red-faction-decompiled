// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CFF0 rf_solid_mark_face_lightmap_near_point
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl point3f,margin,solid,face;4 stack DWORDs. Signed face lightmap indexWORD54<0 skips. Otherwise unchecked solid descriptor-array192[index] pointer;ANY nonzero descriptor flagsBYTE8 skips. With flags0,forms local min=face AABB16 minus margin per axis,max=face AABB28 plus margin,uses inclusive AABB predicate;if inside writes ENTIRE descriptor BYTE8=1. Does not mark material/face flags or OR other bits,calculate Euclidean distance,validate positive index/descriptor pointers or handle negative-margin bound inversion. Known direct callers ignore EAX/AL;old int/char residues were not a boolean return. Corrected effects-only void signature and pointer
// arguments;caller-pop16-byte ABI unchanged.
void __cdecl rf_solid_mark_face_lightmap_near_point(const float *query_point, float margin, void *solid, void *face)
{
  float *v4; // eax
  float *v5; // eax
  float v6[3]; // [esp+4h] [ebp-58h] BYREF
  int v7[3]; // [esp+10h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-40h] BYREF
  int v9[3]; // [esp+28h] [ebp-34h] BYREF
  float v10[3]; // [esp+34h] [ebp-28h] BYREF
  float destination[3]; // [esp+40h] [ebp-1Ch] BYREF
  _BYTE v12[12]; // [esp+4Ch] [ebp-10h] BYREF
  int v13; // [esp+58h] [ebp-4h]

  if ( *((__int16 *)face + 27) >= 0 )
  {
    v13 = *(_DWORD *)sub_552200((_DWORD *)solid + 48, *((__int16 *)face + 27));
    if ( !*(_BYTE *)(v13 + 8) )
    {
      rf_vector3_default_construct_noop(destination);
      rf_vector3_default_construct_noop(v10);
      rf_vector3_default_construct_noop(v12);
      v4 = rf_vector3_subtract_scalar_from_components((float *)face + 4, (float *)v9, margin);
      rf_vector_copy(destination, copy_result, v4);
      v5 = rf_vector3_add_scalar_to_components((float *)face + 7, (float *)v7, margin);
      rf_vector_copy(v10, v6, v5);
      if ( rf_aabb_contains_point_inclusive((float *)query_point, destination, v10) )
        *(_BYTE *)(v13 + 8) = 1;
    }
  }
}

