// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561BC0 rf_model_render_options_reset_defaults
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Writes DWORD0=0,4=-1,8=255,16=0,float20=-1,DWORD28=0,32=-1,36=-1,then identity3x3 at44..79. Leaves color fields12..15,24..27,40..43 untouched. Returns identity helper receiver=record+44, not necessarily record base. No allocation or resource release.
float *__thiscall rf_model_render_options_reset_defaults(void *this)
{
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 1) = -1;
  *((_DWORD *)this + 2) = 255;
  *((_DWORD *)this + 4) = 0;
  *((float *)this + 5) = -1.0;
  *((_DWORD *)this + 7) = 0;
  *((_DWORD *)this + 8) = -1;
  *((_DWORD *)this + 9) = -1;
  return rf_identity_orientation_matrix((float *)this + 11);
}

