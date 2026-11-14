// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486B40 rf_material_custom_sound_set_find
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl C-string name, returns raw set pointer or0. Walks registry0x700460 in insertion order, compares RFString at set+204 with supplied C string using exact null-aware
// case-insensitive helper5609B0. First duplicate name wins; no trim or prefix matching. NULL input can match empty stored RFString through helper semantics. No set-pointer NULL
// guard, fallback allocation or material lookup. Return is borrowed registry entry; not cloned.
int __cdecl rf_material_custom_sound_set_find(char *String2)
{
  _DWORD *v1; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_material_custom_sound_sets); ++i )
  {
    v1 = (_DWORD *)sub_552200(rf_material_custom_sound_sets, i);
    if ( rf_string_equals_case_insensitive(*v1 + 204, String2) )
      return *(_DWORD *)sub_552200(rf_material_custom_sound_sets, i);
  }
  return 0;
}

