// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004997A0 rf_ctf_broadcast_flag_dropped_packet35
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(raw byte red selector), mode1 only. Normalizes any nonzero selector to1. Fixed18-byte packet: opcode35 at0, payload WORD1=15, normalized red selector BYTE3, red/blue capture
// BYTE4/5, XYZ floats at6/10/14. Starts position from shared vector17F10B0; if selected flag pointer exists copies its common position+60. A null flag uses shared-vector contents,
// not a proven zero constant. Broadcasts(buffer,18,0) without own authority/runtime guard. No flag placement, definition/physics-bit change, carrier mutation, score or timer changes.
// Internal cursor is uint16 but total here is fixed18.
int __cdecl rf_ctf_broadcast_flag_dropped_packet35(char a1)
{
  int result; // eax
  float v2[3]; // [esp+0h] [ebp-244h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-238h] BYREF
  __int16 v4; // [esp+18h] [ebp-22Ch]
  float v5; // [esp+1Ch] [ebp-228h]
  float v6; // [esp+20h] [ebp-224h]
  float v7; // [esp+24h] [ebp-220h]
  char v8; // [esp+29h] [ebp-21Bh]
  char v9; // [esp+2Ah] [ebp-21Ah]
  bool v10; // [esp+2Bh] [ebp-219h]
  unsigned __int16 v11; // [esp+2Ch] [ebp-218h]
  bool v12; // [esp+33h] [ebp-211h]
  unsigned __int8 Src; // [esp+34h] [ebp-210h] BYREF
  __int16 Src_1; // [esp+35h] [ebp-20Fh]
  bool Src_3; // [esp+37h] [ebp-20Dh]
  char v16; // [esp+38h] [ebp-20Ch]
  char v17; // [esp+39h] [ebp-20Bh]
  float destination; // [esp+238h] [ebp-Ch] BYREF
  float v19; // [esp+23Ch] [ebp-8h]
  float v20; // [esp+240h] [ebp-4h]

  result = rf_multiplayer_game_mode_get();
  if ( result == 1 )
  {
    v12 = a1 != 0;
    Src = 35;
    v10 = a1 != 0;
    Src_3 = a1 != 0;
    v9 = byte_77D6E0;
    v16 = byte_77D6E0;
    v8 = byte_77D6E1;
    v17 = byte_77D6E1;
    v11 = 6;
    rf_vector3_copy_return_destination(&destination, flt_17F10B0);
    if ( a1 )
    {
      if ( dword_77D6E4 )
        rf_vector_copy(&destination, copy_result, (const float *)(dword_77D6E4 + 60));
    }
    else if ( dword_77D6E8 )
    {
      rf_vector_copy(&destination, v2, (const float *)(dword_77D6E8 + 60));
    }
    v7 = destination;
    *(float *)(&Src + v11) = destination;
    v11 += 4;
    v6 = v19;
    *(float *)(&Src + v11) = v19;
    v11 += 4;
    v5 = v20;
    *(float *)(&Src + v11) = v20;
    v11 += 4;
    v4 = v11 - 3;
    Src_1 = v11 - 3;
    return rf_server_broadcast_packet(&Src, v11, 0);
  }
  return result;
}

