// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DD720 sub_4DD720
// UNREALRED VERIFIED [early-respawn-20260930] Walks the player list and returns only a player whose current entity handle at +0x14 matches the argument. Death finalizer 0x420140 uses this lookup before player death transition. After fresh allocation replaces Player+0x14, finalizing the old entity cannot select that player through this lookup.
_DWORD *__cdecl sub_4DD720(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)dword_87C324; i; i = v2 )
  {
    if ( i[5] == a1 )
      return i;
    if ( *i == dword_87C324 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)*i;
  }
  return nullptr;
}

