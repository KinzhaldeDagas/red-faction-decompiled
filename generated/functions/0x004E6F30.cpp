// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6F30 rf_weapon_has_loaded_fpgun_action_animation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl(weapon index,semantic action slot), canonical ALbool. Native signed slot must be0..11; only weapon EXACT-1 rejected, other negative/too-large weapon IDs unchecked. Find first named animation by full action-name table(slot0 fire,1 alt_fire,2 fire_fail,3..5 idle_1..3,6 draw,7 holster,8 reload,9 jump,10 custom_start,11 custom_leave), selector0 chooses first-person entries. Missing named entry false; otherwise weapon record+756+28*entry DWORD+16 !=0 true. This field receives animation registry handle in5101A0; no remaining-time or current-model-state test. Lookup uses first case-insensitive name match; no alternate/world array or implicit animation load.
bool __cdecl rf_weapon_has_loaded_fpgun_action_animation(int a1, unsigned int a2)
{
  int named_animation_entry; // [esp+0h] [ebp-8h]

  if ( a2 >= 0xC )
    return 0;
  if ( a1 == -1 )
    return 0;
  named_animation_entry = rf_weapon_find_named_animation_entry(a1, (char *)rf_fpgun_action_names[a2], 0);
  return named_animation_entry >= 0 && *((_DWORD *)&rf_weapon_records + 340 * a1 + 7 * named_animation_entry + 193) != 0;
}

