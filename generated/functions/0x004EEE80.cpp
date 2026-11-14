// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EEE80 rf_player_options_initialize_defaults
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl OPTIONS MEMBER pointer, passed as player+228 by player-create caller. Calls input defaults451750. Relative to options: float3700=.5; zero bytes3667,3668,3669,3670,3677; one bytes3671..3676,3678..3680,3684 (3675 written twice); byte3666 copied from PE byte63C220=1; DWORDs3688/3692/3696=0. Constant branch selects localized C-string pointer88D544, copied unbounded to options+3708; hardcoded Player path unreachable. Finds multiplayer character enviro_parker, stores and returns index atoptions3704 including-1. No full-record clear or resource creation.
int __cdecl rf_player_options_initialize_defaults(int a1)
{
  int result; // eax
  char v2; // [esp+3h] [ebp-11h]
  _BYTE *v3; // [esp+8h] [ebp-Ch]
  char *v4; // [esp+Ch] [ebp-8h]

  rf_input_bindings_initialize_defaults(a1);
  *(float *)(a1 + 3700) = 0.5;
  *(_BYTE *)(a1 + 3667) = 0;
  *(_BYTE *)(a1 + 3675) = 1;
  *(_BYTE *)(a1 + 3668) = 0;
  *(_BYTE *)(a1 + 3669) = 0;
  *(_BYTE *)(a1 + 3670) = 0;
  *(_BYTE *)(a1 + 3677) = 0;
  *(_BYTE *)(a1 + 3671) = 1;
  *(_BYTE *)(a1 + 3672) = 1;
  *(_BYTE *)(a1 + 3673) = 1;
  *(_BYTE *)(a1 + 3674) = 1;
  *(_BYTE *)(a1 + 3675) = 1;
  *(_BYTE *)(a1 + 3678) = 1;
  *(_BYTE *)(a1 + 3679) = 1;
  *(_BYTE *)(a1 + 3680) = 1;
  *(_DWORD *)(a1 + 3688) = 0;
  *(_DWORD *)(a1 + 3696) = 0;
  *(_DWORD *)(a1 + 3692) = 0;
  *(_BYTE *)(a1 + 3684) = 1;
  *(_BYTE *)(a1 + 3666) = 1;
  *(_BYTE *)(a1 + 3676) = 1;
  *(_BYTE *)(a1 + 3677) = 0;
  v4 = (char *)unk_88D544;
  v3 = (_BYTE *)(a1 + 3708);
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  result = rf_multiplayer_character_find_by_name("enviro_parker");
  *(_DWORD *)(a1 + 3704) = result;
  return result;
}

