// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561860 rf_text_log_buffer_append_cstr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Computes strlen(input). If used+len+1>=capacity (equality REJECTED), clears record, strcpy-copies verified marker"Buffer overrun!", sets used=strlen(marker), returns that length bits, and discards input. External buffers smaller than marker are not protected. Otherwise adds incoming LF count to lineCount; if maxLines>0 and total exceeds it, computes drop count but scans ONLY old text for those LF. If not enough old LF, scan reaches old used then shifts from buffer+used+1, past old terminator. Manual forward NUL copy shifts retained suffix, subtracts j+1 from used,forces lineCount=maxLines, then strcat input and adds its length. No expansion, null/overflow/alias checks. Successful EAX record pointer,
// failure EAX length; mixed incidental return.
char *__thiscall rf_text_log_buffer_append_cstr(const char **this, const char *a2)
{
  char v2; // cl
  char *result; // eax
  char v4; // cl
  char *v5; // [esp+20h] [ebp-68h]
  char *v6; // [esp+24h] [ebp-64h]
  char *v7; // [esp+5Ch] [ebp-2Ch]
  char *v8; // [esp+60h] [ebp-28h]
  int v10; // [esp+7Ch] [ebp-Ch]
  signed int i; // [esp+80h] [ebp-8h]
  int j; // [esp+80h] [ebp-8h]
  signed int v13; // [esp+84h] [ebp-4h]

  v13 = strlen(a2);
  if ( (int)&(*(this + 3))[v13 + 1] >= (int)*(this + 2) )
  {
    rf_text_log_buffer_clear(this);
    v6 = off_663E98;
    v5 = (char *)*this;
    do
    {
      v4 = *v6;
      *v5++ = *v6++;
    }
    while ( v4 );
    result = (char *)strlen(*this);
    *(this + 3) = result;
  }
  else
  {
    for ( i = 0; i < v13; ++i )
    {
      if ( a2[i] == 10 )
        ++*(this + 5);
    }
    if ( (int)*(this + 4) > 0 && (int)*(this + 5) > (int)*(this + 4) )
    {
      v10 = *(this + 5) - *(this + 4);
      for ( j = 0; j < (int)*(this + 3); ++j )
      {
        if ( (*this)[j] == 10 && !--v10 )
          break;
      }
      v8 = (char *)&(*this)[j + 1];
      v7 = (char *)*this;
      do
      {
        v2 = *v8;
        *v7++ = *v8++;
      }
      while ( v2 );
      *(this + 3) += -j - 1;
      *(this + 5) = *(this + 4);
      strlen(*this);
    }
    strcat((char *)*this, a2);
    *(this + 3) += v13;
    return (char *)this;
  }
  return result;
}

