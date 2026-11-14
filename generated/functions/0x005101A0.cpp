// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005101A0 rf_weapon_load_named_animation_entry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Calls5100E0 with weapon index/name/selector low byte; absent entry returns AL0. Otherwise resolves model definition565EC0 and chooses same28-byte entry array (selector exactly1 =>+672, else+756). Loads entry filename RFString+8 through5884E0 with selector byte and final1, stores returned handle at entry+16, returns AL1 regardless loader result. No prior-cache skip, NULL definition guard or weapon bounds check.
char __cdecl rf_weapon_load_named_animation_entry(int a1, int a2, char *String1, char a4)
{
  const char *v5; // eax
  int named_animation_entry; // [esp+0h] [ebp-10h]
  char *v7; // [esp+4h] [ebp-Ch]
  int v8; // [esp+8h] [ebp-8h]
  _DWORD *definition_pointer; // [esp+Ch] [ebp-4h]

  named_animation_entry = rf_weapon_find_named_animation_entry(a2, String1, a4);
  if ( named_animation_entry < 0 )
    return 0;
  v7 = (char *)&rf_weapon_records + 1360 * a2;
  definition_pointer = (_DWORD *)rf_model_handle_get_definition_pointer(a1);
  if ( a4 == 1 )
    v8 = (int)&v7[28 * named_animation_entry + 672];
  else
    v8 = (int)&v7[28 * named_animation_entry + 756];
  v5 = rf_string_object_c_str_or_empty((const void *)(v8 + 8));
  *(_DWORD *)(v8 + 16) = rf_animation_registry_load(definition_pointer, (int)v5, a4, 1);
  return 1;
}

