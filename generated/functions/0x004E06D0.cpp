// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E06D0 rf_player_set_view_target_uid_from_object
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Tests object argument nonNULL then player nonNULL; if both exist, copy object UID DWORD+44 into player view-target DWORD+180. No resolution/classification, NULL-target clearing or player flag update. EAX holds player on write, is incidental on skipped paths.
int __cdecl rf_player_set_view_target_uid_from_object(int a1, int a2)
{
  int result; // eax

  if ( a2 )
  {
    if ( a1 )
    {
      *(_DWORD *)(a1 + 180) = *(_DWORD *)(a2 + 44);
      return a1;
    }
  }
  return result;
}

