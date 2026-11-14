// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561CD0 rf_model_handle_load_character
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX tagged handle plus filename,cacheFlag,createInstance byte,unusedDWORD; RET16. Sets tag0=2, copies filename includingNUL to+12 with NO length/capacity check, loads character cache and stores definition8. Load failure returns byte0 after tag/name/definition already changed, leaving prior instance4 untouched. Success optionally allocates0x1D5Cbyte character instance and initializes it, or stores instance4=0. Returns1 even if allocation branch produces instanceNULL. Does not release previous handle resources or roll back failed state; fourth stack arg unused.
char __thiscall rf_model_handle_load_character(int *this, char *String1, char a3, char a4, int a5)
{
  char v5; // cl
  int v7; // [esp+4h] [ebp-2Ch]
  _DWORD *v8; // [esp+10h] [ebp-20h]
  char *v9; // [esp+14h] [ebp-1Ch]
  void *v11; // [esp+1Ch] [ebp-14h]

  *this = 2;
  v9 = String1;
  v8 = this + 3;
  do
  {
    v5 = *v9;
    *(_BYTE *)v8 = *v9++;
    v8 = (_DWORD *)((char *)v8 + 1);
  }
  while ( v5 );
  *(this + 2) = rf_character_cache_get_or_load(String1, a3);
  if ( !*(this + 2) )
    return 0;
  if ( a4 )
  {
    v11 = operator new(0x1D5Cu);
    if ( v11 )
      v7 = rf_character_instance_initialize((int)v11, *(this + 2));
    else
      v7 = 0;
    *(this + 1) = v7;
  }
  else
  {
    *(this + 1) = 0;
  }
  return 1;
}

