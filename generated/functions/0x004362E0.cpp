// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004362E0 rf_object_cached_room_byte66
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required record pointer), returns BYTE through AL, NOT normalized Boolean or fullEAX integer.486DE0 with
// ECX=record reads its first DWORD as cached room pointer. NULL cached room returnsAL0; nonNULL returns raw room BYTE+66, including values other than0/1. UpperEAX retains incidental
// room-pointer bits. No input-record NULL guard before first-DWORD getter, geometry/room lookup, flag masking, ownership/type check or mutation.
char __cdecl rf_object_cached_room_byte66(void *a1)
{
  int first_dword; // [esp+0h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(a1);
  if ( first_dword )
    return *(_BYTE *)(first_dword + 66);
  else
    return 0;
}

