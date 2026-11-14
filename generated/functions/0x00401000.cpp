// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401000 rf_ai_copy_route_target_position
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): Cdecl(AI block,output vector), explicit AL0/1. Null block or unresolved COMMON target full handle+704 returns0
// leaving output untouched. Otherwise copies target COMMON position+60 first. If target-is-entity EXACT AL1, owner437F60 EXACT1 (descriptor category12/15/13/11/9), target437EC0
// EXACT1 (descriptor1 and speed mode1), and target FLOAT+1988 ordered<AI FLOAT+1316, adds (AI+1316-target+1988)*DOUBLE0.5 to output.Y with final float32 store; no extra intermediate
// float store. Equal/unordered does not adjust. Returns1 on every resolved target even if no adjustment; no output null guard, further type resolution, geometry/route query or
// independent finite admission.
char __cdecl rf_ai_copy_route_target_position(int a1, float *destination)
{
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v4; // [esp+Ch] [ebp-8h]
  int v5; // [esp+10h] [ebp-4h]

  if ( !a1 )
    return 0;
  v5 = rf_object_resolve_handle(*(_DWORD *)(a1 + 704));
  if ( !v5 )
    return 0;
  rf_vector_copy(destination, copy_result, (const float *)(v5 + 60));
  if ( rf_object_is_entity(v5) )
  {
    v4 = v5;
    if ( rf_entity_descriptor_mode_is_12_15_13_11_or9(*(_DWORD *)a1)
      && rf_entity_descriptor_mode1_and_speedmode1(v4)
      && *(float *)(v4 + 1988) < (double)*(float *)(a1 + 1316) )
    {
      destination[1] = (*(float *)(a1 + 1316) - *(float *)(v4 + 1988)) * 0.5 + destination[1];
    }
  }
  return 1;
}

