// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD040 rf_model_apply_first_matching_skin_profile
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Cdecl model wrapper,signed profile count,profile-array base,C-string name. Scans108-byte records comparing RFString at+0 to name case-insensitively; first match remembers index and record pointer, breaks. If record pointer nonNULL calls rf_model_apply_skin_texture_names(model,record); returns first index even if delegate fails. No match or count<=0 returns-1. If calculated matched record pointer isNULL, skips delegate but still returns index. No own model/base/name NULL check, allocation or profile validation.
int __cdecl rf_model_apply_first_matching_skin_profile(int a1, int a2, int a3, char *String2)
{
  int v5; // [esp+0h] [ebp-Ch]
  int v6; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v5 = -1;
  v6 = 0;
  for ( i = 0; i < a2; ++i )
  {
    if ( rf_string_equals_case_insensitive(a3 + 108 * i, String2) )
    {
      v5 = i;
      v6 = a3 + 108 * i;
      break;
    }
  }
  if ( v6 )
    rf_model_apply_skin_texture_names(a1, v6);
  return v5;
}

