// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00430310 sub_430310
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Owns class prop-cache initialization. If gameplay class Entity+0x294 equals model class +0x29C, uses the actual primary handle and sets class+0x724 bit0x20000000 only after 4305D0 returns0. With distinct classes, loads/destroys a temporary gameplay-class character handle for its cache and uses the actual primary handle for the model-class cache. 420020 consumes model class+0x29C, then vector+0x1D4.
char __cdecl sub_430310(int *a1)
{
  int v1; // eax
  char v3; // [esp+1h] [ebp-57h]
  char v4; // [esp+2h] [ebp-56h]
  char v5; // [esp+3h] [ebp-55h]
  char *v6; // [esp+8h] [ebp-50h]
  const char *v7; // [esp+Ch] [ebp-4Ch]
  bool v8; // [esp+13h] [ebp-45h]
  char *last_char_wrapper; // [esp+28h] [ebp-30h]
  char Str[32]; // [esp+2Ch] [ebp-2Ch] BYREF
  _DWORD *character_instance; // [esp+50h] [ebp-8h]
  char v12; // [esp+57h] [ebp-1h]

  if ( a1[165] == a1[167] )
  {
    LOBYTE(v1) = (_BYTE)a1;
    if ( (*(_DWORD *)(a1[165] + 1828) & 0x20000000) == 0 )
    {
      LOBYTE(v1) = rf_entity_admits_speech_body_actions((int)a1);
      v3 = false;
      if ( (_BYTE)v1 )
      {
        LOBYTE(v1) = rf_entity_has_humanoid_flag((int)a1);
        if ( (_BYTE)v1 )
          v3 = true;
      }
      if ( a1[32] )
      {
        v1 = sub_4305D0((_DWORD *)a1[165], a1[32], v3);
        if ( !v1 )
        {
          v1 = a1[165];
          *(_DWORD *)(v1 + 1828) |= 0x20000000u;
        }
      }
    }
  }
  else
  {
    if ( (*(_DWORD *)(a1[165] + 1828) & 0x20000000) == 0 )
    {
      v8 = *(_DWORD *)(a1[165] + 148) == 2 && (*(_DWORD *)(a1[165] + 1828) & 0x20000) != 0;
      v12 = v8;
      v7 = rf_string_object_c_str_or_empty((const void *)(a1[165] + 8));
      v6 = Str;
      do
      {
        v5 = *v7;
        *v6++ = *v7++;
      }
      while ( v5 );
      last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 46);
      if ( last_char_wrapper )
        *last_char_wrapper = 0;
      character_instance = rf_model_handle_load_character_instance(Str, 0, 0);
      if ( character_instance )
      {
        if ( !sub_4305D0((_DWORD *)a1[165], (int)character_instance, v12) )
          *(_DWORD *)(a1[165] + 1828) |= 0x20000000u;
        rf_model_handle_destroy_cdecl_adapter(character_instance);
      }
    }
    v1 = *(_DWORD *)(a1[167] + 1828) & 0x20000000;
    if ( !v1 )
    {
      v4 = *(_DWORD *)(a1[167] + 148) == 2 && (*(_DWORD *)(a1[167] + 1828) & 0x20000) != 0;
      LOBYTE(v1) = v4;
      if ( a1[32] )
      {
        v1 = sub_4305D0((_DWORD *)a1[167], a1[32], v4);
        if ( !v1 )
        {
          v1 = *(_DWORD *)(a1[167] + 1828) | 0x20000000;
          *(_DWORD *)(a1[167] + 1828) = v1;
        }
      }
    }
  }
  return v1;
}

