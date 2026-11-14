// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445AF0 rf_entity_filter_rotation_axes_for_body
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl(outVector,entity,inputVector),three stackargs. Copies input into local vector;independently zeroes XYZ only if current descriptor2136 DWORD20/24/28 is EXACTLY0 OR1. Any other32-bit selector,including negative,retains component;decompiler unsigned<=1 is equivalent to native equality checks,not a signed<=1 rule. Copies complete local toout,returns outVectorEAX;exact alias with input safe. No rotation or angle clamp;no NULL/descriptor/finite guard.
// UNREALRED VERIFIED [combat-signed-rotation-20261112]: Body-axis selector retains input component only when corresponding descriptor rotation selector20/24/28 is NEITHER exact0 NOR exact1. Negative/raw unknown selector integers are not clamped to table range in this helper.
float *__cdecl rf_entity_filter_rotation_axes_for_body(float *a1, int a2, float *a3)
{
  float v4[3]; // [esp+0h] [ebp-Ch] BYREF

  rf_vector3_copy_return_destination(v4, a3);
  if ( *(_DWORD *)(*(_DWORD *)(a2 + 2136) + 20) <= 1u )
    v4[0] = 0.0;
  if ( *(_DWORD *)(*(_DWORD *)(a2 + 2136) + 24) <= 1u )
    v4[1] = 0.0;
  if ( *(_DWORD *)(*(_DWORD *)(a2 + 2136) + 28) <= 1u )
    v4[2] = 0.0;
  rf_vector3_copy_return_destination(a1, v4);
  return a1;
}

