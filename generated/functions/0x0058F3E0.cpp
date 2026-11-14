// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F3E0 rf_dsound_buffer_slot_stop_release_unless_fading
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument slot. If flags+40 mask8 set,returns record unchanged without stopping/releasing ANYTHING. Otherwise if stream slot+12>=0,enters streaming critical section0x1E014B0,calls0x5D0200,leaves. If DS buffer+0nonnull,calls Stop+72; errors only format local diagnostic. Releases3D interface+4 ifnonnull and mainbuffer+0,each retrying up to10 times WHILE signed Release result is negative (not until reference count zero). Logs only to local formatted buffer. Finally0x58EFF0 clears record. If mainbuffer null but3D interface nonnull,it is not released. No slot guard; return record pointer.
int *__cdecl rf_dsound_buffer_slot_stop_release_unless_fading(int a1)
{
  int *result; // eax
  const char *v2; // eax
  int v3; // edx
  const char *v4; // eax
  int v5; // ecx
  const char *v6; // eax
  int v7; // [esp+0h] [ebp-118h]
  int v8; // [esp+4h] [ebp-114h]
  int *v9; // [esp+8h] [ebp-110h]
  int v10; // [esp+Ch] [ebp-10Ch]
  int v11; // [esp+Ch] [ebp-10Ch]
  int v12; // [esp+Ch] [ebp-10Ch]
  char Buffer[260]; // [esp+10h] [ebp-108h] BYREF

  result = &unk_1BA1820[11 * a1];
  v9 = result;
  if ( (result[10] & 8) == 0 )
  {
    if ( result[3] >= 0 )
    {
      EnterCriticalSection(&unk_1E014B0);
      rf_audio_stream_stop_slot(v9[3]);
      LeaveCriticalSection(&unk_1E014B0);
    }
    if ( *v9 )
    {
      v10 = (*(int (__stdcall **)(int))(*(_DWORD *)*v9 + 72))(*v9);
      if ( v10 < 0 )
      {
        v2 = rf_dsound_hresult_name_string(v10);
        sprintf(Buffer, "c->pdsb->Stop() failed with return value %s\n", v2);
      }
      if ( v9[1] )
      {
        v7 = 0;
        while ( 1 )
        {
          v3 = v7++;
          if ( v3 >= 10 )
            break;
          v11 = (*(int (__stdcall **)(int))(*(_DWORD *)v9[1] + 8))(v9[1]);
          if ( v11 >= 0 )
            break;
          v4 = rf_dsound_hresult_name_string(v11);
          sprintf(Buffer, "c->pds3db->Release() failed with return value %s\n", v4);
        }
      }
      v8 = 0;
      while ( 1 )
      {
        v5 = v8++;
        if ( v5 >= 10 )
          break;
        v12 = (*(int (__stdcall **)(int))(*(_DWORD *)*v9 + 8))(*v9);
        if ( v12 >= 0 )
          break;
        v6 = rf_dsound_hresult_name_string(v12);
        sprintf(Buffer, "c->pdsb->Release() failed with return value %s\n", v6);
      }
    }
    return rf_dsound_buffer_slot_clear_fields(a1);
  }
  return result;
}

