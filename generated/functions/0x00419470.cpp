// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419470 rf_geomod_debris_bounce_event_resolve
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Thiscall config, unsigned material index, out-row DWORD pointer,out-count DWORD pointer; RET12. Byte config+200 selects shared first row/config and count+160 for every index, returning count bits in EAX. Otherwise index>9 unsigned yields row0/count0; valid index yields row=config+16*index and count=DWORD(config+160+4*index). Nonshared paths return out-count pointer bits. Ten 16-byte rows with separate counts; no count-to-four clamp, copying, random selection or null validation.
_DWORD *__thiscall rf_geomod_debris_bounce_event_resolve(int this, unsigned int a2, _DWORD *a3, _DWORD *a4)
{
  _DWORD *result; // eax

  if ( *(_BYTE *)(this + 200) )
  {
    *a3 = this;
    result = *(_DWORD **)(this + 160);
    *a4 = result;
  }
  else if ( a2 > 9 )
  {
    *a3 = 0;
    *a4 = 0;
    return a4;
  }
  else
  {
    *a3 = this + 16 * a2;
    *a4 = *(_DWORD *)(this + 4 * a2 + 160);
    return a4;
  }
  return result;
}

