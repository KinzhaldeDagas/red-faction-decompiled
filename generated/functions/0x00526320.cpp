// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526320 rf_light_additional_receiver_register
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl receiverSolid,positionPointer,orientationPointer, void. If globalD035F0 (pointer to circular-list head cell) NULL do nothing. Else malloc20 bytes WITHOUT failure check; fields next0,prev4,solid8,posPtr12,orientPtr16; borrowed transform pointers, not copied values. Empty list initializes node self-ring and head; nonempty inserts BEFORE unchanged head (tail append) via head.prev, preserving registration order. No duplicate test or flags. Direct D035F0 references are limited to context setup/cleanup, this registration/removal and526820 light coverage traversal; this body does not register collision sweeps. Debris spawn supplies embedded live transform addresses.
void __cdecl rf_light_additional_receiver_register(int a1, int a2, int a3)
{
  _DWORD *v3; // [esp+0h] [ebp-4h]

  if ( dword_D035F0 )
  {
    v3 = malloc(0x14u);
    v3[3] = a2;
    v3[4] = a3;
    v3[2] = a1;
    if ( *dword_D035F0 )
    {
      v3[1] = *(_DWORD *)(*dword_D035F0 + 4);
      *v3 = *dword_D035F0;
      **(_DWORD **)(*dword_D035F0 + 4) = v3;
      *(_DWORD *)(*dword_D035F0 + 4) = v3;
    }
    else
    {
      *v3 = v3;
      v3[1] = v3;
      *dword_D035F0 = v3;
    }
  }
}

