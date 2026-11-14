// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F110 rf_audio_try_a3d_com_device_setup
// UNREALRED VERIFIED [dsound-creation-20261028]: Tests a3d.dll via LoadLibrary/FreeLibrary, failure-1. Calls CoInitialize(NULL),ignores HRESULT,sets COM flag0x193BBE3=1. CoCreateInstance GUID0x664778/IID riid into device0x1951804,then QueryInterface GUID0x664768 into0x193BBE4; failures-1 without balanced release/CoUninitialize here. Queries20-byte capability structure via interface+40; requires unsigned field+4>=12. Calls interface+36(value12),then device+40(value0); latter negative result or insufficient capability releases main device only and zeros it. Success calls secondary interface+20(value3),ignores result,returns0. Does not set overall sound initialized flag or fully roll back partial interfaces.
int rf_audio_try_a3d_com_device_setup()
{
  int v1; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int v2; // [esp+4h] [ebp-18h]
  int v3; // [esp+8h] [ebp-14h]
  int v4; // [esp+Ch] [ebp-10h]
  int v5; // [esp+10h] [ebp-Ch]
  HMODULE hLibModule; // [esp+14h] [ebp-8h]
  HRESULT Instance; // [esp+18h] [ebp-4h]

  hLibModule = LoadLibraryA("a3d.dll");
  if ( !hLibModule )
    return -1;
  FreeLibrary(hLibModule);
  CoInitialize(nullptr);
  unk_193BBE3 = 1;
  Instance = CoCreateInstance(&stru_664778, nullptr, 1u, &riid, (LPVOID *)&dword_1951670[101]);
  if ( Instance < 0 )
    return -1;
  Instance = (**(int (__stdcall ***)(int, void *, void *))dword_1951670[101])(
               dword_1951670[101],
               &unk_664768,
               &dword_193BBE4);
  if ( Instance < 0 )
    return -1;
  v2 = 0;
  v3 = 0;
  v4 = 0;
  v5 = 0;
  v1 = 20;
  (*(void (__stdcall **)(_DWORD *, int *))(*dword_193BBE4 + 40))(dword_193BBE4, &v1);
  if ( v2 < 0xC
    || ((*(void (__stdcall **)(_DWORD *, int))(*dword_193BBE4 + 36))(dword_193BBE4, 12),
        Instance = (*(int (__stdcall **)(int, _DWORD))(*(_DWORD *)dword_1951670[101] + 40))(dword_1951670[101], 0),
        Instance < 0) )
  {
    (*(void (__thiscall **)(int, int))(*(_DWORD *)dword_1951670[101] + 8))(dword_1951670[101], dword_1951670[101]);
    dword_1951670[101] = 0;
    return -1;
  }
  else
  {
    (*(void (__stdcall **)(_DWORD *, int))(*dword_193BBE4 + 20))(dword_193BBE4, 3);
    return 0;
  }
}

