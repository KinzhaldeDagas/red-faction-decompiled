// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A8DB0 rf_replication_select_entity_record38_mask
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(recipientPlayer,entity,outMaskBYTE), output authoritative; EAX incidental. Starts mask=originalWORD662BE8 lowBYTE1. If selected weapon676>=0,
// continuous-mode predicate(weapon,(entityDWORD2000&0x2000)!=0) nonzero AND422270(handle44,weapon) nonzero: add0x40; add0x10 when entity2000 bit0x2000; client runtime1/authority0
// additionally adds hit bit8. Client also adds bit2 when local net deadline524 elapsed any nonzero (unguarded local/net). ONLY runtime1/authorityEXACT1 adds
// weapon4,vitals0x20,powerups0x80; when recipient.handle20==entity.handle44 clears1|0x40|0x10, leaving other fields, normally mask0xA4. All mask values independently PE-verified
// from8 descriptors at662BE8..662C20. No output-null, recipient/entity, upper weapon bounds or empty-mask special case; no distance-based entity suppression.
int *__cdecl rf_replication_select_entity_record38_mask(int a1, int *a2, _BYTE *a3)
{
  int *result; // eax

  *a3 = 0;
  *a3 |= word_662BE8;
  if ( a2[169] >= 0
    && rf_weapon_selected_mode_is_continuous_exact_selector(a2[169], (a2[500] & 0x2000) != 0)
    && rf_entity_weapon_firing_byte_is_set(a2[11], a2[169]) )
  {
    if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
      *a3 |= word_662C00;
    *a3 |= word_662C18;
    if ( (a2[500] & 0x2000) != 0 )
      *a3 |= word_662C08;
  }
  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && rf_clock_deadline_has_elapsed_half_period((int *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 524)) )
  {
    *a3 |= word_662BF0;
  }
  result = (int *)rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    *a3 |= word_662BF8;
    *a3 |= word_662C10;
    *a3 |= word_662C20;
    result = a2;
    if ( *(_DWORD *)(a1 + 20) == a2[11] )
    {
      *a3 &= ~(word_662C08 | word_662C18 | word_662BE8);
      return (int *)a3;
    }
  }
  return result;
}

