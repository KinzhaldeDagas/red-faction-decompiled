// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1F10 rf_d3d8_set_window_client_rectangle_and_viewport
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): cdecl(HWND). Computes but does not use old-window inequality,stores HWND1DAEDF8,gets client RECT and converts BOTH corners to screen coordinates. Width=abs(right-left+1),height=abs(bottom-top+1),so ordinary exclusive Win32 client bounds gain ONE EXTRA PIXEL in each dimension. Caches screen-inclusive rect1DAED74 and local[0,0,width-1,height-1] rect1DAE8E4. Stores context viewport originCCBC/CCC0=screen left/top and effective dimensionsCCC4/CCC8. Calls device vtable+160 with local viewport(0,0,width,height,minZ0,maxZ1),ignores its result,then returns5C2070(device) incidental result. No resize/recreation,physical screen-dimension update,HWND/API/deviceNULL or positive-size guard. Generic wrapper570FB0 subsequently resets
// context/device viewport to full physical screen.
int __cdecl rf_d3d8_set_window_client_rectangle_and_viewport(HWND a1)
{
  _DWORD v2[6]; // [esp+8h] [ebp-3Ch] BYREF
  bool v3; // [esp+23h] [ebp-21h]
  struct tagRECT Rect; // [esp+24h] [ebp-20h] BYREF
  LONG left; // [esp+34h] [ebp-10h]
  LONG top; // [esp+38h] [ebp-Ch]
  int v7; // [esp+3Ch] [ebp-8h]
  int v8; // [esp+40h] [ebp-4h]

  v3 = a1 != unk_1DAEDF8;
  unk_1DAEDF8 = a1;
  GetClientRect(a1, &Rect);
  ClientToScreen(a1, (LPPOINT)&Rect);
  ClientToScreen(a1, (LPPOINT)&Rect.right);
  left = Rect.left;
  top = Rect.top;
  v8 = abs(Rect.right - Rect.left + 1);
  v7 = abs(Rect.bottom - Rect.top + 1);
  MEMORY[0x1DAED74].left = left;
  unk_1DAED78 = top;
  unk_1DAED7C = left + v8 - 1;
  unk_1DAED80 = top + v7 - 1;
  unk_1DAE8E4.left = 0;
  unk_1DAE8E8 = 0;
  unk_1DAE8EC = v8 - 1;
  unk_1DAE8F0 = v7 - 1;
  unk_187CCBC = left;
  unk_187CCC0 = top;
  unk_187CCC4 = v8;
  unk_187CCC8 = v7;
  v2[0] = 0;
  v2[1] = 0;
  v2[2] = v8;
  v2[3] = v7;
  *(float *)&v2[4] = 0.0;
  *(float *)&v2[5] = 1.0;
  (*(void (__stdcall **)(int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 160))(dword_1DAEDC4, v2);
  return rf_d3d8_set_identity_world_view_and_projection(dword_1DAEDC4);
}

