// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5960 rf_clip_plane_record_from_three_points
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Thiscall initializer for a 28-byte clipping-plane record. Writes the supplied outcode byte at +0, constructs a four-float plane from THREE vectors passed BY VALUE in consecutive 12-byte stack regions, copies plane to +4, and stores minimum/maximum AABB support-corner selectors at +20/+24. Padding bytes +1..3 are untouched. RET 0x28 confirms 4-byte outcode slot plus 36 vector bytes. Older types splitting vector coordinates into chars/ints were false ABI inference; revised prototype exposes nine float scalars without adding a local structure type. Frustum/aperture callers use outcodes 4,8,16,32.
void __thiscall rf_clip_plane_record_from_three_points(
        void *this,
        unsigned __int8 a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11)
{
  float *v11; // eax
  _BYTE v13[16]; // [esp+4h] [ebp-10h] BYREF

  *(_BYTE *)this = a2;
  v11 = (float *)rf_plane_construct_from_three_world_points(v13, &a3, &a6, &a9);
  rf_plane_copy((float *)this + 1, v11);
  rf_plane_select_aabb_support_corners((float *)this + 1, (_DWORD *)this + 5, (_DWORD *)this + 6);
}

