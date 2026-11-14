// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00414EF0 rf_clutter_apply_damage
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Damage handler subtracts scaled damage from common life +0x34 and records lethal damage type at +0x2AC. General clutter lifetime/death update 0x414950 later owns the ordinary corpse timer and source retirement; zero life alone does not remove the common handle.
void __cdecl rf_clutter_apply_damage(int a1, float a2, int a3, int a4, int a5)
{
  float copy_result[3]; // [esp+8h] [ebp-14h] BYREF
  _DWORD *v6; // [esp+14h] [ebp-8h]
  _DWORD *v7; // [esp+18h] [ebp-4h]

  if ( a4 != -1 )
    a2 = a2 * *(float *)(*(_DWORD *)(a1 + 660) + 4 * a4 + 156);
  *(float *)(a1 + 52) = *(float *)(a1 + 52) - a2;
  if ( *(float *)(a1 + 52) <= 0.0
    && (*(_DWORD *)(a1 + 684) = a4, *(_DWORD *)(a1 + 664) == unk_666B64)
    && (v7 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 48))) != nullptr )
  {
    if ( v7[1292] )
    {
      rf_vector_copy((float *)(v7[1292] + 4168), copy_result, (const float *)(v7[1292] + 4120));
      rf_matrix3_copy((float *)(v7[1292] + 4180), (const float *)(v7[1292] + 4084));
      rf_vfx_start_instance((int *)dword_87C6E0, 0, 1.0, 1);
      unk_87C6E4 = 1;
    }
    else
    {
      sub_403C20((int)(v7 + 168), unk_911C80);
      v7[169] = -1;
      v7[1300] = -1;
    }
  }
  else if ( *(_DWORD *)(a1 + 664) == unk_666B64 )
  {
    v6 = sub_4DD720(*(_DWORD *)(a1 + 48));
    if ( v6 )
    {
      if ( rf_player_has_flags16_mask10((int)v6) )
      {
        rf_player_add_riotshield_impact_mesh_decal((int)v6, a1, a5);
        if ( *(float *)(a1 + 52) > 0.0 )
          rf_fpgun_dispatch_semantic_action((int)v6, 0xAu);
      }
    }
  }
}

