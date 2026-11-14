// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00587920 rf_character_instance_consume_named_trigger
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Negative selected record index+7496 returnsfalse. Otherwise resolves animation index from action record+4820+12*index, then clip through base-character pointer+7504/handle list+3932. Checks exactly two20-byte trigger records, names at clip+64+20*i, using case-sensitive exact string equality. First matching name returnsfalse if instance flag byte+7492+i is0; otherwise clears that byte and returnstrue. No fallthrough to duplicate later trigger after first name match, no index/NULL validation.
char __thiscall rf_character_instance_consume_named_trigger(int *this, const char *a2)
{
  int i; // [esp+18h] [ebp-8h]
  int v4; // [esp+1Ch] [ebp-4h]

  if ( *(this + 1874) < 0 )
    return 0;
  v4 = *(_DWORD *)(*(this + 1876) + 4 * *(this + 3 * *(this + 1874) + 1205) + 3932);
  for ( i = 0; ; ++i )
  {
    if ( i >= 2 )
      return 0;
    if ( *(_BYTE *)(v4 + 20 * i + 64) && !strcmp(a2, (const char *)(v4 + 20 * i + 64)) )
      break;
  }
  if ( !*((_BYTE *)this + i + 7492) )
    return 0;
  *((_BYTE *)this + i + 7492) = 0;
  return 1;
}

