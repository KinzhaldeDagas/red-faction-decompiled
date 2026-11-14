// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048FEF0 sub_48FEF0
// UNREALRED VERIFIED [lan-match-flow-20261028] Next-level rotation selector increments index 0x704EFC, wraps to zero at the configured rotation count, optionally shuffles on a wrapped index when gameflags bit 8 is set, and assigns the chosen level through 0x4798E0. A one-entry valid rotation naturally selects the same map again; the panel-5 path destroys and reloads level runtime resources.
void __cdecl sub_48FEF0()
{
  int first_dword; // eax
  int v1; // esi
  char **v2; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  char **v5; // eax
  int v6; // eax
  int v7[2]; // [esp-10h] [ebp-48h] BYREF
  int v8; // [esp-8h] [ebp-40h] BYREF
  char *v9; // [esp-4h] [ebp-3Ch]
  int v10; // [esp+8h] [ebp-30h]
  _DWORD *v11; // [esp+Ch] [ebp-2Ch]
  _DWORD *v12; // [esp+10h] [ebp-28h]
  int *v13; // [esp+14h] [ebp-24h]
  void *v14; // [esp+18h] [ebp-20h]
  _DWORD v15[2]; // [esp+1Ch] [ebp-1Ch] BYREF
  int v16; // [esp+24h] [ebp-14h]
  int i; // [esp+28h] [ebp-10h]
  int v18; // [esp+34h] [ebp-4h]

  if ( rf_receiver_get_first_dword(unk_704F00) )
  {
    ++dword_704EFC;
    if ( dword_704EFC >= rf_receiver_get_first_dword(unk_704F00) )
      dword_704EFC = 0;
    if ( (rf_multiplayer_game_flags & 8) != 0 && !dword_704EFC )
    {
      for ( i = 0; ; ++i )
      {
        first_dword = rf_receiver_get_first_dword(unk_704F00);
        if ( i >= first_dword )
          break;
        v1 = rand();
        v16 = v1 % rf_receiver_get_first_dword(unk_704F00);
        v2 = (char **)rf_string_array8_element_unchecked(unk_704F00, v16);
        rf_string_copy_construct_from_object(v15, v2);
        v18 = 0;
        v9 = (char *)rf_string_array8_element_unchecked(unk_704F00, i);
        v3 = (_DWORD *)rf_string_array8_element_unchecked(unk_704F00, v16);
        rf_string_assign_from_object(v3, (int)v9);
        v4 = (_DWORD *)rf_string_array8_element_unchecked(unk_704F00, i);
        rf_string_assign_from_object(v4, (int)v15);
        v18 = -1;
        rf_string_destroy_buffer(v15);
      }
    }
    v14 = &v8;
    v12 = rf_string_construct_from_cstr(&v8, (char *)&byte_6393D7);
    v11 = v12;
    v18 = 1;
    v5 = (char **)rf_string_array8_element_unchecked(unk_704F00, dword_704EFC);
    v13 = v7;
    rf_string_copy_construct_from_object(v7, v5);
    v10 = v6;
    v18 = -1;
    rf_level_transition_assign_level_and_save_strings(v7[0], (char *)v7[1], v8, v9);
  }
}

