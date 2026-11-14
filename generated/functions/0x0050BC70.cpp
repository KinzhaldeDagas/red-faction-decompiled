// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050BC70 rf_projectile_apply_nearby_local_view_impulse
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Shoulder-cannon weapon ID skips all work. Otherwise scans local player entries0..<87C638, resolves each player+20 entity UID. Computes F32 Euclidean squared distance between projectile position+60 and entity position+60; only ORDERED distanceSquared<100 invokes4123F0(player DWORD+196,0.003f,0.75f). Equal100 and NaN skip. Helper resolves its view owner entity and sets entity F32+2228 amplitude, +2232 duration and timestamp+2236; no distance attenuation, LOS/team filter, NULL projectile/entry guard or deduplication. Return EAX is incidental.
int __cdecl rf_projectile_apply_nearby_local_view_impulse(int a1)
{
  int result; // eax
  float out_vector[3]; // [esp+8h] [ebp-1Ch] BYREF
  float v3; // [esp+14h] [ebp-10h]
  int v4; // [esp+18h] [ebp-Ch]
  int v5; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(a1 + 664) != rf_weapon_id_shoulder_cannon )
  {
    for ( i = 0; ; ++i )
    {
      result = i;
      if ( i >= rf_local_player_entry_count )
        break;
      v4 = rf_local_player_entries[i];
      v5 = rf_entity_resolve_handle(*(_DWORD *)(v4 + 20));
      if ( v5 )
      {
        rf_vector_subtract((const float *)(a1 + 60), out_vector, (const float *)(v5 + 60));
        v3 = rf_vector_length_squared(out_vector);
        if ( v3 < 100.0 )
          rf_entity_set_player_linked_perturbation_timer(*(_DWORD *)(v4 + 196), 0.003, 0.75);
      }
    }
  }
  return result;
}

