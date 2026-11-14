// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C59C0 rf_clip_plane_record_from_normal_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Thiscall initializer for the same 28-byte record. Writes outcode byte +0, constructs plane from a normal vector and point passed BY VALUE (normal XYZ then point XYZ), copies plane to +4, and fills support-corner selectors +20/+24. Plane scalar is -dot(normal,point). RET 0x1C confirms outcode stack slot plus 24 vector bytes. Older char/int coordinate types were false inference; revised prototype uses six float scalars. Does not normalize the supplied normal or clear record padding.
void __thiscall rf_clip_plane_record_from_normal_point(
        void *this,
        unsigned __int8 a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8)
{
  float *v8; // eax
  _BYTE v10[16]; // [esp+4h] [ebp-10h] BYREF

  *(_BYTE *)this = a2;
  v8 = (float *)rf_plane_construct_from_normal_point(v10, &a3, (int)&a6);
  rf_plane_copy((float *)this + 1, v8);
  rf_plane_select_aabb_support_corners((float *)this + 1, (_DWORD *)this + 5, (_DWORD *)this + 6);
}

