// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DD65 crt_message_box_a_lazy_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(text,caption,rawFlags), signed dialog result or0. Obtain encoded-null sentinel, initialize local owner0. ONLY literal global encoded MessageBox
// cache2021DB8==0 triggers LoadLibraryA(USER32.DLL); failed load or missing MessageBoxA returns0. Publish encoded MessageBox pointer BEFORE other optional resolves; no lock/once
// rollback/FreeLibrary. Resolve/encode GetActiveWindow->2021DBC,GetLastActivePopup->2021DC0,GetUserObjectInformationA->2021DC8; test ENCODED result against literal0, not
// encoded-null, before optionally resolving GetProcessWindowStation->2021DC4. Later compare station/userinfo caches with encoded-null and decode both; missing/NULL decoded API goes
// owner-selection route without OR flag. If both APIs available: call station(); NULL station, failed userinfo(station,1,12byteBuffer,12,&returnedLength), or unset bufferDWORD+8 bit0
// -> OR rawFlags0x200000 and SKIP owner lookup. Successful visible bit or missing APIs -> decode active-window callback if cache!=sentinel, call it; if owner nonzero and popup
// callback cache!=sentinel and decodednonnull, replace owner with popup return even ifNULL. Finally decode LIVE MessageBox cache; NULL returns0 else
// stdcall(owner,text,caption,flags), forwarding EAX. No string validation, library unloading, API-error normalization, returned-length validation, encoded-cache retry after first
// publication or race protection.
int __cdecl crt_message_box_a_lazy_dispatch(int a1, int a2, int a3)
{
  PVOID v3; // ebx
  HMODULE LibraryA; // eax
  HMODULE v5; // edi
  int (__stdcall *MessageBoxA)(HWND, LPCSTR, LPCSTR, UINT); // eax
  HWND (__stdcall *GetActiveWindow)(); // eax
  HWND (__stdcall *GetLastActivePopup)(HWND); // eax
  BOOL (__stdcall *GetUserObjectInformationA)(HANDLE, int, PVOID, DWORD, LPDWORD); // eax
  HWINSTA (__stdcall *GetProcessWindowStation)(); // eax
  int (*v11)(void); // esi
  PVOID v12; // eax
  int (__stdcall *v13)(int, int, _BYTE *, int, _BYTE *); // edi
  int v14; // eax
  int (*v15)(void); // eax
  int (__stdcall *v16)(int); // eax
  int (__stdcall *v17)(int, int, int, int); // eax
  _BYTE v19[12]; // [esp+10h] [ebp-14h] BYREF
  _BYTE v20[4]; // [esp+1Ch] [ebp-8h] BYREF
  int v21; // [esp+20h] [ebp-4h]

  v21 = 0;
  v3 = _encoded_null();
  if ( !dword_2021DB8 )
  {
    LibraryA = LoadLibraryA("USER32.DLL");
    v5 = LibraryA;
    if ( !LibraryA )
      return 0;
    MessageBoxA = (int (__stdcall *)(HWND, LPCSTR, LPCSTR, UINT))GetProcAddress(LibraryA, "MessageBoxA");
    if ( !MessageBoxA )
      return 0;
    dword_2021DB8 = _encode_pointer(MessageBoxA);
    GetActiveWindow = (HWND (__stdcall *)())GetProcAddress(v5, "GetActiveWindow");
    dword_2021DBC = _encode_pointer(GetActiveWindow);
    GetLastActivePopup = (HWND (__stdcall *)(HWND))GetProcAddress(v5, "GetLastActivePopup");
    dword_2021DC0 = _encode_pointer(GetLastActivePopup);
    GetUserObjectInformationA = (BOOL (__stdcall *)(HANDLE, int, PVOID, DWORD, LPDWORD))GetProcAddress(
                                                                                          v5,
                                                                                          "GetUserObjectInformationA");
    dword_2021DC8 = _encode_pointer(GetUserObjectInformationA);
    if ( dword_2021DC8 )
    {
      GetProcessWindowStation = (HWINSTA (__stdcall *)())GetProcAddress(v5, "GetProcessWindowStation");
      dword_2021DC4 = _encode_pointer(GetProcessWindowStation);
    }
  }
  if ( dword_2021DC4 == v3
    || dword_2021DC8 == v3
    || (v11 = (int (*)(void))_decode_pointer(dword_2021DC4),
        v12 = _decode_pointer(dword_2021DC8),
        v13 = (int (__stdcall *)(int, int, _BYTE *, int, _BYTE *))v12,
        !v11)
    || !v12
    || (v14 = v11()) != 0 && v13(v14, 1, v19, 12, v20) && (v19[8] & 1) != 0 )
  {
    if ( dword_2021DBC != v3 )
    {
      v15 = (int (*)(void))_decode_pointer(dword_2021DBC);
      if ( v15 )
      {
        v21 = v15();
        if ( v21 )
        {
          if ( dword_2021DC0 != v3 )
          {
            v16 = (int (__stdcall *)(int))_decode_pointer(dword_2021DC0);
            if ( v16 )
              v21 = v16(v21);
          }
        }
      }
    }
  }
  else
  {
    a3 |= 0x200000u;
  }
  v17 = (int (__stdcall *)(int, int, int, int))_decode_pointer(dword_2021DB8);
  if ( v17 )
    return v17(v21, a1, a2, a3);
  return 0;
}

