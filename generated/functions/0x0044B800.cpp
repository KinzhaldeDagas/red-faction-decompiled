// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044B800 rf_hud_expand_control_token_in_place
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(required writable token C-string pointer), returns ORIGINAL input pointer. Constructs owned empty RFString, then
// sequential CASE-SENSITIVE full-string comparisons in native order FIRE,ALT_FIRE,USE,JUMP,CROUCH,HOLSTER,RELOAD,NEXT_WEAPON,PREV_WEAPON,MESSAGE_LOG; no prefix/whitespace/case
// folding or delimiter stripping here. Matched token selects pointer from mutable DWORD respectively88E0D4,88E0D8,88D684,88D688,88D68C,88E0DC,88D694,88D698,88E0E0,88D6A8. Every
// apparent English fallback branch is unreachable because its immediately preceding XOR register,register makes JZ unconditional; no NULL-localization fallback is implemented.
// Exactly one matched branch calls4526E0(&distinct temporaryRFString,global87C318+228,selected pointer), assigns returned RFString into owned result through55FF10, then destroys
// branch temporary. Lookup uses the first case-insensitive action-name match; absent lookup becomes "?", while both invalid/empty display codes produce empty text. Input token itself
// does not select a numeric action ID in this body. After matched or unmatched path, append byte0x24($) to result; obtain borrowed C-string, copy every byte INCLUDING NUL back to
// original input with no capacity bound, destroy owned result, return original input pointer (not borrowed destroyed storage). UNKNOWN or empty token therefore becomes "$", not
// original token or empty string. Unmatched path never reads local-player global; matched path adds228 to raw global pointer without checking NULL/player ownership, localization
// string, helper output or lookup success. All helper results are consumed as strings rather than Boolean admission. RFString cleanup state0 covers main result; states1..10 cover
// corresponding branch temporaries through captured SEH funclets, then normal tail resets state-1 and destroys main result. No in-place capacity check, rollback, key polling/input
// dispatch, global localization mutation or special NaN/FPU behavior in this body.
char *__cdecl rf_hud_expand_control_token_in_place(char *a1)
{
  char v2; // [esp+7h] [ebp-1B5h]
  char *v3; // [esp+Ch] [ebp-1B0h]
  const char *v4; // [esp+10h] [ebp-1ACh]
  _DWORD *v5; // [esp+14h] [ebp-1A8h]
  _DWORD *v6; // [esp+34h] [ebp-188h]
  _DWORD *v7; // [esp+54h] [ebp-168h]
  _DWORD *v8; // [esp+74h] [ebp-148h]
  _DWORD *v9; // [esp+94h] [ebp-128h]
  _DWORD *v10; // [esp+B4h] [ebp-108h]
  _DWORD *v11; // [esp+D4h] [ebp-E8h]
  _DWORD *v12; // [esp+F4h] [ebp-C8h]
  _DWORD *v13; // [esp+114h] [ebp-A8h]
  _DWORD *v14; // [esp+134h] [ebp-88h]
  int v15[2]; // [esp+158h] [ebp-64h] BYREF
  int v16[2]; // [esp+160h] [ebp-5Ch] BYREF
  int v17[2]; // [esp+168h] [ebp-54h] BYREF
  int v18[2]; // [esp+170h] [ebp-4Ch] BYREF
  int v19[2]; // [esp+178h] [ebp-44h] BYREF
  int v20[2]; // [esp+180h] [ebp-3Ch] BYREF
  int v21[2]; // [esp+188h] [ebp-34h] BYREF
  int v22[2]; // [esp+190h] [ebp-2Ch] BYREF
  int v23[2]; // [esp+198h] [ebp-24h] BYREF
  int v24[2]; // [esp+1A0h] [ebp-1Ch] BYREF
  _DWORD v25[2]; // [esp+1A8h] [ebp-14h] BYREF
  int v26; // [esp+1B8h] [ebp-4h]

  rf_string_construct_empty(v25);
  v26 = 0;
  if ( !strcmp(a1, "FIRE") )
  {
    v14 = rf_control_binding_construct_display_names(v24, rf_local_fpgun_player + 228, unk_88E0D4);
    LOBYTE(v26) = 1;
    rf_string_assign_from_object(v25, (int)v14);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v24);
  }
  else if ( !strcmp(a1, "ALT_FIRE") )
  {
    v13 = rf_control_binding_construct_display_names(v23, rf_local_fpgun_player + 228, unk_88E0D8);
    LOBYTE(v26) = 2;
    rf_string_assign_from_object(v25, (int)v13);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v23);
  }
  else if ( !strcmp(a1, (const char *)&off_63436C) )
  {
    v12 = rf_control_binding_construct_display_names(v22, rf_local_fpgun_player + 228, unk_88D684);
    LOBYTE(v26) = 3;
    rf_string_assign_from_object(v25, (int)v12);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v22);
  }
  else if ( !strcmp(a1, "JUMP") )
  {
    v11 = rf_control_binding_construct_display_names(v21, rf_local_fpgun_player + 228, unk_88D688);
    LOBYTE(v26) = 4;
    rf_string_assign_from_object(v25, (int)v11);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v21);
  }
  else if ( !strcmp(a1, "CROUCH") )
  {
    v10 = rf_control_binding_construct_display_names(v20, rf_local_fpgun_player + 228, unk_88D68C);
    LOBYTE(v26) = 5;
    rf_string_assign_from_object(v25, (int)v10);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v20);
  }
  else if ( !strcmp(a1, "HOLSTER") )
  {
    v9 = rf_control_binding_construct_display_names(v19, rf_local_fpgun_player + 228, unk_88E0DC);
    LOBYTE(v26) = 6;
    rf_string_assign_from_object(v25, (int)v9);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v19);
  }
  else if ( !strcmp(a1, "RELOAD") )
  {
    v8 = rf_control_binding_construct_display_names(v18, rf_local_fpgun_player + 228, unk_88D694);
    LOBYTE(v26) = 7;
    rf_string_assign_from_object(v25, (int)v8);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v18);
  }
  else if ( !strcmp(a1, "NEXT_WEAPON") )
  {
    v7 = rf_control_binding_construct_display_names(v17, rf_local_fpgun_player + 228, unk_88D698);
    LOBYTE(v26) = 8;
    rf_string_assign_from_object(v25, (int)v7);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v17);
  }
  else if ( !strcmp(a1, "PREV_WEAPON") )
  {
    v6 = rf_control_binding_construct_display_names(v16, rf_local_fpgun_player + 228, unk_88E0E0);
    LOBYTE(v26) = 9;
    rf_string_assign_from_object(v25, (int)v6);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v16);
  }
  else if ( !strcmp(a1, "MESSAGE_LOG") )
  {
    v5 = rf_control_binding_construct_display_names(v15, rf_local_fpgun_player + 228, unk_88D6A8);
    LOBYTE(v26) = 10;
    rf_string_assign_from_object(v25, (int)v5);
    LOBYTE(v26) = 0;
    rf_string_destroy_buffer(v15);
  }
  rf_string_append_byte_in_place(v25, 36);
  v4 = rf_string_object_c_str_or_empty(v25);
  v3 = a1;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  v26 = -1;
  rf_string_destroy_buffer(v25);
  return a1;
}

