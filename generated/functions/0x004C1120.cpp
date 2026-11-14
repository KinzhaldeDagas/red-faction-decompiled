// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1120 rf_bolt_emitter_refresh_attachment
// UNREALRED VERIFIED [world-uid-ownership]: Resolves the emitter's saved attachment index, copies that record's full object UID into emitter +0x0C, and rebuilds derived endpoint state.
_DWORD *__thiscall rf_bolt_emitter_refresh_attachment(int *this)
{
  _DWORD *result; // eax

  result = (_DWORD *)rf_object_find_by_saved_identifier(*(this + 2));
  if ( result )
  {
    *(this + 3) = result[11];
    return rf_bolt_emitter_refresh_cached_room(this);
  }
  return result;
}

