// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402C70 rf_ai_choose_maximum_segment_residual_point
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(required AI block,outCandidate vector). Starts float32 bestScore=0 and snapshots owner COMMON
// position+60. Resolves retained full target handle block+704 as COMMON object; miss returnsAL0 WITHOUT writing caller output. Copies target COMMON position+60 once. Signed loop i=0
// while i<DWORD6663F8, re-reading count, visits contiguous12-byte point6665D8+12*i with no own count cap. Copies each ORIGINAL candidate to local, calls402BA0(P=target
// position,A=owner position,B=candidate,out=local projection). Rounds returned squared residual float32; only ORDERED bestScore<newScore updates bestScore and copies ORIGINAL
// candidate into caller output. Projected point is ignored, no route/visibility test. Strict ties retain earlier candidate; score0,negative or NaN never replaces initial0, so no
// output write if all fail or count<=0. Final AL predicate is literal unordered-or-not-equal-to-zero on bestScore; because stored best changes only on ordered increases from0,
// ordinary flow returns1 for a winning positive score and0 otherwise. No output preinitialization, field/target mutation, closest-point copy, random selection or independent upper
// bound. Caller output may retain prior data on failure.
bool __cdecl rf_ai_choose_maximum_segment_residual_point(_DWORD *a1, float *a2)
{
  float v3[3]; // [esp+4h] [ebp-58h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-4Ch] BYREF
  float v5[3]; // [esp+1Ch] [ebp-40h] BYREF
  float source[3]; // [esp+28h] [ebp-34h] BYREF
  float v7; // [esp+34h] [ebp-28h]
  int i; // [esp+38h] [ebp-24h]
  float destination[3]; // [esp+3Ch] [ebp-20h] BYREF
  int v10; // [esp+48h] [ebp-14h]
  float v11[3]; // [esp+4Ch] [ebp-10h] BYREF
  float v12; // [esp+58h] [ebp-4h]

  v12 = 0.0;
  rf_vector3_copy_return_destination(v11, (float *)(*a1 + 60));
  rf_vector3_default_construct_noop(destination);
  v10 = rf_object_resolve_handle(a1[176]);
  if ( !v10 )
    return 0;
  rf_vector_copy(destination, copy_result, (const float *)(v10 + 60));
  for ( i = 0; i < dword_6663F8; ++i )
  {
    rf_vector3_copy_return_destination(source, &flt_6665D8[3 * i]);
    rf_vector3_default_construct_noop(v5);
    v7 = rf_point_segment_residual_squared_xy_projection(destination, v11, source, v5);
    if ( v12 < (double)v7 )
    {
      v12 = v7;
      rf_vector_copy(a2, v3, source);
    }
  }
  return v12 != 0.0;
}

