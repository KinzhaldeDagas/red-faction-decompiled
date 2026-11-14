// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486C80 rf_material_custom_sound_set_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall212-byte set constructor, returns receiver. Constructs empty RFString at+204, initializes sound ids DWORD[10][4] at0..159 to -1, ten signed row counts at160..199 to0, sets
// all/default BYTE+200=0. Leaves padding201..203 untouched. No per-material resource allocation or sound loading.
int __thiscall rf_material_custom_sound_set_construct(int this)
{
  int j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  rf_string_construct_empty((_DWORD *)(this + 204));
  for ( i = 0; i < 10; ++i )
  {
    for ( j = 0; j < 4; ++j )
      *(_DWORD *)(this + 16 * i + 4 * j) = -1;
    *(_DWORD *)(this + 4 * i + 160) = 0;
  }
  *(_BYTE *)(this + 200) = 0;
  return this;
}

