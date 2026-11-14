// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004953A0 rf_player_copy_runtime_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall assignment of4612-byte Player into ALREADY CONSTRUCTED destination,stack source,RET4,returns destination. Assigns RFString8; copies
// links0/4,rawDWORDs16/20/24,vector28,byte40,score POINTER44,bytes48/49,DWORDs52..76,96 bytes80..175,bytes176/177,DWORDs180..224. Delegates embedded3740-byte state at228,260-byte
// state3968,60-byte pose4244. Copies fourDWORDs4228..4240;DWORDs4304/4308,FLOATs4312/4316,DWORDs4320/4324;25DWORDs4328..4424;latent/deferred alternate-zoom
// BYTE4428(0x114C);DWORD4432;32DWORDs4436..4560;FLOAT4564/4568,DWORD4572,fourFLOATs4576..4588;bytes4592/4593,FLOAT4596,DWORD4600,BYTE4604,net POINTER4608.
// Not whole-block memcpy: direct padding41..43,50..51,178..179,4429..4431,4594..4595,4605..4607 untouched; embedded helpers also omit their padding. Owned strings in128 nested28-byte
// records assigned through RFString API; score44,net4608 and other raw pointer values NOT cloned/addrefed. No source/destinationNULL,overlap or type check,list insertion,network
// socket clone or buffer construction. Scoreboard builder rewrites copied links separately. Existing descriptive name and alternate-zoom annotation preserved.
void *__thiscall rf_player_copy_runtime_state(void *this, int a2)
{
  float copy_result[3]; // [esp+8h] [ebp-1Ch] BYREF
  unsigned int m; // [esp+14h] [ebp-10h]
  unsigned int k; // [esp+18h] [ebp-Ch]
  unsigned int j; // [esp+1Ch] [ebp-8h]
  unsigned int i; // [esp+20h] [ebp-4h]

  *(_DWORD *)this = *(_DWORD *)a2;
  *((_DWORD *)this + 1) = *(_DWORD *)(a2 + 4);
  rf_string_assign_from_object((_DWORD *)this + 2, a2 + 8);
  *((_DWORD *)this + 4) = *(_DWORD *)(a2 + 16);
  *((_DWORD *)this + 5) = *(_DWORD *)(a2 + 20);
  *((_DWORD *)this + 6) = *(_DWORD *)(a2 + 24);
  rf_vector_copy((float *)this + 7, copy_result, (const float *)(a2 + 28));
  *((_BYTE *)this + 40) = *(_BYTE *)(a2 + 40);
  *((_DWORD *)this + 11) = *(_DWORD *)(a2 + 44);
  *((_BYTE *)this + 48) = *(_BYTE *)(a2 + 48);
  *((_BYTE *)this + 49) = *(_BYTE *)(a2 + 49);
  *((_DWORD *)this + 13) = *(_DWORD *)(a2 + 52);
  *((_DWORD *)this + 14) = *(_DWORD *)(a2 + 56);
  *((_DWORD *)this + 15) = *(_DWORD *)(a2 + 60);
  *((_DWORD *)this + 16) = *(_DWORD *)(a2 + 64);
  *((_DWORD *)this + 17) = *(_DWORD *)(a2 + 68);
  *((_DWORD *)this + 18) = *(_DWORD *)(a2 + 72);
  *((_DWORD *)this + 19) = *(_DWORD *)(a2 + 76);
  for ( i = 0; i < 0x60; ++i )
    *((_BYTE *)this + i + 80) = *(_BYTE *)(i + a2 + 80);
  *((_BYTE *)this + 176) = *(_BYTE *)(a2 + 176);
  *((_BYTE *)this + 177) = *(_BYTE *)(a2 + 177);
  *((_DWORD *)this + 45) = *(_DWORD *)(a2 + 180);
  *((_DWORD *)this + 46) = *(_DWORD *)(a2 + 184);
  *((_DWORD *)this + 47) = *(_DWORD *)(a2 + 188);
  *((_DWORD *)this + 48) = *(_DWORD *)(a2 + 192);
  *((_DWORD *)this + 49) = *(_DWORD *)(a2 + 196);
  *((_DWORD *)this + 50) = *(_DWORD *)(a2 + 200);
  *((_DWORD *)this + 51) = *(_DWORD *)(a2 + 204);
  *((_DWORD *)this + 52) = *(_DWORD *)(a2 + 208);
  *((_DWORD *)this + 53) = *(_DWORD *)(a2 + 212);
  *((_DWORD *)this + 54) = *(_DWORD *)(a2 + 216);
  *((_DWORD *)this + 55) = *(_DWORD *)(a2 + 220);
  *((_DWORD *)this + 56) = *(_DWORD *)(a2 + 224);
  rf_player_state3740_assign((int)this + 228, a2 + 228);
  rf_player_state260_assign((_DWORD *)this + 992, a2 + 3968);
  *((_DWORD *)this + 1057) = *(_DWORD *)(a2 + 4228);
  *((_DWORD *)this + 1058) = *(_DWORD *)(a2 + 4232);
  *((_DWORD *)this + 1059) = *(_DWORD *)(a2 + 4236);
  *((_DWORD *)this + 1060) = *(_DWORD *)(a2 + 4240);
  rf_player_pose60_assign((int)this + 4244, a2 + 4244);
  *((_DWORD *)this + 1076) = *(_DWORD *)(a2 + 4304);
  *((_DWORD *)this + 1077) = *(_DWORD *)(a2 + 4308);
  *((float *)this + 1078) = *(float *)(a2 + 4312);
  *((float *)this + 1079) = *(float *)(a2 + 4316);
  *((_DWORD *)this + 1080) = *(_DWORD *)(a2 + 4320);
  *((_DWORD *)this + 1081) = *(_DWORD *)(a2 + 4324);
  for ( j = 0; j < 0x19; ++j )
    *((_DWORD *)this + j + 1082) = *(_DWORD *)(a2 + 4 * j + 4328);
  *((_BYTE *)this + 4428) = *(_BYTE *)(a2 + 4428);
  *((_DWORD *)this + 1108) = *(_DWORD *)(a2 + 4432);
  for ( k = 0; k < 0x20; ++k )
    *((_DWORD *)this + k + 1109) = *(_DWORD *)(a2 + 4 * k + 4436);
  *((float *)this + 1141) = *(float *)(a2 + 4564);
  *((float *)this + 1142) = *(float *)(a2 + 4568);
  *((_DWORD *)this + 1143) = *(_DWORD *)(a2 + 4572);
  for ( m = 0; m < 4; ++m )
    *((float *)this + m + 1144) = *(float *)(a2 + 4 * m + 4576);
  *((_BYTE *)this + 4592) = *(_BYTE *)(a2 + 4592);
  *((_BYTE *)this + 4593) = *(_BYTE *)(a2 + 4593);
  *((float *)this + 1149) = *(float *)(a2 + 4596);
  *((_DWORD *)this + 1150) = *(_DWORD *)(a2 + 4600);
  *((_BYTE *)this + 4604) = *(_BYTE *)(a2 + 4604);
  *((_DWORD *)this + 1152) = *(_DWORD *)(a2 + 4608);
  return this;
}

