// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5820 sub_4A5820
// UNREALRED VERIFIED [lan-match-flow-20261028] Server next-level packet 22 includes the NUL-terminated next-level string at 0x6FC31C followed by dword 0x6FC3A8. When that dword is zero it is lazily computed using rf_vfile_raw_crc32_or_zero; this is a raw file CRC32, not a random seed. Client receiver 0x4A59D0 clears its pending-end network flag 0x20 and requests panel 5 when flagged. No Unreal/native packet wire interoperability is established by this observation.
int sub_4A5820()
{
  const char *v0; // eax
  char *v1; // eax
  unsigned __int16 v3; // [esp+0h] [ebp-228h]
  unsigned __int8 Src[516]; // [esp+20h] [ebp-208h] BYREF

  Src[0] = 22;
  v3 = strlen(rf_string_object_c_str_or_empty(unk_6FC31C));
  v0 = rf_string_object_c_str_or_empty(unk_6FC31C);
  memcpy(&Src[3], v0, v3);
  Src[(unsigned __int16)(v3 + 3)] = 0;
  if ( !dword_6FC3A8 )
  {
    v1 = (char *)rf_string_object_c_str_or_empty(unk_6FC31C);
    dword_6FC3A8 = rf_vfile_raw_crc32_or_zero(v1);
  }
  *(_DWORD *)&Src[(unsigned __int16)(v3 + 4)] = dword_6FC3A8;
  *(_WORD *)&Src[1] = v3 + 5;
  return rf_server_broadcast_packet(Src, (unsigned __int16)(v3 + 8), 0);
}

