// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A7700 rf_multiplayer_weapon_fire_omit_pose_for_peer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(shooterEntity,recipientPlayer,weapon,mode LOW BYTE), BOOL indicates omit explicit pose (sender sets packet flag4). NULL shooter or recipient
// ->TRUE. If BYTE663A38!=0 AND signed weapon>=0 AND weapon flag2[weapon*1360] bit0x800 AND weapon!=DWORD911CE0 ->TRUE, with no upper weapon bound. Otherwise mode==EXACT1 without
// flag0x2000 ->FALSE; mode==0 without flag0x1000 ->FALSE; mode values2..255 skip both selector checks. Then resolve recipient entity+20; missing entity ->TRUE. Existing entity:
// ordered distance(shooterPos60,recipientPos60)>=FLOAT662C30 (original12.0) ->TRUE, elseFALSE; unordered ->FALSE. No team/runtime/authority/culling/death checks.
// Negative/out-of-range weapon can reach unchecked flag indexing on selector paths.
BOOL __cdecl rf_multiplayer_weapon_fire_omit_pose_for_peer(int a1, int a2, int a3, char a4)
{
  float *v5; // eax
  float out_vector[3]; // [esp+0h] [ebp-10h] BYREF
  int v7; // [esp+Ch] [ebp-4h]

  if ( !a1 || !a2 )
    return 1;
  if ( byte_663A38 && a3 >= 0 && (rf_weapon_records_flags2[340 * a3] & 0x800) != 0 && a3 != unk_911CE0 )
    return 1;
  if ( a4 == 1 && (rf_weapon_records_flags2[340 * a3] & 0x2000) == 0 )
    return 0;
  if ( !a4 && (rf_weapon_records_flags2[340 * a3] & 0x1000) == 0 )
    return 0;
  v7 = rf_entity_resolve_handle(*(_DWORD *)(a2 + 20));
  if ( !v7 )
    return 1;
  v5 = rf_vector_subtract((const float *)(a1 + 60), out_vector, (const float *)(v7 + 60));
  return flt_662C30 <= rf_vector3_length(v5);
}

