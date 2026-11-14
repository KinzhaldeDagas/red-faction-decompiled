// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBE30 sub_4DBE30
// UNREALRED VERIFIED [lan-body-credit-20261029] Resets all64 historical body-handle slots to-1 and network-id bytes to0xFF, then resets insertion cursor0x662E48 to0. Called by player initialization4DBC30 and level/player reset4DBEF0. History belongs to the current world/level lifetime, not permanently to a player.
int sub_4DBE30()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    unk_87C328[2 * i] = -1;
    unk_87C32C[8 * i] = -1;
    result = i + 1;
  }
  dword_662E48 = 0;
  return result;
}

