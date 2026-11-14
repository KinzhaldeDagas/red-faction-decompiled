// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005993A0 rf_network_statistics_add_bucket_value
// UNREALRED VERIFIED [system-progress-20261028]: Arguments signed amount and3 boolean selectors(group,direction,category). Selected30-DWORD array: (000)0x1BCA398,(001)0x1C0C378,(010)0x1BCA320,(011)0x1BDB1E8,(100)0x1BDB260,(101)0x1BDB358,(110)0x1BDB2E0,(111)0x1C0C300, where tuple is selector arguments in order after amount. Adds amount at index0x1BDB2D8 when signed index<30,else29. No lower bound,overflow,locking or time advancement here. Does not return accumulated statistic reliably; EAX differs by branch. Poller passes packet bytes with(0,0,type==1) and fixed30 with(1,0,type==1).
int *__cdecl rf_network_statistics_add_bucket_value(int a1, int a2, int a3, int a4)
{
  int *result; // eax
  int *v5; // [esp+0h] [ebp-20h]
  int *v6; // [esp+4h] [ebp-1Ch]
  int *v7; // [esp+8h] [ebp-18h]
  int *v8; // [esp+Ch] [ebp-14h]
  int *v9; // [esp+10h] [ebp-10h]
  int *v10; // [esp+14h] [ebp-Ch]
  int *v11; // [esp+18h] [ebp-8h]

  if ( a2 )
  {
    if ( a3 )
    {
      if ( a4 )
        v11 = dword_1C0C300;
      else
        v11 = dword_1BDB2E0;
      v10 = v11;
    }
    else
    {
      if ( a4 )
        v9 = dword_1BDB358;
      else
        v9 = dword_1BDB260;
      v10 = v9;
    }
    v8 = v10;
  }
  else
  {
    if ( a3 )
    {
      if ( a4 )
        v7 = dword_1BDB1E8;
      else
        v7 = dword_1BCA320;
      v6 = v7;
    }
    else
    {
      if ( a4 )
        v5 = dword_1C0C378;
      else
        v5 = dword_1BCA398;
      v6 = v5;
    }
    v8 = v6;
  }
  if ( dword_1BDB2D8 < 30 )
  {
    result = (int *)(a1 + v8[dword_1BDB2D8]);
    v8[dword_1BDB2D8] = (int)result;
  }
  else
  {
    v8[29] += a1;
    return v8;
  }
  return result;
}

