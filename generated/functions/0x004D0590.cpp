// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D0590 rf_geometry_segment_mask_to_query_flags
// UNREALRED VERIFIED [mission-visibility-20261020] Public segment mask -> internal collision query:1->0x1,2->0x20,4->0x40,8->0x80,16->0x100,32->0x400,64->0x1000,128->0x2000. UnHide mask3 becomes0x21; radial-damage mask5 becomes0x41. These cannot share face admission blindly.
// UNREALRED VERIFIED [mission-unhide-20261020] UnHide public mask3 maps to internal0x21. Live adapter filters face flags and signed portal markers using this query, independently of radial-damage public mask5/internal0x41.
int __cdecl rf_geometry_segment_mask_to_query_flags(char a1)
{
  return ((a1 & 1) != 0)
       | ((a1 & 2) != 0 ? 0x20 : 0)
       | ((a1 & 4) != 0 ? 0x40 : 0)
       | ((a1 & 8) != 0 ? 0x80 : 0)
       | ((a1 & 0x10) != 0 ? 0x100 : 0)
       | ((a1 & 0x20) != 0 ? 0x400 : 0)
       | ((a1 & 0x40) != 0 ? 0x1000 : 0)
       | (a1 < 0 ? 0x2000 : 0);
}

