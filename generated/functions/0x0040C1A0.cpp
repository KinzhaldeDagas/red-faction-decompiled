// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040C1A0 rf_ai_restore_saved_parent_slot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One required AI block. Finds common object by saved identifier block+1200; missing returns. Resolves found handle+44 to ENTITY then immediately
// accesses its pointer registry+2252 without a second null guard. Signed slot count<=0 returns without restore. Source owner player predicate AL==EXACT1: use node record0 DWORD0,
// copy target class(+660) vectors+108/+120 to target+5172/+5184. Other sources choose record0 if count<=1 OR target is use-vehicle, else record1; set ONLY FLOAT target+5172 and+5184
// to0, preserving remaining two components of each vector. Invokes434200 with ECX=target, two stack args(source owner handle+44,node key). Calls numeric mode13(block,-1,-1), then
// target AI+672 mode2(-1,-1) unless target DWORD+2068 mask0x4000. Mode helper may remap2 under runtime/splitscreen. Finally OR target DWORD+2064 mask0x10000. Does not check
// association helper success, validate node-record pointers or clear saved identifier. Native EAX path-dependent (resolverNULL/count/target pointer), not a uniform pointer-success
// result.
float *__cdecl rf_ai_restore_saved_parent_slot(int *a1)
{
  float *result; // eax
  float v2[3]; // [esp+0h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-18h] BYREF
  float *v4; // [esp+18h] [ebp-Ch]
  int v5; // [esp+1Ch] [ebp-8h]
  int v6; // [esp+20h] [ebp-4h]

  result = (float *)rf_object_find_by_saved_identifier(a1[300]);
  v5 = (int)result;
  if ( result )
  {
    v4 = (float *)rf_entity_resolve_handle(*(_DWORD *)(v5 + 44));
    v6 = -1;
    result = (float *)rf_receiver_get_first_dword(v4 + 563);
    if ( (int)result > 0 )
    {
      if ( rf_object_has_player_flag(*a1) )
      {
        v6 = **(_DWORD **)sub_552200((_DWORD *)v4 + 563, 0);
        rf_vector_copy(v4 + 1293, copy_result, (const float *)(*((_DWORD *)v4 + 165) + 108));
        rf_vector_copy(v4 + 1296, v2, (const float *)(*((_DWORD *)v4 + 165) + 120));
      }
      else
      {
        if ( rf_receiver_get_first_dword(v4 + 563) <= 1 || rf_object_is_use_vehicle(v4) )
          v6 = **(_DWORD **)sub_552200((_DWORD *)v4 + 563, 0);
        else
          v6 = **(_DWORD **)sub_552200((_DWORD *)v4 + 563, 1);
        v4[1293] = 0.0;
        v4[1296] = 0.0;
      }
      rf_entity_associate_child_with_last_slot_key((int)v4, *(_DWORD *)(*a1 + 44), v6);
      rf_ai_numeric_mode_write(a1, 13, -1, -1);
      if ( ((_DWORD)v4[517] & 0x4000) == 0 )
        rf_ai_numeric_mode_write((_DWORD *)v4 + 168, 2, -1, -1);
      result = v4;
      *((_DWORD *)v4 + 516) |= 0x10000u;
    }
  }
  return result;
}

