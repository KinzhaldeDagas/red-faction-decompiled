// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6470 rf_server_broadcast_reload_packet46
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Existing verified server reload packet46 confirmed native body. Cdecl(entity,weapon,reserve,magazine), runtime1 authority EXACT1; read entity.handle44 plus
// raw three args, WORD payload16,total19, unreliable broadcast. No own entityNULL/weapon range/ammo clamp. Descriptor46 at662B70 binds recovered client receiver4B6310: maps handle,
// starts reload(entity,1,1) then stores staged/live received values. Existing eager-authoritative inventory note preserved; callback definition now present, all types/bytes
// unchanged.
int __cdecl rf_server_broadcast_reload_packet46(int a1, int a2, int a3, int a4)
{
  int result; // eax
  char Src[7]; // [esp+18h] [ebp-208h] BYREF
  int v6; // [esp+1Fh] [ebp-201h]
  int v7; // [esp+23h] [ebp-1FDh]
  int v8; // [esp+27h] [ebp-1F9h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    Src[0] = 46;
    *(_DWORD *)&Src[3] = *(_DWORD *)(a1 + 44);
    v6 = a2;
    v7 = a3;
    v8 = a4;
    *(_WORD *)&Src[1] = 16;
    return rf_multiplayer_broadcast_unreliable_packet(Src, 19);
  }
  return result;
}

