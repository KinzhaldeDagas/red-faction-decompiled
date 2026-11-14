// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AAB0 rf_multiplayer_send_chat_with_500ms_throttle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl(text,modeDWORD),SEH/native types preserved. Shared deadline6F2CCC: disarmed-negative OR armed-and-half-period-elapsed
// admits. Arm wrapped offset500ms BEFORE calling chat packet12 sender45A3F0(text,mode),without sender result check/rollback. Armed-and-not-elapsed rejects send: enqueue
// localized88E3B4 notification with style4 and empty prefix636083,using two owned8-byte RFStrings plus styleDWORD (20 native stack bytes). No rearm on rejection. Embedded fallback
// says "You cannot talk for 1 second" but branch is constant-unreachable; actual interval500ms. No own runtime/authority,text-empty,length or audience checks. Shared by console
// say/team_say and interactive chat; one global throttle across modes. No own sound or buffer clear.
void __cdecl rf_multiplayer_send_chat_with_500ms_throttle(char *Src, int a2)
{
  int v2[2]; // [esp-14h] [ebp-3Ch] BYREF
  int v3; // [esp-Ch] [ebp-34h]
  int v4[5]; // [esp-8h] [ebp-30h] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-1Ch]
  char *Source; // [esp+10h] [ebp-18h]
  int *v7; // [esp+14h] [ebp-14h]
  void *v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+24h] [ebp-4h]

  if ( rf_timestamp_is_armed_nonnegative(&dword_6F2CCC) && !rf_clock_deadline_has_elapsed_half_period(&dword_6F2CCC) )
  {
    Source = (char *)unk_88E3B4;
    v8 = v4;
    v5 = rf_string_construct_from_cstr(v4, (char *)&byte_636083);
    v4[4] = (int)v5;
    v9 = 0;
    v3 = 4;
    v7 = v2;
    v4[3] = (int)rf_string_construct_from_cstr(v2, Source);
    v9 = -1;
    rf_multiplayer_notification_enqueue(v2[0], v2[1], v3, v4[0]);
  }
  else
  {
    rf_clock_deadline_set_wrapped_offset(&dword_6F2CCC, 500);
    rf_multiplayer_send_chat_line_packet12(Src, a2);
  }
}

