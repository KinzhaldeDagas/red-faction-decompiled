// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577FD0 rf_bitmap_get_source_metadata_byte93
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Returns unsigned byte+93 from source bitmap record. Ordinary subtype2 backs up to parent by byte+67 records. Animated path indexes source through raw stripped handle, WITHOUT modulo, like 0x577F50. No semantic label for byte93 established here; no frame resolution or handle validation.
// UNREALRED VERIFIED SEMANTIC QUALIFICATION [combat-original-physics-20261112]: Existing byte93 label remains structurally correct; its material-cache role is proved by4867F0 caller: exact handle-1 returns Default0, otherwise this getter supplies source cached material id; any nonzero byte is returned verbatim without0..9 validation. Zero invokes source-name first-underscore material prefix resolution and578050 stores the low byte back.574EE0 explicitly initializes parent metadata93=0 on bitmap registration. Default0 is also unresolved sentinel and can be recomputed on later calls. Source record/animation resolution stays as documented; this does not establish a live host bitmap owner or native face handle.
int __cdecl rf_bitmap_get_source_metadata_byte93(unsigned int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  unsigned int v3; // [esp+4h] [ebp-4h]

  v3 = rf_bitmap_handle_to_slot_index(a1);
  if ( (a1 & 0x40000000) != 0 )
    return *(unsigned __int8 *)(dword_1897344 + 108 * unk_187CD40[9 * (a1 & 0xBFFFFFFF)] + 93);
  v2 = dword_1897344 + 108 * v3;
  if ( *(_DWORD *)(v2 + 56) == 2 )
    v2 -= 108 * *(unsigned __int8 *)(v2 + 67);
  return *(unsigned __int8 *)(v2 + 93);
}

