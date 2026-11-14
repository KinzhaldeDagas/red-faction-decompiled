// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042B6E0 rf_entity_read_current_room_byte65
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity pointer), returns literal AL byte, not normalized Boolean. NULL entity returns AL0; otherwise ECX getter486DE0 returns DWORD[entity+0]
// current room pointer. NULL room returnsAL0. Nonnull room loads BYTE[room+65] directly into AL, preserving the other EAX pointer bytes; does not mask/test byte or require exact1. No
// room resolution, validity/ownership/health checks or writes.
char __cdecl rf_entity_read_current_room_byte65(void *a1)
{
  int first_dword; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  first_dword = rf_receiver_get_first_dword(a1);
  if ( first_dword )
    return *(_BYTE *)(first_dword + 65);
  else
    return 0;
}

