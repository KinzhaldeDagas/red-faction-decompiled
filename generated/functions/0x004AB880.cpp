// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AB880 rf_network_broadcast_clutter_removal_type30
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl object pointer,one stackslot. Exact runtimeMultiplayer1 AND serverAuthority1 gates packet construction;otherwise returns incidental runtimeflagEAX without object dereference. Admitted path builds11-byte packet:typeBYTE30,WORDpayloadlength8 at1,DWORDobject32 at3,DWORDobject684 at7. Delegates4A01D0 to queue/broadcast perplayer;no direct delivery/acknowledgment guarantee or local destruction. No own NULLobject/payload validation;security-cookie check/native queueeffects retained. Opaque XOR/JNZ repetition branches are never taken;does not repeatedly append payload. Second payload684 meaning not inferred.
int __cdecl rf_network_broadcast_clutter_removal_type30(int a1)
{
  int result; // eax
  char Src[7]; // [esp+10h] [ebp-208h] BYREF
  int v3; // [esp+17h] [ebp-201h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    Src[0] = 30;
    *(_DWORD *)&Src[3] = *(_DWORD *)(a1 + 32);
    v3 = *(_DWORD *)(a1 + 684);
    *(_WORD *)&Src[1] = 8;
    return rf_multiplayer_broadcast_unreliable_packet(Src, 11);
  }
  return result;
}

