// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495A00 rf_player_state260_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall260-byte embedded state(Player3968),source,RET4,returns receiver. DWORDs0/4/8,16,32/36/40/44,UNALIGNED
// DWORD50,56/60,180/184,192,248/252/256;BYTES12,20/21,28/29,48/49,188,196;FLOATs24/64/164/168/172/176. Copies vector68,matrix80,matrix116,vector152,vector200,matrix212 through
// helpers. Unaligned DWORD50 copies color-like bytes50..53 as raw bits,not pointer dereference or float. Padding13..15,22..23,30..31,54..55,189..191,197..199 untouched. No resource
// ownership operation or validation beyond listed helper copies.
_DWORD *__thiscall rf_player_state260_assign(_DWORD *this, int a2)
{
  float v4[3]; // [esp+4h] [ebp-24h] BYREF
  float v5[3]; // [esp+10h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  *this = *(_DWORD *)a2;
  *(this + 1) = *(_DWORD *)(a2 + 4);
  *(this + 2) = *(_DWORD *)(a2 + 8);
  *((_BYTE *)this + 12) = *(_BYTE *)(a2 + 12);
  *(this + 4) = *(_DWORD *)(a2 + 16);
  *((_BYTE *)this + 20) = *(_BYTE *)(a2 + 20);
  *((_BYTE *)this + 21) = *(_BYTE *)(a2 + 21);
  *((float *)this + 6) = *(float *)(a2 + 24);
  *((_BYTE *)this + 28) = *(_BYTE *)(a2 + 28);
  *((_BYTE *)this + 29) = *(_BYTE *)(a2 + 29);
  *(this + 8) = *(_DWORD *)(a2 + 32);
  *(this + 9) = *(_DWORD *)(a2 + 36);
  *(this + 10) = *(_DWORD *)(a2 + 40);
  *(this + 11) = *(_DWORD *)(a2 + 44);
  *((_BYTE *)this + 48) = *(_BYTE *)(a2 + 48);
  *((_BYTE *)this + 49) = *(_BYTE *)(a2 + 49);
  *(_DWORD *)((char *)this + 50) = *(_DWORD *)(a2 + 50);
  *(this + 14) = *(_DWORD *)(a2 + 56);
  *(this + 15) = *(_DWORD *)(a2 + 60);
  *((float *)this + 16) = *(float *)(a2 + 64);
  rf_vector_copy((float *)this + 17, copy_result, (const float *)(a2 + 68));
  rf_matrix3_copy((float *)this + 20, (const float *)(a2 + 80));
  rf_matrix3_copy((float *)this + 29, (const float *)(a2 + 116));
  rf_vector_copy((float *)this + 38, v5, (const float *)(a2 + 152));
  *((float *)this + 41) = *(float *)(a2 + 164);
  *((float *)this + 42) = *(float *)(a2 + 168);
  *((float *)this + 43) = *(float *)(a2 + 172);
  *((float *)this + 44) = *(float *)(a2 + 176);
  *(this + 45) = *(_DWORD *)(a2 + 180);
  *(this + 46) = *(_DWORD *)(a2 + 184);
  *((_BYTE *)this + 188) = *(_BYTE *)(a2 + 188);
  *(this + 48) = *(_DWORD *)(a2 + 192);
  *((_BYTE *)this + 196) = *(_BYTE *)(a2 + 196);
  rf_vector_copy((float *)this + 50, v4, (const float *)(a2 + 200));
  rf_matrix3_copy((float *)this + 53, (const float *)(a2 + 212));
  *(this + 62) = *(_DWORD *)(a2 + 248);
  *(this + 63) = *(_DWORD *)(a2 + 252);
  *(this + 64) = *(_DWORD *)(a2 + 256);
  return this;
}

