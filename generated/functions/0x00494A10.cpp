// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00494A10 rf_server_send_proximity_packet52
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl(excluded player,rawWORD id,position3f*,radiusFLOAT). Only mode EXACT1,authority EXACT1 builds fixed17-byte packet: opcode52 at0,payload lengthWORD1=14,idWORD3,XYZ binary32
// at5/9/13. No quantization or pointer validation. Traverses player circle,skips local and excluded player,resolves each player entity handle20. Valid entity admitted iff ORDERED
// radius>=fast_length(entity.common60-position); equality sends,unordered/NaN rejects. Does not require net-state2 in this loop or perform visibility/team checks. Calls UNRELIABLE
// queue49FEE0(player,packet,17); does not force immediate send. Void return.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Compiled descriptor52 ->recovered494950 confirms existing rawWORD is positional sound eventID;receiver sign-extends16-bit ID and plays at transmitted XYZ
// with gain1.0 and fixed17F10B0 argument. Sender's original radius-based recipient selection,17-byte envelope and unreliable transport unchanged;receiver has no corresponding own
// distance/runtime/source guard.
void __cdecl rf_server_send_proximity_packet52(int a1, __int16 a2, float *rhs, float a4)
{
  float *v4; // eax
  int v5; // [esp+0h] [ebp-234h]
  float out_vector[3]; // [esp+4h] [ebp-230h] BYREF
  int v7; // [esp+10h] [ebp-224h]
  __int16 v8; // [esp+14h] [ebp-220h]
  float v9; // [esp+18h] [ebp-21Ch]
  float v10; // [esp+1Ch] [ebp-218h]
  float v11; // [esp+20h] [ebp-214h]
  __int16 v12; // [esp+24h] [ebp-210h]
  unsigned __int16 v13; // [esp+28h] [ebp-20Ch]
  char Src[5]; // [esp+2Ch] [ebp-208h] BYREF
  float v15; // [esp+31h] [ebp-203h]
  float v16; // [esp+35h] [ebp-1FFh]
  float v17; // [esp+39h] [ebp-1FBh]
  int i; // [esp+230h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    Src[0] = 52;
    v12 = a2;
    *(_WORD *)&Src[3] = a2;
    v13 = 5;
    v11 = *rhs;
    v15 = v11;
    v13 = 9;
    v10 = rhs[1];
    v16 = v10;
    v13 = 13;
    v9 = rhs[2];
    v17 = v9;
    v13 = 17;
    v8 = 14;
    *(_WORD *)&Src[1] = 14;
    for ( i = dword_87C324; i; i = v5 )
    {
      if ( i != rf_local_fpgun_player && i != a1 )
      {
        v7 = rf_entity_resolve_handle(*(_DWORD *)(i + 20));
        if ( v7 )
        {
          v4 = rf_vector_subtract((const float *)(v7 + 60), out_vector, rhs);
          if ( a4 >= rf_vector_fast_length(v4) )
            rf_network_queue_unreliable_player_packet(i, Src, v13);
        }
      }
      if ( *(_DWORD *)i == dword_87C324 )
        v5 = 0;
      else
        v5 = *(_DWORD *)i;
    }
  }
}

