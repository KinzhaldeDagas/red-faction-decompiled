// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1740 rf_sound_file_probe
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Constructs native virtual file, resolves/opens filename, destroys the temporary virtual file and returns resolve/open success. Does not decode sound PCM. Host registration existence probing can use the same-source current VFS location resolver with before/after epoch guards; unsupported host provider is not native missing-file failure.
char __cdecl rf_sound_file_probe(char *String2)
{
  char v2; // [esp+7h] [ebp-12Dh]
  int self[71]; // [esp+8h] [ebp-12Ch] BYREF
  int v4; // [esp+130h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v4 = 0;
  v2 = rf_vfile_resolve_open_source((int)self, String2, (int)byte_98967F);
  v4 = -1;
  rf_vfile_destruct_close_if_open(self);
  return v2;
}

