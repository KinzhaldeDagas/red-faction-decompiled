// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DB840 rf_segment_find_first_collidable_model_fraction
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl segment start,end,output fraction. Constructs unused query/result locals, then traverses clutter head/sentinel666D18, entity68211C/sentinel681E90, corpse head/sentinel681AF8 in that order, next link652. For each calls object-model hit helper; first nonzero hit returnsAL1 immediately. Otherwise returns0 and leaves fraction untouched. Does not scan for minimum fraction or clear incoming output; no cycle guards or own segment/output NULL checks.
char __cdecl rf_segment_find_first_collidable_model_fraction(int a1, int a2, float *a3)
{
  _BYTE v4[40]; // [esp+0h] [ebp-13Ch] BYREF
  int j; // [esp+28h] [ebp-114h]
  char v6[116]; // [esp+2Ch] [ebp-110h] BYREF
  _BYTE v7[32]; // [esp+A0h] [ebp-9Ch] BYREF
  int k; // [esp+C0h] [ebp-7Ch]
  char v9[104]; // [esp+C4h] [ebp-78h] BYREF
  _BYTE v10[12]; // [esp+12Ch] [ebp-10h] BYREF
  int i; // [esp+138h] [ebp-4h]

  rf_solid_collision_query_construct_clear_face_hint(v6);
  rf_solid_collision_result_construct_noop((int)v4);
  rf_model_collision_query_construct_noop(v9);
  rf_model_collision_result_construct_noop((int)v7);
  rf_vector3_default_construct_noop(v10);
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( rf_object_segment_model_hit_fraction(i, a1, a2, a3) )
      return 1;
  }
  for ( j = dword_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
  {
    if ( rf_object_segment_model_hit_fraction(j, a1, a2, a3) )
      return 1;
  }
  for ( k = rf_corpse_list_head; (_UNKNOWN *)k != &unk_681AF8; k = *(_DWORD *)(k + 652) )
  {
    if ( rf_object_segment_model_hit_fraction(k, a1, a2, a3) )
      return 1;
  }
  return 0;
}

