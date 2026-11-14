// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A1D90 rf_multiplayer_apply_item_active_bitmap_payload37
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(payload). No own runtime/authority/payload-null/length guard or incoming xrefs currently; opcode37 association follows exact25-byte paired encoding. Copies25 bytes into
// borrowed200-bit bitset, then processes ALL200 slots regardless runtime count78C248. Skips signed-negative handles78BF28[slot] and unresolved items. Set bit invokes
// object_respawn_apply (delegate handles inactive admission/sound). Clear bit plays item pickup sound only if currently active, then always marks hidden/inactive. Does not translate
// handles or allocate objects; destroys borrowed bitset with SEH cleanup. This is indexed item visibility/reactivation synchronization, not player-body spawning.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662B04 registers opcode37 (item_update), callback0x004A1D90. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
int __cdecl rf_multiplayer_apply_item_active_bitmap_payload37(int a1)
{
  int v2; // [esp+4h] [ebp-48h]
  int i; // [esp+8h] [ebp-44h]
  _BYTE v4[28]; // [esp+Ch] [ebp-40h] BYREF
  int j; // [esp+2Ch] [ebp-20h]
  _DWORD v6[3]; // [esp+30h] [ebp-1Ch] BYREF
  int v7; // [esp+3Ch] [ebp-10h]
  int v8; // [esp+48h] [ebp-4h]

  rf_bitset_construct_borrowed_storage(v6, (int)v4, 200);
  v8 = 0;
  v7 = 0;
  for ( i = 0; i < 25; ++i )
  {
    v4[i] = *(_BYTE *)(v7 + a1);
    ++v7;
  }
  for ( j = 0; j < 200; ++j )
  {
    if ( dword_78BF28[j] >= 0 )
    {
      v2 = rf_item_resolve_handle(dword_78BF28[j]);
      if ( v2 )
      {
        if ( rf_bitset_get_bit_unchecked(v6, j) )
        {
          rf_object_respawn_apply(v2);
        }
        else
        {
          if ( !rf_object_has_respawn_inactive_flag(v2) )
            rf_item_play_pickup_sound(v2);
          rf_object_mark_hidden_inactive(v2);
        }
      }
    }
  }
  v8 = -1;
  return rf_bitset_destroy(v6);
}

