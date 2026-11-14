// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401260 rf_ai_try_deferred_nearby_route
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(AI block,ignored DWORD,point pointer), explicit AL0/1. No own pointer guards. Euclidean
// length(point-owner COMMON position+60) must be ordered strictly<DOUBLE20; equality/NaN reject. Route-build(owner full handle+44,point) any nonzero AL required. Then Euclidean
// length(AI vector+896-point) ordered strictly<DOUBLE1.5 required. This second rejection happens AFTER route-builder side effects and does not reset installed route. Success
// calls40ECE0 with native stack(route=block+744,extra1), cleans8, IGNORES returnedEAX and returnsAL1. Callee body never reads second input DWORD at[ebp+0xC], even though deferred
// producer stores it. No timer/mode write or rollback in this body; failed builder or either distance gate returnsAL0.
char __cdecl rf_ai_try_deferred_nearby_route(int *a1, int a2, const float *lhs)
{
  float *v3; // eax
  float *v4; // eax
  float v6[3]; // [esp+0h] [ebp-1Ch] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-10h] BYREF
  int v8; // [esp+18h] [ebp-4h]

  v8 = *a1;
  v3 = rf_vector_subtract(lhs, out_vector, (const float *)(v8 + 60));
  if ( rf_vector3_length(v3) >= 20.0 )
    return 0;
  if ( !rf_ai_route_build(*(_DWORD *)(*a1 + 44), (int)lhs) )
    return 0;
  v4 = rf_vector_subtract((const float *)a1 + 224, v6, lhs);
  if ( rf_vector3_length(v4) >= 1.5 )
    return 0;
  rf_ai_route_update((int)(a1 + 186));
  return 1;
}

