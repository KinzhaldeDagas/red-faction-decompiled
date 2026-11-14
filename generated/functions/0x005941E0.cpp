// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005941E0 rf_window_register_class_and_create
// UNREALRED VERIFIED [system-progress-20261028]: Gets module instance,registers WNDCLASSEXA size48 using class string0x1BC1F08 and procedure0x594370,style0x1003,APP_ICON,arrow cursor. Mode0x1BC2140 chooses stock background4 versus5. Register failure returns0. Mode set creates overlapped window style0xCF0000 at default position/size,ShowWindow10,UpdateWindow. Otherwise creates32x32 popup centered on screen,hides cursor,unclips cursor,sets active/foreground. Stores HWND0x1BC212C. Returns1 after registration even if CreateWindowEx fails; does not destroy an old window or unregister class here.
int rf_window_register_class_and_create()
{
  int SystemMetrics; // eax
  int v2; // [esp-1Ch] [ebp-50h]
  HINSTANCE v3; // [esp-8h] [ebp-3Ch]
  WNDCLASSEXA v4; // [esp+0h] [ebp-34h] BYREF
  HINSTANCE hInstance; // [esp+30h] [ebp-4h]

  hInstance = GetModuleHandleA(nullptr);
  v4.hInstance = hInstance;
  v4.lpszClassName = (LPCSTR)&dword_1BA1F00[32770];
  v4.lpfnWndProc = rf_window_message_procedure;
  v4.style = 4099;
  v4.cbSize = 48;
  v4.hIcon = LoadIconA(hInstance, "APP_ICON");
  v4.hIconSm = nullptr;
  v4.hCursor = LoadCursorA(nullptr, (LPCSTR)0x7F00);
  v4.lpszMenuName = nullptr;
  v4.cbClsExtra = 0;
  v4.cbWndExtra = 0;
  if ( unk_1BC2140 )
    v4.hbrBackground = (HBRUSH)GetStockObject(4);
  else
    v4.hbrBackground = (HBRUSH)GetStockObject(5);
  if ( !RegisterClassExA(&v4) )
    return 0;
  if ( unk_1BC2140 )
  {
    hWnd = CreateWindowExA(
             0,
             (LPCSTR)&dword_1BA1F00[32770],
             MEMORY[0x1BC1F88],
             (DWORD)&unk_CF0000,
             0x80000000,
             0,
             0x80000000,
             0,
             nullptr,
             nullptr,
             hInstance,
             nullptr);
    ShowWindow(hWnd, 10);
    UpdateWindow(hWnd);
  }
  else
  {
    v3 = hInstance;
    v2 = (GetSystemMetrics(1) - 32) / 2;
    SystemMetrics = GetSystemMetrics(0);
    hWnd = CreateWindowExA(
             0,
             (LPCSTR)&dword_1BA1F00[32770],
             MEMORY[0x1BC1F88],
             0x80000000,
             (SystemMetrics - 32) / 2,
             v2,
             32,
             32,
             nullptr,
             nullptr,
             v3,
             nullptr);
    ShowCursor(0);
    ClipCursor(nullptr);
    SetActiveWindow(hWnd);
    SetForegroundWindow(hWnd);
  }
  return 1;
}

