// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497980 rf_ctf_drop_player_carried_flag
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(player). Requires mode1, nonnull player and nonzero initialized byte77D6E2. Tests BLUE carrier first: if equal, clears blue carrier (arming25s return), broadcasts
// packet35(selector0), then sets blue definition DWORD+68 bit2. Otherwise tests red carrier and does equivalent selector1/red-definition mutation. If both globals equal player only
// blue is processed. Packet35 only serializes current flag position; it does not reposition the flag. No direct home placement, score-byte clear, scoring or local feedback; flag
// retains last carried world transform. No own authority guard.
int __cdecl rf_ctf_drop_player_carried_flag(int a1)
{
  int result; // eax

  result = rf_multiplayer_game_mode_get();
  if ( result == 1 )
  {
    if ( a1 )
    {
      result = (unsigned __int8)byte_77D6E2;
      if ( byte_77D6E2 )
      {
        if ( rf_ctf_blue_carrier_get() == a1 )
        {
          rf_ctf_blue_carrier_set(0);
          rf_ctf_broadcast_flag_dropped_packet35(0);
          result = *(_DWORD *)(*(_DWORD *)(dword_77D6E8 + 660) + 68) | 2;
          *(_DWORD *)(*(_DWORD *)(dword_77D6E8 + 660) + 68) = result;
        }
        else
        {
          result = rf_ctf_red_carrier_get();
          if ( result == a1 )
          {
            rf_ctf_red_carrier_set(0);
            rf_ctf_broadcast_flag_dropped_packet35(1);
            result = dword_77D6E4;
            *(_DWORD *)(*(_DWORD *)(dword_77D6E4 + 660) + 68) |= 2u;
          }
        }
      }
    }
  }
  return result;
}

