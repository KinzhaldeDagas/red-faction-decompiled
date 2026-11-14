// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445BC0 rf_entity_filter_rotation_axes_for_view_offset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl(outVector,entity,inputVector),three stackargs. Independently retains input XYZ only when corresponding current descriptor2136 DWORD20/24/28 is EXACTLY1,otherwise writes0. Constructor is no-op but all three local components assigned. Copies local toout,returns outVectorEAX;out may aliasinput. Does not rotate,clamp or preserve selectors other than1;no pointer/descriptor validation.
// UNREALRED VERIFIED [combat-signed-rotation-20261112]: View-offset-axis selector retains input component only when corresponding descriptor rotation selector20/24/28 is EXACT1; all other integers producefloat0. This is separate from body selector445AF0 and native current/view matrices cannot collapse into one UE quaternion.
float *__cdecl rf_entity_filter_rotation_axes_for_view_offset(float *a1, int a2, float *a3)
{
  float v4; // [esp+Ch] [ebp-Ch] BYREF
  float v5; // [esp+10h] [ebp-8h]
  float v6; // [esp+14h] [ebp-4h]

  rf_vector3_default_construct_noop(&v4);
  if ( *(_DWORD *)(*(_DWORD *)(a2 + 2136) + 20) == 1 )
    v4 = *a3;
  else
    v4 = 0.0;
  if ( *(_DWORD *)(*(_DWORD *)(a2 + 2136) + 24) == 1 )
    v5 = a3[1];
  else
    v5 = 0.0;
  if ( *(_DWORD *)(*(_DWORD *)(a2 + 2136) + 28) == 1 )
    v6 = a3[2];
  else
    v6 = 0.0;
  rf_vector3_copy_return_destination(a1, &v4);
  return a1;
}

