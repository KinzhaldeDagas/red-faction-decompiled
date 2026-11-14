// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C4160 rf_d3d8_read_backbuffer_rectangle
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Arguments (left,top,width,height,destination). NULL destination returns RF format code 3 immediately. Otherwise optionally flushes pending immediate buffers, calls GetBackBuffer(index0,type0) without checking HRESULT, and LockRect with READONLY=16 and rect {left,top,left+width-1,top+height-1}. Lock failure returns 0 without Release; unsupported format after successful lock also returns 0 without UnlockRect/Release. Supported device format -> (RF format,bytesPerPixel): 20->(6,3),21/22->(7,4),23->(3,2),24/25->(5,2),26/30->(4,2). Copies height rows of width*bpp bytes: source=pBits+pitch*(row+top)+bpp*left, destination=dst+width*bpp*row. This literally reapplies offsets after locking the specified rectangle. Supported path then UnlockRect/Release and returns RF format. No
// dimension/capacity/rectangle validation or conversion; lock right/bottom values are width/height minus one.
int __cdecl rf_d3d8_read_backbuffer_rectangle(int a1, int a2, int a3, int a4, void *a5)
{
  int v6; // [esp+Ch] [ebp-2Ch]
  int v7; // [esp+10h] [ebp-28h] BYREF
  int i; // [esp+14h] [ebp-24h]
  _DWORD v9[4]; // [esp+18h] [ebp-20h] BYREF
  _DWORD v10[2]; // [esp+28h] [ebp-10h] BYREF
  int v11; // [esp+30h] [ebp-8h]
  int v12; // [esp+34h] [ebp-4h]

  v12 = 0;
  if ( a5 )
  {
    if ( unk_1E014E5 )
      rf_renderer_flush_immediate_buffers();
    v7 = 0;
    (*(void (__thiscall **)(int, int, _DWORD, _DWORD, int *))(*(_DWORD *)dword_1DAEDC4 + 64))(
      dword_1DAEDC4,
      dword_1DAEDC4,
      0,
      0,
      &v7);
    v9[0] = a1;
    v9[1] = a2;
    v9[2] = a1 + a3 - 1;
    v9[3] = a2 + a4 - 1;
    if ( !(*(int (__stdcall **)(int, _DWORD *, _DWORD *, int))(*(_DWORD *)v7 + 36))(v7, v10, v9, 16) )
    {
      v6 = v10[1];
      switch ( unk_1DAE8FC )
      {
        case 0x14:
          v12 = 6;
          v11 = 3;
          goto LABEL_13;
        case 0x15:
        case 0x16:
          v12 = 7;
          v11 = 4;
          goto LABEL_13;
        case 0x17:
          v12 = 3;
          v11 = 2;
          goto LABEL_13;
        case 0x18:
        case 0x19:
          v12 = 5;
          v11 = 2;
          goto LABEL_13;
        case 0x1A:
        case 0x1E:
          v12 = 4;
          v11 = 2;
LABEL_13:
          for ( i = 0; i < a4; ++i )
            memcpy((char *)a5 + v11 * a3 * i, (const void *)(v10[0] * (i + a2) + v6 + v11 * a1), v11 * a3);
          (*(void (__stdcall **)(int))(*(_DWORD *)v7 + 40))(v7);
          (*(void (__stdcall **)(int))(*(_DWORD *)v7 + 8))(v7);
          return v12;
        default:
          return v12;
      }
    }
    return 0;
  }
  else
  {
    return 3;
  }
}

