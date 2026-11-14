// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004628A0 rf_browser_join_selected_with_prompt_password
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg modal-confirm callback,existing SEH/ABI retained. Copy inline modal edit buffer via46F8C0(local destination,256):at most255 chars+NUL;construct owned
// local password RFString. Read unguarded localPlayer.net4608 DWORD2492 update rate,format "MAX UPDATE RATE : %d\n" into128-byte stack buffer but NEVER output/use it. Resolve CURRENT
// selected raw index661F9C against current108-byte base without own bounds;set pendingIPv4 from row endpoint84 via462890. Push updateRateDWORD,owned password RFString copy8,owned
// local-player name copy8,endpoint pointer4;call packet2 sender with TOTAL24 native stack bytes,ignore result. Then arm shared join deadline6F537C for1000ms regardless send
// outcome,destroy local password. No own runtime/authority/selection/active-mod/passwordflag validation,player/net NULL check or capture of original prompted row;selection is reread
// at confirmation time. Initial join-selected routine owns earlier checks,but callback does not repeat them. Actual admission/transport delegated.
void rf_browser_join_selected_with_prompt_password()
{
  int v0; // eax
  int v1; // eax
  _DWORD v2[2]; // [esp-14h] [ebp-1C8h] BYREF
  _DWORD v3[2]; // [esp-Ch] [ebp-1C0h] BYREF
  int v4; // [esp-4h] [ebp-1B8h]
  int v5; // [esp+4h] [ebp-1B0h]
  int v6; // [esp+8h] [ebp-1ACh]
  int v7; // [esp+Ch] [ebp-1A8h]
  _DWORD *v8; // [esp+10h] [ebp-1A4h]
  void *v9; // [esp+14h] [ebp-1A0h]
  char Buffer[128]; // [esp+18h] [ebp-19Ch] BYREF
  char Destination[260]; // [esp+98h] [ebp-11Ch] BYREF
  char *v12[2]; // [esp+1A0h] [ebp-14h] BYREF
  int v13; // [esp+1B0h] [ebp-4h]

  rf_ui_copy_modal_edit_text(Destination, 256);
  rf_string_construct_from_cstr(v12, Destination);
  v13 = 0;
  sprintf(Buffer, "MAX UPDATE RATE : %d\n", *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492));
  rf_join_pending_ipv4_set_from_endpoint((int *)dword_6F52CC + 27 * dword_661F9C + 21);
  v4 = *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 2492);
  v9 = v3;
  rf_string_copy_construct_from_object(v3, v12);
  v7 = v0;
  v6 = v0;
  LOBYTE(v13) = 1;
  v8 = v2;
  rf_string_copy_construct_from_object(v2, (char **)(rf_local_fpgun_player + 8));
  v5 = v1;
  LOBYTE(v13) = 0;
  rf_multiplayer_send_join_request_packet2((int)dword_6F52CC + 108 * dword_661F9C + 84, v2[0], v2[1], v3[0], v3[1], v4);
  rf_clock_deadline_set_wrapped_offset(&dword_6F537C, 1000);
  v13 = -1;
  rf_string_destroy_buffer(v12);
}

