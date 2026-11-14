// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570A00 rf_renderer_initialize_context_and_window
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): cdecl(width,height,bpp,backend,windowMode,HWND,opaqueFloat,byteOption,backendArg9,backendArg10),ten stack args. Reads registry Fast Animations default1 into byte663F05. Zeroes144B context187CC90;assigns current sequence182AB94 then increments it. Normalizes backend106->102 but passes original backend==106 as separate backend boolean. Stores physical width/height,bpp and signed bpp/8,mode,opaque float atCCB8 (only observed caller supplies1000),raw byte atCD14,depth modeCD1C=1,texture handlesCCE8/CCEC=-1,fog distances0/60;initial full-screen viewport/relative inclusive clip and aspect correction1. Calls570ED0 environment option;copies normalized backend into182AB90. Window mode200:style00C80000,AdjustWindowRect,queries
// work-area,centers horizontally with left-edge clamp ONLY,places at work-area TOP,shows/updates style/exstyle0 and NOTOPMOST/SWP_SHOWWINDOW;aspect=(desktopW/desktopH)/(float4/3). Mode201:style80080000/exstyle0,popup at0,0 with each size=max(desktop,requested);cached rectangle182A780=[0,0,width-1,height-1],aspect=(REQUESTED width/height)/(float4/3). Mode202:only desktop aspect calculation,does not alter HWND geometry/style here. Other mode invokes fatal error(gr.cpp1106). Win32 API failures and zero dimensions not checked. Sets byte663F06=1 BEFORE backend. Backend102 calls5C2F30(HWND,originalBackend==106,arg9,arg10) and ignores return;other backend IDs skip backend creation. Then fog enable(0..60)/disable(-1,-1),gamma1.0,flag182AB98=1,full viewport,clear color,present iff originalHWND nonNULL;returns0. D3D initializer separately replaces depth mode1 with0. No prior-context teardown or
// rollback.
int __cdecl rf_renderer_initialize_context_and_window(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        HWND a6,
        float a7,
        char a8,
        int a9,
        int a10)
{
  int v11; // [esp+14h] [ebp-78h]
  int v12; // [esp+18h] [ebp-74h]
  int v13; // [esp+28h] [ebp-64h]
  float v14; // [esp+2Ch] [ebp-60h]
  float v15; // [esp+30h] [ebp-5Ch]
  struct tagRECT Rect; // [esp+40h] [ebp-4Ch] BYREF
  float SystemMetrics; // [esp+50h] [ebp-3Ch]
  int Y; // [esp+54h] [ebp-38h]
  DWORD dwStyle; // [esp+58h] [ebp-34h]
  _DWORD pvParam[4]; // [esp+5Ch] [ebp-30h] BYREF
  int X; // [esp+6Ch] [ebp-20h]
  int cy; // [esp+70h] [ebp-1Ch]
  int v23; // [esp+74h] [ebp-18h]
  int v24; // [esp+78h] [ebp-14h]
  int v25; // [esp+7Ch] [ebp-10h]
  float v26; // [esp+80h] [ebp-Ch]
  HWND hWnd; // [esp+84h] [ebp-8h]
  BYTE Data[4]; // [esp+88h] [ebp-4h] BYREF

  hWnd = a6;
  rf_registry_read_dword_or_default(nullptr, "Fast Animations", Data, 1);
  byte_663F05 = *(_DWORD *)Data != 0;
  memset(&dword_187CC90, 0, 0x90u);
  dword_187CC90 = unk_182AB94++;
  if ( a4 == 106 )
    v13 = 102;
  else
    v13 = a4;
  dword_187CC9C = v13;
  dword_187CCB0 = a3;
  unk_187CCB4 = a3 / 8;
  unk_187CCA0 = a5;
  dword_187CC94 = a1;
  dword_187CC98 = a2;
  unk_187CCA8 = 1.0;
  unk_187CCBC = 0;
  unk_187CCC0 = 0;
  unk_187CCD4 = 0;
  unk_187CCDC = 0;
  unk_187CCD8 = a1 - 1;
  unk_187CCE0 = a2 - 1;
  unk_187CCC4 = a1;
  unk_187CCC8 = a2;
  unk_187CCB8 = a7;
  dword_187CD1C = 1;
  unk_187CCE8 = -1;
  unk_187CCEC = -1;
  flt_187CCF8 = 0.0;
  flt_187CCFC = 60.0;
  byte_187CD14 = a8;
  unk_187CD18 = 0;
  rf_renderer_read_sst_dualhead_environment_for_mode201();
  dword_182AB90 = dword_187CC9C;
  switch ( unk_187CCA0 )
  {
    case 0xC8:
      dwStyle = (DWORD)&unk_C80000;
      Rect.top = 0;
      Rect.left = 0;
      Rect.right = dword_187CC94;
      Rect.bottom = dword_187CC98;
      AdjustWindowRect(&Rect, (DWORD)&unk_C80000, 0);
      SystemParametersInfoA(0x30u, 0, pvParam, 0);
      v23 = pvParam[0] + (pvParam[2] - pvParam[0] - (Rect.right - Rect.left)) / 2;
      v24 = pvParam[1];
      if ( v23 < pvParam[0] )
        v23 = pvParam[0];
      X = v23;
      Y = v24;
      v25 = Rect.right - Rect.left;
      cy = Rect.bottom - Rect.top;
      ShowWindow(hWnd, 1);
      SetWindowLongA(hWnd, -16, dwStyle);
      SetWindowLongA(hWnd, -20, 0);
      SetWindowPos(hWnd, (HWND)0xFFFFFFFE, X, Y, v25, cy, 0x40u);
      SetActiveWindow(hWnd);
      SetForegroundWindow(hWnd);
      SystemMetrics = (float)GetSystemMetrics(0);
      v26 = (float)GetSystemMetrics(1);
      unk_187CCA8 = SystemMetrics / v26 / 1.333333373069763;
      break;
    case 0xC9:
      SetWindowLongA(hWnd, -20, 0);
      SetWindowLongA(hWnd, -16, -2146959360);
      ShowWindow(hWnd, 1);
      if ( GetSystemMetrics(0) <= dword_187CC94 )
        v12 = dword_187CC94;
      else
        v12 = GetSystemMetrics(0);
      if ( GetSystemMetrics(1) <= dword_187CC98 )
        v11 = dword_187CC98;
      else
        v11 = GetSystemMetrics(1);
      SetWindowPos(hWnd, (HWND)0xFFFFFFFE, 0, 0, v12, v11, 0);
      SetActiveWindow(hWnd);
      SetForegroundWindow(hWnd);
      unk_182A780 = 0;
      unk_182A784 = 0;
      unk_182A788 = dword_187CC94 - 1;
      unk_182A78C = dword_187CC98 - 1;
      unk_187CCA8 = (double)dword_187CC94 / (double)dword_187CC98 / 1.333333373069763;
      break;
    case 0xCA:
      v14 = (float)GetSystemMetrics(0);
      v15 = (float)GetSystemMetrics(1);
      unk_187CCA8 = v14 / v15 / 1.333333373069763;
      break;
    default:
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\gr\\gr.cpp",
        1106,
        "Invalid window_mode passed to gr_init\n");
  }
  byte_663F06 = 1;
  if ( dword_187CC9C == 102 )
    rf_d3d8_initialize_backend(a6, a4 == 106, a9, a10);
  rf_renderer_set_vertex_fog(1, 0, 0, 0, 0.0, 60.0);
  rf_renderer_set_vertex_fog(0, 0, 0, 0, -1.0, -1.0);
  rf_graphics_gamma_set(1.0);
  unk_182AB98 = 1;
  rf_renderer_reset_viewport_full_screen();
  rf_renderer_clear_color_backend_dispatch();
  if ( a6 )
    rf_renderer_present_with_full_viewport();
  return 0;
}

