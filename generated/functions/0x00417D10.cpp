// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417D10 rf_monitor_find_record
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Walk circular monitor list from dword0x6807E4 through next pointer+0 until sentinel address0x6807E4. Return first record whose identifier+0xC equals input, else0. Uses exact identifier equality; does not resolve the clutter or validate its continued existence.
int *__cdecl rf_monitor_find_record(int a1)
{
  _DWORD *i; // [esp+0h] [ebp-4h]

  for ( i = (_DWORD *)dword_6807E4; i != &dword_6807E4; i = (_DWORD *)*i )
  {
    if ( i[3] == a1 )
      return i;
  }
  return nullptr;
}

