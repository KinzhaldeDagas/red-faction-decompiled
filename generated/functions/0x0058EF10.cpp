// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058EF10 rf_sound_initialize_sample_record_fields
// UNREALRED VERIFIED [dsound-playback-20261028]: Loops4096 fixed592-byte records at0x1951808. Sets static DS buffer+524,3D pointer+528,output WAVEFORMAT+536,HMMIO+544 toNULL; namebyte0 andfilepathbyte256 empty;hash+516=-1,referencecount+588=0,fileoffset+512=0. Returns4096. Does NOT clear source WAVEFORMAT+532,ACM handle+540,metadata+520,chunk structures or global registrycount0x1BA1818. Does not release prior owned resources before overwriting pointers.
int rf_sound_initialize_sample_record_fields()
{
  int result; // eax
  char *v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 4096; ++i )
  {
    v1 = (char *)&unk_1951808 + 592 * i;
    *((_DWORD *)v1 + 131) = 0;
    *((_DWORD *)v1 + 132) = 0;
    *((_DWORD *)v1 + 134) = 0;
    *((_DWORD *)v1 + 136) = 0;
    *v1 = 0;
    v1[256] = 0;
    *((_DWORD *)v1 + 129) = -1;
    *((_DWORD *)v1 + 147) = 0;
    *((_DWORD *)v1 + 128) = 0;
    result = i + 1;
  }
  return result;
}

