// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004915F0 rf_multiplayer_object_delete_callback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl object pointer,thin wrapper calls object_delete_dispatch and returns delegate EAX. No own object-type gate,deferred-delete flag,player unlink or NULL guard. Does not always
// free a particular resource class; destruction policy delegated to type dispatcher.
int __cdecl rf_multiplayer_object_delete_callback(_DWORD *a1)
{
  return rf_object_delete_dispatch(a1);
}

