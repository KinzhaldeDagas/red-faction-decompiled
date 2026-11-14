// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557F00 rf_face_metadata_set_portal_index_plus_two
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): ECX metadata40 pointer plus signed index. Writes metadata WORD12(Face52) =0 if index<=-1, otherwise low16(index+2). No upper-bound/overflow checks; positive large indices truncate/wrap, potentially producing0/1 reserved values. EAX mixed metadata pointer or encoded integer, incidental.
_WORD *__thiscall rf_face_metadata_set_portal_index_plus_two(_WORD *this, int a2)
{
  if ( a2 <= -1 )
  {
    *(this + 6) = 0;
    return this;
  }
  else
  {
    *(this + 6) = a2 + 2;
    return (_WORD *)(a2 + 2);
  }
}

