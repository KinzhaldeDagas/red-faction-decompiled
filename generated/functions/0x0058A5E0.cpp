// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A5E0 rf_mouse_initialize_directinput8
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Cursor mode flag exactly1 returns-1. Otherwise lazily LoadLibraryA("dinput8.dll") and resolves DirectInput8Create; missing DLL/export raises fatal mouse.cpp:408/417. Clears ready flag, creates version0x800 interface with IID at656360, creates system mouse device GUID656320, applies data format6562B8 and cooperative flags6 with main HWND, returning-1 on negative HRESULT at each stage. Calls Acquire without checking result, then sets ready1 and returns0. Failure does not immediately release partially created interfaces; release helper handles existing pointers later. No FreeLibrary here.
int rf_mouse_initialize_directinput8()
{
  HMODULE ModuleHandleA; // eax
  HWND main_hwnd; // eax
  HRESULT (__stdcall *DirectInput8Create)(HINSTANCE, DWORD, const IID *const, LPVOID *, LPUNKNOWN); // [esp+0h] [ebp-8h]

  if ( dword_663F4C == 1 )
    return -1;
  if ( !MEMORY[0x193A07C] )
  {
    MEMORY[0x193A07C] = LoadLibraryA("dinput8.dll");
    if ( !MEMORY[0x193A07C] )
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\input\\mouse.cpp", 408, "DirectX 8 not found!");
  }
  DirectInput8Create = (HRESULT (__stdcall *)(HINSTANCE, DWORD, const IID *const, LPVOID *, LPUNKNOWN))GetProcAddress(MEMORY[0x193A07C], "DirectInput8Create");
  if ( !DirectInput8Create )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\input\\mouse.cpp",
      417,
      "Cannot find d3d entry point!");
  unk_193A06C = 0;
  ModuleHandleA = GetModuleHandleA(nullptr);
  if ( DirectInput8Create(ModuleHandleA, 2048, (const IID *const)&unk_656360, &dword_193A064, nullptr) < 0 )
    return -1;
  if ( (*(int (__thiscall **)(LPVOID, LPVOID, void *, _DWORD **, _DWORD))(*(_DWORD *)dword_193A064 + 12))(
         dword_193A064,
         dword_193A064,
         &unk_656320,
         &dword_193A068,
         0) < 0 )
    return -1;
  if ( (*(int (__stdcall **)(_DWORD *, void *))(*dword_193A068 + 44))(dword_193A068, &unk_6562B8) < 0 )
    return -1;
  main_hwnd = rf_window_get_main_hwnd();
  if ( (*(int (__stdcall **)(_DWORD *, HWND, int))(*dword_193A068 + 52))(dword_193A068, main_hwnd, 6) < 0 )
    return -1;
  (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_193A068 + 28))(dword_193A068, dword_193A068);
  unk_193A06C = 1;
  return 0;
}

