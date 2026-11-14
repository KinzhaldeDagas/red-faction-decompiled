// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005932D0 rf_vfile_flush_stdio_preserve_prior_status
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall open VFile. Derives slot from signed index+272 without validation. If FILE pointer at slot+32812 nonnull, calls fflush even when prior status nonzero; nonzero fflush result sets status at slot+12=-99999 ONLY if old status0. Returns current status. No fflush for VPP slot with NULL FILE, no reset of prior error, position/counter updates or extra encoding/cache flushing here.
int __thiscall rf_vfile_flush_stdio_preserve_prior_status(_DWORD *this)
{
  int *v2; // [esp+4h] [ebp-4h]

  v2 = &unk_189CEB0[8208 * *(this + 68)];
  if ( v2[8203] && fflush((FILE *)v2[8203]) && !v2[3] )
    v2[3] = -99999;
  return v2[3];
}

