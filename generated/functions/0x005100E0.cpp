// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005100E0 rf_weapon_find_named_animation_entry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Unchecked weapon index selects1360-byte record at912000. Selector LOW BYTE EXACTLY1 scans signed count+664 and28-byte entries+672; all other values scan count+668, entries+756. Returns first index whose entry RFString+0 equals supplied CString case-insensitively via560960; otherwise -1. No fixed-capacity enforcement (arrays nominally3 and12), model checks or mutation.
int __cdecl rf_weapon_find_named_animation_entry(int a1, char *String1, char a3)
{
  char *v4; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  v4 = (char *)&rf_weapon_records + 1360 * a1;
  if ( a3 == 1 )
  {
    for ( i = 0; i < *((_DWORD *)v4 + 166); ++i )
    {
      if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&v4[28 * i + 672]) )
        return i;
    }
  }
  else
  {
    for ( j = 0; j < *((_DWORD *)v4 + 167); ++j )
    {
      if ( rf_cstring_equals_rf_string_case_insensitive(String1, (int)&v4[28 * j + 756]) )
        return j;
    }
  }
  return -1;
}

