// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602130 rf_jpeg_huff_finish_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:finish_pass_huff matched): Createslocalworkingstatefromdest/savedentropy,flush_bits;FALSEisfatal24 CantSuspend(finishingpasscannotpause). CommitssuccessfulnextByte/freeandbitstate/predictorsbacktocinfo/entropy. DoesnotwriteEOI,closeFILE,destroyencoderorchangeglobalcompressionstate. Voidcallback;incidentalreturnlastDCvalue.
int __cdecl rf_jpeg_huff_finish_pass(int a1)
{
  _DWORD *v1; // ecx
  int result; // eax
  int v3; // [esp+0h] [ebp-28h] BYREF
  int v4; // [esp+4h] [ebp-24h]
  int v5; // [esp+8h] [ebp-20h]
  int v6; // [esp+Ch] [ebp-1Ch]
  int v7; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+1Ch] [ebp-Ch]
  int v11; // [esp+20h] [ebp-8h]
  _DWORD *v12; // [esp+24h] [ebp-4h]

  v12 = *(_DWORD **)(a1 + 360);
  v3 = **(_DWORD **)(a1 + 24);
  v4 = *(_DWORD *)(*(_DWORD *)(a1 + 24) + 4);
  v5 = v12[3];
  v6 = v12[4];
  v7 = v12[5];
  v8 = v12[6];
  v9 = v12[7];
  v10 = v12[8];
  v11 = a1;
  if ( !rf_jpeg_huff_flush_bits((int)&v3) )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 24;
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  **(_DWORD **)(a1 + 24) = v3;
  *(_DWORD *)(*(_DWORD *)(a1 + 24) + 4) = v4;
  v1 = v12 + 3;
  v12[3] = v5;
  v1[1] = v6;
  v1[2] = v7;
  v1[3] = v8;
  v1[4] = v9;
  result = v10;
  v1[5] = v10;
  return result;
}

