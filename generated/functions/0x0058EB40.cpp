// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058EB40 rf_audio_initialize_device_primary_and_modes
// UNREALRED VERIFIED [dsound-playback-20261028]: Seven arguments window handle,sample rate,bits WORD,channels WORD,3D-mode byte,A3D-mode byte,property-extension byte. Overall initialized byte0x1BA1810==1 returns0. Clears COM-owned flag0x193BBE3,stores mode globals0x193BBE0/1/2; A3D or extension forces3D1,requesting both clears extension. A3D byte exactly1 attempts0x58F110; failure clears A3D and3D mode. Without A3D calls CoInitialize(NULL),ignores HRESULT,sets COM flag1,CoCreateInstance into device0x1951804,and device Initialize+40(NULL); failure-1 without complete rollback. Sets cooperative level+24(window,3); failure sets deviceNULL WITHOUT Release,formats local diagnostic,returns-1. Creates primary buffer descriptor36,flags17 if3D==1 else1,other fields0. On CreateSoundBuffer failure releases device andsetsNULL. If3D==1 then clears all modes,changes flags1,and IMMEDIATELY dereferences
// that NULL device for retry; assembly confirms no recreation between nulling and call. Returns-1 on failure branch even if retry could succeed. On primary success sets PCM format(tag1,requested channels/rate/bits,blockAlign=(bits/8)*channels),IGNORES SetFormat HRESULT. Initializes4096 sample records,30 backend slots,and16 stream slots. If3D==1,calls property-query-buffer setup0x58E970 but ignores result; listener setup0x5ED400 receives bool(A3D!=1),failure clears3D andextension modes. Extension exactly1 calls0x598950,ignores result. Builds volume tables,marks overall initialized1,returns0. No validation of format fields or broad partial-resource cleanup.
int __cdecl rf_audio_initialize_device_primary_and_modes(
        int a1,
        int a2,
        unsigned __int16 a3,
        __int16 a4,
        char a5,
        char a6,
        char a7)
{
  const char *v8; // eax
  const char *v9; // eax
  int v10; // [esp+4h] [ebp-144h]
  int v11; // [esp+4h] [ebp-144h]
  _WORD v12[2]; // [esp+8h] [ebp-140h] BYREF
  int v13; // [esp+Ch] [ebp-13Ch]
  int v14; // [esp+10h] [ebp-138h]
  unsigned __int16 v15; // [esp+14h] [ebp-134h]
  unsigned __int16 v16; // [esp+16h] [ebp-132h]
  __int16 v17; // [esp+18h] [ebp-130h]
  int v18; // [esp+1Ch] [ebp-12Ch] BYREF
  int v19; // [esp+20h] [ebp-128h]
  int v20; // [esp+24h] [ebp-124h]
  int v21; // [esp+28h] [ebp-120h]
  int v22; // [esp+2Ch] [ebp-11Ch]
  int v23; // [esp+30h] [ebp-118h]
  int v24; // [esp+34h] [ebp-114h]
  int v25; // [esp+38h] [ebp-110h]
  int v26; // [esp+3Ch] [ebp-10Ch]
  char Buffer[260]; // [esp+40h] [ebp-108h] BYREF

  if ( unk_1BA1810 == 1 )
    return 0;
  unk_193BBE3 = 0;
  unk_193BBE0 = a5;
  unk_193BBE1 = a6;
  unk_193BBE2 = a7;
  if ( a6 || a7 )
    unk_193BBE0 = 1;
  if ( a6 && a7 )
    unk_193BBE2 = 0;
  if ( unk_193BBE1 == 1 && rf_audio_try_a3d_com_device_setup() )
  {
    unk_193BBE1 = 0;
    unk_193BBE0 = 0;
  }
  if ( !unk_193BBE1 )
  {
    CoInitialize(nullptr);
    unk_193BBE3 = 1;
    if ( CoCreateInstance(&rclsid, nullptr, 1u, &riid, &MEMORY[0x1951804]) < 0 )
      return -1;
    if ( (*(int (__stdcall **)(LPVOID, _DWORD))(*(_DWORD *)MEMORY[0x1951804] + 40))(MEMORY[0x1951804], 0) < 0 )
      return -1;
  }
  v10 = (*(int (__stdcall **)(LPVOID, int, int))(*(_DWORD *)MEMORY[0x1951804] + 24))(MEMORY[0x1951804], a1, 3);
  if ( v10 >= 0 )
  {
    v19 = 0;
    v20 = 0;
    v21 = 0;
    v22 = 0;
    v23 = 0;
    v24 = 0;
    v25 = 0;
    v26 = 0;
    v18 = 36;
    if ( unk_193BBE0 == 1 )
      v19 = 17;
    else
      v19 = 1;
    v11 = (*(int (__stdcall **)(LPVOID, int *, _DWORD **, _DWORD))(*(_DWORD *)MEMORY[0x1951804] + 12))(
            MEMORY[0x1951804],
            &v18,
            &dword_195166C,
            0);
    if ( v11 >= 0 )
    {
      v12[0] = 1;
      v12[1] = a4;
      v13 = a2;
      v16 = a3;
      v17 = 0;
      v15 = a3 / 8 * a4;
      v14 = a2 * v15;
      (*(void (__stdcall **)(_DWORD *, _WORD *))(*dword_195166C + 56))(dword_195166C, v12);
      rf_sound_initialize_sample_record_fields();
      rf_dsound_initialize_backend_slot_fields();
      rf_audio_streaming_initialize_slots();
      if ( unk_193BBE0 == 1 )
      {
        rf_dsound_create_property_query_buffer();
        if ( rf_dsound3d_initialize_with_optional_property_check(unk_193BBE1 != 1) )
        {
          unk_193BBE0 = 0;
          unk_193BBE2 = 0;
        }
      }
      if ( unk_193BBE2 == 1 )
        rf_audio_property_extension_initialize();
      rf_dsound_build_volume_lookup_tables();
      unk_1BA1810 = 1;
      return 0;
    }
    else
    {
      v9 = rf_dsound_hresult_name_string(v11);
      sprintf(Buffer, "pDirectSound->CreateSoundBuffer() failed with return value: %s\n", v9);
      (*(void (__thiscall **)(LPVOID, LPVOID))(*(_DWORD *)MEMORY[0x1951804] + 8))(MEMORY[0x1951804], MEMORY[0x1951804]);
      MEMORY[0x1951804] = nullptr;
      if ( unk_193BBE0 == 1
        && (unk_193BBE0 = 0,
            unk_193BBE2 = 0,
            unk_193BBE1 = 0,
            v19 = 1,
            (*(int (__thiscall **)(LPVOID, LPVOID, int *, _DWORD **, _DWORD))(*(_DWORD *)MEMORY[0x1951804] + 12))(
              MEMORY[0x1951804],
              MEMORY[0x1951804],
              &v18,
              &dword_195166C,
              0) < 0) )
      {
        (*(void (__stdcall **)(LPVOID))(*(_DWORD *)MEMORY[0x1951804] + 8))(MEMORY[0x1951804]);
        MEMORY[0x1951804] = nullptr;
        return -1;
      }
      else
      {
        return -1;
      }
    }
  }
  else
  {
    MEMORY[0x1951804] = nullptr;
    v8 = rf_dsound_hresult_name_string(v10);
    sprintf(Buffer, "SetCooperativeLevel() failed with return value: %s\n", v8);
    return -1;
  }
}

