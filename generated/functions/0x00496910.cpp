// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496910 rf_ctf_flag_return_notification
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(optional player, integer red selector). Selector exactly 1 chooses red/style2; all other values choose blue/style3. Nonnull player uses localized prefix 88E304/88E308
// followed by player RFString +8; null player uses complete localized text 88E30C/88E310. Dead fallback literal references identify red/blue returned wording. Calls notification with
// first RFString, style DWORD, trailing empty RFString: native caller cleanup is 20 bytes; callee consumes strings with SEH protecting the trailing constructed argument. Does not
// change game mode, score, carrier, timer or network state.
void __cdecl rf_ctf_flag_return_notification(int a1, int a2)
{
  int v2[2]; // [esp-14h] [ebp-84h] BYREF
  int v3; // [esp-Ch] [ebp-7Ch]
  int v4[5]; // [esp-8h] [ebp-78h] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-64h]
  char *v6; // [esp+10h] [ebp-60h]
  _DWORD *v7; // [esp+14h] [ebp-5Ch]
  _DWORD *v8; // [esp+18h] [ebp-58h]
  _DWORD *v9; // [esp+1Ch] [ebp-54h]
  char *Source; // [esp+20h] [ebp-50h]
  void *v11; // [esp+24h] [ebp-4Ch]
  _DWORD *v12; // [esp+28h] [ebp-48h]
  _DWORD *v13; // [esp+2Ch] [ebp-44h]
  const char *v14; // [esp+30h] [ebp-40h]
  void *v15; // [esp+34h] [ebp-3Ch]
  _DWORD *v16; // [esp+38h] [ebp-38h]
  _DWORD *v17; // [esp+3Ch] [ebp-34h]
  const char *v18; // [esp+40h] [ebp-30h]
  int *v19; // [esp+44h] [ebp-2Ch]
  void *v20; // [esp+48h] [ebp-28h]
  int *v21; // [esp+4Ch] [ebp-24h]
  void *v22; // [esp+50h] [ebp-20h]
  int *v23; // [esp+54h] [ebp-1Ch]
  void *v24; // [esp+58h] [ebp-18h]
  int *v25; // [esp+5Ch] [ebp-14h]
  void *v26; // [esp+60h] [ebp-10h]
  int v27; // [esp+6Ch] [ebp-4h]

  if ( a1 )
  {
    if ( a2 == 1 )
    {
      v18 = (const char *)unk_88E304;
      v26 = v4;
      v17 = rf_string_construct_from_cstr(v4, (char *)&byte_639F64);
      v16 = v17;
      v27 = 0;
      v3 = 2;
      v25 = v2;
      v15 = rf_string_concat_cstr_object(v2, v18, (const void **)(a1 + 8));
    }
    else
    {
      v14 = (const char *)unk_88E308;
      v24 = v4;
      v13 = rf_string_construct_from_cstr(v4, (char *)&byte_639F65);
      v12 = v13;
      v27 = 1;
      v3 = 3;
      v23 = v2;
      v11 = rf_string_concat_cstr_object(v2, v14, (const void **)(a1 + 8));
    }
  }
  else if ( a2 == 1 )
  {
    Source = (char *)unk_88E30C;
    v22 = v4;
    v9 = rf_string_construct_from_cstr(v4, (char *)&byte_639F66);
    v8 = v9;
    v27 = 2;
    v3 = 2;
    v21 = v2;
    v7 = rf_string_construct_from_cstr(v2, Source);
  }
  else
  {
    v6 = (char *)unk_88E310;
    v20 = v4;
    v5 = rf_string_construct_from_cstr(v4, (char *)&byte_639F67);
    v4[4] = (int)v5;
    v27 = 3;
    v3 = 3;
    v19 = v2;
    v4[3] = (int)rf_string_construct_from_cstr(v2, v6);
  }
  v27 = -1;
  rf_multiplayer_notification_enqueue(v2[0], v2[1], v3, v4[0]);
}

