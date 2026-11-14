// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E970 rf_dsound_create_property_query_buffer
// UNREALRED VERIFIED [dsound-playback-20261028]: Constructs mono PCM WAVEFORMAT:22050Hz,16bits,blockAlign2,avgBytes44100,cbSize0. Creates32-byte secondary DS buffer,descriptor size36,flags131314,through device0x1951804 into0x1BA1808. Queries3D interface IID0x6562E0 into0x1BA180C,then property interface IID0x6562D0 into0x19514D4. Success requires nonnegative finalHRESULT andnonnull property,returns0. Failures-1; create failure nulls property,3D QI failure nulls3D pointer. Partial buffer/interface allocations are NOT released here,old globals not proactively released. Final diagnostic only sprintf into local buffer. No device-null guard.
int rf_dsound_create_property_query_buffer()
{
  const char *v1; // eax
  int v2; // [esp+0h] [ebp-144h]
  _WORD v3[2]; // [esp+4h] [ebp-140h] BYREF
  int v4; // [esp+8h] [ebp-13Ch]
  int v5; // [esp+Ch] [ebp-138h]
  __int16 v6; // [esp+10h] [ebp-134h]
  __int16 v7; // [esp+12h] [ebp-132h]
  __int16 v8; // [esp+14h] [ebp-130h]
  _DWORD v9[9]; // [esp+18h] [ebp-12Ch] BYREF
  char Buffer[260]; // [esp+3Ch] [ebp-108h] BYREF

  v3[0] = 1;
  v3[1] = 1;
  v4 = 22050;
  v7 = 16;
  v8 = 0;
  v6 = 2;
  v5 = 44100;
  v9[3] = 0;
  memset(&v9[5], 0, 16);
  v9[0] = 36;
  v9[1] = 131314;
  v9[2] = 32;
  v9[4] = v3;
  if ( (*(int (__stdcall **)(LPVOID, _DWORD *, _DWORD **, _DWORD))(*(_DWORD *)MEMORY[0x1951804] + 12))(
         MEMORY[0x1951804],
         v9,
         &dword_1BA1808,
         0) >= 0 )
  {
    if ( (*(int (__stdcall **)(_DWORD *, void *, _DWORD **))*dword_1BA1808)(dword_1BA1808, &unk_6562E0, &dword_1BA180C) >= 0 )
    {
      v2 = (*(int (__stdcall **)(_DWORD *, void *, _DWORD *))*dword_1BA180C)(dword_1BA180C, &unk_6562D0, &dword_19514D4);
      if ( v2 >= 0 && dword_19514D4 )
      {
        return 0;
      }
      else
      {
        v1 = rf_dsound_hresult_name_string(v2);
        sprintf(Buffer, "Failed to get sound card property set: %s\n", v1);
        return -1;
      }
    }
    else
    {
      dword_1BA180C = nullptr;
      return -1;
    }
  }
  else
  {
    dword_19514D4 = 0;
    return -1;
  }
}

