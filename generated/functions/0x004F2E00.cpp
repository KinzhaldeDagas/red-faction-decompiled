// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2E00 rf_build_version_initialize
// UNREALRED VERIFIED [save-validation-20261028]: Opens build.ver in text-read mode; if open, reads4 bytes into0x663114 without checking short read, otherwise sets that word to-1. Formats Version %d.%02d at0x88E788 from0x663118 and0x66311C. Returns sprintf result; getcwd result is unused in this body.
int rf_build_version_initialize()
{
  char DstBuf[256]; // [esp+0h] [ebp-108h] BYREF
  FILE *Stream; // [esp+104h] [ebp-4h]

  Stream = fopen("build.ver", "r");
  _getcwd(DstBuf, 256);
  if ( Stream )
  {
    fread(&dword_663114, 4u, 1u, Stream);
    fclose(Stream);
  }
  else
  {
    dword_663114 = -1;
  }
  return sprintf(unk_88E788, "Version %d.%02d", dword_663118, dword_66311C);
}

