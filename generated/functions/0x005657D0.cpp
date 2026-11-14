// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005657D0 rf_material200_clone_for_model_handle
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl(handle,count,destination,source),200byte stride. Selective copy, not raw200byte memcpy:DWORD0,flags4 OR1,byte8,DWORD9,two52byte texture layers(start16/68:id,name NUL-copy,fields56/60/64 relative to layer0),DWORD120,floats132/136/140,name144 NUL-copy,DWORD180. No string length bound. For source positive counts at124,184,192, tag3 allocates/copies ALL float entries into pointers128,188,196. Other tags allocate one float and keep ONLY first entry/count1, freezing later samples. Nonpositive arrays retain initialized destination state. Flags&1 makes arrays destination-owned for5C94A0. No preexisting-destination array cleanup, alias or null guard.
void __cdecl rf_material200_clone_for_model_handle(_DWORD *a1, int a2, int a3, int a4)
{
  char v4; // dl
  char v5; // dl
  _BYTE *v6; // [esp+Ch] [ebp-44h]
  char *v7; // [esp+10h] [ebp-40h]
  _BYTE *v8; // [esp+1Ch] [ebp-34h]
  char *v9; // [esp+20h] [ebp-30h]
  int v10; // [esp+3Ch] [ebp-14h]
  int v11; // [esp+40h] [ebp-10h]
  int v12; // [esp+44h] [ebp-Ch]
  int j; // [esp+48h] [ebp-8h]
  int k; // [esp+48h] [ebp-8h]
  int m; // [esp+48h] [ebp-8h]
  int n; // [esp+48h] [ebp-8h]
  int i; // [esp+4Ch] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    *(_DWORD *)(a3 + 200 * i) = *(_DWORD *)(a4 + 200 * i);
    *(_DWORD *)(a3 + 200 * i + 4) = *(_DWORD *)(a4 + 200 * i + 4) | 1;
    *(_BYTE *)(a3 + 200 * i + 8) = *(_BYTE *)(a4 + 200 * i + 8);
    *(_DWORD *)(a3 + 200 * i + 9) = *(_DWORD *)(a4 + 200 * i + 9);
    for ( j = 0; j < 2; ++j )
    {
      *(_DWORD *)(a3 + 200 * i + 52 * j + 16) = *(_DWORD *)(a4 + 200 * i + 52 * j + 16);
      if ( a4 + 200 * i + 52 * j == -20 )
      {
        *(_BYTE *)(a3 + 200 * i + 52 * j + 20) = 0;
      }
      else
      {
        v9 = (char *)(a4 + 200 * i + 52 * j + 20);
        v8 = (_BYTE *)(a3 + 200 * i + 52 * j + 20);
        do
        {
          v4 = *v9;
          *v8++ = *v9++;
        }
        while ( v4 );
      }
      *(_DWORD *)(a3 + 200 * i + 52 * j + 56) = *(_DWORD *)(a4 + 200 * i + 52 * j + 56);
      *(float *)(a3 + 200 * i + 52 * j + 60) = *(float *)(a4 + 200 * i + 52 * j + 60);
      *(_DWORD *)(a3 + 200 * i + 52 * j + 64) = *(_DWORD *)(a4 + 200 * i + 52 * j + 64);
    }
    *(_DWORD *)(a3 + 200 * i + 120) = *(_DWORD *)(a4 + 200 * i + 120);
    *(float *)(a3 + 200 * i + 132) = *(float *)(a4 + 200 * i + 132);
    *(float *)(a3 + 200 * i + 136) = *(float *)(a4 + 200 * i + 136);
    *(float *)(a3 + 200 * i + 140) = *(float *)(a4 + 200 * i + 140);
    v7 = (char *)(a4 + 200 * i + 144);
    v6 = (_BYTE *)(a3 + 200 * i + 144);
    do
    {
      v5 = *v7;
      *v6++ = *v7++;
    }
    while ( v5 );
    *(_DWORD *)(a3 + 200 * i + 180) = *(_DWORD *)(a4 + 200 * i + 180);
    if ( *a1 == 3 )
    {
      v10 = *(_DWORD *)(a4 + 200 * i + 124);
      if ( v10 > 0 )
      {
        *(_DWORD *)(a3 + 200 * i + 128) = operator new(4 * v10);
        *(_DWORD *)(a3 + 200 * i + 124) = v10;
        for ( k = 0; k < v10; ++k )
          *(float *)(*(_DWORD *)(a3 + 200 * i + 128) + 4 * k) = *(float *)(*(_DWORD *)(a4 + 200 * i + 128) + 4 * k);
      }
      v12 = *(_DWORD *)(a4 + 200 * i + 184);
      if ( v12 > 0 )
      {
        *(_DWORD *)(a3 + 200 * i + 188) = operator new(4 * v12);
        *(_DWORD *)(a3 + 200 * i + 184) = v12;
        for ( m = 0; m < v12; ++m )
          *(float *)(*(_DWORD *)(a3 + 200 * i + 188) + 4 * m) = *(float *)(*(_DWORD *)(a4 + 200 * i + 188) + 4 * m);
      }
      v11 = *(_DWORD *)(a4 + 200 * i + 192);
      if ( v11 > 0 )
      {
        *(_DWORD *)(a3 + 200 * i + 196) = operator new(4 * v11);
        *(_DWORD *)(a3 + 200 * i + 192) = v11;
        for ( n = 0; n < v11; ++n )
          *(float *)(*(_DWORD *)(a3 + 200 * i + 196) + 4 * n) = *(float *)(*(_DWORD *)(a4 + 200 * i + 196) + 4 * n);
      }
    }
    else
    {
      if ( *(int *)(a4 + 200 * i + 124) > 0 )
      {
        *(_DWORD *)(a3 + 200 * i + 128) = operator new(4u);
        *(_DWORD *)(a3 + 200 * i + 124) = 1;
        **(float **)(a3 + 200 * i + 128) = **(float **)(a4 + 200 * i + 128);
      }
      if ( *(int *)(a4 + 200 * i + 184) > 0 )
      {
        *(_DWORD *)(a3 + 200 * i + 188) = operator new(4u);
        *(_DWORD *)(a3 + 200 * i + 184) = 1;
        **(float **)(a3 + 200 * i + 188) = **(float **)(a4 + 200 * i + 188);
      }
      if ( *(int *)(a4 + 200 * i + 192) > 0 )
      {
        *(_DWORD *)(a3 + 200 * i + 196) = operator new(4u);
        *(_DWORD *)(a3 + 200 * i + 192) = 1;
        **(float **)(a3 + 200 * i + 196) = **(float **)(a4 + 200 * i + 196);
      }
    }
  }
}

