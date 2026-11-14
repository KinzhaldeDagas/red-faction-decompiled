// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00494F20 rf_server_send_glass_break_packet54
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl(rawDWORD identifier,vectorA3f*,vectorB3f*,rawBYTE flag). Only mode1/authority EXACT1 builds32-byte packet: opcode54,payloadWORD1=29,identifierDWORD3,flagBYTE7,vectorA
// floats8/12/16,vectorB20/24/28. Individual float loads/stores preserve binary32 serialization order; no normal/radius validation or quantization. Glass face break callers invoke it.
// Sends reliable queue4A0070(player,packet,32,0) to nonlocal players with net nonnull and netDWORD12 EXACT2. No distance/visibility filter or local glass mutation; return EAX
// traversal artifact.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Compiled descriptor54 ->recovered495200 identifies DWORD as saved geometry ID,vectorA as impact position,vectorB as direction;flag nonzero chooses
// nondirectional break,zero directional. Receiver normalizes vectorB before world check,looks up savedID then consumes first face at record+40,forces final delegate argument1.
// Existing32-byte reliable sender type/audience unchanged.
int __cdecl rf_server_send_glass_break_packet54(int a1, float *a2, float *a3, unsigned __int8 a4)
{
  int result; // eax
  int v5; // [esp+0h] [ebp-23Ch]
  unsigned __int8 Src[8]; // [esp+2Ch] [ebp-210h] BYREF
  float v7; // [esp+34h] [ebp-208h]
  float v8; // [esp+38h] [ebp-204h]
  float v9; // [esp+3Ch] [ebp-200h]
  float v10; // [esp+40h] [ebp-1FCh]
  float v11; // [esp+44h] [ebp-1F8h]
  float v12; // [esp+48h] [ebp-1F4h]
  unsigned __int8 v13; // [esp+237h] [ebp-5h]
  int i; // [esp+238h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v13 = a4;
    Src[0] = 54;
    *(_DWORD *)&Src[3] = a1;
    Src[7] = a4;
    v7 = *a2;
    v8 = a2[1];
    v9 = a2[2];
    v10 = *a3;
    v11 = a3[1];
    v12 = a3[2];
    *(_WORD *)&Src[1] = 29;
    result = 0;
    for ( i = dword_87C324; i; i = v5 )
    {
      if ( i != rf_local_fpgun_player && *(_DWORD *)(i + 4608) && *(_DWORD *)(*(_DWORD *)(i + 4608) + 12) == 2 )
        rf_multiplayer_queue_reliable_packet(i, Src, 0x20u, 0);
      if ( *(_DWORD *)i == dword_87C324 )
        v5 = 0;
      else
        v5 = *(_DWORD *)i;
      result = v5;
    }
  }
  return result;
}

