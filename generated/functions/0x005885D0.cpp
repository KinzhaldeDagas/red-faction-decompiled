// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005885D0 rf_animation_trigger_append
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Clip selected from character handle list+3932+4*index. Chooses first of exactly two20-byte trigger records with empty first name byte (clip+64+20*i), copies input name without length bound, stores tick int32 at+80+20*i using float expression frame/30*30*160 then truncation. Full pair silently leaves data unchanged; return register varies by branch. No animation index/name size/finite or tick-range validation; authored name storage before tick is16 bytes.
int __thiscall rf_animation_trigger_append(_DWORD *this, int a2, char *a3, float a4)
{
  int result; // eax
  char v5; // al
  _BYTE *v6; // [esp+8h] [ebp-14h]
  int v8; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  result = a2;
  v8 = *(this + a2 + 983);
  for ( i = 0; i < 2; ++i )
  {
    result = *(char *)(v8 + 20 * i + 64);
    if ( !*(_BYTE *)(v8 + 20 * i + 64) )
      break;
    result = i + 1;
  }
  if ( i != 2 )
  {
    v6 = (_BYTE *)(v8 + 20 * i + 64);
    do
    {
      v5 = *a3;
      *v6++ = *a3++;
    }
    while ( v5 );
    result = (int)(a4 / 30.0 * 30.0 * 160.0);
    *(_DWORD *)(v8 + 20 * i + 80) = result;
  }
  return result;
}

