// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00407CF0 rf_ai_primary_range_target_gate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): ABI corrected: cdecl ONE required AI-block pointer, explicit AL0/1 bool, NO incoming ST0. Require BYTE+668
// or+669 any nonzero OR flags DWORD+1328 mask0x1000. Resolve ENTITY target full handle+704; missAL0. Computes Euclidean distance between owner and target COMMON positions+60,
// roundsfloat32; calls primary attack-range resolver(block,1) returning its own ST0 value, loads saved distance and FCOMPP. ReturnsAL0 ONLY when ordered distance>range.
// Distance<=range OR UNORDERED returnsAL1. No zeroing flags, timer admission, distance clamp or own class/role test. Old usercall(double@ST0,int) and inferred void pseudocode lost
// the native comparison/result.
bool __cdecl rf_ai_primary_range_target_gate(int a1)
{
  float v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  if ( !*(_BYTE *)(a1 + 668) && !*(_BYTE *)(a1 + 669) && (*(_DWORD *)(a1 + 1328) & 0x1000) == 0 )
    return 0;
  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 704));
  if ( !v3 )
    return 0;
  v2 = rf_vector_distance((const float *)(*(_DWORD *)a1 + 60), (const float *)(v3 + 60));
  return v2 <= rf_ai_resolve_attack_range(a1, 1);
}

