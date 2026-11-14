// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048DEE0 rf_multiplayer_character_caches_preload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl no arguments. Signed-loop i<global multiplayer_character_count,record stride320 at multiplayer_character_table. Uses recordDWORD4 as MODEL EntityInfo index and DWORD8 as
// ANIMATION-source EntityInfo index,both stride5396,without range checks. Reads model RFString at modelInfo+8,copies stem without last extension into local128-byte buffer through
// unbounded helper. Native cache lookup call pushes THREE words(stem,0,0),cleans12; adapter564180 reads filename/cacheByte first two only. Marks returned cache retained by OR DWORD68
// with0x10,stores pointer704BE0[i],withoutNULL guard.
// Loads animation names from52-byte source records with RFString+8,in order:first source count1876/base1884 using animation_registry_load(cache,name,1,0); then ALL64 groups
// count[1896+4*k],base[2408+4*k] with same(1,0); finally source count1880/base1888 with(0,0). Native registry receiver ECX=cache and THREE stack args(name,flag,0). Does not use
// modelInfo's animation lists,cap counts/registry index,deduplicate animation names or roll back prior retains on error. Return register incidental.
void rf_multiplayer_character_caches_preload()
{
  char *v0; // eax
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  char v4[128]; // [esp+0h] [ebp-A0h] BYREF
  int *v5; // [esp+84h] [ebp-1Ch]
  char *v6; // [esp+88h] [ebp-18h]
  _DWORD *v7; // [esp+8Ch] [ebp-14h]
  char *v8; // [esp+90h] [ebp-10h]
  int j; // [esp+94h] [ebp-Ch]
  int k; // [esp+98h] [ebp-8h]
  int i; // [esp+9Ch] [ebp-4h]

  for ( i = 0; i < rf_multiplayer_character_count; ++i )
  {
    v5 = &rf_multiplayer_character_table[80 * i];
    v8 = &rf_entity_info_definitions[5396 * v5[1]];
    v6 = &rf_entity_info_definitions[5396 * v5[2]];
    v0 = (char *)rf_string_object_c_str_or_empty(v8 + 8);
    rf_path_copy_without_last_extension(v4, v0);
    v7 = (_DWORD *)rf_character_cache_lookup_adapter(v4, 0);
    rf_character_cache_mark_record_retained((int)v7);
    unk_704BE0[i] = (int)v7;
    for ( j = 0; j < *((_DWORD *)v6 + 469); ++j )
    {
      v1 = rf_string_object_c_str_or_empty((const void *)(*((_DWORD *)v6 + 471) + 52 * j + 8));
      rf_animation_registry_load(v7, (int)v1, 1u, 0);
    }
    for ( k = 0; k < 64; ++k )
    {
      for ( j = 0; j < *(_DWORD *)&v6[4 * k + 1896]; ++j )
      {
        v2 = rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)&v6[4 * k + 2408] + 52 * j + 8));
        rf_animation_registry_load(v7, (int)v2, 1u, 0);
      }
    }
    for ( j = 0; j < *((_DWORD *)v6 + 470); ++j )
    {
      v3 = rf_string_object_c_str_or_empty((const void *)(*((_DWORD *)v6 + 472) + 52 * j + 8));
      rf_animation_registry_load(v7, (int)v3, 0, 0);
    }
  }
}

