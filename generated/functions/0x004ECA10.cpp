// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ECA10 rf_weapon_preload_named_animation_file
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl five stack arguments: weapon index, entry name, optional raw-file buffer, extra DWORD, low-byte state/action selector. Finds named entry; negative index returns zero. Selector exactly 1 uses weapon offset672, otherwise756; entries are28 bytes, filename RFString at+8. Passes filename, optional buffer and extra DWORD on the stack to rf_rfa_load_raw_file (whose verified implementation consumes only its first two arguments); returns its integer result. Zero also means already loaded. No entry/model/buffer capacity validation.
int __cdecl rf_weapon_preload_named_animation_file(int a1, char *String1, void *a3, int a4, char a5)
{
  const char *v6; // eax
  int named_animation_entry; // [esp+0h] [ebp-10h]
  char *v8; // [esp+8h] [ebp-8h]
  int v9; // [esp+Ch] [ebp-4h]

  named_animation_entry = rf_weapon_find_named_animation_entry(a1, String1, a5);
  if ( named_animation_entry < 0 )
    return 0;
  v8 = (char *)&rf_weapon_records + 1360 * a1;
  if ( a5 == 1 )
    v9 = (int)&v8[28 * named_animation_entry + 672];
  else
    v9 = (int)&v8[28 * named_animation_entry + 756];
  v6 = rf_string_object_c_str_or_empty((const void *)(v9 + 8));
  return rf_rfa_load_raw_file(v6, a3);
}

