// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A66E0 rf_text_entry_buffered_set_text
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall buffered entry,C string. Measures strlen manually; length<255 copies source including NUL to embedded buffer+60 (max254 source characters). Longer input stores literal text too long for pc version instead of truncating. No null guard,allocation or dirty BYTE+4 update. Return low byte is incidental copy/length-loop value,not success or length.
char __thiscall rf_text_entry_buffered_set_text(char *this, char *a2)
{
  char result; // al
  char v3; // dl
  char *v4; // [esp+10h] [ebp-1Ch]
  char *v5; // [esp+14h] [ebp-18h]
  char *v7; // [esp+24h] [ebp-8h]

  v7 = a2;
  do
    result = *v7;
  while ( *v7++ );
  if ( (unsigned int)(v7 - (a2 + 1)) < 0xFF )
  {
    v5 = a2;
    v4 = this + 60;
    do
    {
      v3 = *v5;
      *v4 = *v5;
      result = (_BYTE)v5++ + 1;
      ++v4;
    }
    while ( v3 );
  }
  else
  {
    strcpy(this + 60, "text too long for pc version");
  }
  return result;
}

