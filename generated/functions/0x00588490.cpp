// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588490 rf_character_read_bone_chunk_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Constructs a local stream-adapter reader via57D330, binds supplied virtual stream via57D3E0, and forwards it to bone import5882A0. Returns importer byte boolean. Does not itself seek chunk end or allocate bone array.
char __thiscall rf_character_read_bone_chunk_adapter(int *this, int a2)
{
  void *v4[23]; // [esp+4h] [ebp-60h] BYREF

  rf_stream_adapter_construct_unbound(v4);
  rf_stream_adapter_bind_vfile(v4, a2);
  return rf_character_import_primary_bones(this, v4);
}

