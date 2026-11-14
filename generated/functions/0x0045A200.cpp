// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A200 rf_multiplayer_enqueue_player_chat_notification
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Cdecl(player,text,modeDWORD),existing SEH ABI preserved. No NULL/player/runtime admission or network send. Game mode0: prefix player RFString name+8 plus ":
// ",style0,mode ignored. Any NONZERO game mode: modeDWORD EXACT1 prepends localized team prefix pointed by88E13C;otherwise empty prefix636073. Then append player name and ": ";style0
// if player teamBYTE48 zero,style1 for ANY nonzero team. Construct owned RFString text/prefix arguments,enqueue notification as8+4+8=20 native stack bytes, release temporary
// concatenation/prefix strings via ordinary/SEH cleanup. Does not filter audience or play chat sound; caller owns those decisions. Localization pointer used at runtime; embedded
// "[Team] " fallback is unreachable under constant branch.
void __cdecl rf_multiplayer_enqueue_player_chat_notification(int a1, char *Source, int a3)
{
  int v3; // [esp-14h] [ebp-94h] BYREF
  int v4; // [esp-10h] [ebp-90h]
  int v5; // [esp-Ch] [ebp-8Ch]
  int v6[6]; // [esp-8h] [ebp-88h] BYREF
  void *v7; // [esp+10h] [ebp-70h]
  _DWORD *v8; // [esp+14h] [ebp-6Ch]
  _DWORD *v9; // [esp+18h] [ebp-68h]
  _DWORD *v10; // [esp+1Ch] [ebp-64h]
  void *v11; // [esp+20h] [ebp-60h]
  void *v12; // [esp+24h] [ebp-5Ch]
  _DWORD *v13; // [esp+28h] [ebp-58h]
  _DWORD *v14; // [esp+2Ch] [ebp-54h]
  char *v15; // [esp+30h] [ebp-50h]
  int v16; // [esp+34h] [ebp-4Ch]
  _DWORD *v17; // [esp+38h] [ebp-48h]
  void *v18; // [esp+3Ch] [ebp-44h]
  void *v19; // [esp+40h] [ebp-40h]
  int *v20; // [esp+44h] [ebp-3Ch]
  _BYTE v21[8]; // [esp+48h] [ebp-38h] BYREF
  void *v22; // [esp+50h] [ebp-30h]
  int *v23; // [esp+54h] [ebp-2Ch]
  _BYTE v24[8]; // [esp+58h] [ebp-28h] BYREF
  void *v25; // [esp+60h] [ebp-20h]
  int *v26; // [esp+64h] [ebp-1Ch]
  void *v27; // [esp+68h] [ebp-18h]
  int v28[2]; // [esp+6Ch] [ebp-14h] BYREF
  int v29; // [esp+7Ch] [ebp-4h]

  if ( rf_multiplayer_game_mode_get() )
  {
    if ( a3 == 1 )
    {
      v16 = unk_88E13C;
      v15 = (char *)unk_88E13C;
    }
    else
    {
      v15 = (char *)&unk_636073;
    }
    rf_string_construct_from_cstr(v28, v15);
    v29 = 1;
    if ( *(_BYTE *)(a1 + 48) )
    {
      v22 = v6;
      v9 = rf_string_concat_two_objects(v21, v28, a1 + 8);
      v8 = v9;
      LOBYTE(v29) = 4;
      v7 = rf_string_concat_object_cstr(v6, v9, ": ");
      v6[5] = (int)v7;
      LOBYTE(v29) = 5;
      v5 = 1;
      v20 = &v3;
      v6[4] = (int)rf_string_construct_from_cstr(&v3, Source);
      LOBYTE(v29) = 4;
      rf_multiplayer_notification_enqueue(v3, v4, v5, v6[0]);
      LOBYTE(v29) = 1;
      rf_string_destroy_buffer(v21);
    }
    else
    {
      v25 = v6;
      v14 = rf_string_concat_two_objects(v24, v28, a1 + 8);
      v13 = v14;
      LOBYTE(v29) = 2;
      v12 = rf_string_concat_object_cstr(v6, v14, ": ");
      v11 = v12;
      LOBYTE(v29) = 3;
      v5 = 0;
      v23 = &v3;
      v10 = rf_string_construct_from_cstr(&v3, Source);
      LOBYTE(v29) = 2;
      rf_multiplayer_notification_enqueue(v3, v4, v5, v6[0]);
      LOBYTE(v29) = 1;
      rf_string_destroy_buffer(v24);
    }
    v29 = -1;
    rf_string_destroy_buffer(v28);
  }
  else
  {
    v27 = v6;
    v19 = rf_string_concat_object_cstr(v6, (_DWORD *)(a1 + 8), ": ");
    v18 = v19;
    v29 = 0;
    v5 = 0;
    v26 = &v3;
    v17 = rf_string_construct_from_cstr(&v3, Source);
    v29 = -1;
    rf_multiplayer_notification_enqueue(v3, v4, v5, v6[0]);
  }
}

