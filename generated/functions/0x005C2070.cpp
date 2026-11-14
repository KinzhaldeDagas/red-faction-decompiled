// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C2070 rf_d3d8_set_identity_world_view_and_projection
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl device pointer. Creates3 zeroed64-byte matrices with diagonal1. Calls device vtable148 with transform type256 and identity,returns immediately on ANY nonzero result;then type2 identity,same any-nonzero early return. Projection uses width2,height2*screenHeight187CC98/screenWidth187CC94. BYTE1DAEDA9 nonzero chooses near1,far10.001;zero near0.001,far1.001. Projection entries[0]=2*near/width,[5]=2*near/height,[10]=far/(far-near),[11]=1,[14]=-[10]*near,[15]=0;remaining entries0. Values pass through float locals/stores. Calls vtable148 type3 with projection and returns raw result. No screen/divisor/finite/device validation,viewport/FOV/aspect-source override or prior-transform
// restoration. Positive nonzero world/view return also stops,not merely negative HRESULT.
int __cdecl rf_d3d8_set_identity_world_view_and_projection(int a1)
{
  float v2; // [esp+0h] [ebp-E4h]
  float v3[16]; // [esp+4h] [ebp-E0h] BYREF
  float v4[17]; // [esp+44h] [ebp-A0h] BYREF
  float v5; // [esp+88h] [ebp-5Ch]
  float v6; // [esp+8Ch] [ebp-58h]
  float v7; // [esp+90h] [ebp-54h]
  float v8; // [esp+94h] [ebp-50h]
  int v9; // [esp+98h] [ebp-4Ch]
  float v10[16]; // [esp+9Ch] [ebp-48h] BYREF
  float v11; // [esp+DCh] [ebp-8h]
  float v12; // [esp+E0h] [ebp-4h]

  memset(v10, 0, sizeof(v10));
  memset(v3, 0, sizeof(v3));
  memset(v4, 0, 0x40u);
  v10[0] = 1.0;
  v10[5] = 1.0;
  v10[10] = 1.0;
  v10[15] = 1.0;
  v3[0] = 1.0;
  v3[5] = 1.0;
  v3[10] = 1.0;
  v3[15] = 1.0;
  v4[0] = 1.0;
  v4[5] = 1.0;
  v4[10] = 1.0;
  v4[15] = 1.0;
  v9 = (*(int (__stdcall **)(int, int, float *))(*(_DWORD *)a1 + 148))(a1, 256, v10);
  if ( v9 )
    return v9;
  v9 = (*(int (__stdcall **)(int, int, float *))(*(_DWORD *)a1 + 148))(a1, 2, v3);
  if ( v9 )
    return v9;
  v7 = 2.0;
  v6 = (double)dword_187CC98 / (double)dword_187CC94 * (float)2.0;
  if ( unk_1DAEDA9 )
  {
    v5 = 1.0;
    v2 = 10.001;
  }
  else
  {
    v5 = 0.001;
    v2 = 1.001;
  }
  v12 = v5 * 2.0 / v7;
  v11 = v5 * 2.0 / v6;
  v8 = v2 / (v2 - v5);
  v4[0] = v12;
  v4[5] = v11;
  v4[10] = v8;
  v4[11] = 1.0;
  v4[14] = -v8 * v5;
  v4[15] = 0.0;
  return (*(int (__stdcall **)(int, int, float *))(*(_DWORD *)a1 + 148))(a1, 3, v4);
}

