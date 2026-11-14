// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00494E80 rf_multiplayer_apply_team_score_payload53
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Recovered494E80..494F1F,lastRET494F1E; descriptor53 team_score. Cdecl payload only,source extra word ignored,no length. Read two WORDs at0/2, then query game
// mode. Mode1 invokes client CTF red/blue capture setters;mode2 invokes client mode2 team0/team1 score setters;others no action. Each native argument is MOVZX from LOW BYTE of its
// received WORD, so high byte discarded before call. No own runtime/authority/source guard; setters independently own client admission. Does not add scores or validate monotonicity.
// Sender494C50 writes zero-extended score bytes into these two WORDs in7-byte reliable packet.
void __cdecl rf_multiplayer_apply_team_score_payload53(const unsigned __int8 *payload)
{
  __int16 v1; // [esp+0h] [ebp-10h]
  __int16 v2; // [esp+4h] [ebp-Ch]
  int v3; // [esp+Ch] [ebp-4h]

  v1 = *(_WORD *)payload;
  v2 = *((_WORD *)payload + 1);
  v3 = rf_multiplayer_game_mode_get();
  if ( v3 == 1 )
  {
    rf_client_ctf_red_capture_byte_set(v1);
    rf_client_ctf_blue_capture_byte_set(v2);
  }
  else if ( v3 == 2 )
  {
    rf_client_mode2_set_team0_score_byte(v1);
    rf_client_mode2_set_team1_score_byte(v2);
  }
}

