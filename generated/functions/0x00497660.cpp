// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497660 rf_ctf_flag_capture_notification
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(player, integer red selector). Exactly1 selects red wording; every other selector chooses blue. If a local player exists and equals player, uses complete localized text
// red88E314/blue88E31C and style4. Otherwise appends localized suffix red88E318/style3 or blue88E320/style2 to player RFString+8; remote null player is unguarded. Dead fallback
// literals identify captured-red/blue wording. Native notification call consumes first RFString, style DWORD and trailing empty RFString, 20-byte caller cleanup with SEH temporary
// ownership. No score, timer, carrier, mode or networking changes. Both calls in capture_at_base pass0, including its red-flag branch.
void __cdecl rf_ctf_flag_capture_notification(int a1, int a2)
{
  int v2; // [esp-14h] [ebp-84h] BYREF
  int v3; // [esp-10h] [ebp-80h]
  int v4; // [esp-Ch] [ebp-7Ch]
  int v5[5]; // [esp-8h] [ebp-78h] BYREF
  _DWORD *v6; // [esp+Ch] [ebp-64h]
  const char *v7; // [esp+10h] [ebp-60h]
  _DWORD *v8; // [esp+14h] [ebp-5Ch]
  _DWORD *v9; // [esp+18h] [ebp-58h]
  _DWORD *v10; // [esp+1Ch] [ebp-54h]
  char *v11; // [esp+20h] [ebp-50h]
  void *v12; // [esp+24h] [ebp-4Ch]
  _DWORD *v13; // [esp+28h] [ebp-48h]
  _DWORD *v14; // [esp+2Ch] [ebp-44h]
  const char *v15; // [esp+30h] [ebp-40h]
  _DWORD *v16; // [esp+34h] [ebp-3Ch]
  _DWORD *v17; // [esp+38h] [ebp-38h]
  _DWORD *v18; // [esp+3Ch] [ebp-34h]
  char *Source; // [esp+40h] [ebp-30h]
  int *v20; // [esp+44h] [ebp-2Ch]
  void *v21; // [esp+48h] [ebp-28h]
  int *v22; // [esp+4Ch] [ebp-24h]
  void *v23; // [esp+50h] [ebp-20h]
  int *v24; // [esp+54h] [ebp-1Ch]
  void *v25; // [esp+58h] [ebp-18h]
  int *v26; // [esp+5Ch] [ebp-14h]
  void *v27; // [esp+60h] [ebp-10h]
  int v28; // [esp+6Ch] [ebp-4h]

  if ( a2 == 1 )
  {
    if ( rf_local_fpgun_player && a1 == rf_local_fpgun_player )
    {
      Source = (char *)unk_88E314;
      v27 = v5;
      v18 = rf_string_construct_from_cstr(v5, (char *)&byte_639F86);
      v17 = v18;
      v28 = 0;
      v4 = 4;
      v26 = &v2;
      v16 = rf_string_construct_from_cstr(&v2, Source);
      v28 = -1;
      rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
    }
    else
    {
      v15 = (const char *)unk_88E318;
      v25 = v5;
      v14 = rf_string_construct_from_cstr(v5, (char *)&byte_639F87);
      v13 = v14;
      v28 = 1;
      v4 = 3;
      v24 = &v2;
      v12 = rf_string_concat_object_cstr(&v2, (_DWORD *)(a1 + 8), v15);
      v28 = -1;
      rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
    }
  }
  else if ( rf_local_fpgun_player && a1 == rf_local_fpgun_player )
  {
    v11 = (char *)unk_88E31C;
    v23 = v5;
    v10 = rf_string_construct_from_cstr(v5, (char *)&byte_639FA7);
    v9 = v10;
    v28 = 2;
    v4 = 4;
    v22 = &v2;
    v8 = rf_string_construct_from_cstr(&v2, v11);
    v28 = -1;
    rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
  }
  else
  {
    v7 = (const char *)unk_88E320;
    v21 = v5;
    v6 = rf_string_construct_from_cstr(v5, (char *)&byte_639FC2);
    v5[4] = (int)v6;
    v28 = 3;
    v4 = 2;
    v20 = &v2;
    v5[3] = (int)rf_string_concat_object_cstr(&v2, (_DWORD *)(a1 + 8), v7);
    v28 = -1;
    rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
  }
}

