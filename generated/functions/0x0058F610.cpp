// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F610 rf_sound_sample_release_formats_file_buffers
// UNREALRED VERIFIED [dsound-creation-20261028]: Argument sample index; negative no-op,upper bound unchecked. Stops each active streaming slot whose sample index matches,under streaming critical section. Frees/nulls output WAVEFORMAT+536 and source WAVEFORMAT+532; closes HMMIO+544 ifnonnull. If sample DS buffer+524nonnull,Stop,then release3D interface+528 and main buffer,each retrying up to10 times only while signed Release returnnegative; nulls pointers. If main DS pointer null,orphan3D pointer not released. Clears name byte0,file-path byte256,hash+516=-1. Does NOT close sample ACM handle+540,reset references+588,offset+512,other metadata or registry count. Local diagnostics formatted but not emitted here.
void __cdecl rf_sound_sample_release_formats_file_buffers(int a1)
{
  const char *v1; // eax
  int v2; // ecx
  const char *v3; // eax
  int v4; // edx
  const char *v5; // eax
  int v6; // [esp+0h] [ebp-118h]
  int v7; // [esp+4h] [ebp-114h]
  int v8; // [esp+8h] [ebp-110h]
  int v9; // [esp+8h] [ebp-110h]
  int v10; // [esp+8h] [ebp-110h]
  int i; // [esp+Ch] [ebp-10Ch]
  char Buffer[256]; // [esp+10h] [ebp-108h] BYREF
  char *v13; // [esp+114h] [ebp-4h]

  if ( a1 >= 0 )
  {
    v13 = (char *)&unk_1951808 + 592 * a1;
    for ( i = 0; i < 16; ++i )
    {
      if ( (unk_1E01308[7 * i] & 1) != 0 && unk_1E012F0[7 * i] == a1 )
      {
        EnterCriticalSection(&unk_1E014B0);
        rf_audio_stream_stop_slot(i);
        LeaveCriticalSection(&unk_1E014B0);
      }
    }
    if ( *((_DWORD *)v13 + 134) )
    {
      free(*((void **)v13 + 134));
      *((_DWORD *)v13 + 134) = 0;
    }
    if ( *((_DWORD *)v13 + 133) )
    {
      free(*((void **)v13 + 133));
      *((_DWORD *)v13 + 133) = 0;
    }
    if ( *((_DWORD *)v13 + 136) )
      rf_wave_mmio_close_handle_pointer((HMMIO *)v13 + 136);
    if ( *((_DWORD *)v13 + 131) )
    {
      v8 = (*(int (__stdcall **)(_DWORD))(**((_DWORD **)v13 + 131) + 72))(*((_DWORD *)v13 + 131));
      if ( v8 < 0 )
      {
        v1 = rf_dsound_hresult_name_string(v8);
        sprintf(Buffer, "s->pdsb->Stop() failed with return value %s\n", v1);
      }
      if ( *((_DWORD *)v13 + 132) )
      {
        v7 = 0;
        while ( 1 )
        {
          v2 = v7++;
          if ( v2 >= 10 )
            break;
          v9 = (*(int (__stdcall **)(_DWORD))(**((_DWORD **)v13 + 132) + 8))(*((_DWORD *)v13 + 132));
          if ( v9 >= 0 )
            break;
          v3 = rf_dsound_hresult_name_string(v9);
          sprintf(Buffer, "s->pds3db->Release() failed with return value %s\n", v3);
        }
        *((_DWORD *)v13 + 132) = 0;
      }
      if ( *((_DWORD *)v13 + 131) )
      {
        v6 = 0;
        while ( 1 )
        {
          v4 = v6++;
          if ( v4 >= 10 )
            break;
          v10 = (*(int (__stdcall **)(_DWORD))(**((_DWORD **)v13 + 131) + 8))(*((_DWORD *)v13 + 131));
          if ( v10 >= 0 )
            break;
          v5 = rf_dsound_hresult_name_string(v10);
          sprintf(Buffer, "s->pdsb->Release() failed with return value %s\n", v5);
        }
        *((_DWORD *)v13 + 131) = 0;
      }
    }
    *v13 = 0;
    v13[256] = 0;
    *((_DWORD *)v13 + 129) = -1;
  }
}

