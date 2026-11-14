// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B7F80 sub_5B7F80
// UNREALRED VERIFIED [mesh-streaming-20260930] Canonicalizes to .v3m through 0x57C380, searches the resource cache, and appends a newly allocated resource only when 0x5B8D90 returns nonnegative. Parse failure destroys the allocation and returns null. No sibling-format retry in this manager. Unreal source-generation validation is a host adaptation preserving selection-to-publication ownership; current broad Unreal aliases are a compatibility approximation.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Static item model filename canonicalization replaces last-dot suffix ANYWHERE in full raw input with .v3m via57C380, otherwise appends .v3m. No trim, same-stem .v3c retry or weapon-class substitute. Cache first case-insensitive canonicalfilename hit; failed new5B8D90 parse removes/destroys allocation and returnsnull. Host exact item loader must preserve this canonicalization before single-resource admission.
char *__cdecl sub_5B7F80(char *Str, char a2, int a3)
{
  char *v4; // [esp+8h] [ebp-138h]
  _DWORD *v5; // [esp+14h] [ebp-12Ch]
  char String2[268]; // [esp+1Ch] [ebp-124h] BYREF
  char *v7; // [esp+12Ch] [ebp-14h]
  int i; // [esp+130h] [ebp-10h]
  int v9; // [esp+13Ch] [ebp-4h]

  rf_path_replace_last_dot_suffix_unbounded(String2, Str, ".v3m");
  v7 = nullptr;
  for ( i = 0; i < unk_1D6DA20; ++i )
  {
    if ( !_stricmp((&unk_1D6D250)[i], String2) )
    {
      v7 = (&unk_1D6D250)[i];
      break;
    }
  }
  if ( !v7 )
  {
    v5 = operator new(0x90u);
    v9 = 0;
    if ( v5 )
      v4 = (char *)rf_v3c_asset_base_construct(v5);
    else
      v4 = nullptr;
    v9 = -1;
    v7 = v4;
    rf_renderer_reserved_noop_5709C0();
    if ( sub_5B8D90(v7, String2, 1, (unsigned __int8)a2, a3) >= 0 )
    {
      (&unk_1D6D250)[unk_1D6DA20++] = v7;
    }
    else
    {
      if ( v7 )
        rf_v3c_asset_base_scalar_deleting_destructor(v7, 1);
      v7 = nullptr;
    }
    rf_renderer_reserved_noop_5709D0();
  }
  return v7;
}

