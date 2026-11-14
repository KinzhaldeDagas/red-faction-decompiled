// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1E60 sub_4E1E60
// UNREALRED VERIFIED [lan-body-credit-20261029] If multiplayer, nonnull player, nonnull network record Player+0x1200 and current body handle Player+0x14!=-1: append handle/network-id at cursor in64-entry ring, advance cursor and wrap at64. Sole direct caller4E1D70 records BEFORE clearing current body handle. It is death-transition history, not projectile-launch registration or a hit-time last-attacker cache.
unsigned __int8 __cdecl sub_4E1E60(int a1)
{
  unsigned __int8 result; // al

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode && a1 && *(_DWORD *)(a1 + 4608) && *(_DWORD *)(a1 + 20) != -1 )
  {
    unk_87C328[2 * dword_662E48] = *(_DWORD *)(a1 + 20);
    result = *(_BYTE *)(*(_DWORD *)(a1 + 4608) + 20);
    unk_87C32C[8 * dword_662E48++] = result;
    if ( dword_662E48 >= 64 )
      dword_662E48 = 0;
  }
  return result;
}

