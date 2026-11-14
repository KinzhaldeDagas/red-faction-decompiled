// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005138E0 rf_projected_shadows_submit_room
// VERIFIED: Per-room projected-shadow submission. It is option-gated, walks two runtime entity registries with distinct eligibility flags, requires the submitted room argument to match, computes view-distance fade, then submits the projector.
// UNREALRED VERIFIED [general-gap-20260830]: Option-gated per-room projected-shadow submission: walks two entity registries, applies their distinct eligibility flags and room match, computes view fade, then submits accepted projectors.
int __cdecl rf_projected_shadows_submit_room(int a1)
{
  int result; // eax
  int v2; // [esp+8h] [ebp-4Ch] BYREF
  _DWORD *i; // [esp+Ch] [ebp-48h]
  char v4[60]; // [esp+10h] [ebp-44h] BYREF
  float v5; // [esp+4Ch] [ebp-8h] BYREF
  _DWORD *j; // [esp+50h] [ebp-4h]

  rf_embedded_vector12_matrix24_construct_noop(v4);
  result = (unsigned __int8)rf_projected_shadows_enabled;
  if ( rf_projected_shadows_enabled )
  {
    for ( i = (_DWORD *)dword_68211C; i != (_DWORD *)&unk_681E90 && rf_projected_shadow_work_count < 8; i = (_DWORD *)result )
    {
      if ( !sub_438AC0((int)i)
        && (i[31] & 0x10) != 0
        && !rf_object_has_respawn_inactive_flag((int)i)
        && rf_entity_has_humanoid_flag((int)i)
        && (i[517] & 2) == 0
        && i[1313] == -1
        && rf_receiver_get_first_dword(i) == a1 )
      {
        if ( rf_projected_shadow_compute_view_fade((int)i, &v5, &v2) )
        {
          rf_projected_shadow_build_entity_packet((int)i, (int)v4);
          rf_projected_shadow_build_and_submit(a1, (int)v4, v5, v2);
        }
      }
      result = i[163];
    }
    for ( j = (_DWORD *)rf_corpse_list_head;
          j != (_DWORD *)&unk_681AF8 && rf_projected_shadow_work_count < 8;
          j = (_DWORD *)j[163] )
    {
      if ( (j[167] & 0x10) == 0
        && (j[167] & 0x80) != 0
        && j[184]
        && rf_receiver_get_first_dword(j) == a1
        && rf_projected_shadow_compute_view_fade((int)j, &v5, &v2) )
      {
        rf_projected_shadow_build_and_submit(a1, (int)(j + 183), v5, v2);
      }
      result = (int)j;
    }
  }
  return result;
}

