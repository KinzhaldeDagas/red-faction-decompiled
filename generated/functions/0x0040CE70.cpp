// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CE70 rf_object_resolve_handle
// UNREALRED VERIFIED [mission-when-dead-20261013] Common handle lookup checks low16 slot bound, nonnull slot, and full generation-bearing handle equality. It does not reject combat-dead or pending-delete objects. A pending delete therefore remains a present blocker for When_Dead until object retirement removes its handle.
int __cdecl rf_object_resolve_handle(int a1)
{
  if ( a1 == -1 )
    return 0;
  if ( (unsigned __int16)a1 >= 0x400u )
    return 0;
  if ( unk_7B7E10[(unsigned __int16)a1] && *(_DWORD *)(unk_7B7E10[(unsigned __int16)a1] + 44) == a1 )
    return unk_7B7E10[(unsigned __int16)a1];
  return 0;
}

