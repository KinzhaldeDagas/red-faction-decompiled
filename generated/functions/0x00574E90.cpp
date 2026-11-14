// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574E90 rf_bitmap_load_with_optional_mipmap_generation
// UNREALRED VERIFIED [bitmap-loading-20261028]: Arguments name, source context, allow-auto-mips byte. Saves global0x189744C; if byte0 temporarily clears it, calls0x574EE0, then restores it. Nonzero byte leaves global unchanged; does not force it on. Returns loader handle. No exception-safe restoration or independent load logic.
int __cdecl rf_bitmap_load_with_optional_mipmap_generation(char *String2, void *a2, char a3)
{
  int v4; // [esp+0h] [ebp-8h]
  char v5; // [esp+7h] [ebp-1h]

  v5 = unk_189744C;
  if ( !a3 )
    unk_189744C = 0;
  v4 = rf_bitmap_load_or_register_metadata_and_slots(String2, a2);
  if ( !a3 )
    unk_189744C = v5;
  return v4;
}

